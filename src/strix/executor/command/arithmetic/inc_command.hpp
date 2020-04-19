#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/arithmetic/arithmetic_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


struct IncOperation {
    template <typename T>
    static void Apply(T& iRegsiterValue, const std::vector<T>& /* iArgs */) {
        ++iRegsiterValue;
    }
};


class IncCommand : public ArithmeticCommand<IncOperation> {
public:
    IncCommand() = default;
    virtual ~IncCommand() = default;
};


} // namespace command
} // namespace executor
} // namespace strix
