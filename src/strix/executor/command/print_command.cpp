#include "strix/executor/command/print_command.hpp"

#include <iostream>
#include <string>

#include "strix/common/type.hpp"

namespace strix {
namespace executor {
namespace command {

bool PrintCommand::isValid(const std::vector<common::Argument>& iArguments) const {
    return iArguments.size() == 1;
}

Return PrintCommand::run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const {
    using common::Type;

    const common::Argument& anArgument = iArguments[0];
    std::cout << ioExecutionContext.evaluate<std::string>(anArgument);

    return {};
}


} // namespace command
} // namespace executor
} // namespace strix
