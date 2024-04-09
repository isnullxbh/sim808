/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.03.2024
 */

#include <iostream>
#include <future>
#include <chrono>
#include <format>
#include <functional>

#include <asio/io_context.hpp>

#include <Sim808/ShortMessages/Service.hpp>
#include <Sim808/DefaultCommandGateway.hpp>

#include <Sim808/CommandLineTool/CommandDispatcher.hpp>
#include <Sim808/CommandLineTool/Utility.hpp>

using namespace std::chrono_literals;
using Sim808::CommandGateway;
using Sim808::CommandLineTool::CommandDispatcher;
using ShortMessageService = Sim808::ShortMessages::Service;

/// Handle the command to get message list.
/// @param   service Short message service.
/// @param   command Command.
/// @ingroup sim-clt
/// @since   0.1.0
void handleListShortMessages(ShortMessageService& service, std::string_view command);

/// Handle the command to send message.
/// @param   service Short message service.
/// @param   command Command.
/// @ingroup sim-clt
/// @since   0.1.0
void handleSendMessage(ShortMessageService& service, std::string_view command);

/// Handle the command to delete message(s).
/// @param   service Short message service.
/// @param   command Command.
/// @ingroup sim-clt
/// @since   0.1.0
void handleDeleteMessages(ShortMessageService& service, std::string_view command);

auto main(int argc, char** argv) -> int
{
    if (argc < 2)
    {
        std::cerr << "Serial interface is not specified" << std::endl;
        return EXIT_FAILURE;
    }

    asio::io_context ioc {};

    auto gateway = std::make_shared<Sim808::DefaultCommandGateway>(std::ref(ioc), argv[1]);
    auto ioc_ctl = std::async(std::launch::async, [&]{ ioc.run(); });

    std::this_thread::sleep_for(1s);
    gateway->send("ATE0\r");

    ShortMessageService shortMessageService { gateway };

    CommandDispatcher dispatcher;
    dispatcher.registerHandler("sms:list", std::bind_front(handleListShortMessages, std::ref(shortMessageService)));
    dispatcher.registerHandler("sms:send", std::bind_front(handleSendMessage, std::ref(shortMessageService)));
    dispatcher.registerHandler("sms:delete", std::bind_front(handleDeleteMessages, std::ref(shortMessageService)));

    std::string command;
    while (true)
    {
        std::cout << "> ";
        std::cin.clear();
        std::getline(std::cin, command);

        if (command.starts_with("quit"))
            break;

        try
        {
            dispatcher.execute(command);
        }
        catch (const std::exception& ex)
        {
            std::cerr << "An error occurred during command execution: " << ex.what() << std::endl;
        }
    }

    ioc.stop();
    ioc_ctl.wait();

    return 0;
}

void handleListShortMessages(ShortMessageService& service, std::string_view command)
{
    using Sim808::ShortMessages::MessageStorageType;

    const auto messages = service.getMessages(MessageStorageType::Unread, false);

    if (messages.empty())
    {
        std::cout << "No messages" << std::endl;
        return;
    }

    for (const auto& message : messages)
    {
        std::cout << "Message: "
                  << "index=" << message.index() << ", "
                  << "sender=" << message.senderNumber() << ", "
                  << "text=\"" << message.text() << "\""
                  << std::endl;
    }
}

void handleSendMessage(ShortMessageService& service, std::string_view command)
{
    using Sim808::CommandLineTool::Utility;

    const auto parameters = Utility::extractKeyValuePairs(command);

    if (!parameters.contains("to") || !parameters.contains("text"))
    {
        std::cerr << "The required parameters are missing" << std::endl;
        return;
    }

    const auto send_result = service.sendMessage(parameters.at("to"), parameters.at("text"));

    if (!send_result)
    {
        std::cerr << send_result.error().toString() << std::endl;
        return;
    }

    std::cout << "Message sent [index=" << send_result.value() << "]" << std::endl;
}

void handleDeleteMessages(ShortMessageService& service, std::string_view command)
{
    using Sim808::CommandLineTool::Utility;
    using Sim808::ShortMessages::DeletionRequestType;
    using Sim808::ShortMessages::MessageIndex;
    using Sim808::ResultCode;

    const auto parameters = Utility::extractKeyValuePairs(command);

    ResultCode rc;

    if (parameters.contains("index"))
    {
        MessageIndex index;

        try
        {
            index = std::stoul(std::string(parameters.at("index")));
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Wrong index format" << std::endl;
            return;
        }

        rc = service.deleteMessage(index);
    }
    else if (parameters.contains("del_type"))
    {
        DeletionRequestType type;

        const auto type_as_str = parameters.at("del_type");
        if (type_as_str == "read")
            type = DeletionRequestType::Read;
        else if (type_as_str == "unread")
            type = DeletionRequestType::Unread;
        else if (type_as_str == "sent")
            type = DeletionRequestType::Sent;
        else if (type_as_str == "unsent")
            type = DeletionRequestType::Unsent;
        else if (type_as_str == "inbox")
            type = DeletionRequestType::Received;
        else if (type_as_str == "all")
            type = DeletionRequestType::All;
        else
        {
            std::cerr << "Unknown deletion request type: \"" << type_as_str << "\"" << std::endl;
            return;
        }

        rc = service.deleteMessages(type);
    }
    else
    {
        std::cerr << "Wrong command format" << std::endl;
        return;
    }

    std::cout << rc.toString() << std::endl;
}
