#include "pch.h"
#include  "gtest/gtest.h"
#include "../AnyBarWin/Protocol/Protocol.h"

TEST(PackMessageTest, IconCommand)
{
    std::string parameter = "red";
    auto cmd = Protocol::Icon;
    auto data = packMessage(cmd, parameter);

    int32_t resCmd;
    memcpy(&resCmd, data.data(), sizeof(resCmd));
    EXPECT_EQ(resCmd, cmd);

    int32_t length;
    memcpy(&length, data.data() + sizeof(int32_t), sizeof(length));
    EXPECT_EQ(length, parameter.length());

    char buffer[1024]{};
    memcpy(buffer, data.data() + sizeof(int32_t) * 2, length);
    EXPECT_STREQ(parameter.c_str(), buffer);

}

TEST(PackMessageTest, PathCommand)
{
    std::string parameter = R"(C:\User\pics\img.jpeg)";
    auto cmd = Protocol::Path;
    auto data = packMessage(cmd, parameter);

    int32_t resCmd;
    memcpy(&resCmd, data.data(), sizeof(resCmd));
    EXPECT_EQ(resCmd, cmd);

    int32_t length;
    memcpy(&length, data.data() + sizeof(int32_t), sizeof(length));
    EXPECT_EQ(length, parameter.length());

    char buffer[1024]{};
    memcpy(buffer, data.data() + sizeof(int32_t) * 2, length);
    EXPECT_STREQ(parameter.c_str(), buffer);

}

TEST(PackMessageTest, QuitCommand)
{
    std::string parameter = "";
    auto cmd = Protocol::Quit;
    auto data = packMessage(cmd, parameter);

    int32_t resCmd;
    memcpy(&resCmd, data.data(), sizeof(resCmd));
    EXPECT_EQ(resCmd, cmd);

    int32_t length;
    memcpy(&length, data.data() + sizeof(int32_t), sizeof(length));
    EXPECT_EQ(length, parameter.length());

    char buffer[1024]{};
    memcpy(buffer, data.data() + sizeof(int32_t) * 2, length);
    EXPECT_STREQ(parameter.c_str(), buffer);
}

TEST(UnpackMessageTest, NormalCommand)
{
    std::string parameter = "red";
    auto cmd = Protocol::Icon;
    auto data = Protocol::packMessage(cmd, parameter);

    auto result = Protocol::unpackMessage(data.data(), data.size());
    EXPECT_EQ(parameter, result.second);
    EXPECT_EQ(cmd, result.first);
}

TEST(UnpackMessageTest, BadCommand)
{
    std::string parameter = "abc";
    auto cmd = Protocol::Icon;
    auto data = Protocol::packMessage(cmd, parameter);

    EXPECT_THROW(Protocol::unpackMessage(data.data(), data.size() - 10), std::runtime_error);
}

