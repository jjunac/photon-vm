#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/base_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


///////////////////////////////////////
/// Declaration
///////////////////

class PrintCommand : public BaseCommand {
public:
    PrintCommand() = default;
    virtual ~PrintCommand() = default;

    bool isValid(const std::vector<common::Argument>& iArguments) const override;
    Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const override;

};


///////////////////////////////////////
/// Definition
///////////////////

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
