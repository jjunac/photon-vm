#include "strix/executor/command/end_command.hpp"

#include <iostream>

namespace strix {
namespace executor {
namespace command {

bool EndCommand::isValid(const std::vector<common::Argument>& iArguments) const {
    return iArguments.empty();
}

Return EndCommand::run(ExecutionContext& /* ioExecutionContext */, const std::vector<common::Argument>& /* iArguments */) const {
    return {true};
}


} // namespace command
} // namespace executor
} // namespace strix
