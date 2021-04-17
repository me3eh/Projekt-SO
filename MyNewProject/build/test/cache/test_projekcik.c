#include "src/projekcik.h"
#include "src/fun.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.0/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



void test_projekcik_checkingfunction__amount_of_arguments(void)

{

    fprintf(

           stderr

                 , "\n\nfun__amount_of_arguments():\n------------------\n");

    do {if (!(amount_of_arguments(4, "./minicrom") == 0)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(18)));}} while(0);

    do {if ((amount_of_arguments(1, "./minicrom") != 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);

    do {if ((amount_of_arguments(3, "./minicrom") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(20)));}} while(0);



}

void test_projekcik_checkingfunction__checking_file_valid(void){



    fprintf(

           stderr

                 , "\n\nfun__checking_file_valid():\n------------------\n");



    do {if ((checking_file_valid("./test/text.txt") != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(27)));}} while(0);

    do {if ((checking_file_valid("./test/text123.txt") == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(28)));}} while(0);



}

void test_projekcik_checkingfunction__check_format(void){



    fprintf(

           stderr

                 , "\n\nfun__check_format():\n------------------\n");



    FILE * file = checking_file_valid("./test/text.tx");

    do {if ((check_format(file) == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(36)));}} while(0);

    if(file != 

              ((void *)0)

                  )

        fclose(file);



    FILE * test_file = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file) > 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(41)));}} while(0);

    if(test_file !=

                  ((void *)0)

                      )

        fclose(test_file);



    FILE * test_file2 = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(46)));}} while(0);

    if(test_file2 !=

                   ((void *)0)

                       )

        fclose(test_file2);



}

void test_projekcik_checking_function__equal_namings(void){



    fprintf(

           stderr

                 , "\n\nfun__equal_namings():\n------------------\n");



    do {if ((equal_namings("pol", "pol"))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(55)));}} while(0);

    do {if (!(equal_namings("epicki", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(56)));}} while(0);

    do {if (!(equal_namings("poIak", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(57)));}} while(0);



}

void test_projekcik_checking_function__length_of_file(void){



    fprintf(

           stderr

                 , "\n\nfun__length_of_file():\n------------------\n");



    FILE * test_file2 = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(65)));}} while(0);

    do {if ((length_of_file(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(66)));}} while(0);

    perror("siusiak");

    if(test_file2 != 

                    ((void *)0)

                        )

        fclose(test_file2);



    FILE * file = checking_file_valid("./test/text.tx");

    do {if ((check_format(file) == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(72)));}} while(0);

    do {if (!(length_of_file(file) == -1)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(73)));}} while(0);

    if(file != 

              ((void *)0)

                  )

        fclose(file);



}

void test_projekcik__get_array_of_tasks(void){



    fprintf(

           stderr

                 , "\n\nfun__get_array_of_tasks():\n------------------\n");



    FILE * test_file2 = checking_file_valid("./test/perfect.txt");

    do {if ((test_file2 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(83)));}} while(0);

    task_temp * array;



    do {if (((array = get_array_of_tasks(test_file2)) != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(86)));}} while(0);

    if(array != 

               ((void *)0)

                   )

        free_space(array);

    perror("667");

    if(test_file2 != 

                    ((void *)0)

                        )

        fclose(test_file2);



    FILE * test_file1 = checking_file_valid("./test/text.txt");

    do {if ((test_file1 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(94)));}} while(0);

    task_temp * array2;

    do {if (((array2 = get_array_of_tasks(test_file1)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(96)));}} while(0);

    if(array2 != 

                ((void *)0)

                    )

        free_space(array2);

    if(test_file1 != 

                    ((void *)0)

                        )

        fclose(test_file1);



    FILE * test_file4 = checking_file_valid("./test/text.tx");

    do {if ((test_file4 == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(103)));}} while(0);

    task_temp * array4;

    do {if (((array4 = get_array_of_tasks(test_file4)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(105)));}} while(0);

    if(array4 != 

                ((void *)0)

                    )

        free_space(array4);

    if(test_file4 != 

                    ((void *)0)

                        )

        fclose(test_file4);



    FILE * test_file3 = checking_file_valid("./test/bad.txt");

    do {if ((test_file3 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(112)));}} while(0);

    task_temp * array3;

    do {if (((array3 = get_array_of_tasks(test_file3)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(114)));}} while(0);

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



    do {if ((amount_of_pipes(" pol | lkok") == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(123)));}} while(0);

    do {if (!(amount_of_pipes(" pol \\| lkok") == 4)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(124)));}} while(0);

    do {if ((amount_of_pipes("lk | grep \\| | hihi") == 3)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(125)));}} while(0);

}

void test_projekcik__string_to_array(void){

    char pol[] ="           never gonna give you up";

    int size_free[2];

    size_free[0] = 1;

    size_free[1] = 1;

    char ** array = string_to_array(pol, &size_free[0]);

    do {if ((strcmp(array[0], "never") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(133)));}} while(0);

    do {if ((strcmp(array[1], "gonna") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(134)));}} while(0);

    do {if ((strcmp(array[2], "give") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(135)));}} while(0);

    do {if ((strcmp(array[3], "you") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(136)));}} while(0);

    do {if ((strcmp(array[4], "up") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(137)));}} while(0);

    do {if ((size_free[0] == 6)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(138)));}} while(0);

    for(int i = 0 ; i < size_free[0]-1 ; ++i)

        free(array[i]);

    free(array);

}



void test_projekcik__set_time_to_exec_temp(void){

    time_t rawtime;

    time (&rawtime);



    struct tm * timeinfo = localtime(&rawtime);

    task_temp arr[2];

    arr[0].hours = timeinfo->tm_hour;

    arr[0].minutes = timeinfo->tm_min;

    arr[1].minutes = timeinfo->tm_min;

    if(timeinfo->tm_hour < 23)

        arr[1].hours = timeinfo->tm_hour + 1;

    if(timeinfo->tm_min < 40){

        arr[0].minutes += 20;

        arr[1].minutes += 20;

        set_time_to_exec_temp(arr, 2);

        do {if ((arr[0].time_to_exec == 20)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(159)));}} while(0);

        if(timeinfo->tm_hour < 23)

            do {if ((arr[1].time_to_exec == 60 + 20)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(161)));}} while(0);

        else

            do {if ((arr[1].time_to_exec == 20)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(163)));}} while(0);

    }

    else{

        set_time_to_exec_temp(arr, 2);

        do {if ((arr[0].time_to_exec == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(167)));}} while(0);

        if(timeinfo->tm_hour < 23)

            do {if ((arr[1].time_to_exec == 60)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(169)));}} while(0);

        else

            do {if ((arr[1].time_to_exec == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(171)));}} while(0);

    }

}
