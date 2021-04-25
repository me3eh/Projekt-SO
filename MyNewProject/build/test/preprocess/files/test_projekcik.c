#include "src/projekcik.h"
#include "src/fun.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.0/vendor/unity/src/unity.h"




char PATH[200];







_Bool 

    first_time = 

                 1

                     ;

void setUp(void)

{

    if(first_time){

        getcwd(PATH, sizeof(PATH));

        strcat(PATH, "/test");

    first_time = 

                0

                     ;

    }

}



void tearDown(void)

{

}



void test_projekcik__checking_file_access(void){

    chmod("./test/cant_open.txt", 0333);

    do {if ((checking_file_access("cant_open.txt", "./test") == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(25)));}} while(0);

}



void test_projekcik__amount_of_arguments(void){

    fprintf(

           stderr

                 , "\n\nfun__amount_of_arguments():\n------------------\n");

    do {if (!(amount_of_arguments(4, "./minicrom") == 0)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(30)));}} while(0);

    do {if ((amount_of_arguments(1, "./minicrom") != 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(31)));}} while(0);

    do {if ((amount_of_arguments(3, "./minicrom") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(32)));}} while(0);



}

void test_projekcik__checking_file_valid(void){



    fprintf(

           stderr

                 , "\n\nfun__checking_file_valid():\n------------------\n");

    do {if ((checking_file_valid("text.txt", PATH) != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(38)));}} while(0);

    do {if ((checking_file_valid("text123.txt", PATH) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(39)));}} while(0);



}

void test_projekcik__check_format(void){



    fprintf(

           stderr

                 , "\n\nfun__check_format():\n------------------\n");



    FILE * file = checking_file_valid("text.tx", PATH);

    do {if ((check_format(file) == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(47)));}} while(0);

    if(file != 

              ((void *)0)

                  )

        fclose(file);



    FILE * test_file = checking_file_valid("perfect.txt", PATH);

    do {if ((check_format(test_file) > 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(52)));}} while(0);

    if(test_file !=

                  ((void *)0)

                      )

        fclose(test_file);



    FILE * test_file2 = checking_file_valid("perfect.txt", PATH);

    do {if ((check_format(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(57)));}} while(0);

    if(test_file2 !=

                   ((void *)0)

                       )

        fclose(test_file2);



}

void test_projekcik__equal_namings(void){



    fprintf(

           stderr

                 , "\n\nfun__equal_namings():\n------------------\n");



    do {if ((equal_namings("pol", "pol"))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(66)));}} while(0);

    do {if (!(equal_namings("epicki", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(67)));}} while(0);

    do {if (!(equal_namings("poIak", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(68)));}} while(0);



}

void test_projekcik__length_of_file(void){



    fprintf(

           stderr

                 , "\n\nfun__length_of_file():\n------------------\n");



    FILE * test_file2 = checking_file_valid("perfect.txt", PATH);

    do {if ((check_format(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(76)));}} while(0);

    do {if ((length_of_file(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(77)));}} while(0);

    if(test_file2 != 

                    ((void *)0)

                        )

        fclose(test_file2);



    FILE * file = checking_file_valid("text.tx",PATH);

    do {if ((check_format(file) == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(82)));}} while(0);

    do {if (!(length_of_file(file) == -1)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(83)));}} while(0);

    if(file != 

              ((void *)0)

                  )

        fclose(file);



}

void test_projekcik__get_array_of_tasks(void){



    fprintf(

           stderr

                 , "\n\nfun__get_array_of_tasks():\n------------------\n");



    FILE * test_file2 = checking_file_valid("perfect.txt", PATH);

    do {if ((test_file2 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(93)));}} while(0);

    task_temp * array;

    do {if (((array = get_array_of_tasks(test_file2)) != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(95)));}} while(0);

    if(array != 

               ((void *)0)

                   )

        free_space(array);

    if(test_file2 != 

                    ((void *)0)

                        )

        fclose(test_file2);



    FILE * test_file1 = checking_file_valid("text.txt", PATH);

    do {if ((test_file1 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(102)));}} while(0);

    task_temp * array2;

    do {if (((array2 = get_array_of_tasks(test_file1)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(104)));}} while(0);

    if(array2 != 

                ((void *)0)

                    )

        free_space(array2);

    if(test_file1 != 

                    ((void *)0)

                        )

        fclose(test_file1);



    FILE * test_file4 = checking_file_valid("text.tx", PATH);

    do {if ((test_file4 == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(111)));}} while(0);

    task_temp * array4;

    do {if (((array4 = get_array_of_tasks(test_file4)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(113)));}} while(0);

    if(array4 != 

                ((void *)0)

                    )

        free_space(array4);

    if(test_file4 != 

                    ((void *)0)

                        )

        fclose(test_file4);



    FILE * test_file3 = checking_file_valid("bad.txt", PATH);

    do {if ((test_file3 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(120)));}} while(0);

    task_temp * array3;

    do {if (((array3 = get_array_of_tasks(test_file3)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(122)));}} while(0);

    if(array3 != 

                ((void *)0)

                    )

        free_space(array3);

    if(test_file3 != 

                    ((void *)0)

                        )

        fclose(test_file3);

}

void test_projekcik__amount_of_pipes(void){

    fprintf(

           stderr

                 , "\n\nfun__amount_of_pipes():\n------------------\n");



    do {if ((amount_of_pipes(" pol | lkok") == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(131)));}} while(0);

    do {if (!(amount_of_pipes(" pol \\| lkok") == 4)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(132)));}} while(0);

    do {if ((amount_of_pipes("lk | grep \\| | hihi") == 3)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(133)));}} while(0);

}

void test_projekcik__string_to_array(void){

    char pol[] ="           never gonna give you up";

    int size_free[2];

    size_free[0] = 1;

    size_free[1] = 1;

    char ** array = string_to_array(pol, &size_free[0]);

    do {if ((strcmp(array[0], "never") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(141)));}} while(0);

    do {if ((strcmp(array[1], "gonna") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(142)));}} while(0);

    do {if ((strcmp(array[2], "give") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(143)));}} while(0);

    do {if ((strcmp(array[3], "you") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(144)));}} while(0);

    do {if ((strcmp(array[4], "up") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(145)));}} while(0);

    do {if ((size_free[0] == 6)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(146)));}} while(0);

    for(int i = 0 ; i < size_free[0]-1 ; ++i)

        free(array[i]);

    free(array);

}

void test_projekcik__preventing_pipe_at_end(void){

    do {if ((preventing_pipe_at_end("20:15:ls -l | wc -c |:2") == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(207)));}} while(0);

    do {if ((preventing_pipe_at_end("20:15:ls -l | wc -c |.:2") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(208)));}} while(0);

    

   (*__errno_location ())

        =0;

}



void test_projekcik__general_test(void){







    

   (*__errno_location ()) 

         = 0;

    FILE * file = checking_file_valid("perfect.txt", PATH);

    do {if ((file != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(218)));}} while(0);

    task_temp *ar;

    ar = get_array_of_tasks(file);

    do {if ((ar != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(221)));}} while(0);

    int length = length_of_file();

    printf("%d\n\n", length);

    set_time_to_exec_temp(ar, length);

    qsort(ar, length, sizeof(*ar), comparator_temp);

    set_time_to_sleep_temp(ar, length);

    

   _Bool 

        first_time =

                    1

                        ;

    fclose(file);

    for(int i = 0; i < length ; ++i){

        if((title_in_file(ar[i].original_command_from_file, "output.txt", first_time, PATH)) == -1)

            exit(

                1

                            );

        pipe_fork_stuff(ar[i].program, ar[i].no_pipes, "output.txt", ar[i].state, ar, ar[i].original_command_from_file, PATH);

        first_time = 

                    0

                         ;

    }

    free_space(ar);

}
