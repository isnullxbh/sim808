/**
 * @file    CommandDispatcher.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#include <Sim808/CommandLineTool/CommandDispatcher.hpp>

#include <iostream>

namespace Sim808::CommandLineTool
{

auto CommandDispatcher::execute(std::string_view command) -> void
{
    for (auto& handler : _handlers)
    {
        if (handler->match(command))
        {
            try
            {
                handler->execute(command);
            }
            catch (const std::exception& ex)
            {
                std::cerr << "An error occurred during command execution: " << ex.what() << std::endl;
            }

            return;
        }
    }

    std::cerr << "Unknown command: \"" << command << "\"" << std::endl;
}

} // namespace Sim808::CommandLineTool
