#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/base_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


struct DecOperation {
    template <typename T>
    static void Apply(T& iRegsiterValue, const std::vector<T>& /* iArgs */) {
        --iRegsiterValue;
    }
};


class DecCommand : public ArithmeticCommand<DecOperation> {
public:
    DecCommand() = default;
    virtual ~DecCommand() = default;
};


} // namespace command
} // namespace executor
} // namespace strix
