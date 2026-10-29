#include <gtest/gtest.h>
#include <regex>
#include "CommandProcessor.h"

// Ping
TEST(CommandProcessorTest, PingUpper) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("PING"), "pong");
}

TEST(CommandProcessorTest, PingLower) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("ping"), "pong");
}

TEST(CommandProcessorTest, PingRandom) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("PiNg"), "pong");
}

TEST(CommandProcessorTest, PingSpaces) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("    PiNg     "), "pong");
}


// Time
TEST(CommandProcessorTest, TimeUpper) {
    CommandProcessor cp;
    std::regex time_pattern(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
    EXPECT_TRUE(std::regex_match(cp.process_command("TIME"), time_pattern));
}

TEST(CommandProcessorTest, TimeLower) {
    CommandProcessor cp;
    std::regex time_pattern(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
    EXPECT_TRUE(std::regex_match(cp.process_command("time"), time_pattern));
}

TEST(CommandProcessorTest, TimeRandom) {
    CommandProcessor cp;
    std::regex time_pattern(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
    EXPECT_TRUE(std::regex_match(cp.process_command("TimE"), time_pattern));
}

TEST(CommandProcessorTest, TimeSpaces) {
    CommandProcessor cp;
    std::regex time_pattern(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
    EXPECT_TRUE(std::regex_match(cp.process_command("        TimE "), time_pattern));
}

// Echo
TEST(CommandProcessorTest, EchoOneLetter) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("Echo n"), "n");
}

TEST(CommandProcessorTest, EchoOneLetterBig) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("Echo N"), "N");
}

TEST(CommandProcessorTest, EchoWord) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("Echo word"), "word");
}

TEST(CommandProcessorTest, EchoWords) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("Echo word word banana"), "word word banana");
}

TEST(CommandProcessorTest, EchoLower) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("echo haha"), "haha");
}

TEST(CommandProcessorTest, EchoUpper) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("ECHO HAHAHAHH check join"), "HAHAHAHH check join");
}

TEST(CommandProcessorTest, EchoSpaces) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("        Echo  djsidjisdsdsd 4545 uisudis   kkk  "), "djsidjisdsdsd 4545 uisudis   kkk");
}

// unknown commands
TEST(CommandProcessorTest, Unknown1) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("ec ho"), "unknown command");
}

TEST(CommandProcessorTest, Unknown2) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("pong"), "unknown command");
}

TEST(CommandProcessorTest, Unknown3) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("pi ng"), "unknown command");
}

TEST(CommandProcessorTest, Unknown4) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("time e"), "unknown command");
}

TEST(CommandProcessorTest, Unknown5) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("time echo"), "unknown command");
}

TEST(CommandProcessorTest, Unknown6) {
    CommandProcessor cp;
    EXPECT_EQ(cp.process_command("ping pong"), "unknown command");
}
