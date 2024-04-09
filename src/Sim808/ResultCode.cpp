/**
 * @file    ResultCode.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    05.04.2024
 */

#include <Sim808/ResultCode.hpp>

#include <algorithm>
#include <unordered_map>

namespace Sim808
{

static const std::unordered_map<std::string_view, decltype(ResultCode::Ok)> mapping
    {
        { "OK",             ResultCode::Ok          },
        { "CONNECT",        ResultCode::Connect     },
        { "RING",           ResultCode::Ring        },
        { "NO CARRIER",     ResultCode::NoCarrier   },
        { "ERROR",          ResultCode::Error       },
        { "NO DIALTONE",    ResultCode::NoDialtone  },
        { "BUSY",           ResultCode::Busy        },
        { "NO ANSWER",      ResultCode::NoAnswer    }
    };

static constexpr std::string_view connect_ex_prefix { "CONNECT " };
static constexpr std::string_view cms_error_prefix { "+CMS ERROR: "};

static std::string_view convertToString(decltype(ResultCode::Ok) value)
{
    const auto it =
        std::find_if(mapping.cbegin(), mapping.cend(), [=](const decltype(mapping)::value_type& kv)
            {
                return kv.second == value;
            });

    return it != mapping.cend() ? it->first : "<Unknown>";
}

ResultCode::ResultCode(decltype(Ok) value)
    : _value(value)
{}

ResultCode::ResultCode(decltype(Ok) value, std::string message)
    : _value(value)
    , _message(std::move(message))
{}

auto ResultCode::value() const noexcept -> decltype(Ok)
{
    return _value;
}

auto ResultCode::message() const noexcept -> const std::string&
{
    return _message;
}

ResultCode::operator bool() const noexcept
{
    return _value != Error;
}

auto ResultCode::toString() const -> std::string
{
    std::string res { convertToString(_value) };
    if ((_value == Error || _value == ConnectEx) && !_message.empty())
    {
        res += ": ";
        res += _message;
    }
    return res;
}

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
    else if (str.starts_with(connect_ex_prefix))
    {
        auto message = std::string(str.substr(connect_ex_prefix.size()));
        return ResultCode { ResultCode::ConnectEx, std::move(message) };
    }
    else if (str.starts_with(cms_error_prefix))
    {
        auto message = std::string(str.substr(cms_error_prefix.size()));
        return ResultCode { ResultCode::Error, std::move(message) };
    }
    else
    {
        return std::nullopt;
    }
}

} // namespace Sim808
