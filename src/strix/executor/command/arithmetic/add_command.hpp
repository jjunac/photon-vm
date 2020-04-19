#pragma once

#include <string>
#include <array>

#include "strix/executor/command/arithmetic/arithmetic_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


struct AddOperation {
    template <typename T>
    static void Apply(T& iRegsiterValue, const std::vector<T>& iArgs) {
        if (iArgs.size() > 1) {
            iRegsiterValue = iArgs[0] + iArgs[1];
        } else {
            iRegsiterValue += iArgs[0];
        }
    }
};


class AddCommand : public ArithmeticCommand<AddOperation> {
public:
    AddCommand() = default;
    virtual ~AddCommand() = default;
};


} // namespace command
} // namespace executor
} // namespace strix
