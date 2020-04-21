#pragma once

#include <vector>
#include <string>

#include "photon/common/argument.hpp"
#include "photon/executor/return.hpp"
#include "photon/executor/execution_context.hpp"

namespace photon {
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
} // namespace photon
