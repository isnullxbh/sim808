/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.03.2024
 */

#include <iostream>
#include <future>
#include <chrono>
#include <functional>

#include <asio/io_context.hpp>

#include <Sim808/ShortMessages/Service.hpp>
#include <Sim808/DefaultCommandGateway.hpp>

#include <Sim808/CommandLineTool/CommandDispatcher.hpp>

using namespace std::chrono_literals;
using Sim808::CommandGateway;
using Sim808::CommandLineTool::CommandDispatcher;
using ShortMessageService = Sim808::ShortMessages::Service;

void handleListShortMessages(ShortMessageService& service, std::string_view input);
void handleSendMessage(ShortMessageService& service, std::string_view input);

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

    std::string command;
    while (true)
    {
        std::cout << "> ";
        std::cin.clear();
        std::getline(std::cin, command);

        std::cout << "Done" << std::endl;

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

void handleListShortMessages(ShortMessageService& service, std::string_view input)
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

void handleSendMessage(ShortMessageService& service, std::string_view input)
{
    constexpr std::string_view to_prefix   { "to=\"" };
    constexpr std::string_view text_prefix { "text=\"" };

    const auto to_pos = input.find(to_prefix);
    if (to_pos == std::string_view::npos)
    {
        std::cerr << "Number is not specified" << std::endl;
        return;
    }

    const auto text_pos = input.find(text_prefix);
    if (text_pos == std::string_view::npos)
    {
        std::cerr << "Enter message text" << std::endl;
        return;
    }

    const auto to_end_pos = input.find('"', to_pos + to_prefix.size());
    if (to_end_pos == std::string_view::npos)
    {
        std::cerr << "Invalid syntax" << std::endl;
        return;
    }

    const auto text_end_pos = input.find('"', text_pos + text_prefix.size());
    if (text_end_pos == std::string_view::npos)
    {
        std::cerr << "Invalid syntax" << std::endl;
        return;
    }

    const auto number = input.substr(to_pos + to_prefix.size(), to_end_pos - (to_pos + to_prefix.size()));
    const auto text = input.substr(text_pos + text_prefix.size(), text_end_pos - (text_pos + text_prefix.size()));

    service.sendMessage(number, text);
}