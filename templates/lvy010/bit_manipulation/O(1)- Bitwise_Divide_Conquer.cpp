class Solution {
    static constexpr uint32_t m0 = 0x55555555; // 01010101 ...
    static constexpr uint32_t m1 = 0x33333333; // 00110011 ...
    static constexpr uint32_t m2 = 0x0f0f0f0f; // 00001111 ...
    static constexpr uint32_t m3 = 0x00ff00ff; // 00000000111111110000000011111111

    uint32_t reverseBits32(uint32_t n) {
        n = n>>1&m0 | (n&m0)<<1; // 交换相邻位
        n = n>>2&m1 | (n&m1)<<2; // 两个两个交换
        n = n>>4&m2 | (n&m2)<<4; // 四个四个交换
        n = n>>8&m3 | (n&m3)<<8; // 八个八个交换
        return n>>16 | n<<16;    // 交换高低 16 位
    }

public:
    int reverseBits(int n) {
        return reverseBits32(n);
    }
};
