/**
 * @file    MessageStorageType.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#pragma once

#include <optional>
#include <string_view>

namespace Sim808::ShortMessages
{

/// Defines message storage type.
/// @ingroup sim-sms
/// @since   0.1.0
enum class MessageStorageType
{
    Unread,     ///< A type of storage of unread messages.
    Read,       ///< A type of storage of read messages.
    Unsent,     ///< A type of storage of unsent messages.
    Sent,       ///< A type of storage of sent messages.
    Unspecified ///< A type of global message storage (i.e. storage that contains all messages).
};

/// Gets the string representation of the specified message storage type.
/// @param   type Message storage type.
/// @return  A string representation of the message storage type.
/// @ingroup sim-sms
/// @since   0.1.0
auto convertToString(MessageStorageType type) -> std::string_view;

/// Converts string to message storage type.
/// Input string may be prefixed with the "REC", "STO", e.t.c., these prefixes are not taken into account during
/// conversion.
/// @param   str A string representation of the message storage type.
/// @return  If there is a message storage type with a given string representation - message storage type, otherwise -
///          std::nullopt.
/// @ingroup sim-sms
/// @since   0.1.0
auto tryConvertToMessageStorageType(std::string_view str) -> std::optional<MessageStorageType>;

} // namespace Sim808::ShortMessages
