#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/base_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


class SetCommand : public BaseCommand {
public:
    SetCommand() = default;
    virtual ~SetCommand() = default;

    bool isValid(const std::vector<common::Argument>& iArguments) const override;
    Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const override;

    template <typename T>
    void assign(ExecutionContext& ioExecutionContext, const common::Register& iLhs, const common::Argument& iRhs) const;


};


} // namespace command
} // namespace executor
} // namespace strix
