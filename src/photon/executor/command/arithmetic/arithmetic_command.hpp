#pragma once

#include <vector>
#include <string>

#include "photon/executor/command/base_command.hpp"
#include "photon/executor/return.hpp"

namespace photon {
namespace executor {
namespace command {


///////////////////////////////////////
/// Declaration
///////////////////

template <typename ArithmeticOperation>
class ArithmeticCommand : public BaseCommand {
public:
    ArithmeticCommand() = default;
    virtual ~ArithmeticCommand() = default;

    bool isValid(const std::vector<common::Argument>& iArguments) const override;
    Return run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const override;

    template <typename T>
    void assign(ExecutionContext& ioExecutionContext, const common::Register& iRegister, const std::vector<common::Argument>& iArguments) const;

};

///////////////////////////////////////
/// Definition
///////////////////

template <typename ArithmeticOperation>
bool ArithmeticCommand<ArithmeticOperation>::isValid(const std::vector<common::Argument>& /* iArguments */) const {
    // TODO:
    return true;
}

template <typename ArithmeticOperation>
Return ArithmeticCommand<ArithmeticOperation>::run(ExecutionContext& ioExecutionContext, const std::vector<common::Argument>& iArguments) const {
    using common::Type;
    const auto& aRegister = iArguments[0].get<common::Register>();
    switch(aRegister.getType()) {
    case Type::LONG:
        assign<long>(ioExecutionContext, aRegister, iArguments);
        break;
    case Type::DOUBLE:
        assign<double>(ioExecutionContext, aRegister, iArguments);
        break;
    default:
        throw exception::BadConversion();
    }
    return {};
}

template <typename ArithmeticOperation>
template <typename T>
void ArithmeticCommand<ArithmeticOperation>::assign(ExecutionContext& ioExecutionContext, const common::Register& iRegister, 
        const std::vector<common::Argument>& iArguments) const {
    std::vector<T> aTypedArgs;
    aTypedArgs.reserve(iArguments.size() - 1);
    std::transform(std::next(iArguments.begin()), iArguments.end(), std::back_inserter(aTypedArgs),
            [&](const common::Argument& iArg) { return ioExecutionContext.evaluate<T>(iArg); });
    ArithmeticOperation::template Apply<T>(ioExecutionContext.accessRegisterValue<T>(iRegister.getRegisterNumber()), aTypedArgs);
}


} // namespace command
} // namespace executor
} // namespace photon
