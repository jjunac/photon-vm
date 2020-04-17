#include "strix/executor/command/set_command.hpp"

#include <iostream>
#include <string>

#include "strix/common/type.hpp"

namespace strix {
namespace executor {
namespace command {

bool SetCommand::isValid(const std::vector<common::Argument>& iArguments) const {
    return iArguments.size() == 2 && iArguments[0].isRegister();
}

Return SetCommand::run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const {
    using common::Type;

    const auto& aLhs = iArguments[0].get<common::Register>();
    const auto& aRhs = iArguments[1];
    switch(aLhs.getType()) {
    case Type::LONG: {
        assign<long>(ioExecutionContext, aLhs, aRhs);
        break;
    }
    case Type::DOUBLE: {
        assign<double>(ioExecutionContext, aLhs, aRhs);
        break;
    }
    case Type::STRING:
        assign<std::string>(ioExecutionContext, aLhs, aRhs);
        break;
    default:
        throw exception::BadConversion();
    }

    return {};
}

template <typename T>
void SetCommand::assign(ExecutionContext& ioExecutionContext, const common::Register& iLhs, const common::Argument& iRhs) const {
    ioExecutionContext.setRegisterValue(aLhs.getRegisterNumber(), ioExecutionContext.evaluate<T>(aRhs));
}


} // namespace command
} // namespace executor
} // namespace strix
