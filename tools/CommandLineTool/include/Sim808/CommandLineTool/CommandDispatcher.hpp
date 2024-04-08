/**
 * @file    CommandDispatcher.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

/// Command-line tool.
namespace Sim808::CommandLineTool
{

/// A command dispatcher.
/// @ingroup sim_clt
/// @since   0.1.0
class CommandDispatcher
{
private:
    /// A base class for command handlers.
    class Handler
    {
    public:
        using Ptr = std::unique_ptr<Handler>; ///< A type of pointer to handler.

    public:
        /// Destructor.
        virtual ~Handler() = default;

        /// Execute the specified command.
        /// @param command Command to execute.
        virtual auto execute(std::string_view command) -> void = 0;

        /// Checks if handler can execute the specified command.
        /// @param command Command to check.
        /// @return If the handler can execute the command - true, otherwise - false.
        virtual auto match(std::string_view command) const noexcept -> bool = 0;
    };

public:
    /// Register a handler for commands starting with the specified prefix.
    /// @tparam ConcreteHandler Command handler type.
    /// @param  command_prefix  Command prefix.
    /// @param  handler         Command handler.
    template<typename ConcreteHandler>
    auto registerHandler(std::string command_prefix, ConcreteHandler&& handler) -> void;

    /// Execute the specified command.
    /// To execute a command, the dispatcher finds the appropriate handler and calls it. If there are no suitable
    /// handlers, the command will not be executed.
    /// @param command Command to execute.
    auto execute(std::string_view command) -> void;

private:
    std::vector<Handler::Ptr> _handlers {}; ///< Command handlers.
};

template<typename ConcreteHandler>
auto CommandDispatcher::registerHandler(std::string command_prefix, ConcreteHandler&& handler) -> void
{
    class HandlerImpl : public Handler
    {
    public:
        explicit HandlerImpl(std::string command_prefix, ConcreteHandler&& handler)
            : _command_prefix(std::move(command_prefix))
            , _handler(std::forward<ConcreteHandler>(handler))
        {}

        auto execute(std::string_view command) -> void final
        {
            _handler(command);
        }

        auto match(std::string_view command) const noexcept -> bool final
        {
            return command.starts_with(_command_prefix);
        }

    private:
        std::string     _command_prefix;
        ConcreteHandler _handler;
    };

    _handlers.emplace_back(
        std::make_unique<HandlerImpl>(std::move(command_prefix), std::forward<ConcreteHandler>(handler)));
}

} // namespace Sim808::CommandLineTool
