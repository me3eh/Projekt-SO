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

    do {if (!(amount_of_arguments(4, "./minicrom") == 0)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(17)));}} while(0);

    do {if ((amount_of_arguments(1, "./minicrom") != 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(18)));}} while(0);

    do {if ((amount_of_arguments(3, "./minicrom") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);

    perror("1\n");



}

void test_projekcik_checkingfunction__checking_file_valid(void){

    do {if ((checking_file_valid("./test/text.txt") != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(24)));}} while(0);

    do {if ((checking_file_valid("./test/text123.txt") == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(25)));}} while(0);

    perror("2\n");



}

void test_projekcik_checkingfunction__check_format(void){









    FILE * test_file = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file) > 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(35)));}} while(0);

    fclose(test_file);

    perror("3\n");

    FILE * test_file2 = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(39)));}} while(0);

    fclose(test_file2);

    perror("3\n");



}

void test_projekcik_checking_function__equal_namings(void){

    do {if ((equal_namings("pol", "pol"))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(45)));}} while(0);

    do {if (!(equal_namings("epicki", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(46)));}} while(0);

    do {if (!(equal_namings("poIak", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(47)));}} while(0);

    perror("4\n");



}

void test_projekcik_checking_function__length_of_file(void){

    FILE * test_file2 = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(53)));}} while(0);

    do {if ((length_of_file(test_file2) == 2)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(54)));}} while(0);

    fclose(test_file2);









    perror("5\n");



}

void test_projekcik__get_array_of_tasks(void){

    FILE * test_file2 = checking_file_valid("./test/perfect.txt");

    do {if ((test_file2 != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(65)));}} while(0);

    task_temp * array;

    do {if (((array = get_array_of_tasks(test_file2)) != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(67)));}} while(0);

    free_space(array);

    fclose(test_file2);

    perror("6\n");











}
