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

void test_projekcik__checking_file_access(void){
    chmod("./test/cant_open.txt", 0333);
    TEST_ASSERT_TRUE(checking_file_access("cant_open.txt", "./test") == -1);
}

void test_projekcik__amount_of_arguments(void){
    fprintf(stderr, "\n\nfun__amount_of_arguments():\n------------------\n");
    TEST_ASSERT_FALSE(amount_of_arguments(4, "./minicrom") == 0); 
    TEST_ASSERT_TRUE(amount_of_arguments(1, "./minicrom") != 0);
    TEST_ASSERT_TRUE(amount_of_arguments(3, "./minicrom") == 0);

}
void test_projekcik__checking_file_valid(void){
    
    fprintf(stderr, "\n\nfun__checking_file_valid():\n------------------\n");
    
    TEST_ASSERT_TRUE(checking_file_valid("./test/text.txt", "NULL|||") != NULL);
    TEST_ASSERT_TRUE(checking_file_valid("./test/text123.txt", "NULL|||") == NULL);

}
void test_projekcik__check_format(void){
    
    fprintf(stderr, "\n\nfun__check_format():\n------------------\n");
    
    FILE * file = checking_file_valid("./test/text.tx", "NULL|||");
    TEST_ASSERT_TRUE(check_format(file) == -1);
    if(file != NULL)
        fclose(file);

    FILE * test_file = checking_file_valid("./test/perfect.txt", "NULL|||");
    TEST_ASSERT_TRUE(check_format(test_file) > 0);
    if(test_file !=NULL)
        fclose(test_file);
    
    FILE * test_file2 = checking_file_valid("./test/perfect.txt", "NULL|||");
    TEST_ASSERT_TRUE(check_format(test_file2) == 2);
    if(test_file2 !=NULL)
        fclose(test_file2);

}
void test_projekcik__equal_namings(void){
    
    fprintf(stderr, "\n\nfun__equal_namings():\n------------------\n");
    
    TEST_ASSERT_TRUE( equal_namings("pol", "pol"));
    TEST_ASSERT_FALSE( equal_namings("epicki", "polak"));
    TEST_ASSERT_FALSE( equal_namings("poIak", "polak"));

}
void test_projekcik__length_of_file(void){
    
    fprintf(stderr, "\n\nfun__length_of_file():\n------------------\n");
    
    FILE * test_file2 = checking_file_valid("perfect.txt", "./test/");
    TEST_ASSERT_TRUE(check_format(test_file2) == 2);
    TEST_ASSERT_TRUE(length_of_file(test_file2) == 2);
    if(test_file2 != NULL)
        fclose(test_file2);
   
    FILE * file = checking_file_valid("text.tx","./test/");
    TEST_ASSERT_TRUE(check_format(file) == -1);
    TEST_ASSERT_FALSE(length_of_file(file) == -1);
    if(file != NULL)
        fclose(file);

}
void test_projekcik__get_array_of_tasks(void){
    
    fprintf(stderr, "\n\nfun__get_array_of_tasks():\n------------------\n");
    
    FILE * test_file2 = checking_file_valid("perfect.txt", "./test/");
    TEST_ASSERT_TRUE(test_file2 != NULL);
    task_temp * array;
    TEST_ASSERT_TRUE((array = get_array_of_tasks(test_file2)) != NULL);
    if(array != NULL)
        free_space(array);
    if(test_file2 != NULL)
        fclose(test_file2);
    
    FILE * test_file1 = checking_file_valid("text.txt", "./test/");
    TEST_ASSERT_TRUE(test_file1 != NULL);
    task_temp * array2;
    TEST_ASSERT_TRUE((array2 = get_array_of_tasks(test_file1)) == NULL);
    if(array2 != NULL)
        free_space(array2);
    if(test_file1 != NULL)
        fclose(test_file1);

    FILE * test_file4 = checking_file_valid("text.tx", "./test/");
    TEST_ASSERT_TRUE(test_file4 == NULL);
    task_temp * array4;
    TEST_ASSERT_TRUE((array4 = get_array_of_tasks(test_file4)) == NULL);
    if(array4 != NULL)
        free_space(array4);
    if(test_file4 != NULL)
        fclose(test_file4);
    
    FILE * test_file3 = checking_file_valid("./test/bad.txt", "NULL|||");
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
    
    TEST_ASSERT_TRUE(amount_of_pipes(" pol | lkok") == 2);
    TEST_ASSERT_FALSE(amount_of_pipes(" pol \\| lkok") == 4);
    TEST_ASSERT_TRUE(amount_of_pipes("lk | grep \\| | hihi") == 3);
}
void test_projekcik__string_to_array(void){
    char pol[] ="           never gonna give you up";
    int size_free[2];
    size_free[0] = 1;
    size_free[1] = 1;
    char ** array = string_to_array(pol, &size_free[0]);
    TEST_ASSERT_TRUE(strcmp(array[0], "never") == 0);
    TEST_ASSERT_TRUE(strcmp(array[1], "gonna") == 0);
    TEST_ASSERT_TRUE(strcmp(array[2], "give") == 0);
    TEST_ASSERT_TRUE(strcmp(array[3], "you") == 0);
    TEST_ASSERT_TRUE(strcmp(array[4], "up") == 0);
    TEST_ASSERT_TRUE(size_free[0] == 6);
    for(int i = 0 ; i < size_free[0]-1 ; ++i)
        free(array[i]);
    free(array);
}

// void test_projekcik__set_time_to_exec_temp__AND__set_time_to_sleep_before_exec(void){
//     time_t rawtime;
//     time (&rawtime);

//     struct tm * timeinfo = localtime(&rawtime);
//     task_temp arr[2];
//     arr[0].hours = timeinfo->tm_hour;
//     arr[1].hours = timeinfo->tm_hour;

//     arr[0].minutes = timeinfo->tm_min;
//     arr[1].minutes = timeinfo->tm_min;
//     if(timeinfo->tm_hour < 23)
//         ++arr[1].hours;

//     if(timeinfo->tm_min < 40){
//         arr[0].minutes += 20;
//         arr[1].minutes += 20;
//         set_time_to_exec_temp(arr, 2);
//         set_time_to_sleep_temp(arr, 2);
//         printf("\n\n----\nMinutes:%ld\n", arr[0].minutes);
//         printf("----Time_to_exec%ld", arr[0].time_to_exec);
//         TEST_ASSERT_TRUE(arr[0].time_to_exec <= 20*60 + timeinfo->tm_sec);
//         if(timeinfo->tm_hour < 23){
//             TEST_ASSERT_TRUE(arr[1].time_to_exec == 3600 + 60*20  - timeinfo->tm_sec);
//             TEST_ASSERT_TRUE(arr[1].time_to_sleep_before_exec <= 60 * 60 - timeinfo->tm_sec);
//         }
//         else{
//             TEST_ASSERT_TRUE(arr[1].time_to_exec == 20 * 60 - timeinfo->tm_sec);
//             TEST_ASSERT_TRUE(arr[1].time_to_exec == 0 + timeinfo->tm_sec);
//         }
//     }
//     else{
//         set_time_to_exec_temp(arr, 2);
//         set_time_to_sleep_temp(arr, 2);
//         TEST_ASSERT_TRUE(arr[0].time_to_exec == 0);
//         TEST_ASSERT_TRUE(arr[0].time_to_sleep_before_exec == 0);
//         if(timeinfo->tm_hour < 23){
//             //time_to_Exec
//             printf("MM:0-:::%d\n", timeinfo->tm_sec);
//             printf("GG:::::%ld", arr[1].time_to_exec);
//             TEST_ASSERT_TRUE(arr[1].time_to_exec == 60 * 60 - timeinfo->tm_sec);
//             //time_to_sleep
//             TEST_ASSERT_TRUE(arr[1].time_to_sleep_before_exec <= 60 * 60 - timeinfo->tm_sec);
//         }
//         else{
//             //time_to_Exec
//             TEST_ASSERT_TRUE(arr[1].time_to_exec == 0);
//             //time_to_sleep
//             TEST_ASSERT_TRUE(arr[1].time_to_sleep_before_exec == 0);
//         }
//     }
// }


void test_projekcik__preventing_pipe_at_end(void){
    TEST_ASSERT_TRUE(preventing_pipe_at_end("20:15:ls -l | wc -c |:2") == -1);
    TEST_ASSERT_TRUE(preventing_pipe_at_end("20:15:ls -l | wc -c |.:2") == 0);
    errno=0;
}

void test_projekcik__general_test(void){
    errno = 0;
    FILE * file = checking_file_valid("perfect.txt", "./test");
    TEST_ASSERT_TRUE(file != NULL);
    task_temp *ar;
    ar = get_array_of_tasks(file);
    TEST_ASSERT_TRUE(ar != NULL);
    int length = length_of_file();
    printf("%d\n\n", length);
    set_time_to_exec_temp(ar, length);
    qsort(ar, length, sizeof(*ar), comparator_temp);
    set_time_to_sleep_temp(ar, length);
    bool first_time =true;
    fclose(file);
    char p [200];
    getcwd(p, sizeof(p));
    strcat(p, "/test");
    // chdir("/");
    // execlp("ls", "ls", NULL);
    for(int i = 0; i < length ; ++i){
        // if((title_in_file(ar[i].original_command_from_file, "output.txt", first_time, "./test")) == -1)
            // exit(EXIT_FAILURE);
        pipe_fork_stuff(ar[i].program, ar[i].no_pipes, "output.txt", ar[i].state, ar, ar[i].original_command_from_file, p);
        first_time = false;
    }
    free_space(ar);
    // TEST_ASSERT_TRUE(ar == NULL);
}
#endif // TEST
