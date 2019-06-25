#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE 0

#include "gtest/gtest.h"
#include "../AnyBarWin/Utils.h"

#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE 0

static std::string globRes;

void mockDebug(const char* str)
{
    globRes = str;
}

TEST(DebugTest, multipleTypes)
{
    // Utils::Details::debugFunc = mockDebug;
    // Utils::debug("abc", 25, 87.374, 'z');
    // EXPECT_EQ(std::string{ "abc2487.374000z" }, globRes);

}