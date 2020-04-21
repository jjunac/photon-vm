#pragma once

#include <vector>
#include <string>

#include "photon/executor/command/base_command.hpp"
#include "photon/executor/return.hpp"

namespace photon {
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
} // namespace photon
