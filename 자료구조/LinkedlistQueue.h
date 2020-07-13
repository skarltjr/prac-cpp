#pragma once
#include<iostream> // 연결리스트로 큐 구현하기.선입선출
//그럼 데이터를 맨뒤에 넣고 삭제는 앞에서부터하면 먼저들어간게 먼저 삭제된다. ★
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
	bool isEmpty() { return Size() == 0; } // 싱글리스트 함수중에 사이즈를 확인하는 함수가 있는데 이게 0이면 비어있다.
	void enqueue(int e)
	{
		push_back(e);
	}
	int dequeue()
	{
		if (isEmpty())
		{
			error("큐가 비어있습니다.\n");
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
			error("큐가 비었습니다.\n");
		}
		else
		{
			return head->data;
		}
	}
	void display()
	{
		std::cout << " 큐 안에는 : " << std::endl;
		node* ptr = head;
		while (ptr != nullptr) {
			std::cout << ptr->data << "->";
			ptr = ptr->next;
		}
		std::cout << "nullptr" << "\n";
	}
};