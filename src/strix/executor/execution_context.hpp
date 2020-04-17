#pragma once

#include <unordered_map>

#include "strix/common/argument.hpp"
#include "strix/executor/conversion_helper.hpp"
#include "strix/executor/memory.hpp"
#include "strix/exception.hpp"


namespace strix {
namespace executor {


class ExecutionContext final {
public:
    ExecutionContext() = default;
    ~ExecutionContext() = default;

    template <typename T>
    void setRegisterValue(uint32_t iRegisterNumber, const T& iValue);

    template <typename U>
    U evaluate(const common::Argument& iArgument) const;
    template <typename U>
    U evaluate(const common::Register& iRegister) const;

private:
    executor::Memory _memory;

};

template <typename T>
void ExecutionContext::setRegisterValue(uint32_t iRegisterNumber, const T& iValue) {
    _memory.accessValue<T>(iRegisterNumber) = iValue;
}

template <typename U>
inline U ExecutionContext::evaluate(const common::Argument& iValue) const {
    using common::Type;
    switch(iValue.getType()) {
    case Type::LONG:
        return ConversionHelper<U, long>().convert(iValue.get<long>());
    case Type::DOUBLE:
        return ConversionHelper<U, double>().convert(iValue.get<double>());
    case Type::STRING:
        return ConversionHelper<U, std::string>().convert(iValue.get<std::string>());
    case Type::REGISTER:
        return evaluate<U>(iValue.get<common::Register>());
    default:
        throw exception::BadConversion();
    }
}

template <typename U>
inline U ExecutionContext::evaluate(const common::Register& iRegister) const {
    using common::Type;
    auto aRegisterNumber = iRegister.getRegisterNumber();
    switch(iRegister.getType()) {
    case Type::LONG:
        return ConversionHelper<U, long>().convert(_memory.getValue<long>(aRegisterNumber));
    case Type::DOUBLE:
        return ConversionHelper<U, double>().convert(_memory.getValue<double>(aRegisterNumber));
    case Type::STRING:
        return ConversionHelper<U, std::string>().convert(_memory.getValue<std::string>(aRegisterNumber));
    default:
        throw exception::BadConversion();
    }
}



} // namespace executor
} // namespace strix

