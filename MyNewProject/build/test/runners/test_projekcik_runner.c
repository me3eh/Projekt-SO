/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_projekcik_checkingfunction__amount_of_arguments(void);
extern void test_projekcik_checkingfunction__checking_file_valid(void);
extern void test_projekcik_checkingfunction__check_format(void);
extern void test_projekcik_checking_function__equal_namings(void);
extern void test_projekcik_checking_function__length_of_file(void);
extern void test_projekcik__get_array_of_tasks(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_projekcik.c");
  run_test(test_projekcik_checkingfunction__amount_of_arguments, "test_projekcik_checkingfunction__amount_of_arguments", 15);
  run_test(test_projekcik_checkingfunction__checking_file_valid, "test_projekcik_checkingfunction__checking_file_valid", 23);
  run_test(test_projekcik_checkingfunction__check_format, "test_projekcik_checkingfunction__check_format", 29);
  run_test(test_projekcik_checking_function__equal_namings, "test_projekcik_checking_function__equal_namings", 44);
  run_test(test_projekcik_checking_function__length_of_file, "test_projekcik_checking_function__length_of_file", 51);
  run_test(test_projekcik__get_array_of_tasks, "test_projekcik__get_array_of_tasks", 63);

  return UnityEnd();
}
