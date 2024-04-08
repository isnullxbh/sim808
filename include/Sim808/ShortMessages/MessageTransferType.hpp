/**
 * @file    MessageTransferType.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#pragma once

namespace Sim808::ShortMessages
{

/// Defines the types of messages transfer between the mobile station and the SMS center.
/// @ingroup sim_short-messages
/// @since   0.1.0
enum class MessageTransferType
{
    Deliver,        ///< Represents messages delivered from the SMS center to a mobile phone.
    DeliverReport,  ///< Represents messages that acknowledge delivery.
    Submit,         ///< Represents messages sending from a mobile phone to the SMS center.
    SubmitReport,   ///< Represents messages that acknowledge submit.
    Command,        ///< Represents messages used to query for a message buffered in SMS center, to modify its parameters or to delete it.
    StatusReport,   ///< Represents information messages sends from the SMS center to a mobile phone.
    Unspecified     ///< Reserved.
};

} // namespace Sim808::ShortMessages
