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

void test_projekcik_checkingfunction__amount_of_arguments(void)
{
    TEST_ASSERT_FALSE(amount_of_arguments(4, "./minicrom") == 0); 
    TEST_ASSERT_TRUE(amount_of_arguments(1, "./minicrom") != 0);
    TEST_ASSERT_TRUE(amount_of_arguments(3, "./minicrom") == 0);
}
void test_projekcik_checkingfunction__checking_file_valid(void){
    // execlp("ls","ls", NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text.txt") != NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text123.txt") == NULL);
}
void test_projekcik_checkingfunction__check_format(void){
    // execlp("ls","ls", NULL);
    FILE * file = checking_file_valid("./test/text.txt");
    TEST_ASSERT_TRUE(check_format(file) == -1);
    FILE * test_file = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file) > 0);
}
void test_projekcik_checking_function__equal_namings(void){
    TEST_ASSERT_TRUE( equal_namings("pol", "pol"));
    TEST_ASSERT_FALSE( equal_namings("epicki", "polak"));
    TEST_ASSERT_FALSE( equal_namings("poIak", "polak"));
}

#endif // TEST
