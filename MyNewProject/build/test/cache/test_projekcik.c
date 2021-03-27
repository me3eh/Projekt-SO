#include "src/projekcik.h"
#include "src/fun.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.0/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



void test_projekcik_inserting_values(void)

{

    do {if (!(amount_of_arguments(4, "./minicrom") == 0)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(17)));}} while(0);

    do {if ((amount_of_arguments(1, "./minicrom") != 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(18)));}} while(0);

    do {if ((amount_of_arguments(3, "./minicrom") == 0)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);

}



void test_projekcik_is_file_valid(void){



    do {if ((checking_file_valid("./test/text.txt", 

   0

   ) != 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(24)));}} while(0);

    do {if ((checking_file_valid("./test/text123.txt", 

   0

   ) == 

   ((void *)0)

   )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(25)));}} while(0);

}
