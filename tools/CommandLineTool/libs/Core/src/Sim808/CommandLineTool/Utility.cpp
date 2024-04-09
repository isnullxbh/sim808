/**
 * @file    Utility.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    08.04.2024
 */

#include <Sim808/CommandLineTool/Utility.hpp>

#include <algorithm>
#include <regex>

namespace Sim808::CommandLineTool
{

auto Utility::extractKeyValuePairs(std::string_view str) -> std::unordered_map<std::string_view, std::string_view>
{
    static const std::regex regexp { "[\\w]+\\=\"[^\"]+\"" };

    std::unordered_map<std::string_view, std::string_view> key_values;
    for (auto it = std::cregex_iterator(str.data(), str.data() + str.size(), regexp); it != std::cregex_iterator(); ++it)
    {
        const auto matched =
            str.substr(static_cast<std::string_view::size_type>(it->position()),
                       static_cast<std::string_view::size_type>(it->length()));
        const auto sep_pos = matched.find('=');

        if (sep_pos == std::string_view::npos)
        {
            continue;
        }

        key_values.emplace(matched.substr(0, sep_pos),
                           matched.substr(sep_pos + 2, matched.size() - sep_pos - 3));
    }

    return key_values;
}

} // namespace Sim808::CommandLineTool
