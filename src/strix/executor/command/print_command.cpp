#include "strix/executor/command/print_command.hpp"

#include <iostream>

namespace strix {
namespace executor {
namespace command {


Return PrintCommand::run(const std::vector<std::string>& iArguments) const {
    std::cout << iArguments[0];
    return {};
}


} // namespace command
} // namespace executor
} // namespace strix
