/**
 * @file    Sim808.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    19.03.2024
 */

#pragma once

#include <memory>
#include <string_view>

#include <Sim808/CommandGateway.hpp>
#include <Sim808/ShortMessages/Service.hpp>

/// @defgroup sim Driver

/// @defgroup sim-sms Short Message Service (SMS)
/// @ingroup  sim

/// @defgroup sim-utilities Utility
/// @ingroup  sim

/// @defgroup sim-clt Command-line tool

/// Entry point namespace.
namespace Sim808
{

/// Driver for SIM808 cellular module.
/// @ingroup sim
/// @since   0.1.0
class Sim808
{
public:
    /// Constructs driver object that communicate with cellular module via specified command gateway.
    /// @param gateway Command gateway.
    explicit Sim808(std::shared_ptr<CommandGateway> gateway);

    /// Gets a service for working with short messages.
    /// @return A reference to service.
    auto shortMessageService() noexcept -> ShortMessages::Service&;

private:
    std::shared_ptr<CommandGateway> _gateway;             ///< Command gateway.
    ShortMessages::Service          _shortMessageService; ///< Short message service.
};

} // namespace Sim808
