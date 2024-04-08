/**
 * @file    MessageStorageType.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#include <Sim808/ShortMessages/MessageStorageType.hpp>

#include <unordered_map>

namespace Sim808::ShortMessages
{

static const std::unordered_map<MessageStorageType, std::string_view> mapping
    {
        { MessageStorageType::Unread,      "UNREAD" },
        { MessageStorageType::Read,        "READ"   },
        { MessageStorageType::Unsent,      "UNSENT" },
        { MessageStorageType::Sent,        "SENT"   },
        { MessageStorageType::Unspecified, "ALL"    }
    };

static constexpr std::string_view prefixes[]
    {
        "REC ",
        "STO "
    };

auto convertToString(MessageStorageType type) -> std::string_view
{
    if (const auto it = mapping.find(type); it != mapping.cend())
    {
        return it->second;
    }

    return "<UNKNOWN>";
}

auto tryConvertToMessageStorageType(std::string_view str) -> std::optional<MessageStorageType>
{
    for (const auto& prefix : prefixes)
    {
        if (str.starts_with(prefix))
        {
            str.remove_prefix(prefix.size());
            break;
        }
    }

    for (const auto& [type, str_rep] : mapping)
    {
        if (str == str_rep)
        {
            return type;
        }
    }

    return std::nullopt;
}

} // namespace Sim808::ShortMessages

