
#include <iostream>
#include<string>
#include <gtest/gtest.h>

std::string ulld_to_b(uint64_t i) {
    return std::bitset<64>(i).to_string();
}

TEST(TestCase, test1) {
    EXPECT_STREQ("10010", ulld_to_b(18ULL).c_str());
}
TEST(TestCase, test2) {
    EXPECT_STREQ("00000000000000000000000000010010", ulld_to_b(18ULL).c_str());
}
TEST(TestCase, test3) {
    EXPECT_STREQ("0000000000000000000000000000000000000000000000000000000000010010", ulld_to_b(18ULL).c_str());
}
int main(int argc,char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}ma
