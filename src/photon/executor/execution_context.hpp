#pragma once

#include <unordered_map>

#include "photon/common/argument.hpp"
#include "photon/executor/conversion_helper.hpp"
#include "photon/executor/memory.hpp"
#include "photon/exception.hpp"


namespace photon {
namespace executor {


///////////////////////////////////////
/// Declaration
///////////////////

class ExecutionContext final {
public:
    ExecutionContext() = default;
    ~ExecutionContext() = default;

    template <typename T>
    const T& getRegisterValue(uint32_t iRegisterNumber) const;
    template <typename T>
    T& accessRegisterValue(uint32_t iRegisterNumber);

    template <typename U, typename V>
    U evaluate(const V& iValue) const;
    template <typename T>
    T evaluate(const common::Argument& iArgument) const;
    template <typename T>
    T evaluate(const common::Register& iRegister) const;

private:
    executor::Memory _memory;
};

///////////////////////////////////////
/// Definition
///////////////////

template <typename T>
const T& ExecutionContext::getRegisterValue(uint32_t iRegisterNumber) const {
    return _memory.getValue<T>(iRegisterNumber);
}
template <typename T>
T& ExecutionContext::accessRegisterValue(uint32_t iRegisterNumber) {
    return _memory.accessValue<T>(iRegisterNumber);
}

template <typename U, typename V>
U ExecutionContext::evaluate(const V& iValue) const {
    return ConversionHelper<U, V>().convert(iValue);
}

template <typename T>
T ExecutionContext::evaluate(const common::Argument& iValue) const {
    using common::Type;
    switch(iValue.getType()) {
    case Type::LONG:
        return evaluate<T>(iValue.get<long>());
    case Type::DOUBLE:
        return evaluate<T>(iValue.get<double>());
    case Type::STRING:
        return evaluate<T>(iValue.get<std::string>());
    case Type::REGISTER:
        return evaluate<T>(iValue.get<common::Register>());
    default:
        throw exception::BadConversion();
    }
}

template <typename T>
T ExecutionContext::evaluate(const common::Register& iRegister) const {
    using common::Type;
    auto aRegisterNumber = iRegister.getRegisterNumber();
    switch(iRegister.getType()) {
    case Type::LONG:
        return evaluate<T>(_memory.getValue<long>(aRegisterNumber));
    case Type::DOUBLE:
        return evaluate<T>(_memory.getValue<double>(aRegisterNumber));
    case Type::STRING:
        return evaluate<T>(_memory.getValue<std::string>(aRegisterNumber));
    default:
        throw exception::BadConversion();
    }
}


} // namespace executor
} // namespace photon

