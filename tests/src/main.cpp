/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    06.04.2024
 */

#include <gtest/gtest.h>

auto main(int argc, char** argv) -> int
{
    using ::testing::InitGoogleTest, ::testing::UnitTest;
    InitGoogleTest(&argc, argv);
    return UnitTest::GetInstance()->Run();
}
