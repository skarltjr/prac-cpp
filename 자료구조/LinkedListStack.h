#pragma once
#include"SingleLinkedList.h"

inline int error(const char* str) //상수일 때 const붙여주는 습관 갖자.
{
	std::cerr << str << std::endl; // 에러를 나타낼때 cout 대신 cerr을 쓰는 법
	exit(1);  //1인 이유는 이 함수가 사용될때는 비정상 종료이기때문에 정상인경우만 0을 쓴다.
};

class LinkedlistStack : public s_linked_list
{
public:
	LinkedlistStack():s_linked_list	(){} //LinkedlistStack생성자를 s_linked_list와 똑같이 하겠다.
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
			error("스택이 비어있습니다");
		}
		return pop_front();
	}
	int peek()
	{
		if (isEmpty())
		{
			error("스택이 비어있습니다");
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

