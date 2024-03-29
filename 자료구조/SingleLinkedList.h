#pragma once
#include <iostream>
#include <vector>
#include <chrono>

struct node {
	int data;
	node* next;
};
// Single linked list는 다음 element만 가지고 있으면 되지요.
// node는 한 개의 자료를 말합니다.
// 이번에는 편하게 int로만 만듭니다만, 어떤 자료형도 넣을 수 있겠죠.
// Stack과 Queue를 배우는 주에 이것을 활용해서 Stack과 Queue를 배우겠습니다.
// C++에서는 template <typename T> 형태로 다양한 자료형에 대해 한 번만 정의하는
// template를 쓸 수 있습니다만, 이해가 복잡해지니 오늘은 int만 된다고 봅시다.

class s_linked_list {
protected:
	node* head, * tail; // head: first node, tail: last node
	int size = 0;
public:
	s_linked_list() {
		head = nullptr;
		tail = nullptr;
	}
	~s_linked_list() {
		delete_list();
	} //소멸자

	// 삽입연산들
	void push_front(int n); // 노드를 맨 앞에 한 개 추가합니다.
	void push_back(int n); // 노드를 끝에 한 개 추가합니다.
	void insert_node_at(int idx, int n); // 정해진 위치에 추가합니다.

	// 삭제연산들
	int pop_front(); // 맨 앞 노드를 지웁니다.
	int pop_back(); // 끝 노드를 지웁니다. 
	int pop_node_at(int idx); // idx 위치의 노드를 지웁니다.
	void remove_node(int n); // 값과 같은 노드를 한 개 지웁니다.	
	void delete_list(); // linked list 전체를 지웁니다.

	// 대입
	void replace_value_at(int idx, int n);	

	// 검색 및 표시
	int Size();
	void display_contents(); // linked list의 내용을 보여줍니다.
	int search_value(int n); // n과 같은 값의 인덱스를 반환합니다.
	int lookup_value_at(int n); // n과 같은 값의 인덱스를 반환합니다.

};

// 삽입연산들
void s_linked_list::push_front(int n) { // 리스트의 맨 앞에 노드를 추가합니다.
	node* ptr = new node; // 새 노드의 메모리를 할당해주고
	ptr->next = head;
	ptr->data = n;
	head = ptr;
	if (ptr->next == nullptr) {
		tail = ptr;
	}
	size++;
}

void s_linked_list::push_back(int n) { // 리스트의 끝에 노드를 추가합니다.
	node* tmp = new node; // 새 노드의 메모리를 할당해주고
	size++;
	tmp->data = n;
	tmp->next = nullptr;
	if (head == nullptr) {// head가 없다면 당연히 tail도 없겠죠. 
		head = tmp;
		tail = tmp;
	}
	else {
		tail->next = tmp;
		tail = tail->next;
	}
}

void s_linked_list::insert_node_at(int idx, int n) { // index에 있는 값을 지웁니다.
	if (size < idx || 0 > idx) {
		std::cout << "해당 인덱스는 존재하지 않습니다\n";
	}
	else {
		node* ptr = head;
		node* tmp = ptr;
		node* new_node = new node;
		new_node->data = n;
		new_node->next = nullptr; // 새 node를 일단 초기화해줍니다.
		for (int i = 0; i < idx; i++) {
			tmp = ptr; // 들어갈 노드의 직전 노드 위치
			ptr = ptr->next; // 들어갈 노드의 위치
		}
		tmp->next = new_node;
		new_node->next = ptr;
		size++; // 노드를 삽입합니다.
	}
}

// 삭제연산
int s_linked_list::pop_front() { // 리스트의 맨 앞 노드를 지웁니다.
	node* ptr = head;
	int value = head->data;
	head = ptr->next;
	delete ptr;
	size--;
	return value;
}

int s_linked_list::pop_back() {
	node* ptr = head;
	node* tmp = new node;
	while (ptr->next != nullptr) {
		tmp = ptr;
		ptr = ptr->next;
	}
	int value = ptr->data;
	tail = tmp;
	tail->next = nullptr;
	delete ptr;
	size--;
	return value;
}

int s_linked_list::pop_node_at(int idx) { // index에 있는 값을 지웁니다.
	int value = -1;
	if (size < idx || 0 > idx) {
		std::cout << "해당 인덱스는 존재하지 않습니다\n";
	}
	else {
		node* ptr = head;
		node* tmp = ptr;
		for (int i = 0; i < idx; i++) {
			tmp = ptr; // 현재 노드를 tmp로 두고
			ptr = ptr->next; // 다음 노드로 타겟을 바꿉니다.
		}
		//std::cout << ptr->data << "값의 노드를 하나 지웁니다\n";
		value = ptr->data;
		tmp->next = ptr->next; // 삭제할 노드를 빼고 연결하고
		if (ptr == tail) {
			tail = tmp;
		}
		size--; // 노드를 삽입합니다.
		delete ptr;
	}
	return value;
}

void s_linked_list::remove_node(int n) { // 값을 찾아서 한 개를 지웁니다.
	node* ptr = head;
	node* tmp = ptr;
	while (ptr != nullptr) {
		if (ptr->data == n) {
			break;
		}
		else {
			tmp = ptr; // 현재 노드를 tmp로 두고
			ptr = ptr->next; // 다음 노드로 타겟을 바꿉니다.
		}
	}
	if (ptr == nullptr) {
		std::cout << "값의 노드는 존재하지 않습니다\n";
	}
	else {
		size--;
		std::cout << ptr->data << "값의 노드를 하나 지웁니다\n";
		tmp->next = ptr->next; // 삭제할 노드를 빼고 연결하고
		if (ptr == tail) {
			tail = tmp;
		}
		delete ptr; // 동적 할당을 해제합니다		
	}

}


void s_linked_list::delete_list() {
	node* ptr = head;
	while (ptr != nullptr) {
		head = ptr->next;
		delete ptr;
		ptr = head;
	}
	size = 0;
	std::cout << "리스트가 삭제되었습니다 \n";
}

// 대입
void s_linked_list::replace_value_at(int idx, int n) {
	node* ptr = head;
	if (size < idx || 0 > idx) {
		std::cout << "해당 인덱스는 존재하지 않습니다\n";
	}
	else {
		for (int i = 0; i < idx; i++) {
			ptr = ptr->next; // 들어갈 노드의 위치
		}
		ptr->data = n;
	}
}

// 검색 및 표시
int s_linked_list::Size() {
	return size;
}

void s_linked_list::display_contents() {
	node* ptr = head;
	while (ptr != nullptr) {
		std::cout << ptr->data << "->";
		ptr = ptr->next;
	}
	std::cout << "nullptr" << "\n";
}


int s_linked_list::search_value(int n) {
	node* ptr = head;
	int idx = 0;
	bool isFind = false;
	while (ptr != nullptr) {
		if (ptr->data == n) {
			std::cout << n << " 은 " << idx << " 에 있습니다.\n";
			isFind = true;
			break;
		}
		ptr = ptr->next;
		idx++;
	}
	if (isFind == false) {
		std::cout << n << " 은 리스트 안에 없습니다.\n";
		return -1;
	}
	else {
		return idx;
	}
}