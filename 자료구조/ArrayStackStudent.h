#pragma once
#include<iostream>
#include<string>
#include"Student.h"
#define MAX_STACK_SIZE 100

inline int error(const char* str) //����� �� const�ٿ��ִ� ���� ����.
{
	std::cerr << str << std::endl; // ������ ��Ÿ���� cout ��� cerr�� ���� ��
	exit(1);  //1�� ������ �� �Լ��� ���ɶ��� ������ �����̱⶧���� �����ΰ�츸 0�� ����.
}


class ArrayStack
{
private:
	Student data[MAX_STACK_SIZE];
	int top; // ����� ��ġ�� �� �� �ְ����ִ� ����
public:
	ArrayStack()
	{
		top = -1; // ������ �迭�� �����. �׷� �� ù��°. �ǾƷ��� 0������ �������ٵ� ��������� �˷��ֱ����� 0���� ���� -1���
	}
	~ArrayStack() {}
	bool isEmpty() { return top == -1; }//top=-1�̸� �翬�� ����ִ� ����
	bool isFull() { return top == MAX_STACK_SIZE - 1; }//0���� �����̴ϱ� ���� 99���� ����
	void push(Student e)
	{
		if (isFull())
		{
			error("������ ���� �� �ֽ��ϴ�.");
		}
		data[++top] = e; //�� ���� ���� �߰��ϱ� top�� ++�� ��ġ�� e�� �־��ش� ++top�� ������ ������ ���� ������ϴϱ�
	}

	Student pop() // �����͸� ���� �����ִ� �Լ�. �翬�� ���⼱ ���������͸� �Է¹����� �����ٶ��� int���̾���Ѵ�
	{
		if (isEmpty())
		{
			error("������ ����ֽ��ϴ�");
		}
		return data[top--]; //top-- �� ������ top�� �����͸� ������ ��! �� top�� �����ϴϱ� ������ �ٱ� ����
	}

	Student peek()
	{
		if (isEmpty())
		{
			error("������ ����ֽ��ϴ�");
		}
		return data[top];
	}

	void display()
	{
		std::cout << "���� �׸��� ��= " << top + 1 << "�� "; // top�� 0���ͽ����̴ϱ�
		//size ������ ����� �� �ʿ䰡���°� size�� ������ top+1�̶� ����.
		for (int i = 0; i <= top; i++)
		{
			std::cout << "[ " << data[i].contents() << " ]";
		}
		std::cout << std::endl;
	}
};	