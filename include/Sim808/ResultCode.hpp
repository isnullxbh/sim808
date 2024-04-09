/**
 * @file    ResultCode.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    05.04.2024
 */

#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace Sim808
{

/// Defines result codes.
/// @ingroup sim
/// @since   0.1.0
class ResultCode
{
public:
    enum
    {
        Ok          = 0, ///< Acknowledges execution of a command.
        Connect     = 1, ///< Indicates that connection has been established.
        Ring        = 2, ///< Indicates that DCE detected an incoming call.
        NoCarrier   = 3, ///< Indicates that connection has been terminated.
        Error       = 4, ///< Indicates that an error occurred.
        NoDialtone  = 6, ///< Indicates that dial tone has not been detected.
        Busy        = 7, ///< Indicates that busy signal detected.
        NoAnswer    = 8, ///< Indicates that call has not been answered.
        ConnectEx,       ///< Indicates that connect has been established (includes manufacturer specific data).
    };

public:
    /// Constructs result code with value Ok.
    ResultCode() = default;

    /// Constructs result code with the specified value.
    /// @param code Value.
    ResultCode(decltype(Ok) value);

    /// Constructs result code with the specified value and message.
    /// @param code    Value.
    /// @param message Message.
    explicit ResultCode(decltype(Ok) value, std::string message);

    /// Gets the value of the result code.
    /// @return Code.
    auto value() const noexcept -> decltype(Ok);

    /// Gets the message.
    /// @return A reference to message.
    auto message() const noexcept -> const std::string&;

    /// Checks if the result code is an error.
    /// @return If value of the error code is Error - false, otherwise - true.
    explicit operator bool() const noexcept;

    /// Gets the string representation of the result code.
    /// @return
    auto toString() const -> std::string;

private:
    decltype(Ok) _value;      ///< Value.
    std::string  _message {}; ///< Message.
};

/// Converts string to result code.
/// @param   str String representation of a result code.
/// @return  If the specified string can be converted to a result code - code, otherwise - nullopt.
/// @ingroup sim
/// @since   0.1.0
auto tryConvertToResultCode(std::string_view str) -> std::optional<ResultCode>;

} // namespace Sim808
