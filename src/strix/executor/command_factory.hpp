#pragma once

#include <unordered_map>
#include <memory>

#include "strix/executor/command/base_command.hpp"

namespace strix {
namespace executor {


class CommandFactory final {
public:
    CommandFactory();
    ~CommandFactory() = default;

    const command::BaseCommand& getCommand(const std::string& iCommandName);

private:
    std::unordered_map<std::string, std::unique_ptr<command::BaseCommand> > _commandInstances;
};


} // namespace executor
} // namespace strix

