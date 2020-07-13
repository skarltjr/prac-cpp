#pragma once
#include <iostream>
#include <vector>
#include <chrono>

struct node {
	int data;
	node* next;
};
// Single linked list�� ���� element�� ������ ������ ������.
// node�� �� ���� �ڷḦ ���մϴ�.
// �̹����� ���ϰ� int�θ� ����ϴٸ�, � �ڷ����� ���� �� �ְ���.
// Stack�� Queue�� ���� �ֿ� �̰��� Ȱ���ؼ� Stack�� Queue�� ���ڽ��ϴ�.
// C++������ template <typename T> ���·� �پ��� �ڷ����� ���� �� ���� �����ϴ�
// template�� �� �� �ֽ��ϴٸ�, ���ذ� ���������� ������ int�� �ȴٰ� ���ô�.

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
	} //�Ҹ���

	// ���Կ����
	void push_front(int n); // ��带 �� �տ� �� �� �߰��մϴ�.
	void push_back(int n); // ��带 ���� �� �� �߰��մϴ�.
	void insert_node_at(int idx, int n); // ������ ��ġ�� �߰��մϴ�.

	// ���������
	int pop_front(); // �� �� ��带 ����ϴ�.
	int pop_back(); // �� ��带 ����ϴ�. 
	int pop_node_at(int idx); // idx ��ġ�� ��带 ����ϴ�.
	void remove_node(int n); // ���� ���� ��带 �� �� ����ϴ�.	
	void delete_list(); // linked list ��ü�� ����ϴ�.

	// ����
	void replace_value_at(int idx, int n);	

	// �˻� �� ǥ��
	int Size();
	void display_contents(); // linked list�� ������ �����ݴϴ�.
	int search_value(int n); // n�� ���� ���� �ε����� ��ȯ�մϴ�.
	int lookup_value_at(int n); // n�� ���� ���� �ε����� ��ȯ�մϴ�.

};

// ���Կ����
void s_linked_list::push_front(int n) { // ����Ʈ�� �� �տ� ��带 �߰��մϴ�.
	node* ptr = new node; // �� ����� �޸𸮸� �Ҵ����ְ�
	ptr->next = head;
	ptr->data = n;
	head = ptr;
	if (ptr->next == nullptr) {
		tail = ptr;
	}
	size++;
}

void s_linked_list::push_back(int n) { // ����Ʈ�� ���� ��带 �߰��մϴ�.
	node* tmp = new node; // �� ����� �޸𸮸� �Ҵ����ְ�
	size++;
	tmp->data = n;
	tmp->next = nullptr;
	if (head == nullptr) {// head�� ���ٸ� �翬�� tail�� ������. 
		head = tmp;
		tail = tmp;
	}
	else {
		tail->next = tmp;
		tail = tail->next;
	}
}

void s_linked_list::insert_node_at(int idx, int n) { // index�� �ִ� ���� ����ϴ�.
	if (size < idx || 0 > idx) {
		std::cout << "�ش� �ε����� �������� �ʽ��ϴ�\n";
	}
	else {
		node* ptr = head;
		node* tmp = ptr;
		node* new_node = new node;
		new_node->data = n;
		new_node->next = nullptr; // �� node�� �ϴ� �ʱ�ȭ���ݴϴ�.
		for (int i = 0; i < idx; i++) {
			tmp = ptr; // �� ����� ���� ��� ��ġ
			ptr = ptr->next; // �� ����� ��ġ
		}
		tmp->next = new_node;
		new_node->next = ptr;
		size++; // ��带 �����մϴ�.
	}
}

// ��������
int s_linked_list::pop_front() { // ����Ʈ�� �� �� ��带 ����ϴ�.
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

int s_linked_list::pop_node_at(int idx) { // index�� �ִ� ���� ����ϴ�.
	int value = -1;
	if (size < idx || 0 > idx) {
		std::cout << "�ش� �ε����� �������� �ʽ��ϴ�\n";
	}
	else {
		node* ptr = head;
		node* tmp = ptr;
		for (int i = 0; i < idx; i++) {
			tmp = ptr; // ���� ��带 tmp�� �ΰ�
			ptr = ptr->next; // ���� ���� Ÿ���� �ٲߴϴ�.
		}
		//std::cout << ptr->data << "���� ��带 �ϳ� ����ϴ�\n";
		value = ptr->data;
		tmp->next = ptr->next; // ������ ��带 ���� �����ϰ�
		if (ptr == tail) {
			tail = tmp;
		}
		size--; // ��带 �����մϴ�.
		delete ptr;
	}
	return value;
}

void s_linked_list::remove_node(int n) { // ���� ã�Ƽ� �� ���� ����ϴ�.
	node* ptr = head;
	node* tmp = ptr;
	while (ptr != nullptr) {
		if (ptr->data == n) {
			break;
		}
		else {
			tmp = ptr; // ���� ��带 tmp�� �ΰ�
			ptr = ptr->next; // ���� ���� Ÿ���� �ٲߴϴ�.
		}
	}
	if (ptr == nullptr) {
		std::cout << "���� ���� �������� �ʽ��ϴ�\n";
	}
	else {
		size--;
		std::cout << ptr->data << "���� ��带 �ϳ� ����ϴ�\n";
		tmp->next = ptr->next; // ������ ��带 ���� �����ϰ�
		if (ptr == tail) {
			tail = tmp;
		}
		delete ptr; // ���� �Ҵ��� �����մϴ�		
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
	std::cout << "����Ʈ�� �����Ǿ����ϴ� \n";
}

// ����
void s_linked_list::replace_value_at(int idx, int n) {
	node* ptr = head;
	if (size < idx || 0 > idx) {
		std::cout << "�ش� �ε����� �������� �ʽ��ϴ�\n";
	}
	else {
		for (int i = 0; i < idx; i++) {
			ptr = ptr->next; // �� ����� ��ġ
		}
		ptr->data = n;
	}
}

// �˻� �� ǥ��
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
			std::cout << n << " �� " << idx << " �� �ֽ��ϴ�.\n";
			isFind = true;
			break;
		}
		ptr = ptr->next;
		idx++;
	}
	if (isFind == false) {
		std::cout << n << " �� ����Ʈ �ȿ� �����ϴ�.\n";
		return -1;
	}
	else {
		return idx;
	}
}