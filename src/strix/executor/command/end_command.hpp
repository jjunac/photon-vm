#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/base_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


class EndCommand : public BaseCommand {
public:
    EndCommand() = default;
    virtual ~EndCommand() = default;

    bool isValid(const std::vector<common::Argument>& iArguments) const override;
    Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const override;

};


} // namespace command
} // namespace executor
} // namespace strix
