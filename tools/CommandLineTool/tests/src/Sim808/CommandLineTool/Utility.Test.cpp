/**
 * @file    Utility.Test.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    08.04.2024
 */

#include <gtest/gtest.h>

#include <Sim808/CommandLineTool/Utility.hpp>

TEST(CommandLineTool_Core_Utility, ParseKeyValuePairs)
{
    using Sim808::CommandLineTool::Utility;
    std::string_view str { "a=\"abc\" b1=\"a\" c=\"x2x\"" };
    const auto key_values = Utility::extractKeyValuePairs(str);
    ASSERT_EQ(key_values.size(), 3U);
    ASSERT_TRUE(key_values.contains("a"));
    ASSERT_TRUE(key_values.contains("b1"));
    ASSERT_TRUE(key_values.contains("c"));
    EXPECT_EQ(key_values.at("a"), "abc");
    EXPECT_EQ(key_values.at("b1"), "a");
    EXPECT_EQ(key_values.at("c"), "x2x");
}
