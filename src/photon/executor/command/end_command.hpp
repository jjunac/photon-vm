#pragma once

#include <vector>
#include <string>

#include "photon/executor/command/base_command.hpp"
#include "photon/executor/return.hpp"

namespace photon {
namespace executor {
namespace command {


///////////////////////////////////////
/// Declaration
///////////////////

class EndCommand : public BaseCommand {
public:
    EndCommand() = default;
    virtual ~EndCommand() = default;

    bool isValid(const std::vector<common::Argument>& iArguments) const override;
    Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const override;

};

///////////////////////////////////////
/// Definition
///////////////////

bool EndCommand::isValid(const std::vector<common::Argument>& iArguments) const {
    return iArguments.empty();
}

Return EndCommand::run(ExecutionContext& /* ioExecutionContext */, const std::vector<common::Argument>& /* iArguments */) const {
    return {true};
}


} // namespace command
} // namespace executor
} // namespace photon
