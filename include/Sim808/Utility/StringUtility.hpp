/**
 * @file    StringUtility.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#pragma once

#include <string_view>

namespace Sim808
{

/// Provides an auxiliary methods to works with strings.
/// @ingroup sim-utilities
/// @since   0.1.0
class StringUtility
{
public:
    /// Remove quotes in the specified string, if any.
    /// @param  str Input string.
    /// @return Unquoted string.
    static auto unquote(std::string_view str) -> std::string_view;
};

} // namespace Sim808

