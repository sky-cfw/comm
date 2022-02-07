/*
 * @Author: your name
 * @Date: 2022-01-03 23:11:54
 * @LastEditTime: 2022-01-04 00:12:47
 * @LastEditors: Please set LastEditors
 * @Description: C语言之面向对象
 * @FilePath: /comm/language/cpp/pointer/orient_object.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tAnimal
{
    char name[10];
    void (*Eat)(struct _tAnimal *this, char *food);//声明一个指针变量Eat
    void (*Sleep)(struct _tAnimal *this);//声明一个指针变量 Sleep
}Animal;

typedef void (*pInit)(struct _tAnimal *this, char *name);
typedef void (*pEat)(struct _tAnimal *this, char *food);
typedef void (*pSleep)(struct _tAnimal *this);

void Init(struct _tAnimal *this, char *name, pEat eat, pSleep sleep)
{
    strncpy(this->name, name, sizeof(name));
    this->Eat = eat;
    this->Sleep = sleep;
    return ;
}

void Eat(struct _tAnimal *this, char *food)
{
    printf("animal %s eat %s\n", this->name, food);
    return ;
}

void Sleep(struct _tAnimal *this)
{
    printf("%s sleep\n", this->name);
    return ;
}

int main()
{
    Animal *animal = (Animal *)malloc(sizeof(Animal));
    Init(animal, "dog", Eat, Sleep);
    animal->Eat(animal, "bone");
    animal->Sleep(animal);
    
    return 0;
}