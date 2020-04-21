#include "photon/executor/command_factory.hpp"

// #include "photon/executor/command/add_command.hpp"
// #include "photon/executor/command/dec_command.hpp"
// #include "photon/executor/command/end_command.hpp"
// #include "photon/executor/command/inc_command.hpp"
// #include "photon/executor/command/print_command.hpp"
// #include "photon/executor/command/set_command.hpp"

#include "photon/executor/command.hpp"


namespace photon {
namespace executor {


CommandFactory::CommandFactory() :
        _commandInstances() {
    using namespace command;

    _commandInstances["add"]    = std::make_unique<AddCommand>();
    _commandInstances["dec"]    = std::make_unique<DecCommand>();
    _commandInstances["end"]    = std::make_unique<EndCommand>();
    _commandInstances["inc"]    = std::make_unique<IncCommand>();
    _commandInstances["print"]  = std::make_unique<PrintCommand>();
    _commandInstances["set"]    = std::make_unique<SetCommand>();
    _commandInstances["sub"]    = std::make_unique<SubCommand>();
    _commandInstances["mul"]    = std::make_unique<MulCommand>();
    _commandInstances["div"]    = std::make_unique<DivCommand>();
}

const command::BaseCommand& CommandFactory::getCommand(const std::string& iCommandName) {
    return *_commandInstances.at(iCommandName);
}


} // namespace executor
} // namespace photon