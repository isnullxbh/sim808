/**
 * @file    DeletionRequestType.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    09.04.2024
 */

#pragma once

#include <string_view>

namespace Sim808::ShortMessages
{

/// Defines the types of message deletion requests.
/// @ingroup sim-sms
/// @version 0.1.0
enum class DeletionRequestType
{
    Read     = 1, ///< Delete all read messages.
    Unread   = 2, ///< Delete all unread messages.
    Sent     = 3, ///< Delete all sent messages.
    Unsent   = 4, ///< Delete all unsent messages.
    Received = 5, ///< Delete all received messages (read and unread).
    All      = 6  ///< Delete all messages.
};

/// Gets the string representation of the specified deletion request type.
/// @param   type Deletion request type.
/// @return  A string representation of the specified type.
/// @ingroup sim-sms
/// @version 0.1.0
auto convertToString(DeletionRequestType type) -> std::string_view;

} // namespace Sim808::ShortMessages
