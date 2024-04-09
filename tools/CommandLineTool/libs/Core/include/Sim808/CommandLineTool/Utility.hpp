/**
 * @file    Utility.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    08.04.2024
 */

#pragma once

#include <string_view>
#include <unordered_map>

namespace Sim808::CommandLineTool
{

/// Provides a set an auxiliary functions for command-line tool.
/// @ingroup sim-clt
/// @since   0.1.0
class Utility
{
public:
    /// Extracts key-value pairs from the specified string.
    /// Key-value pairs must be represented as follows: key="value".
    /// @param  str String to parse.
    /// @return Mapping parameter names to their values.
    static auto extractKeyValuePairs(std::string_view str) -> std::unordered_map<std::string_view, std::string_view>;
};

} // namespace Sim808::CommandLineTool
