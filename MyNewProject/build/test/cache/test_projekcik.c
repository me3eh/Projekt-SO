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

    if(test_file2 != 

                    ((void *)0)

                        )

        fclose(test_file2);



    FILE * file = checking_file_valid("./test/text.tx");

    do {if ((check_format(file) == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(71)));}} while(0);

    do {if (!(length_of_file(file) == -1)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(72)));}} while(0);

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

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(82)));}} while(0);

    task_temp * array;

    do {if (((array = get_array_of_tasks(test_file2)) != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(84)));}} while(0);

    if(array != 

               ((void *)0)

                   )

        free_space(array);

    if(test_file2 != 

                    ((void *)0)

                        )

        fclose(test_file2);



    FILE * test_file1 = checking_file_valid("./test/text.txt");

    do {if ((test_file1 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(91)));}} while(0);

    task_temp * array2;

    do {if (((array2 = get_array_of_tasks(test_file1)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(93)));}} while(0);

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

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(100)));}} while(0);

    task_temp * array4;

    do {if (((array4 = get_array_of_tasks(test_file4)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(102)));}} while(0);

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

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(109)));}} while(0);

    task_temp * array3;

    do {if (((array3 = get_array_of_tasks(test_file3)) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(111)));}} while(0);

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

    do {if ((amount_of_pipes(" pol | lkok") == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(119)));}} while(0);

    do {if (!(amount_of_pipes(" pol \| lkok") == 1)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(120)));}} while(0);

    printf("%d\n",amount_of_pipes("lk | grep \| | hihi"));

    printf("%d",amount_of_pipes("lk | grep | hihi | pol | d"));

    printf("4");





}
