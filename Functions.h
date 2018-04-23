#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "Data_type.h"

extern char filename[20];

extern student per[200];

void Release(student** head);

void swap_node(student** left,student** right);

void add_node(student** head,student* to_add);

void delet_node(student** head,student* to_delete);

void menu_filename();

void clear_filename();

void open_create_file(char filename_[20],student** head);//自动检测所需文件是否存在，存在就读取，不存在就创建文件

void display(student** head);

void add(student** head);                                      //成绩的录入与添加函数

void delet(student** head);

void Welcome();                                            //登陆函数 使系统更显完善

void new_screen();

void title();

void Modifie(student** head);

void show(student** head);                        //显示记录  进行全面信息浏览

void find(student** head);                     //学生信息的不同方式查询

void sort(student** head);

#endif // FUNCTIONS_H_INCLUDED
