#ifndef DATA_TYPE_H_INCLUDED
#define DATA_TYPE_H_INCLUDED
#include <stdbool.h>
typedef struct                                //定义结构体
{
	bool value;
	char num[10];   //学号
	char name[20]; //姓名
	int sex;//性别
	float CS11;    //CS11成绩
	float FM13;      //FM13成绩
	float  AS11;      //AS11成绩
	float  EM11;      //EM11成绩
	float  EM13;  //EM13成绩
	struct student_* next;
}student;


#endif // DATA_TYPE_H_INCLUDED
