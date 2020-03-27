#pragma once

#include <vector>
#include <string>

#include "strix/common/argument.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual Return run(const std::vector<common::Argument>& iArguments) const = 0;

};


} // namespace command
} // namespace executor
} // namespace strix
