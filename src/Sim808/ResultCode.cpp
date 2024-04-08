/**
 * @file    ResultCode.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    05.04.2024
 */

#include <Sim808/ResultCode.hpp>
#include <unordered_map>

namespace Sim808
{

static const std::unordered_map<std::string_view, ResultCode> mapping
    {
        { "OK", ResultCode::Ok },
        { "CONNECT", ResultCode::Connect },
        { "RING", ResultCode::Ring },
        { "NO CARRIER", ResultCode::NoCarrier },
        { "ERROR", ResultCode::Error },
        { "NO DIALTONE", ResultCode::NoDialtone },
        { "BUSY", ResultCode::Busy },
        { "NO ANSWER", ResultCode::NoAnswer }
    };

auto tryConvertToResultCode(std::string_view str) -> std::optional<ResultCode>
{
    if (str.ends_with("\r\n"))
    {
        str.remove_suffix(2);
    }

    if (const auto it = mapping.find(str); it != mapping.cend())
    {
        return it->second;
    }
    else if (str.starts_with("CONNECT "))
    {
        return ResultCode::ConnectEx;
    }
    else if (str.starts_with("+CMS ERROR"))
    {
        return ResultCode::Error;
    }
    else
    {
        return std::nullopt;
    }
}

} // namespace Sim808
