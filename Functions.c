#include "functions.h"
#include <stdio.h>
#include "data_type.h"
//#define DEBUG
//#define DEBUG_SORT
extern char filename[20];

void Release(student** head)
{
  student* tmp;
  while(*head!=NULL)
  {
    tmp=*head;
    *head=(*head)->next;
    free(tmp);
  }
}


void swap_node(student** left,student** right)
{
  student* p_tmp;//用于交换指针
  student tmp;//用于交换数据
#ifdef DEBUG_SWAP
  printf("Before changing, left_addr=%p, next=%p, cs11=%f right_adr=%p, next=%p, cs11=%f\n",*left,(*left)->next,(*left)->CS11,*right,(*right)->next,(*right)->CS11);
#endif
  //先备份右节点所指向的下一个节点地址
  p_tmp=(*right)->next;
  //再将两个节点的数据互换，并将它们指向的下一节点地址修正
  tmp=**right;
  **right=**left;
  **left=tmp;
  (*left)->next=*right;
  (*right)->next=p_tmp;
#ifdef DEBUG_SWAP
  printf("After changing, left_addr=%p, next=%p, cs11=%f right_adr=%p, next=%p, cs11=%f\n",*left,(*left)->next,(*left)->CS11,*right,(*right)->next,(*right)->CS11);
  system("pause");
#endif
}
student* create()
{
  student*   head=(student*)malloc(sizeof(student));
  head->value=false;
  head->next=NULL;
  return head;
}


void add_node(student** head,student* to_add)
{
  student* tmp=*head;
  while(tmp->next!=NULL) tmp=tmp->next;
  tmp->next=to_add;
}


void delet_node(student** head,student* to_delete)
{
  student* tmp=*head;
  if(tmp==to_delete)//如果头结点为要删除的点，则将下一个节点作为头结点
  {
    if(tmp->next!=NULL)//如果第二个节点存在
      *head=tmp->next;
    else
      *head=NULL;
    free(to_delete);
    return;
  }
  while(tmp->next!=to_delete&&tmp!=NULL)tmp=tmp->next;
  tmp->next=to_delete->next;
  free(to_delete);
}


void menu_filename()
{
  system("cls");
  printf("请输入将要创建或打开的文件名：");
  scanf("\t%s",filename);
}


void clear_filename()
{
  filename[0]='*';//文件名不存在*号，以此来表示输入的文件不存在
}

int write_file(char filename_[20],student** head)
{
  int n;
  FILE* fp;
  student* tmp=*head;//student*指针副本用来遍历输出而不改变调用函数中原指针的位置
  fp=fopen(filename_,"w");
  while(tmp!=NULL)
  {
    #ifdef FUNCTION_COMPLETE
    fprintf(fp,"# %s %s %d %f %f %f %f %f\n",tmp->name,tmp->num,tmp->sex,tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);    //以2进制形式写入文件中//一次写入一个数组//
    #else
    fprintf(fp,"# %s %s %d %f %f %f \n",tmp->name,tmp->num,tmp->sex,tmp->CS11,tmp->FM13,tmp->AS11);    //以2进制形式写入文件中//一次写入一个数组//
   #endif
    tmp=tmp->next;
  }
  fclose(fp);
  return 1;                                    //关闭文件
}
//非空文件打开时，head指针所指向的student指针指向有效的数据链表头地址
int read_file(char filename_[20],student** head)
{
  FILE* fp;
  student* tmp;
  fp=fopen(filename_,"r");
  char test=fgetc(fp);
  fclose(fp);
  if(test=='#')
  {
    fp=fopen(filename_,"r");
    student stu_tmp;
    *head=create();
    tmp=*head;
    while(1)
    {
      #ifdef FUNCTION_COMPLETE
      fscanf(fp,"#%s%s%d%f%f%f%f%f\n",stu_tmp.name,stu_tmp.num,&stu_tmp.sex,&stu_tmp.CS11,&stu_tmp.FM13,&stu_tmp.AS11,&stu_tmp.EM11,&stu_tmp.EM13);
      #else
      fscanf(fp,"#%s%s%d%f%f%f\n",stu_tmp.name,stu_tmp.num,&stu_tmp.sex,&stu_tmp.CS11,&stu_tmp.FM13,&stu_tmp.AS11);
      #endif
      *tmp=stu_tmp;
      if(feof(fp))break;
      tmp->next=create();
      tmp=tmp->next;
    }
    if((*head)->next==NULL)
    {
      (*head)->value=true;//如果只有一行数据，标记为有效数据
    }
    return 1;
  }
  else//空文件
  {
    tmp->value=false;
    fclose(fp);
    return -1;
  }
  fclose(fp);
}


void open_create_file(char filename_[20],student** head)//自动检测所需文件是否存在，存在就读取，不存在就创建文件
{
  FILE* fp;
  student* p=NULL;
  menu_filename();
  if(*head!=NULL)Release(head);//重新打开文件时释放之前保留的数据，留下头节点的内存
  if(fp=fopen(filename_,"r")!=NULL)
  {
    printf("读取文件中...\n");
    read_file(filename_,head);
    printf("操作完成！\n");
    system("pause");
  }
  else
  {
    fp=fopen(filename_,"w");
    printf("  %s不存在，文件创建中...\n",filename_);
    printf("操作完成！\n");
    system("pause");
    fclose(fp);
  }
}

void display(student** head)
{
    student* tmp=NULL;//student*指针副本用来遍历输出而不改变调用函数中原指针的位置
    if(filename[0]=='*')open_create_file(filename,head);
    tmp=*head;
    title();
    if(tmp==NULL)
    {
      printf("no data!\n");
      return;
    }
    else
    {
      while(tmp!=NULL)
      {
    #ifdef FUNCTION_COMPLETE
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);
      #else
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11);
      #endif
      tmp=tmp->next;
      }
    }
}

student* check_existence(char num[15],student** head,char last_node_check,student* node_to_ignoe)
{
  student* tmp=*head;
  if(tmp==NULL)return NULL;
  else
  {
    while(tmp->next!=NULL)
    {
      if(strcmp(tmp->num,num)==0&&tmp!=node_to_ignoe)
        {
        title();
        #ifdef FUNCTION_COMPLETE
        printf("  %-7s %-10s %-s %10.2f %10.2f %10.2f %10.2f %10.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);
        #else
        printf("  %-7s %-10s %-s %10.2f %10.2f %10.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11);
        #endif
        return tmp;
      }
      tmp=tmp->next;
    }
    if(last_node_check=='y')
        if(strcmp(tmp->num,num)==0&&tmp!=node_to_ignoe)
        {
        title();
    #ifdef FUNCTION_COMPLETE
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);
      #else
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11);
      #endif
      return tmp;
    }
    return NULL;
  }
}

void add(student** head)                                      //成绩的录入与添加函数
{
    int i=0,n=0;
    char sign='y';
    char sex[2];
    student* p=NULL;                         //首先定义sing='y'
    system("cls");
    if(filename[0]=='*')open_create_file(filename,head);
    if(*head==NULL)//如果文件中有有效数据就创建新的student来存储新的学生信息并添加到现有的学生链表中
    {
      p=*head=create();
#ifdef DEBUG_ADD
      printf("create new node...\n");
      printf("new *head==NULL?=%p\n",*head);
      system("pause");
#endif
    }
    else
    {
      p=create();
      add_node(head,p);
#ifdef DEBUG_ADD
      printf("new *head==NULL?=%p\n",*head);
      system("pause");
#endif
    }
    while(1)                    //其实只有当输入n或n时才跳出循环
    {
      student* check=NULL;
      system("cls");
      printf("             ----添加纪录----\n");
      printf("姓名：\n");
      scanf("\t%s",p->name);
      printf("学号:\n");
      scanf("\t%s",p->num);
      check=check_existence(p->num,head,'n',NULL);
      if(check!=NULL)//最后一个节点是目前正在存储的节点，不检查该节点
      {
        printf("学号%s 对应的学生已存在!\n",p->num);
        printf("请重新输入\n");
        system("pause");
        continue;
      }
#ifndef DEBUG
      printf("性别：男(0);女(1)\n");
      scanf("%d",&p->sex);
      while(p->sex!=0&&p->sex!=1)
      {
        printf("请重新输入性别:男(0);女(1)\n");
        scanf("%d",&p->sex);
      }
      printf("计算机科学：\n");
      scanf("\t%10.2f",&p->CS11);
      printf("流体力学：\n");
      scanf("\t%10.2f",&p->FM13);
      printf("线弹性力学：\n");
      scanf("\t%10.2f",&p->AS11);
      #ifdef FUNCTION_COMPLETE
      printf("泛函分析：\n");
      scanf("\t%10.2f",&p->EM11);
      printf("概率论与数理统计：\n");
      scanf("\t%10.2f",&p->EM13);
      #endif
#else
      printf("性别：男(0);女(1)\n");
      scanf("%d",&p->sex);
      while(p->sex!=0&&p->sex!=1)
      {
        printf("请重新输入性别:男(0);女(1)\n");
        scanf("%d",&p->sex);
      }
      p->CS11=1;
      p->FM13=1;
      p->AS11=1;
      #ifdef FUNCTION_COMPLETE
      p->EM11=1;
      p->EM13=1;
      #endif
#endif
      display(head);
      printf("是否继续添加?(y/n)");
      scanf("\t%c",&sign);
      if(sign=='n'||sign=='n')break;
      system( "cls ");
      p->next=create();
      p=p->next;
    }
    write_file(filename,head);
}


void delet(student** head)
{
  char s[10];
  int i=0,n=0;
  student* tmp=NULL;
  student* check=NULL;
  if(filename[0]=='*')open_create_file(filename,head);
  if(*head==NULL)
  {
    system("cls");
    printf("No data!\n");
    system("pause");
    return;
  }
  tmp=*head;
  printf("学生学号：");
  scanf("%s",s);
  check=check_existence(s,head,'y',NULL);
  if(check==NULL)
  {
    printf("\t数据库中没有此人!\n");
    system("pause");
    return;
  }
  delet_node(head,check);
  printf("删除成功！\n");
  write_file(filename,head);
  system("pause");
}


void Welcome()                                            //登陆函数 使系统更显完善
{
  system("cls");
  printf("                                                                 \n");
  printf("|===============================================================|\n");
  printf("|                                                               |\n");
  printf("|            计 算 机 科 学 大 作 业                            |\n");
  printf("|           computer science project                            |\n");
  printf("|                    胡   刚                                    |\n");
  printf("|                      tom                                      |\n");
  printf("|                    14142408                                   |\n");
  printf("|                                       E-mail:wdqqhs@qq.com    |\n");
  printf("|                                       version：1.0            |\n");
  printf("|                                       2017年11月10日          |\n");
  printf("|                                                               |\n");
  printf("|===============================================================|\n");
  printf("                                                                 \n");
  system("pause");
}
int menu_select()                              //菜单选择系统函数
{
  char c;
  do{
    system("cls");
    printf("                                                                 \n");
    printf("|===============================================================|\n");
    printf("|                                                               |\n");
    printf("|                学 生 成 绩 管 理 系 统                        |\n");
    printf("|                                                               |\n");
    printf("|        【1】打开文件                【2】新增信息             |\n");
    printf("|        【3】浏览信息                【4】查询信息             |\n");
    printf("|        【5】修改信息                【6】删除信息             |\n");
    printf("|        【7】成绩排序                【0】退出                 |\n");
    printf("|                                                               |\n");
    printf("|===============================================================|\n");
    printf("                                当前文件：%-4s                  \n",filename[0]=='*'?"无":filename);
    printf("                                                                 \n");
    printf("输入数字（0-7）进行选择：【  】\b\b");
    c=getchar();
  }while(c<'0'||c>'7');
  return (c-'0');                                      //字符减去'0'得到的是数字整型//
}


void new_screen()
{
  system("cls");
}


void title()
{
  new_screen();
  printf("================================================================================\n");
  #ifdef FUNCTION_COMPLETE
  printf("  姓名     学号     性别  计算机科学   流体力学    线弹性力学   泛函分析   概率论数理统计\n");
  #else
  printf("  姓名     学号     性别  计算机科学   流体力学    线弹性力学   \n");
  #endif
  printf("================================================================================\n");
}

void Modifie(student** head)
{
  student* check=NULL;
  student* repet=NULL;
  char s[15];
  int selection;
  if(filename[0]=='*')open_create_file(filename,head);
    if(*head==NULL)
    {
      system("cls");
      printf("No data!\n");
      system("pause");
      return;
    }
  system("cls");
  printf("请输入需要修改的学号\n");
  scanf("%s",s);
  check=check_existence(s,head,'y',NULL);
  if(check==NULL)
  {
    printf("\t数据库中没有此人!\n");
    system("pause");
    return;
  }
  else system("pause");//如果查询到此人，显示信息，暂停
  while(1){
    system("cls");
    printf("                                                                 \n");
    printf("|===============================================================|\n");
    printf("|                                                               |\n");
    printf("|                        修  改  选  项                         |\n");
    printf("|                                                               |\n");
    printf("|        【1】修改姓名                【2】修改学号             |\n");
    printf("|        【3】修改性别                【4】修改CS11             |\n");
    printf("|        【5】修改FM13                【6】修改AS11             |\n");
#ifdef FUNCTION_COMPLETE
     printf("|        【7】修改EM11                【8】修改EM13             |\n");
#endif
    printf("|        【0】保存返回                                          |\n");
    printf("|                                                               |\n");
    printf("|===============================================================|\n");
    printf("                                        当前学号：%-s           \n",check->num);
    printf("                                                                 \n");
    #ifdef FUNCTION_COMPLETE
    printf("请输入数字进行选择【0-8】【  】\b\b");
    #else
    printf("请输入数字进行选择【0-6】【  】\b\b");
    #endif // FUNCTION_COMPLETE
    scanf("%d",&selection);
    switch(selection){
      case 1:
      printf("重新输入姓名：\n");
      scanf("\t%s",check->name);
      break;
      case 2:
          printf("重新输入学号：\n");
          scanf("\t%s",check->num);
      repet=check_existence(check->num,head,'y',check);
      while(repet!=NULL)
      {
        printf("学号%s 对应的学生已存在!\n",check->num);
        printf("请重新输入\n");
        scanf("\t%s",check->num);
        repet=check_existence(check->num,head,'y',check);
      }
          break;
      case 3:
      printf("重新输入性别：男(0);女(1)\n");
      scanf("\t%d",&check->sex);
       //scanf("%d",&check->sex);
      while(check->sex!=0&&check->sex!=1)
      {
        printf("请重新输入性别:男(0);女(1)\n");
        scanf("%d",&check->sex);
      }
      break;
      case 4:
      printf("重新输入计算机科学成绩：\n");
      scanf("\t%f",&check->CS11);
      break;
      case 5:
      printf("重新输入流体力学成绩：\n");
      scanf("\t%f",&check->FM13);
      break;
      case 6:
      printf("重新输入线弹性力学成绩：\n");
      scanf("\t%f",&check->AS11);
      break;
#ifdef FUNCTION_COMPLETE
      case 7:
      printf("重新输入泛函分析成绩：\n");
      scanf("\t%f",&check->EM11);
      break;
      case 8:
      printf("重新输入概率论与数理统计成绩：\n");
      scanf("\t%f",&check->EM13);
      break;
#endif
      case 0:
      default:
      write_file(filename,head);
      return;
      break;
    }
    title();
    #ifdef FUNCTION_COMPLETE
    printf("  %-7s %-5s %-6s %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f \n",check->name,check->num,check->sex==0?"男":"女",check->CS11,check->FM13,check->AS11,check->EM11,check->EM13);
    #else
    printf("  %-7s %-5s %-6s %-12.2f %-12.2f %-12.2f \n",check->name,check->num,check->sex==0?"男":"女",check->CS11,check->FM13,check->AS11);
    #endif
    system("pause");
    selection=-1;
  }
}


void show(student** head)                        //显示记录  进行全面信息浏览
{
  char sign;
  display(head);
  system("pause");
  system("cls");
  if(*head!=NULL)//数据存在是提示是否修改数据
  {
  printf("是否需要修改?(y/n)");
  scanf("\t%c",&sign);
  if(sign!='n'&&sign!='N')Modifie(head);
  }
}


void find(student** head)                     //学生信息的不同方式查询
{
  int m;
  if(filename[0]=='*')open_create_file(filename,head);
  if(*head==NULL)
  {
    system("cls");
    printf("No data!\n");
    system("pause");
    return;
  }
  while(1)
  {
    student* tmp=*head;
    char find_flag='n';
    system("cls");
    printf("                                                                 \n");
    printf("|===============================================================|\n");
    printf("|                                                               |\n");
    printf("|                 请 选 择 查 询 方 式                          |\n");
    printf("|              【1】按姓氏查询                                  |\n");
    printf("|              【2】按姓名查询                                  |\n");
    printf("|              【3】按学号查询                                  |\n");
    printf("|              【0】返      回                                  |\n");
    printf("|===============================================================|\n");
    printf("请输入指令【0-3】【  】\b\b");
    fflush(stdin);
    scanf("%d",&m);
    if(m!=1&&m!=2&&m!=3&&m!=0)continue;
    if(m==1)                                                 //模糊查询
    {
      char s[2];                                             //定义输入的文字所占的字节 /一个汉字占2个字节 外加一结尾符此处小心溢出
      system("cls");
      printf("请输入不多于两个字的姓氏:\n");
      scanf("%s",s);
      title();
      for(;tmp!=NULL;tmp=tmp->next)                                               //文件信息已经读取到数组中 此处进行循环用于下一语句的查找
      {
        switch(strlen(s))
        {
          case 1:
            if(tmp->name[0]==s[0])
            {
    #ifdef FUNCTION_COMPLETE
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);
      #else
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11);
      #endif
              find_flag='y';
            }
            break;
          case 2:
            if(tmp->name[0]==s[0]&&tmp->name[1]==s[1])
            {
    #ifdef FUNCTION_COMPLETE
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);
      #else
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11);
      #endif
              find_flag='y';
            }
            break;
          default:
          break;
        }
      }
    }
    if(m==2)                                            //姓名查询
    {
      char s[20];
      int j=0;
      printf("请输入想查询的姓名:");
      scanf("\t%s",s);
      title();
      for(;tmp!=NULL;tmp=tmp->next)                                               //文件信息已经读取到数组中 此处进行循环用于下一语句的查找
      {
        if(strcmp(tmp->name,s)==0)
        {
    #ifdef FUNCTION_COMPLETE
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11,tmp->EM11,tmp->EM13);
      #else
      printf("  %-7s %-10s %-6s %-12.2f %-12.2f %-12.2f \n",tmp->name,tmp->num,tmp->sex==0?"男":"女",tmp->CS11,tmp->FM13,tmp->AS11);
      #endif
          find_flag='y';
        }
      }
    }
    if(m==3)                                                            //学号查询
    {
      char s[15];
      int i=0;
      printf("请输入想查询的学号：");
      scanf("\t%s",s);
      title();
      if(check_existence(s,head,'y',NULL)!=NULL)find_flag='y';
    }
    if(m==0)return;
    if(find_flag=='n')printf("查询无果！\n");
    else find_flag='n';
    system("pause");
    m=-1;
  }
}


void sort(student** head)
{
    if(filename[0]=='*')open_create_file(filename,head);
    student* tmp_1=NULL;                              //定义临时数组用于交换时存放数组信息用于后面的交换//
    student* tmp_2=NULL;
    student* tmp=NULL;
    float sum=0;
    int m;
    if(*head==NULL)
    {
      system("cls");
      printf("No data!\n");
      system("pause");
      return;
    }
    while(1)
    {
    system("cls");
    printf("                                                                 \n");
    printf("|===============================================================|\n");
    printf("|                                                               |\n");
    printf("|                 请 选 择 排 序 方 式                          |\n");
    printf("|          【1】按CS11成绩排序                                  |\n");
    printf("|          【2】按FM13成绩排序                                  |\n");
    printf("|          【3】按AS11成绩排序                                  |\n");
    #ifdef FUNCTION_COMPLETE
    printf("|          【4】按EM11成绩排序                                  |\n");
    printf("|          【5】按EM13成绩排序                                  |\n");
    #endif
    printf("|          【0】返          回                                  |\n");
    printf("|===============================================================|\n");
    #ifdef FUNCTION_COMPLETE
    printf("请输入排序方式【0-5】【  】\b\b");
    #else
    printf("请输入排序方式【0-3】【  】\b\b");
    #endif // FUNCTION_COMPLETE
    scanf("%d",&m);
    system("cls");
    if(m==1)
    {
        //临时指针复位，避免上次排序带来的影响
        tmp_1=*head;
        tmp_2=tmp_1->next;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next){
            printf("*****=====*****nstart_addr=%s\n",tmp->name);
        for(tmp_1=*head,tmp_2=tmp_1->next;tmp_2!=NULL;tmp_1=tmp_1->next,tmp_2=tmp_1->next)
        {
#ifdef DEBUG_SORT
        printf("Before changing, tmp_1's name=%s\ntmp_1->next's name=%s\n",tmp_1->name,tmp_2->name);
#endif
            if(tmp_1->CS11<tmp_2->CS11)
          {
            swap_node(&tmp_1,&tmp_2);
#ifdef DEBUG_SORT
            printf("After changing, tmp_1's name=%s\ntmp_1->next's name=%s\n",tmp_1->name,tmp_2->name);
            system("pause");
            #endif
          }
          }
    }
    display(head);
        m=0;
    sum=0.0;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next,m++)sum+=tmp->CS11;
    display(head);
    printf("Average :%-.2f\n",sum/m);
    system("pause");
    m=-1;
    }
#ifndef DEBUG_SORT
    if(m==2)
    {
        //临时指针复位，避免上次排序带来的影响
        tmp_1=*head;
        tmp_2=tmp_1->next;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next)
        for(tmp_1=*head,tmp_2=tmp_1->next;tmp_2!=NULL;tmp_1=tmp_1->next,tmp_2=tmp_1->next)
        {
            if(tmp_1->FM13<tmp_2->FM13)
          {
            swap_node(&tmp_1,&tmp_2);
          }
    }
    display(head);
        m=0;
    sum=0.0;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next,m++)sum+=tmp->FM13;
    display(head);
    printf("Average :%-.2f\n",sum/m);
    system("pause");
    m=-1;
    }
    if(m==3)
    {
        //临时指针复位，避免上次排序带来的影响
        tmp_1=*head;
        tmp_2=tmp_1->next;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next)
        for(tmp_1=*head,tmp_2=tmp_1->next;tmp_2!=NULL;tmp_1=tmp_1->next,tmp_2=tmp_1->next)
        {
            if(tmp_1->AS11<tmp_2->AS11)
          {
            swap_node(&tmp_1,&tmp_2);
          }
    }
    m=0;
    sum=0.0;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next,m++)sum+=tmp->AS11;
    display(head);
    printf("Average :%-.2f\n",sum/m);
    system("pause");
    m=-1;
    }
#ifdef FUNCTION_COMPLETE
    if(m==4)
    {
        //临时指针复位，避免上次排序带来的影响
        tmp_1=*head;
        tmp_2=tmp_1->next;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next)
        for(tmp_1=*head,tmp_2=tmp_1->next;tmp_2!=NULL;tmp_1=tmp_1->next,tmp_2=tmp_1->next)
        {
            if(tmp_1->EM11<tmp_2->EM11)
          {
            swap_node(&tmp_1,&tmp_2);
          }
    }
    for(tmp=*head;tmp!=NULL;tmp=tmp->next,m++)sum+=tmp->EM11;
    display(head);
    printf("Average :%-.2f\n",sum/m);
    system("pause");
    m=-1;
    }
    if(m==5)
    {
        //临时指针复位，避免上次排序带来的影响
        tmp_1=*head;
        tmp_2=tmp_1->next;
    for(tmp=*head;tmp!=NULL;tmp=tmp->next)
        for(tmp_1=*head,tmp_2=tmp_1->next;tmp_2!=NULL;tmp_1=tmp_1->next,tmp_2=tmp_1->next)
        {
            if(tmp_1->EM13<tmp_2->EM13)
          {
            swap_node(&tmp_1,&tmp_2);
          }
    }
    for(tmp=*head;tmp!=NULL;tmp=tmp->next,m++)sum+=tmp->EM13;
    display(head);
    printf("Average :%-.2f\n",sum/m);
    system("pause");
    m=-1;
    }
#endif //endif of FUNCTION_COMPLETE
#endif //endif of DEBUG_SORT
    if(m==0){
        write_file(filename,head);
            return;
    }
    fflush(stdin); //清楚错误的输入指令
    }
}

