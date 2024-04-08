/**
 * @file    Message.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#pragma once

#include <optional>
#include <string>
#include <string_view>

#include <Sim808/ShortMessages/MessageStorageType.hpp>
#include <Sim808/ShortMessages/MessageTransferType.hpp>

namespace Sim808::ShortMessages
{

/// A short message.
/// @ingroup sim-short_messages
/// @since   0.1.0
class Message
{
private:
    /// Constructor.
    Message() = default;

public:
    /// Gets message index.
    /// @return Message index.
    auto index() const noexcept -> std::size_t;

    /// Gets the type of storage in which the current message is stored.
    /// @return Message storage type.
    auto storageType() const noexcept -> MessageStorageType;

    /// Gets the message transfer type.
    /// @return Message transfer type.
    auto transferType() const noexcept -> MessageTransferType;

    /// Gets the number of a sender (originating address).
    /// @return Number in string representation.
    auto senderNumber() const noexcept -> const std::string&;

    /// Gets the alphanumerical representation of the originating address from the phonebook.
    /// @return If phonebook contains an entry for the originating address - entry name, otherwise - empty string.
    auto sender() const noexcept -> const std::string&;

    /// Gets the delivery timestamp.
    /// @return A string representation of the timestamp.
    auto timestamp() const noexcept -> const std::string&;

    /// Gets message text.
    /// @return Text.
    auto text() const noexcept -> const std::string&;

    /// Creates message from its string representation.
    /// @param  str A string representation of a message.
    /// @return If the input string contains a valid representation of a message - created message, otherwise -
    ///         std::nullopt.
    static auto parse(std::string_view str) -> std::optional<Message>;

private:
    std::size_t         _index          {}; ///< Index of the message in the associated message storage.
    MessageStorageType  _storage_type   {}; ///< Type of message storage.
    MessageTransferType _transfer_type  {}; ///< Message transfer type.
    std::string         _sender_number  {}; ///< A sender number (originating address).
    std::string         _sender         {}; ///< An alphanumerical representation of originating address corresponding to the entry in phonebook (if exists).
    std::string         _timestamp      {}; ///< Message delivery timestamp.
    std::string         _text           {}; ///< Message text.
};

} // namespace Sim808::ShortMessages
