#pragma once

#include <vector>
#include <string>

#include "strix/common/argument.hpp"
#include "strix/executor/return.hpp"
#include "strix/executor/execution_context.hpp"

namespace strix {
namespace executor {
namespace command {


class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual bool isValid(const std::vector<common::Argument>& iArguments) const = 0;
    virtual Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const = 0;

};


} // namespace command
} // namespace executor
} // namespace strix
