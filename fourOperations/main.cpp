/*************************************************************************
	> File Name: main.cpp
	> Author: wangning
	> Mail: 201207wangning@edu2act.org
	> Created Time: 2013��09��05�� ������ 14ʱ40��43��
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "fourOperations.h"

using namespace std;

int main()
{
    char choice;

    cout << "\n��ӭʹ����������С����\n" << endl;
   
	while(1)
	{
		cout << "\n��ѡ���������:" << endl;
		cout << "A:�ӷ�����" << endl;
		cout << "S:��������" << endl;
		cout << "M:�˷�����" << endl;
		cout << "D:��������" << endl;
		cout << "Q:�˳���������" << endl;

		cout << "��ѡ�����Ĳ�����";
		cin.get(choice);
		fflush(stdin);
		
		switch(choice)
		{
			case 'A': 
				addition();

				system("pause");
				fflush(stdin);			
				break;
			case 'S': 
				subtraction();

				system("pause");
				fflush(stdin);	
				break;
			case 'M':
				multiplication();

				system("pause");
				fflush(stdin);	
				break;
			case 'D': 
				division();

				system("pause");
				fflush(stdin);	
				break;
			case 'Q': return 0;
		
			default: 
				cout << "\n**********�����������������룡************\n" << endl;
		}
	}

    return 0;
}
