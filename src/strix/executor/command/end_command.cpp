#include "strix/executor/command/end_command.hpp"

#include <iostream>

namespace strix {
namespace executor {
namespace command {


Return EndCommand::run(const std::vector<std::string>& /* iArguments */) const {
    return {true};
}


} // namespace command
} // namespace executor
} // namespace strix
