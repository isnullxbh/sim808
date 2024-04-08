/**
 * @file    DefaultCommandGateway.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    22.03.2024
 */

#pragma once

#include <filesystem>
#include <string_view>

#include <asio/serial_port.hpp>

#include <Sim808/CommandGateway.hpp>

namespace Sim808
{

/// A command gateway based on serial interface.
/// @ingroup sim
/// @since   0.1.0
class DefaultCommandGateway : public CommandGateway
{
public:
    /// Constructs the command gateway that works via serial device with the specified path.
    /// @param ioc  IO context.
    /// @param path Path to serial port device.
    explicit DefaultCommandGateway(asio::io_context& ioc, const std::filesystem::path& path);

    /// Destructor.
    ~DefaultCommandGateway() override;

    auto send(std::string_view command) -> Response override;

    auto sendData(std::string_view data) -> void override;

    auto waitFor(std::string_view str) -> void override;

private:
    /// Reads command response.
    /// @return A command response.
    auto readResponse() -> Response;

private:
    asio::serial_port _serial; ///< Serial port.

    static constexpr std::string_view cr_lf { "\r\n" }; ///< Line delimiter.
};

} // namespace Sim808
