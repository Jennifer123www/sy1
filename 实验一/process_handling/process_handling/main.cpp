#include "head.h"
int main()
{
 cout<<"*************欢迎进入进程调度模拟算法程序****************"<<endl;
 while (1)
 {
   menu();                             //显示菜单
   int i;                              //输入选择算法的序号
   cin >> i; 
   if (i==3)
	   break;
   switch(i)
   {
   case 1:                             //优先数调度算法
		    Insert1();                 //用户输入进程标识，需要时间，计算优先数，按照优先级排序，插入就绪队列
		    Prisch();                  //按优先级进行进程调度
			run.clear();               //清空执行队列
			ready.clear();             //清空就绪队列
	 		finish.clear();            //清空完成队列
		    break;                     
   case 2:                             //循环轮转调度算法
	        Insert2();                 //插入就绪队列
		    Roundsch();                //循环轮转调度算法
		   	run.clear();               //清空执行队列
			ready.clear();             //清空就绪队列
			finish.clear();            //清空完成队列
	        break;
   default:
	   cout << "输入错误" << endl;
   }
 }
 return 0;
}
