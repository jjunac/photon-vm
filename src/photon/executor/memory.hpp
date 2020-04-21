#pragma once

#include <unordered_map>
#include <string>

namespace photon {
namespace executor {


class Memory final {
public:
    Memory() = default;
    ~Memory() = default;

    template <typename T>
    const T& getValue(uint32_t iRegisterNumber) const;
    template <typename T>
    T& accessValue(uint32_t iRegisterNumber);

private:
    std::unordered_map<uint32_t, long> _longRegisters;
    std::unordered_map<uint32_t, double> _doubleRegisters;
    std::unordered_map<uint32_t, std::string> _stringRegisters;
};

template <>
inline const long& Memory::getValue<long>(uint32_t iRegisterNumber) const { return _longRegisters.at(iRegisterNumber); }
template <>
inline long& Memory::accessValue<long>(uint32_t iRegisterNumber) { return _longRegisters[iRegisterNumber]; }

template <>
inline const double& Memory::getValue<double>(uint32_t iRegisterNumber) const { return _doubleRegisters.at(iRegisterNumber); }
template <>
inline double& Memory::accessValue<double>(uint32_t iRegisterNumber) { return _doubleRegisters[iRegisterNumber]; }

template <>
inline const std::string& Memory::getValue<std::string>(uint32_t iRegisterNumber) const { return _stringRegisters.at(iRegisterNumber); }
template <>
inline std::string& Memory::accessValue<std::string>(uint32_t iRegisterNumber) { return _stringRegisters[iRegisterNumber]; }

} // namespace executor
} // namespace photon

