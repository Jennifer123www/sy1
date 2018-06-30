
/*
*��Ŀ�����̵���ģ���㷨
*���ߣ������
*ʱ�䣺2018-04-25
*�汾�ţ�3

*��Ŀ˵�����ֱ������ֵ����㷨��������̽��е��ȡ�ÿ�����̿�������״̬��ִ��״̬��RUN���� ����״̬��READY,�����ȴ�״̬�������״̬��FINISH�������ٶ���ʼ״̬Ϊ����״̬��
��һ�����̿��ƿ�ṹ���£�
NAME�������̱�ʾ�� 
PRIO/ROUND��������������/����ÿ����ת��ʱ��Ƭ������Ϊ���� 2�� 
CPUTIME���������ۼ�ռ�� CPU ��ʱ��Ƭ�� 
NEEDTIME�������̵���ɻ���Ҫ��ʱ��Ƭ��
STATE��������״̬ NEXT������ָ��
ע��
1.Ϊ�˱��ڴ��������н��̵ĵ�����ʱ����ʱ��ƬΪ��λ���м��㣻
2.�����̵�����������תʱ��Ƭ�����Լ���������ʱ��Ƭ���ĳ�ֵ�������û��ڳ����� ��ʱ������
���������̵ľ���̬�͵ȴ�̬��Ϊ����ṹ�������ĸ�ָ�����£�
RUN������ǰ���н���ָ�� READY�����������ͷָ�� TAIL���� �������βָ�� FINISH���� ��ɶ���ͷָ��
����������˵��
1. ���������㷨�У������������ĳ�ֵ��Ϊ��
50-NEEDTIME
ÿִ��һ�Σ��������� 1��CPU ʱ��Ƭ���� 1�����̻���Ҫ��ʱ��Ƭ���� 1�� ����ת���У����ù̶�ʱ��Ƭ��λ������ʱ��ƬΪһ����λ��������ÿ��תһ�Σ�CPU
ʱ��Ƭ���� 2�����̻���Ҫ��ʱ��Ƭ���� 2�����˳� CPU���ŵ���������β���ȴ���һ�ε� �ȡ�
2.  �����ģ��ṹ��ʾ���£�
���������������������� 7 ��������ɣ�
��1��INSERT1�������������㷨�У�����δ��ɵ� PCB ��������˳����뵽��������
�У�
��2��INSERT2��������ת���У���ִ����һ��ʱ��Ƭ��λ��Ϊ 2��������δ��ɵĽ���
�� PCB���嵽�������еĶ�β��
��3��FIRSTIN�������Ⱦ������еĵ�һ������Ͷ�����У�
��4��PRINT������ʾÿִ��һ�κ����н��̵�״̬���й���Ϣ��
��5��CREATE���������½��̣��������� PCB ����������У�
��6��PRISCH�������������㷨���Ƚ��̣�
��7��ROUNDSCH������ʱ��Ƭ��ת�����Ƚ��̡� �������� PCB �ṹ�������йر�����
���ģ����к���ʾ
����ʼ���к�������ʾ�����û�ѡ���㷨���������������Ӧ�� NEEDTIME ֵ�� ÿ����ʾ�����Ϊ���� 5 ���ֶΣ�
name	cputime	needtime	priority	state
ע��
1���� state �ֶ��У�"R"����ִ��̬��"W"����������ȴ���̬��"F"�������̬��
2��Ӧ����ʾ"R"̬�ģ�����ʾ"W"̬�ģ�����ʾ"F"̬�ġ�
3����"W"̬�У����������ߵͻ���ת˳���Ŷӣ���"F"̬�У�������Ⱥ�˳���Ŷӡ�
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
typedef struct node       //����ڵ�ṹ
{
	int PRIO;             //�������ȼ�
	string NAME;          //���̱�ʶ��
	int ROUND;            //��תʱ��Ƭ��
	int CPUTIME;          //�����ۼ�ռ��CPU����ʱ��Ƭ��
	int NEEDTIME;         //���̻���Ҫ��ʱ��Ƭ��
	char STATE;           //����״̬ "R"����ִ��̬��"W"����������ȴ���̬��"F"�������̬
	int count;            //��¼ִ�еĴ���
} PCB;

int num;

//����<
bool operator < (const PCB &a,const PCB &b)
{
	bool flag;
	a.PRIO < b.PRIO?flag = true:flag = false;
	return flag;
}

//����<<
ostream& operator << (ostream &os,const PCB &p)
{
	os << p.NAME << "\t" << p.CPUTIME << "\t" << p.NEEDTIME << "\t"<<p.PRIO << "\t" << p.STATE << endl;
	return os;
}

//������������,�������У����ж��У���ɶ���
deque<node> ready,run,finish; 

//��ʾ��������
 void Display(deque <node> d)
 {
	 int i;
	 for( i = 0;i < d.size();i++)
	    cout << d[i].NAME << "\t   " << d[i].CPUTIME << "\t      " << d[i].NEEDTIME << "\t\t     " << d[i].PRIO << "\t\t  " << d[i].STATE << endl;
 }

//��ʾÿִ��һ�κ����н��̵�״̬���й���Ϣ
 void Print()
 {
  	cout << "---------------------------------------------------" << endl;
	if (!ready.empty()) Display(ready);      //�����������
	if (!run.empty()) Display(run);          //������ж���
	if (!finish.empty()) Display(finish);    //�����ɶ���
 }

  //������������
  void Sort()
  {
	  multiset<PCB> m;
	  multiset<PCB>::iterator it;
	  for (int i = 0;i < ready.size();i++)
	  {
		  m.insert(ready[i]);
	  }
	  ready.clear();                //���
	 for (it = m.begin();it != m.end();it++)
	  {
		ready.push_front(*it);      //ǰ�壬�Զ������,���ȼ��ߵ���ǰ��
	  }
  }
//**************************************�����������㷨***************************************
//��ʼ�� �û�������̱�ʶ����Ҫʱ�䣬�������������������ȼ����򣬲����������
void Insert1()
{
	multiset<PCB> m;
	multiset<PCB>::iterator it;
    multiset<PCB>::reverse_iterator rit;
	PCB temp;                      //����
	int n;                         //������
	cout << "�����������:" << endl;
	cin >> n;
	cout << "������ÿ�����̵Ľ���������Ҫ��ʱ��Ƭ��:" << endl;
	//������Ϣ������������multiset����
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
	//�����������
	for (it = m.begin();it != m.end();it++)
	{
		ready.push_front(*it);    //ǰ�壬�Զ������,���ȼ��ߵ���ǰ��
	}
	cout << "name" << "\t" << "cputime" << "\t" << "   needtime" << "\t" << "priority" << "\t" << "state" << endl;
	Print();
}

//�����ȼ����н��̵���
void Prisch()
{
	PCB temp,temp1;
    while (1)
   {
	  if (run.empty())         //���ж���Ϊ��  ,��һ�λ��������
	  {
		if (ready.empty())      //��������ҲΪ�� ,���������
		 {
			 cout<<"��ǰû����Ҫ���н��̣�����"<<endl;
			 break;
	     }
		else                   //�������д�����Ҫ���еĳ���,��һ��
		{
			temp = ready.front();//�õ�����������Ԫ��
			temp.STATE = 'R';    //����תΪ����̬
			run.push_front(temp);//�������ж��ж���
			ready.pop_front(); //����������Ԫ�س���	 	
			Print();
		}
	}
	else //���ж��зǿ�,���н��̲��ж�
	{
		//���н���
		run.front().CPUTIME++; //ռ��cpuһ��
		run.front().NEEDTIME--;//��Ҫʱ�����
		run.front().PRIO--;    //���ȼ�����
		//�ж�״̬
		if (run.front().NEEDTIME==0)  //�������
		{
			temp = run.front();
			temp.STATE = 'F';          //״̬��Ϊ���
			finish.push_back(temp);  //������ɶ���
			run.pop_front();         //���ж��г���,���ж���Ϊ��
		}
		else //δ������,�жϺ;������ж��׵����ȼ�
		{
			if(ready.empty())        //û�о�������
			{}
			else
			{
				Sort();
				temp = run.front();       //�ݴ�run�׽���
				temp1 = ready.front();    //�ݴ�ready�׽���
				if(temp.PRIO<temp1.PRIO)//��Ҫ��
				{	
					run.pop_front();    //run����
					ready.pop_front();  //ready����
					temp.STATE = 'W';
					temp1.STATE = 'R';
					run.push_front(temp1);//runǰ��,,,֮ǰ�����
					ready.push_front(temp);//readyǰ��
				}
				else{}//����Ҫ������ȥ��������
			}
		}
        Print();
	}	
   }//while����
}
//**************************************ѭ����ת�����㷨***************************************
//ѭ����ת�����㷨,�����������
void Insert2()           
{
	PCB temp;             //����
	int n;                //������
	cout << "�����������:" << endl;
	cin >> n;
	cout << "������ÿ�����̵Ľ���������Ҫ��ʱ��Ƭ��:" << endl;
	//������Ϣ��FCFS���ԣ��Ӻ�����������
	for (int i = 0;i < n;i++)
	{
		cin >> temp.NAME >> temp.NEEDTIME;
		temp.PRIO = i;
		temp.ROUND = 2;
		temp.STATE = 'W';
		temp.count = 0;
		temp.CPUTIME = 0;
		ready.push_back(temp);   //���
	}
	cout << "name" << "\t" << "cputime" << "\t" << "   needtime" << "\t" << "priority" << "\t" << "state" << endl;
    Display(ready);
}
//ѭ����ת�����㷨
void Roundsch() 
{
	PCB temp,temp1;
	int temp_round;
	while (1)
	{
	  if (run.empty())              //���ж���Ϊ��  ,��һ�λ��������
	  {
		  if (ready.empty()) 
		  {
			  cout << "��ǰû����Ҫ���н��̣�����" << endl;
			  break;
		  }
		  else                     //�������д�����Ҫ���еĽ���
		  {
			temp = ready.front();    //�õ�����������Ԫ��
			temp.STATE = 'R';        //����תΪ����̬
			run.push_front(temp);  //�������ж��ж���
			ready.pop_front();     //����������Ԫ�س���
			for(int i = 0;i<ready.size();i++)//�������ȼ�
			{
				ready[i].PRIO = i;
			}
		  }
	  }
	  else                             //�����������еĽ���
	  {
		  temp_round = run.front().ROUND;
		  while(temp_round)            //����һ��ʱ��Ƭ,���ڳ�ʼ��ʱ����
		  {
			//���н���
			run.front().CPUTIME++;     //ռ��cpuһ��
			run.front().NEEDTIME--;    //��Ҫʱ�����
			temp_round--;              //ʱ�����
			cout << run.front().NAME << " is running..." << endl;
			//�жϽ����Ƿ�������
			if (run.front().NEEDTIME == 0) //�������,������ɶ���
			{
                cout << run.front().NAME << "�������,�����ж�..." << endl;
				temp = run.front();
				temp.STATE = 'F';
				run.pop_front();
				finish.push_back(temp);
				break;
			}
			else                        //����δ�������
			{
			  if (temp_round==0)         //ʱ��Ƭ�ù⵫δ���,���ж�
			  {
				cout << "�жϴ�����򱻼���," << run.front().NAME << "���ж�..." << endl;
			    temp = run.front();      //�ݴ�run�׽���
				run.pop_front();        //run����
				temp.STATE = 'W';
				temp.PRIO = ready.size();
				ready.push_back(temp);  //�ŵ�ready��
			  }
			  else 
				  continue;             //ʱ��Ƭû�ù�
			}
		  }
	  }
	  Print();
	}
}
void menu()
{
 cout << "*************1.�����������㷨  2.ѭ����ת�����㷨(ʱ��ƬΪ2,���ȼ����Ⱥ�˳��)********" << endl;
 cout << "*************3.�˳�****************" << endl;
 cout << "�������㷨���:" << endl;
}