#pragma once
#include<iostream>
inline void error(const char* str)
{
	std::cerr << str << std::endl;
	exit(1);
}

class node
{
private:
	int data;
	node* next;
public:
	node(int val = 0)
	{
		data = val;
		next = nullptr;
	}
	node* getLink() { return next; } // 구조체로 node를 만들었을 땐 next에 바로 접근이 가능했지만
	//객체지향에선 안전하게 함수로 리턴해주는게 맞다.
	int getData() { return data; }
	void setLink(node* target) { next = target; }

	void insertNext(node* newnode)
	{
		if (newnode != nullptr)
		{
			newnode->next = next; //a-b()-c가 있을 때 (n)에 추가하기위해 n을 c와 연결 
			next = newnode;	//b와 n을 연결
		}
	}
	node* removeNext()
	{
		node* removed = next;
		if (removed != nullptr)
		{
			next = removed->next;
		}
		return removed;
	}
};
class hn_s_linked_list
{
protected:
	node origin;
public:
	hn_s_linked_list()
		:origin(0) {}
	~hn_s_linked_list() { clear(); }
	void clear();
	node* getHead();
	bool isEmpty();
	node* getEntry(int pos);
	void insert(int pos, node* n);
	node* remove(int pos);
	node* find(int value);
	void replace(int pos, node* n);
	size_t size();
	void display();

};
void hn_s_linked_list::clear()
{
	while (!isEmpty())
	{
		delete remove(0);
	}
}
node* hn_s_linked_list::getHead()
{
	return origin.getLink(); //origin의 다음 노드가 실제 헤드 노드가된다. 오리진은 그 앞에 가상
}
bool hn_s_linked_list::isEmpty()
{
	return getHead() == nullptr;
}
node* hn_s_linked_list::getEntry(int pos)
{
	node* n = &origin;
	for (int i = -1; i < pos; i++, n = n->getLink()) // for 문 안에서 연산 여러개 가능
							//여기서 부터 i++랑 n=n->getLink가 같이 일어난다. 
	{
		if (n == nullptr)
		{
			break;
		}
		return n;
	}
}
void hn_s_linked_list::insert(int pos, node* n)
{
	node* prev = getEntry(pos - 1);
	if (prev != nullptr)
	{
		prev->insertNext(n);
	}
}
node* hn_s_linked_list::remove(int pos)
{
	node* prev = getEntry(pos - 1);
	if (prev != nullptr)
	{
		prev->removeNext();
	}
}
node* hn_s_linked_list::find(int value)
{
	for (node* p = getHead(); p != nullptr; p->getLink())
	{
		if (p->getData() == value)
		{
			return p;
		}return nullptr;
	}
}
void hn_s_linked_list::replace(int pos, node* n)
{
	node* prev = getEntry(pos - 1);
	if (prev != nullptr)
	{
		delete prev->removeNext();
		prev->insertNext(n);
	}
}
size_t hn_s_linked_list::size()
{
	int count = 0;
	for (node* p = getHead(); p != nullptr; p->getLink())
	{
		count++;
	}
	return count;
}
void hn_s_linked_list::display()
{
	int count = 0;
	std::cout << " 전체 항목의 수  :" << size() << ", ";
	for (node* p = getHead(); p != nullptr; p->getLink())
	{
		std::cout << p->getData() << " ";

	}
}