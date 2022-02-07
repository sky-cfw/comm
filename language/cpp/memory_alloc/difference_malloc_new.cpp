#include <stdio.h>
#include <stdlib.h>
#include "difference_malloc_new.h"

CTest::CTest()
{
    printf("construct was called!\n");
}

CTest::~CTest()
{
    printf("deconstruct was called!\n");
}

int main(int argc, char const *argv[])
{
    CTest *pT1 = new CTest();
    printf("object of class CTest was created by new operator!\n");

    CTest *pT2 = (CTest *)malloc(sizeof(CTest));
    printf("object of class CTest was created by malloc function!\n\n");



    delete pT1;
    pT1 = NULL;
    printf("object of class CTest was deleted by delete operator!\n");

    free(pT2);
    pT2 = NULL;
    printf("object of class CTest was deleted by free function!\n");

    return 0;
}
