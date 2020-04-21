#pragma once

#include <string>
#include <array>

#include "photon/executor/command/arithmetic/arithmetic_command.hpp"
#include "photon/executor/return.hpp"

namespace photon {
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
} // namespace photon
