#include "unity.h"
#include "crc8.h"
#include "stdbool.h"

#define POLYNOMIAL 0x1c

Sarwate engine;

void setUp()
{
    init_sarwate(&engine, POLYNOMIAL);
}

void test_table(void)
{
    bool test_result = true;
    unsigned char expected[0x100] = {
        0, 28, 56, 36, 112, 108, 72, 84, 224, 252, 216, 196, 144, 140, 168, 180, 220,
        192, 228, 248, 172, 176, 148, 136, 60, 32, 4, 24, 76, 80, 116, 104, 164,
        184, 156, 128, 212, 200, 236, 240, 68, 88, 124, 96, 52, 40, 12, 16, 120,
        100, 64, 92, 8, 20, 48, 44, 152, 132, 160, 188, 232, 244, 208, 204, 84,
        72, 108, 112, 36, 56, 28, 0, 180, 168, 140, 144, 196, 216, 252, 224, 136,
        148, 176, 172, 248, 228, 192, 220, 104, 116, 80, 76, 24, 4, 32, 60, 240, 236,
        200, 212, 128, 156, 184, 164, 16, 12, 40, 52, 96, 124, 88, 68, 44, 48, 20, 8,
        92, 64, 100, 120, 204, 208, 244, 232, 188, 160, 132, 152, 168, 180, 144, 140,
        216, 196, 224, 252, 72, 84, 112, 108, 56, 36, 0, 28, 116, 104, 76, 80, 4, 24,
        60, 32, 148, 136, 172, 176, 228, 248, 220, 192, 12, 16, 52, 40, 124, 96, 68, 88,
        236, 240, 212, 200, 156, 128, 164, 184, 208, 204, 232, 244, 160, 188, 152, 132,
        48, 44, 8, 20, 64, 92, 120, 100, 252, 224, 196, 216, 140, 144, 180, 168, 28, 0,
        36, 56, 108, 112, 84, 72, 32, 60, 24, 4, 80, 76, 104, 116, 192, 220, 248, 228,
        176, 172, 136, 148, 88, 68, 96, 124, 40, 52, 16, 12, 184, 164, 128, 156, 200, 212,
        240, 236, 132, 152, 188, 160, 244, 232, 204, 208, 100, 120, 92, 64, 20, 8, 44, 48};
    for (uint32_t i = 0; i < 0x100; ++i)
    {
        if (engine.table[i] != expected[i])
        {
            test_result = false;
            break;
        }
    }
    TEST_ASSERT(test_result);
}

void test_buildCRC8_one_byte(void)
{
    unsigned char result;
    unsigned char test_case[1] = {0x00};
    result = buildCRC8(&engine, &test_case[0], 1);
    TEST_ASSERT_EQUAL_HEX16(result, 0x00);
}

void test_buildCRC8_many_bytes_all_in_cero(void)
{
    unsigned char test_case[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char expected = 0x00;
    unsigned char computed = buildCRC8(&engine, &test_case[0], 9);
    TEST_ASSERT_EQUAL_HEX16(expected, computed);
}

void test_buildCRC8_many_bytes(void)
{
    unsigned char test_case[9] = {0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31}; // "111111111"
    unsigned char expected = 0x70;
    unsigned char computed = buildCRC8(&engine, &test_case[0], 9);
    TEST_ASSERT_EQUAL_HEX16(expected, computed);
}

void test_invalid_buffer_size(void)
{
    unsigned char test_case[9] = {0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31}; // "111111111"
    unsigned char expected = 0xfc;
    unsigned char computed = buildCRC8(&engine, &test_case[0], 8);
    TEST_ASSERT_EQUAL_HEX16(expected, computed);
}