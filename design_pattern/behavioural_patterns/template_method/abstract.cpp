#include "abstract.h"
#include <stdio.h>


int CAbstract::DoSomething()
{
    Start();
    Step1();
    Step2();
    printf("....\n");//......
    StepN();
    End();
    
    return 0;
}

int CAbstract::Start()
{
    printf("start ....\n");

    return 0;
}

int CAbstract::Step1()
{
    printf("step1 ....\n");
    return 0;
}

int CAbstract::Step2()
{
    printf("step2 ....\n");
    return 0;
}

int CAbstract::StepN()
{
    printf("stepN ....\n");
    return 0;
}

int CAbstract::End()
{
    printf("end ....\n");
    return 0;
}