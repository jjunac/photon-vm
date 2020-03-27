#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/base_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


class PrintCommand : public BaseCommand {
public:
    PrintCommand() = default;
    virtual ~PrintCommand() = default;

    Return run(const std::vector<std::string>& iArguments) const override;

};


} // namespace command
} // namespace executor
} // namespace strix
