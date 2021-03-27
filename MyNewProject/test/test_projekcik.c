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
    TEST_ASSERT_TRUE(amount_of_arguments(3, "./minicrom") == 0);
}

void test_projekcik_is_file_valid(void){
    // execlp("ls","ls", NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text.txt", false) != NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text123.txt", false) == NULL);
}

void test_projekcik_is_file_valid(void){
    // execlp("ls","ls", NULL);
    FILE * file = checking_file_valid("./test/text.txt", false);
    TEST_ASSERT_TRUE(are_3colons_presented(file) == false);
}

#endif // TEST
