#ifdef TEST

#include "unity.h"
#include "fun.h"
#include "projekcik.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_projekcik_inserting_values(void)
{
    TEST_ASSERT_FALSE(amount_of_arguments(4, "./minicrom") == 0); 
    TEST_ASSERT_TRUE(amount_of_arguments(1, "./minicrom") != 0);
}

void test_projekcik_inserting_values2(void){
    TEST_ASSERT_TRUE(amount_of_arguments(3, "./minicrom") == 0);
}

#endif // TEST
