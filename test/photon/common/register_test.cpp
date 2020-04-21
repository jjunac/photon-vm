#include "photon/common/register.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace photon {
namespace common {

class RegisterTest : public ::testing::Test {
protected:
    RegisterTest() = default;
    ~RegisterTest() override = default;
};


TEST_F(RegisterTest, testStringRegistry) {
    Register aRegister {Type::STRING, 1u};

    EXPECT_FALSE(aRegister.isLongRegister());
    EXPECT_FALSE(aRegister.isDoubleRegister());
    EXPECT_TRUE(aRegister.isStringRegister());
    EXPECT_EQ(Type::STRING, aRegister.getType());
    EXPECT_EQ(1u, aRegister.getRegisterNumber());
}

}  // namespace common
}  // namespace photon