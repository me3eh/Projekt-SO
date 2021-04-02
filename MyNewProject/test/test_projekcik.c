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
    fprintf(stderr, "\n\nfun__amount_of_arguments():\n------------------\n");
    TEST_ASSERT_FALSE(amount_of_arguments(4, "./minicrom") == 0); 
    TEST_ASSERT_TRUE(amount_of_arguments(1, "./minicrom") != 0);
    TEST_ASSERT_TRUE(amount_of_arguments(3, "./minicrom") == 0);

}
void test_projekcik_checkingfunction__checking_file_valid(void){
    
    fprintf(stderr, "\n\nfun__checking_file_valid():\n------------------\n");
    
    TEST_ASSERT_TRUE(checking_file_valid("./test/text.txt") != NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text123.txt") == NULL);

}
void test_projekcik_checkingfunction__check_format(void){
    
    fprintf(stderr, "\n\nfun__check_format():\n------------------\n");
    
    FILE * file = checking_file_valid("./test/text.tx");
    TEST_ASSERT_TRUE(check_format(file) == -1);
    if(file != NULL)
        fclose(file);

    FILE * test_file = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file) > 0);
    if(test_file !=NULL)
        fclose(test_file);
    
    FILE * test_file2 = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file2) == 2);
    if(test_file2 !=NULL)
        fclose(test_file2);

}
void test_projekcik_checking_function__equal_namings(void){
    
    fprintf(stderr, "\n\nfun__equal_namings():\n------------------\n");
    
    TEST_ASSERT_TRUE( equal_namings("pol", "pol"));
    TEST_ASSERT_FALSE( equal_namings("epicki", "polak"));
    TEST_ASSERT_FALSE( equal_namings("poIak", "polak"));

}
void test_projekcik_checking_function__length_of_file(void){
    
    fprintf(stderr, "\n\nfun__length_of_file():\n------------------\n");
    
    FILE * test_file2 = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(check_format(test_file2) == 2);
    TEST_ASSERT_TRUE(length_of_file(test_file2) == 2);
    if(test_file2 != NULL)
        fclose(test_file2);
   
    FILE * file = checking_file_valid("./test/text.tx");
    TEST_ASSERT_TRUE(check_format(file) == -1);
    TEST_ASSERT_FALSE(length_of_file(file) == -1);
    if(file != NULL)
        fclose(file);

}
void test_projekcik__get_array_of_tasks(void){
    
    fprintf(stderr, "\n\nfun__get_array_of_tasks():\n------------------\n");
    
    FILE * test_file2 = checking_file_valid("./test/perfect.txt");
    TEST_ASSERT_TRUE(test_file2 != NULL);
    task_temp * array;
    TEST_ASSERT_TRUE((array = get_array_of_tasks(test_file2)) != NULL);
    if(array != NULL)
        free_space(array);
    if(test_file2 != NULL)
        fclose(test_file2);
    
    FILE * test_file1 = checking_file_valid("./test/text.txt");
    TEST_ASSERT_TRUE(test_file1 != NULL);
    task_temp * array2;
    TEST_ASSERT_TRUE((array2 = get_array_of_tasks(test_file1)) == NULL);
    if(array2 != NULL)
        free_space(array2);
    if(test_file1 != NULL)
        fclose(test_file1);

    FILE * test_file4 = checking_file_valid("./test/text.tx");
    TEST_ASSERT_TRUE(test_file4 == NULL);
    task_temp * array4;
    TEST_ASSERT_TRUE((array4 = get_array_of_tasks(test_file4)) == NULL);
    if(array4 != NULL)
        free_space(array4);
    if(test_file4 != NULL)
        fclose(test_file4);
    
    FILE * test_file3 = checking_file_valid("./test/bad.txt");
    TEST_ASSERT_TRUE(test_file3 != NULL);
    task_temp * array3;
    TEST_ASSERT_TRUE((array3 = get_array_of_tasks(test_file3)) == NULL);
    if(array3 != NULL)
        free_space(array3);
    if(test_file3 != NULL)
        fclose(test_file3);
}
void test_projekcik__amount_of_pipes(void){
    fprintf(stderr, "\n\nfun__amount_of_pipes():\n------------------\n");
    fprintf(stderr, "-->%d",amount_of_pipes("pol  lkok"));
    fprintf(stderr, "===>%d",amount_of_pipes("pol | lkok"));
    fprintf(stderr, "===>%d",amount_of_pipes("pol \\| lkok"));
    
    TEST_ASSERT_TRUE(amount_of_pipes(" pol | lkok") == 2);
    // fprintf(stderr, "%d",amount_of_pipes(" pol | lkok"));
    // TEST_ASSERT_FALSE(amount_of_pipes(" pol \| lkok") == 4);
    // TEST_ASSERT_TRUE(amount_of_pipes("lk | grep \| | hihi") == 3);
    // printf("%d\n",amount_of_pipes("lk | grep \| | hihi"));
    // printf("%d",amount_of_pipes("lk | grep | hihi | pol | d"));

    // TEST_ASSERT_TRUE(amount_of_pipes("lk | grep \| | hihi") == 3);
}
#endif // TEST
