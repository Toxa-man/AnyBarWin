#include "pch.h"
#include  "gtest/gtest.h"
#include "../AnyBarWinClient/ClientLogic.h"
#include "NamedPipeWin.h"
#include <thread>


void shutdownServer()
{
    using namespace std::chrono_literals;
    NamedPipeWin pipe(Protocol::pipeName, NamedPipe::Write);
    pipe.write(Protocol::packMessage(Protocol::Quit, ""));
    std::this_thread::sleep_for(2s);
}

TEST(ToLowerTest, SwitchStringRegister)
{
    std::string testStr = "abcDEFbgh";
    toLower(testStr);

    EXPECT_EQ(testStr, "abcdefbgh");
}

TEST(fileFormatParseTest, InvalidFormat)
{
    std::string invalidName = "abc";
    EXPECT_THROW(checkFileFormat(invalidName), std::invalid_argument);
}

TEST(fileFormatParseTest, InvalidExtension)
{
    std::string invalidName = "abc.jpeg";
    EXPECT_THROW(checkFileFormat(invalidName), std::invalid_argument);
}

TEST(fileFormatParseTest, ValidFormat)
{
    std::string invalidName = "abc.ico";
    EXPECT_NO_THROW(checkFileFormat(invalidName));
}

TEST(ServerStartTest, StartServer)
{
    EXPECT_EQ(startServer(), true);
    shutdownServer();
}

TEST(ServerStatusTest, ServerIsRunning)
{
    EXPECT_EQ(checkIfServerIsRunning(), false);
    startServer();
    EXPECT_EQ(checkIfServerIsRunning(), true);


    shutdownServer();
}

TEST(ServerStatusTest, ServerShutdown)
{
    EXPECT_EQ(checkIfServerIsRunning(), false);
    startServer();
    EXPECT_EQ(checkIfServerIsRunning(), true);

    shutdownServer();

    EXPECT_EQ(checkIfServerIsRunning(), false);
}

TEST(OneArgumentTest, iconParamter)
{
    auto[cmd, parameter] = parseOneArgument("red");
    EXPECT_EQ(cmd, Protocol::Icon);
    EXPECT_EQ(parameter, std::to_string(Protocol::Red));

    EXPECT_EQ(checkIfServerIsRunning(), true);

    shutdownServer();

}

TEST(OneArgumentTest, StartParameter)
{
    auto[cmd, parameter] = parseOneArgument("start");
    EXPECT_EQ(cmd, Protocol::Invalid);
    EXPECT_EQ(parameter, "");

    EXPECT_EQ(checkIfServerIsRunning(), true);

    shutdownServer();

}

TEST(OneArgumentTest, QuitParameter)
{
    auto[cmd, parameter] = parseOneArgument("quit");
    EXPECT_EQ(cmd, Protocol::Quit);
    EXPECT_EQ(parameter, "");
}

TEST(TwoArgumentTest, PathParameter)
{
    auto[cmd, parameter] = parseOneArgument("abd.ico");
    EXPECT_EQ(cmd, Protocol::Path);
    EXPECT_EQ(parameter, "abd.ico");

    shutdownServer();

}