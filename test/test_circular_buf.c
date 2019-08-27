// DONE Add checks for empty
// DONE Add more tests for adding and removing data
// DONE Add returns 0 if buffer is full
// DONE Get returns 0 if buffer is empty    

#include "unity.h" 
#include "circular_buf.h"
#include <stdbool.h>

#define buf_size        8

static circular_buf_t circular_buf;
static circular_buf_t * p_circular_buf = &circular_buf;
static uint8_t p_buf_array[buf_size];

void setUp(void)
{
    p_circular_buf = circular_buf_create(buf_size, p_buf_array, p_circular_buf); 
}

void tearDown(void)
{
   circular_buff_destroy(p_circular_buf);
}

void test_buffer_returns_correct_sizeof_after_creation(void)
{
    uint8_t size = circular_buf_capacity(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(buf_size, size);
}

void test_buffer_index_starts_at_0(void)
{
    uint8_t index = circular_buf_get_index(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, index);
}

void test_outdex_starts_at_0(void)
{
    uint8_t outdex = circular_buf_get_outdex(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, outdex);
}

void test_add_will_increment_index_by_one(void)
{
    circular_buf_add(p_circular_buf, 'A');
    uint8_t index = circular_buf_get_index(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(1, index);
}

void test_get_will_increase_outdex_by_1(void)
{
    circular_buf_add(p_circular_buf, 'A');
    circular_buf_get(p_circular_buf);
    uint8_t index = circular_buf_get_outdex(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(1, index);
}

void test_put_and_get_will_return_same_values(void)
{
    uint8_t c;
    circular_buf_add(p_circular_buf, 'A');
    c = circular_buf_get(p_circular_buf);
    TEST_ASSERT_EQUAL('A', c);

    circular_buf_add(p_circular_buf, 'B');
    c = circular_buf_get(p_circular_buf);
    TEST_ASSERT_EQUAL('B', c);

    circular_buf_add(p_circular_buf, 'C');
    c = circular_buf_get(p_circular_buf);
    TEST_ASSERT_EQUAL('C', c);
}

void test_index_will_go_back_to_zero_after_overrunning(void)
{
    int i=0;
    uint8_t index = 0;
    for (i = 0; i < buf_size; i++)
    {
        circular_buf_add(p_circular_buf, 'A');
        circular_buf_get(p_circular_buf);
        // index = circular_buf_get_index(p_circular_buf);
        // TEST_ASSERT_EQUAL_HEX8(i+1, index); 
    }

    index = circular_buf_get_index(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, index); 
}

void test_outdex_will_go_back_to_zero_after_overrunning(void)
{
    int i=0;
    for (i = 0; i < buf_size; i++)
    {
        circular_buf_add(p_circular_buf, 'A');
        circular_buf_get(p_circular_buf);
    }

    uint8_t outdex = circular_buf_get_outdex(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, outdex); 
}

void test_is_empty_will_return_correct(void)
{
    bool is_empty = circular_buf_is_empty(p_circular_buf);
    TEST_ASSERT(is_empty);
}

void test_testing_is_full(void)
{
    int i=0;
    bool is_full = false;

    for (i = 0; i < buf_size; i++)
    {
        circular_buf_add(p_circular_buf, 'A');
        is_full = circular_buf_is_full(p_circular_buf);
        if (i < (buf_size - 2))
        {
            TEST_ASSERT_FALSE(is_full);
        }
    }
    is_full = circular_buf_is_full(p_circular_buf);
    TEST_ASSERT(is_full);
}

void test_is_empty(void)
{
    bool is_empty = false;

    circular_buf_add(p_circular_buf, 'A');
    is_empty = circular_buf_is_empty(p_circular_buf);
    TEST_ASSERT_FALSE(is_empty);

    circular_buf_get(p_circular_buf);
    is_empty = circular_buf_is_empty(p_circular_buf);
    TEST_ASSERT(is_empty);
}

void test_get_returns_0_if_buffer_is_empty(void)
{
    uint8_t c = 0;
    c = circular_buf_get(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, c);
}

void test_add_returns_0_if_buffer_is_full(void)
{
    uint8_t c = 0;
    uint8_t i = 0;
    for (i=0; i<buf_size; i++)
    {
        c = circular_buf_add(p_circular_buf, 'A');
    }
    c = circular_buf_add(p_circular_buf, 'A');
    TEST_ASSERT_EQUAL_HEX8(0, c);
}

void test_add_returns_1_if_not_full(void)
{
    uint8_t c = 0;
    uint8_t i = 0;
    for (i=0; i<buf_size; i++)
    {
        c = circular_buf_add(p_circular_buf, 'A');
        TEST_ASSERT_EQUAL_HEX8(1, c);
    }
}

void test_get_size_is_correct_at_0(void)
{
    uint8_t size = 0;
    size = circular_buf_size(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, size);
}

void test_get_size_is_correct_at_1(void)
{
    uint8_t size = 0;
    circular_buf_add(p_circular_buf, 'A');
    size = circular_buf_size(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(1, size);
}

void test_get_size_is_correct_after_add_and_remove(void)
{
    uint8_t size = 0;
    circular_buf_add(p_circular_buf, 'A');
    circular_buf_get(p_circular_buf);
    size = circular_buf_size(p_circular_buf);
    TEST_ASSERT_EQUAL_HEX8(0, size);
}

void test_filling_buf_not_full_while_below_capacity(void)
{
    int i = 0;
    for (i = 0; i < buf_size-1; i++)
    {
        circular_buf_add(p_circular_buf, 'A');
        TEST_ASSERT_FALSE(circular_buf_is_full(p_circular_buf));
    }
    circular_buf_add(p_circular_buf, 'A');
    TEST_ASSERT(circular_buf_is_full(p_circular_buf));
}