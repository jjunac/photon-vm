#pragma once

#include <vector>
#include <string>

namespace strix {
namespace executor {


struct Return {
    bool isEnd;
    int exitCode;

    Return(bool iIsEnd = false, int iExitCode = 0) : isEnd(iIsEnd), exitCode(iExitCode) {};
};

} // namespace executor
} // namespace strix

