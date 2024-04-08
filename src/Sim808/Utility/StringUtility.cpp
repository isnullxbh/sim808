/**
 * @file    StringUtility.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#include <Sim808/Utility/StringUtility.hpp>

namespace Sim808
{

auto StringUtility::unquote(std::string_view str) -> std::string_view
{
    if (str.size() >= 2 && str.starts_with('"') && str.ends_with('"'))
    {
        str.remove_prefix(1);
        str.remove_suffix(1);
    }

    return str;
}

} // namespace Sim808

