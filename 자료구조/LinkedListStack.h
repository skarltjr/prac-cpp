#pragma once
#include"SingleLinkedList.h"

inline int error(const char* str) //����� �� const�ٿ��ִ� ���� ����.
{
	std::cerr << str << std::endl; // ������ ��Ÿ���� cout ��� cerr�� ���� ��
	exit(1);  //1�� ������ �� �Լ��� ���ɶ��� ������ �����̱⶧���� �����ΰ�츸 0�� ����.
};

class LinkedlistStack : public s_linked_list
{
public:
	LinkedlistStack():s_linked_list	(){} //LinkedlistStack�����ڸ� s_linked_list�� �Ȱ��� �ϰڴ�.
	bool isEmpty()
	{
		return Size() == 0;
	}
	void push(int e)
	{
		push_front(e);
	}
	int pop()
	{
		if (isEmpty())
		{
			error("������ ����ֽ��ϴ�");
		}
		return pop_front();
	}
	int peek()
	{
		if (isEmpty())
		{
			error("������ ����ֽ��ϴ�");
		}
		return head->data;
	}
	void display()
	{
		node* ptr = head;
		for (int i = 0; i < Size(); i++)
		{
			std::cout << " [" << ptr->data << " ]";
			ptr = ptr->next;
		}
		std::cout << "\n";
	}
};

