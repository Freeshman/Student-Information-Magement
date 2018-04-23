#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Data_type.h"
#include "Functions.c"
char filename[20]="*";                                      //定义全局变量
int main()
{
    student** head=(student**)malloc(sizeof(student*));

    *head=NULL;

      Welcome();
      for(;;)                                                 //循环使用主界面直到遇到结束命令
      {
          switch(menu_select())                               // 函数的调用//
          {
          case 1:
              open_create_file(filename,head);
              break;
          case 2:
              add(head);
              break;
          case 3:
              show(head);
              break;
          case 4:
              find(head);
              break;
          case 5:
              Modifie(head);
              break;
          case 6:
               delet(head);
               break;
          case 7:
               sort(head);
               break;
          case 0:
              if(*head!=NULL)Release(head);
                free(*head);
                exit(0);
          }
      }
  return 0;
}
