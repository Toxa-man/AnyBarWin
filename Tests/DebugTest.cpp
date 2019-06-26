

#include "gtest/gtest.h"
#include "../AnyBarWin/Utils.h"

static std::string globRes;

void __stdcall mockDebug(const char* str)
{
    globRes += str;
}

TEST(DebugTest, multipleTypes)
{
    Utils::Details::OSPrintFunc = mockDebug;
    Utils::debug("abc", 25, 87.374, 'z');
    if (Utils::Details::loggingEnabled) {
        globRes.erase(0, globRes.find(']') + 2);
    }
    EXPECT_EQ(std::string{ "abc2587.374000z\n" }, globRes);

}