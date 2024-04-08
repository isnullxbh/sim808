/**
 * @file    Sim808.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    18.03.2024
 */

#include <Sim808/Sim808.hpp>

namespace Sim808
{

Sim808::Sim808(std::shared_ptr<CommandGateway> gateway)
    : _gateway(std::move(gateway))
    , _shortMessageService(_gateway)
{}

auto Sim808::shortMessageService() noexcept -> ShortMessages::Service&
{
    return _shortMessageService;
}

} // namespace Sim808
