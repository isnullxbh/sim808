/**
 * @file    DeletionRequestType.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    09.04.2024
 */

#include <Sim808/ShortMessages/DeletionRequestType.hpp>

#include <unordered_map>

namespace Sim808::ShortMessages
{

static const std::unordered_map<DeletionRequestType, std::string_view> mapping
    {
        { DeletionRequestType::Read,     "DEL READ"   },
        { DeletionRequestType::Unread,   "DEL UNREAD" },
        { DeletionRequestType::Sent,     "DEL SENT"   },
        { DeletionRequestType::Unsent,   "DEL UNSENT" },
        { DeletionRequestType::Received, "DEL INBOX"  },
        { DeletionRequestType::All,      "DEL ALL"    }
    };

auto convertToString(DeletionRequestType type) -> std::string_view
{
    const auto it = mapping.find(type);
    return it != mapping.cend() ? it->second : "<UNKNOWN>";
}

} // namespace Sim808::ShortMessages
