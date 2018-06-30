
/*
*项目：进程调度模拟算法
*作者：王秀杰
*时间：2018-04-25
*版本号：3

*项目说明：分别用两种调度算法对五个进程进行调度。每个进程可有三种状态；执行状态（RUN）、 就绪状态（READY,包括等待状态）和完成状态（FINISH），并假定初始状态为就绪状态。
（一）进程控制块结构如下：
NAME——进程标示符 
PRIO/ROUND——进程优先数/进程每次轮转的时间片数（设为常数 2） 
CPUTIME——进程累计占用 CPU 的时间片数 
NEEDTIME——进程到完成还需要的时间片数
STATE——进程状态 NEXT——链指针
注：
1.为了便于处理，程序中进程的的运行时间以时间片为单位进行计算；
2.各进程的优先数或轮转时间片数，以及进程运行时间片数的初值，均由用户在程序运 行时给定。
（二）进程的就绪态和等待态均为链表结构，共有四个指针如下：
RUN——当前运行进程指针 READY——就需队列头指针 TAIL—— 就需队列尾指针 FINISH—— 完成队列头指针
（三）程序说明
1. 在优先数算法中，进程优先数的初值设为：
50-NEEDTIME
每执行一次，优先数减 1，CPU 时间片数加 1，进程还需要的时间片数减 1。 在轮转法中，采用固定时间片单位（两个时间片为一个单位），进程每轮转一次，CPU
时间片数加 2，进程还需要的时间片数减 2，并退出 CPU，排到就绪队列尾，等待下一次调 度。
2.  程序的模块结构提示如下：
整个程序可由主程序和如下 7 个过程组成：
（1）INSERT1——在优先数算法中，将尚未完成的 PCB 按优先数顺序插入到就绪队列
中；
（2）INSERT2——在轮转法中，将执行了一个时间片单位（为 2），但尚未完成的进程
的 PCB，插到就绪队列的队尾；
（3）FIRSTIN——调度就绪队列的第一个进程投入运行；
（4）PRINT——显示每执行一次后所有进程的状态及有关信息。
（5）CREATE——创建新进程，并将它的 PCB 插入就绪队列；
（6）PRISCH——按优先数算法调度进程；
（7）ROUNDSCH——按时间片轮转法调度进程。 主程序定义 PCB 结构和其他有关变量。
（四）运行和显示
程序开始运行后，首先提示：请用户选择算法，输入进程名和相应的 NEEDTIME 值。 每次显示结果均为如下 5 个字段：
name	cputime	needtime	priority	state
注：
1．在 state 字段中，"R"代表执行态，"W"代表就绪（等待）态，"F"代表完成态。
2．应先显示"R"态的，再显示"W"态的，再显示"F"态的。
3．在"W"态中，以优先数高低或轮转顺序排队；在"F"态中，以完成先后顺序排队。
*/
#include<iostream>     
#include<string>
#include<set>
#include<queue>
#include<deque>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
typedef struct node       //定义节点结构
{
	int PRIO;             //进程优先级
	string NAME;          //进程标识符
	int ROUND;            //轮转时间片数
	int CPUTIME;          //进程累计占用CPU运行时间片数
	int NEEDTIME;         //进程还需要的时间片数
	char STATE;           //进程状态 "R"代表执行态，"W"代表就绪（等待）态，"F"代表完成态
	int count;            //记录执行的次数
} PCB;

int num;

//重载<
bool operator < (const PCB &a,const PCB &b)
{
	bool flag;
	a.PRIO < b.PRIO?flag = true:flag = false;
	return flag;
}

//重载<<
ostream& operator << (ostream &os,const PCB &p)
{
	os << p.NAME << "\t" << p.CPUTIME << "\t" << p.NEEDTIME << "\t"<<p.PRIO << "\t" << p.STATE << endl;
	return os;
}

//定义三个队列,就绪队列，运行队列，完成队列
deque<node> ready,run,finish; 

//显示队列内容
 void Display(deque <node> d)
 {
	 int i;
	 for( i = 0;i < d.size();i++)
	    cout << d[i].NAME << "\t   " << d[i].CPUTIME << "\t      " << d[i].NEEDTIME << "\t\t     " << d[i].PRIO << "\t\t  " << d[i].STATE << endl;
 }

//显示每执行一次后所有进程的状态及有关信息
 void Print()
 {
  	cout << "---------------------------------------------------" << endl;
	if (!ready.empty()) Display(ready);      //输出就绪队列
	if (!run.empty()) Display(run);          //输出运行队列
	if (!finish.empty()) Display(finish);    //输出完成队列
 }

  //就绪队列排序
  void Sort()
  {
	  multiset<PCB> m;
	  multiset<PCB>::iterator it;
	  for (int i = 0;i < ready.size();i++)
	  {
		  m.insert(ready[i]);
	  }
	  ready.clear();                //清空
	 for (it = m.begin();it != m.end();it++)
	  {
		ready.push_front(*it);      //前插，自动向后推,优先级高的在前面
	  }
  }
//**************************************优先数调度算法***************************************
//初始化 用户输入进程标识，需要时间，计算优先数，按照优先级排序，插入就绪队列
void Insert1()
{
	multiset<PCB> m;
	multiset<PCB>::iterator it;
    multiset<PCB>::reverse_iterator rit;
	PCB temp;                      //进程
	int n;                         //进程数
	cout << "请输入进程数:" << endl;
	cin >> n;
	cout << "请输入每个进程的进程名和需要的时间片数:" << endl;
	//输入信息，输出化后插入multiset排序
	for (int i = 0;i < n;i++)
	{
		cin >> temp.NAME >> temp.NEEDTIME;
		temp.PRIO = 50 - temp.NEEDTIME;
		temp.ROUND = 0;
		temp.STATE = 'W';
		temp.count = 0;
		temp.CPUTIME = 0;
		m.insert(temp);
	}
	//插入就绪队列
	for (it = m.begin();it != m.end();it++)
	{
		ready.push_front(*it);    //前插，自动向后推,优先级高的在前面
	}
	cout << "name" << "\t" << "cputime" << "\t" << "   needtime" << "\t" << "priority" << "\t" << "state" << endl;
	Print();
}

//按优先级进行进程调度
void Prisch()
{
	PCB temp,temp1;
    while (1)
   {
	  if (run.empty())         //运行队列为空  ,第一次或运行完成
	  {
		if (ready.empty())      //就绪队列也为空 ,最后运行完
		 {
			 cout<<"当前没有需要运行进程！！！"<<endl;
			 break;
	     }
		else                   //就绪队列存在需要运行的程序,第一次
		{
			temp = ready.front();//得到就绪队列首元素
			temp.STATE = 'R';    //进程转为运行态
			run.push_front(temp);//插入运行队列队首
			ready.pop_front(); //就绪队列首元素出队	 	
			Print();
		}
	}
	else //运行队列非空,运行进程并判断
	{
		//运行进程
		run.front().CPUTIME++; //占用cpu一次
		run.front().NEEDTIME--;//需要时间减少
		run.front().PRIO--;    //优先级降低
		//判断状态
		if (run.front().NEEDTIME==0)  //运行完毕
		{
			temp = run.front();
			temp.STATE = 'F';          //状态改为完成
			finish.push_back(temp);  //插入完成队列
			run.pop_front();         //运行队列出队,运行队列为空
		}
		else //未运行完,判断和就绪队列队首的优先级
		{
			if(ready.empty())        //没有就绪的了
			{}
			else
			{
				Sort();
				temp = run.front();       //暂存run首进程
				temp1 = ready.front();    //暂存ready首进程
				if(temp.PRIO<temp1.PRIO)//需要换
				{	
					run.pop_front();    //run出队
					ready.pop_front();  //ready出队
					temp.STATE = 'W';
					temp1.STATE = 'R';
					run.push_front(temp1);//run前插,,,之前插错了
					ready.push_front(temp);//ready前插
				}
				else{}//不需要换，回去继续运行
			}
		}
        Print();
	}	
   }//while结束
}
//**************************************循环轮转调度算法***************************************
//循环轮转调度算法,插入就绪队列
void Insert2()           
{
	PCB temp;             //进程
	int n;                //进程数
	cout << "请输入进程数:" << endl;
	cin >> n;
	cout << "请输入每个进程的进程名和需要的时间片数:" << endl;
	//输入信息，FCFS策略，从后插入就绪队列
	for (int i = 0;i < n;i++)
	{
		cin >> temp.NAME >> temp.NEEDTIME;
		temp.PRIO = i;
		temp.ROUND = 2;
		temp.STATE = 'W';
		temp.count = 0;
		temp.CPUTIME = 0;
		ready.push_back(temp);   //后插
	}
	cout << "name" << "\t" << "cputime" << "\t" << "   needtime" << "\t" << "priority" << "\t" << "state" << endl;
    Display(ready);
}
//循环轮转调度算法
void Roundsch() 
{
	PCB temp,temp1;
	int temp_round;
	while (1)
	{
	  if (run.empty())              //运行队列为空  ,第一次或运行完成
	  {
		  if (ready.empty()) 
		  {
			  cout << "当前没有需要运行进程！！！" << endl;
			  break;
		  }
		  else                     //就绪队列存在需要运行的进程
		  {
			temp = ready.front();    //得到就绪队列首元素
			temp.STATE = 'R';        //进程转为运行态
			run.push_front(temp);  //插入运行队列队首
			ready.pop_front();     //就绪队列首元素出队
			for(int i = 0;i<ready.size();i++)//调整优先级
			{
				ready[i].PRIO = i;
			}
		  }
	  }
	  else                             //存在正在运行的进程
	  {
		  temp_round = run.front().ROUND;
		  while(temp_round)            //运行一个时间片,可在初始化时定义
		  {
			//运行进程
			run.front().CPUTIME++;     //占用cpu一次
			run.front().NEEDTIME--;    //需要时间减少
			temp_round--;              //时间减少
			cout << run.front().NAME << " is running..." << endl;
			//判断进程是否运行完
			if (run.front().NEEDTIME == 0) //进程完成,放入完成队列
			{
                cout << run.front().NAME << "运行完毕,主动中断..." << endl;
				temp = run.front();
				temp.STATE = 'F';
				run.pop_front();
				finish.push_back(temp);
				break;
			}
			else                        //进程未运行完成
			{
			  if (temp_round==0)         //时间片用光但未完成,被中断
			  {
				cout << "中断处理程序被激活," << run.front().NAME << "被中断..." << endl;
			    temp = run.front();      //暂存run首进程
				run.pop_front();        //run出队
				temp.STATE = 'W';
				temp.PRIO = ready.size();
				ready.push_back(temp);  //排到ready后
			  }
			  else 
				  continue;             //时间片没用光
			}
		  }
	  }
	  Print();
	}
}
void menu()
{
 cout << "*************1.优先数调度算法  2.循环轮转调度算法(时间片为2,优先级按先后顺序)********" << endl;
 cout << "*************3.退出****************" << endl;
 cout << "请输入算法序号:" << endl;
}