#pragma once

#include <vector>
#include <string>

#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual Return run(const std::vector<std::string>& iArguments) const = 0;

};


} // namespace command
} // namespace executor
} // namespace strix
