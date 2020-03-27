#include "strix/executor/command/print_command.hpp"

#include <iostream>
#include <string>

namespace strix {
namespace executor {
namespace command {


Return PrintCommand::run(const std::vector<common::Argument>& iArguments) const {
    using common::Argument;

    const auto& anArgument = iArguments[0];
    switch(anArgument.getType()) {
    case Argument::Type::LONG:
        std::cout << std::to_string(anArgument.getLong());
        break;
    case Argument::Type::DOUBLE:
        std::cout << std::to_string(anArgument.getDouble());
        break;
    case Argument::Type::STRING:
        std::cout << anArgument.getString();
        break;
    }

    return {};
}


} // namespace command
} // namespace executor
} // namespace strix
