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

}



void test_projekcik_checkingfunction__checking_file_valid(void){



    do {if ((checking_file_valid("./test/text.txt") != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(24)));}} while(0);

    do {if ((checking_file_valid("./test/text123.txt") == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(25)));}} while(0);

}



void test_projekcik_checkingfunction__check_format(void){



    FILE * file = checking_file_valid("./test/text.txt");

    do {if ((check_format(file) == -1)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(31)));}} while(0);

    FILE * test_file = checking_file_valid("./test/perfect.txt");

    do {if ((check_format(test_file) > 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(33)));}} while(0);

}

void test_projekcik_checking_function__equal_namings(void){

    do {if ((equal_namings("pol", "pol"))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(36)));}} while(0);

    do {if (!(equal_namings("epicki", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(37)));}} while(0);

    do {if (!(equal_namings("poIak", "polak"))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(38)));}} while(0);

}
