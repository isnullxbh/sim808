/**
 * @file    Message.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#include <Sim808/ShortMessages/Message.hpp>

#include <algorithm>
#include <charconv>
#include <vector>

#include <Sim808/Utility/StringUtility.hpp>

namespace Sim808::ShortMessages
{

static constexpr std::string_view cr_lf { "\r\n" };
static constexpr bool isQuote(char c){ return c == '"'; }

auto Message::index() const noexcept -> std::size_t
{
    return _index;
}

auto Message::storageType() const noexcept -> MessageStorageType
{
    return _storage_type;
}

auto Message::transferType() const noexcept -> MessageTransferType
{
    return _transfer_type;
}

auto Message::senderNumber() const noexcept -> const std::string&
{
    return _sender_number;
}

auto Message::sender() const noexcept -> const std::string&
{
    return _sender;
}

auto Message::timestamp() const noexcept -> const std::string&
{
    return _timestamp;
}

auto Message::text() const noexcept -> const std::string&
{
    return _text;
}

auto Message::parse(std::string_view str) -> std::optional<Message>
{
    while (str.ends_with("\r\n"))
    {
        str.remove_suffix(2);
    }

    const auto text_delimiter_pos = str.find(cr_lf);
    if (text_delimiter_pos == std::string_view::npos)
    {
        return std::nullopt;
    }

    auto parameters_data = std::string_view(str.data(), text_delimiter_pos);

    std::vector<std::string_view> parameters;
    std::string_view::size_type   search_pos { 0 };

    while (true)
    {
        const auto comma_pos = parameters_data.find(',', search_pos);

        if (comma_pos == std::string_view::npos)
        {
            break;
        }

        // Check for quotes balancing to avoid splitting the string in cases where a comma is placed inside quoted
        // substring, like as: "xxx", "yy,y".
        const auto quotes_num = std::count_if(parameters_data.cbegin(), parameters_data.cbegin() + comma_pos, isQuote);
        if (quotes_num % 2)
        {
            search_pos = comma_pos + 1;
            continue;
        }

        parameters.push_back(StringUtility::unquote(parameters_data.substr(0, comma_pos)));
        parameters_data.remove_prefix(comma_pos + 1);
        search_pos = 0;
    }

    if (!parameters_data.empty())
    {
        parameters.push_back(StringUtility::unquote(parameters_data));
    }

    if (parameters.size() < 5)
    {
        return std::nullopt;
    }

    Message message {};

    const auto parse_index_result =
        std::from_chars(parameters[0].data(), parameters[0].data() + parameters[0].size(), message._index);
    if (parse_index_result.ec != std::errc())
    {
        return std::nullopt;
    }

    const auto maybe_storage_type = tryConvertToMessageStorageType(parameters[1]);
    if (!maybe_storage_type)
    {
        return std::nullopt;
    }
    message._storage_type = maybe_storage_type.value();

    message._transfer_type = MessageTransferType::Deliver;
    message._sender_number = parameters[2];
    message._sender = parameters[3];
    message._timestamp = parameters[4];
    message._text = str.substr(text_delimiter_pos + cr_lf.size());

    return message;
}

} // namespace Sim808::ShortMessages
