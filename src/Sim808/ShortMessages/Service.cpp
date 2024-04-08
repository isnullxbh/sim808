/**
 * @file    Service.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.03.2024
 */

#include "Sim808/ShortMessages/Service.hpp"

#include <chrono>
#include <format>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

namespace Sim808::ShortMessages
{

static constexpr std::string_view cmgl_prefix { "+CMGL: " };

Service::Service(CommandGateway::Ptr gateway)
    : _gateway(std::move(gateway))
{}

auto Service::sendMessage(std::string_view number, std::string_view text) -> void
{
    _gateway->send("AT+CSCS=\"GSM\"\r");
    _gateway->sendData(std::format("AT+CMGS=\"{}\"\r", number));
    _gateway->waitFor(">");
    const auto response = _gateway->send(std::format("{}\032", text));
    std::cout << "Response: code=" << (int)response.code << " data=" << response.data << std::endl;
}

auto Service::getMessages(MessageStorageType type, bool update_status) -> Messages
{
    std::string store;
    switch (type)
    {
        case MessageStorageType::Unread:
        case MessageStorageType::Read:
            store = std::format("REC {}", convertToString(type));
            break;

        case MessageStorageType::Unsent:
        case MessageStorageType::Sent:
            store = std::format("STO {}", convertToString(type));
            break;

        default:
            break;
    }

    const auto command = std::format("AT+CMGL=\"{}\", {}\r", store, static_cast<int>(!update_status));
    const auto response = _gateway->send(command);

    if (response.code != ResultCode::Ok)
    {
        return {};
    }

    Messages messages;

    auto str = std::string_view(response.data);
    while (true)
    {
        const auto start_pos = str.find(cmgl_prefix);
        if (start_pos == std::string_view::npos)
        {
            break;
        }

        str.remove_prefix(start_pos + cmgl_prefix.size());

        auto end_pos = str.find("\r\n+CMGL");
        if (end_pos == std::string_view::npos)
        {
            end_pos = str.size();
        }

        if (auto maybe_message = Message::parse(str.substr(0, end_pos)))
        {
            messages.push_back(std::move(maybe_message).value());
        }
    }

    return messages;
}

} // namespace Sim808::ShortMessages