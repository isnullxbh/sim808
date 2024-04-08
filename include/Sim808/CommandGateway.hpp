/**
 * @file    CommandGateway.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.03.2024
 */

#pragma once

#include <memory>
#include <string>
#include <string_view>

#include <Sim808/ResultCode.hpp>

namespace Sim808
{

/// A command gateway interface.
/// @ingroup sim
/// @since   0.1.0
class CommandGateway
{
public:
    using Ptr = std::shared_ptr<CommandGateway>; ///< A type of pointer to command gateway.

    /// Command response.
    struct Response
    {
        ResultCode  code; ///< Result code.
        std::string data; ///< Data.
    };

public:
    /// Destructor.
    virtual ~CommandGateway() = default;

    /// Sends the specified command to the data terminal equipment.
    /// @param  command Command.
    /// @return A command response.
    virtual auto send(std::string_view command) -> Response = 0;

    /// Sends the specified data to the data terminal equipment.
    /// @param data Data.
    virtual auto sendData(std::string_view data) -> void = 0;

    /// Waits for the specified string from the data terminal equipment.
    /// @param str String.
    virtual auto waitFor(std::string_view str) -> void = 0;
};

} // namespace Sim808
