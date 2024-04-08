/**
 * @file    ResultCode.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    05.04.2024
 */

#pragma once

#include <optional>
#include <string_view>

namespace Sim808
{

/// Defines result codes.
/// @ingroup sim
/// @since   0.1.0
enum class ResultCode
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

/// Converts string to result code.
/// @param   str String representation of a result code.
/// @return  If the specified string can be converted to a result code - code, otherwise - nullopt.
/// @ingroup sim
/// @since   0.1.0
auto tryConvertToResultCode(std::string_view str) -> std::optional<ResultCode>;

} // namespace Sim808
