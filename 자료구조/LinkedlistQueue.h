#pragma once
#include<iostream> // ���Ḯ��Ʈ�� ť �����ϱ�.���Լ���
//�׷� �����͸� �ǵڿ� �ְ� ������ �տ��������ϸ� �������� ���� �����ȴ�. ��
#include"SingleLinkedList.h"
#define MAX_QUEUE_SIZE	100
inline void error(const char* str)
{
	std::cerr << str << "\n";
	exit(1);
};

class LinkedlistQueue : public s_linked_list
{
public:
	LinkedlistQueue()
		:s_linked_list()
	{}
	~LinkedlistQueue() {}
	bool isEmpty() { return Size() == 0; } // �̱۸���Ʈ �Լ��߿� ����� Ȯ���ϴ� �Լ��� �ִµ� �̰� 0�̸� ����ִ�.
	void enqueue(int e)
	{
		push_back(e);
	}
	int dequeue()
	{
		if (isEmpty())
		{
			error("ť�� ����ֽ��ϴ�.\n");
		}
		else
		{
			return pop_front();
		}
	}
	int peek()
	{
		if (isEmpty())
		{
			error("ť�� ������ϴ�.\n");
		}
		else
		{
			return head->data;
		}
	}
	void display()
	{
		std::cout << " ť �ȿ��� : " << std::endl;
		node* ptr = head;
		while (ptr != nullptr) {
			std::cout << ptr->data << "->";
			ptr = ptr->next;
		}
		std::cout << "nullptr" << "\n";
	}
};