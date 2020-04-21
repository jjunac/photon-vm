#pragma once

#include "photon/common/argument.hpp"
#include "photon/executor/memory.hpp"
#include "photon/exception.hpp"


namespace photon {
namespace executor {


template<typename U, typename V, class Enable = void>
class ConversionHelper final {
public:
    U convert(const V& /* iValue */) const { throw exception::BadConversion(); }
};

template <typename U, typename V>
class ConversionHelper<U, V, typename std::enable_if<std::is_convertible<U&, V>::value>::type> final {
public:
    U convert(const V& iValue) const { return iValue; }
};

template <typename V>
class ConversionHelper<std::string, V, typename std::enable_if<std::is_integral<V>{} || std::is_floating_point<V>{}>::type> final {
public:
    std::string convert(const V& iValue) const { return std::to_string(iValue); }
};


} // namespace executor
} // namespace photon

