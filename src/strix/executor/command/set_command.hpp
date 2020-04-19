#pragma once

#include <vector>
#include <string>

#include "strix/executor/command/base_command.hpp"
#include "strix/executor/return.hpp"

namespace strix {
namespace executor {
namespace command {


///////////////////////////////////////
/// Declaration
///////////////////

class SetCommand : public BaseCommand {
public:
    SetCommand() = default;
    virtual ~SetCommand() = default;

    bool isValid(const std::vector<common::Argument>& iArguments) const override;
    Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const override;

    template <typename T>
    void assign(ExecutionContext& ioExecutionContext, const common::Register& iLhs, const common::Argument& iRhs) const;
};


///////////////////////////////////////
/// Definition
///////////////////

bool SetCommand::isValid(const std::vector<common::Argument>& iArguments) const {
    return iArguments.size() == 2 && iArguments[0].isRegister();
}

Return SetCommand::run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const {
    using common::Type;

    const auto& aLhs = iArguments[0].get<common::Register>();
    const auto& aRhs = iArguments[1];
    switch(aLhs.getType()) {
    case Type::LONG:
        assign<long>(ioExecutionContext, aLhs, aRhs);
        break;
    case Type::DOUBLE:
        assign<double>(ioExecutionContext, aLhs, aRhs);
        break;
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
    ioExecutionContext.accessRegisterValue<T>(iLhs.getRegisterNumber()) = ioExecutionContext.evaluate<T>(iRhs);
}


} // namespace command
} // namespace executor
} // namespace strix
