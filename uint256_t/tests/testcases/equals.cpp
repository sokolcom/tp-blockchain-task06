#include <gtest/gtest.h>

#include "uint256_t.h"

TEST(Comparison, equals){
    EXPECT_EQ( (uint256_t(0xdeadbeefULL) == uint256_t(0xdeadbeefULL)), true);
    EXPECT_EQ(!(uint256_t(0xdeadbeefULL) == uint256_t(0xfee1baadULL)), true);
}

TEST(External, equals){
    const bool     t   = true;
    const bool     f   = false;
    const uint8_t  u8  = 0xaaULL;
    const uint16_t u16 = 0xaaaaULL;
    const uint32_t u32 = 0xaaaaaaaaULL;
    const uint64_t u64 = 0xaaaaaaaaaaaaaaaaULL;

    EXPECT_EQ(t,   uint256_t(t));
    EXPECT_EQ(f,   uint256_t(f));
    EXPECT_EQ(u8,  uint256_t(u8));
    EXPECT_EQ(u16, uint256_t(u16));
    EXPECT_EQ(u32, uint256_t(u32));
    EXPECT_EQ(u64, uint256_t(u64));
}
