#pragma once

#include <vector>
#include <string>
#include <array>

#include "photon/executor/command/arithmetic/arithmetic_command.hpp"
#include "photon/executor/return.hpp"

namespace photon {
namespace executor {
namespace command {


struct MulOperation {
    template <typename T>
    static void Apply(T& iRegsiterValue, const std::vector<T>& iArgs) {
        if (iArgs.size() > 1) {
            iRegsiterValue = iArgs[0] * iArgs[1];
        } else {
            iRegsiterValue *= iArgs[0];
        }
    }
};


class MulCommand : public ArithmeticCommand<MulOperation> {
public:
    MulCommand() = default;
    virtual ~MulCommand() = default;
};


} // namespace command
} // namespace executor
} // namespace photon
