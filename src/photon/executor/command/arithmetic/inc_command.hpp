#pragma once

#include <vector>
#include <string>

#include "photon/executor/command/arithmetic/arithmetic_command.hpp"
#include "photon/executor/return.hpp"

namespace photon {
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
} // namespace photon
