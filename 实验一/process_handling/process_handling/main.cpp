#include "head.h"
int main()
{
 cout<<"*************��ӭ������̵���ģ���㷨����****************"<<endl;
 while (1)
 {
   menu();                             //��ʾ�˵�
   int i;                              //����ѡ���㷨�����
   cin >> i; 
   if (i==3)
	   break;
   switch(i)
   {
   case 1:                             //�����������㷨
		    Insert1();                 //�û�������̱�ʶ����Ҫʱ�䣬�������������������ȼ����򣬲����������
		    Prisch();                  //�����ȼ����н��̵���
			run.clear();               //���ִ�ж���
			ready.clear();             //��վ�������
	 		finish.clear();            //�����ɶ���
		    break;                     
   case 2:                             //ѭ����ת�����㷨
	        Insert2();                 //�����������
		    Roundsch();                //ѭ����ת�����㷨
		   	run.clear();               //���ִ�ж���
			ready.clear();             //��վ�������
			finish.clear();            //�����ɶ���
	        break;
   default:
	   cout << "�������" << endl;
   }
 }
 return 0;
}
