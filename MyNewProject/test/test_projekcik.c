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
    perror("1\n");

}
void test_projekcik_checkingfunction__checking_file_valid(void){
    TEST_ASSERT_TRUE(checking_file_valid("./test/text.txt") != NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text123.txt") == NULL);
    perror("2\n");

}
void test_projekcik_checkingfunction__check_format(void){
    // FILE * file = checking_file_valid("./test/text.tx");
    // TEST_ASSERT_TRUE(check_format(file) == -1);
    // fclose(file);
    // perror("3\n");
    FILE * test_file = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file) > 0);
    fclose(test_file);
    perror("3\n");
    FILE * test_file2 = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file2) == 2);
    fclose(test_file2);
    perror("3\n");

}
void test_projekcik_checking_function__equal_namings(void){
    TEST_ASSERT_TRUE( equal_namings("pol", "pol"));
    TEST_ASSERT_FALSE( equal_namings("epicki", "polak"));
    TEST_ASSERT_FALSE( equal_namings("poIak", "polak"));
    perror("4\n");

}
void test_projekcik_checking_function__length_of_file(void){
    FILE * test_file2 = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file2) == 2);
    TEST_ASSERT_TRUE(length_of_file(test_file2) == 2);
    fclose(test_file2);
    // FILE * file = checking_file_valid("./test/text.tx");
    // TEST_ASSERT_TRUE(check_format(file) == -1);
    // TEST_ASSERT_FALSE(length_of_file(file) == -1);
    // fclose(file);
    perror("5\n");

}
void test_projekcik__get_array_of_tasks(void){
    FILE * test_file2 = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(test_file2 != NULL);
    task_temp * array;
    TEST_ASSERT_TRUE((array = get_array_of_tasks(test_file2)) != NULL);
    free_space(array);
    fclose(test_file2);
    perror("6\n");
    // FILE * test_file1 = checking_file_valid("./test/text.txt");
    // TEST_ASSERT_TRUE(test_file1 != NULL);
    // task_temp * array2;
    // TEST_ASSERT_TRUE((array2 = get_array_of_tasks(test_file1)) == NULL);
    // free_space(array2);
}
#endif // TEST
