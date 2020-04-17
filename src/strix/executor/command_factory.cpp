#include "strix/executor/command_factory.hpp"

#include "strix/executor/command/end_command.hpp"
#include "strix/executor/command/print_command.hpp"
#include "strix/executor/command/set_command.hpp"


namespace strix {
namespace executor {


CommandFactory::CommandFactory() :
        _commandInstances() {
    using namespace command;

    _commandInstances["end"] = std::make_unique<EndCommand>();
    _commandInstances["print"] = std::make_unique<PrintCommand>();
    _commandInstances["set"] = std::make_unique<SetCommand>();
}

const command::BaseCommand& CommandFactory::getCommand(const std::string& iCommandName) {
    return *_commandInstances.at(iCommandName);
}


} // namespace executor
} // namespace strix