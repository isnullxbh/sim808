/**
 * @file    Service.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    23.03.2024
 */

#pragma once

#include <string_view>
#include <vector>

#include <Sim808/CommandGateway.hpp>

#include <Sim808/ShortMessages/BaseTypes.hpp>
#include <Sim808/ShortMessages/DeletionRequestType.hpp>
#include <Sim808/ShortMessages/Message.hpp>
#include <Sim808/ShortMessages/MessageStorageType.hpp>

/// Short Message Service (SMS).
namespace Sim808::ShortMessages
{

/// A service intended to work with SMS messages.
/// @ingroup sim-sms
/// @since   0.1.0
class Service
{
public:
    using Messages = std::vector<Message>; ///< The type of message list.

public:
    /// Constructor.
    /// @param gateway Command gateway.
    explicit Service(CommandGateway::Ptr gateway);

public:
    /// Deletes the message with the specified index.
    /// @param  index Message index.
    /// @return The result code of the operation.
    auto deleteMessage(MessageIndex index) -> ResultCode;

    /// Deletes messages from the specified message storage.
    /// @param  type Deletion request type.
    /// @return The result code of the operation.
    auto deleteMessages(DeletionRequestType type) -> ResultCode;

    /// Sends message.
    /// @param number A number of a caller.
    /// @param text   Message text.
    auto sendMessage(std::string_view number, std::string_view text) -> void;

    /// Gets messages from the specified message storage.
    /// @param  type          Message storage type.
    /// @param  update_status Configures the behaviour of updating message status in the storage - if true, status of
    ///                       unread message will be changed to read, otherwise no changes occurs.
    /// @return A list of messages.
    auto getMessages(MessageStorageType type, bool update_status) -> Messages;

private:
    CommandGateway::Ptr _gateway; ///< Command gateway.
};

} // namespace Sim808::ShortMessages
