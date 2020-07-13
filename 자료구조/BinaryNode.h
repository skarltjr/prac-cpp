#pragma once
#include<iostream>
#define MAX_QUEUE_SIZE 100

inline void error(const char* str) {
	std::cerr << str << "\n"; // ������ ���� std::cerr�� ����մϴ�.
	exit(1);
};

//======================================= level ��ȸ �����ϱ����ؼ� ����ť�� �ʿ���
class BinaryNode
{
protected:
	int data;
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(int val = 0, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
		:data(val), left(l), right(r) {}
	~BinaryNode() {}
	void setData(int val)
	{
		data = val;
	}
	void setLeft(BinaryNode* l)
	{
		left = l;
	}
	void setRight(BinaryNode* r)
	{
		right = r;
	}
	int getData()
	{
		return data;
	}
	BinaryNode* getLeft()
	{
		return left;
	}
	BinaryNode* getRight()
	{
		return right;
	}
	bool isLeaf()  //������ �ڽ����� Ȯ��
	{
		return left == nullptr && right == nullptr;
	}
};
class CircularQueue {
protected:
	int front; // ���� �� (�����͸� ������ ��ġ)
	int rear; // ���� �� (�����͸� �ִ� ��ġ)
	BinaryNode* data[MAX_QUEUE_SIZE];
public:
	CircularQueue() { front = rear = 0; }
	~CircularQueue() {}
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; } // ������ �������� ��ġ�� ã���ϴ�.
	void enqueue(BinaryNode* val) { // ť �� �ڿ� �����͸� �߰�
		if (isFull()) {
			error(" Error: ť�� ��ȭ�����Դϴ�\n");
		}
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = val;
		}
	}
	BinaryNode* dequeue() { // ť �� �տ��� �����͸� ����
		if (isEmpty()) {
			error(" Error: ť�� ��������Դϴ�\n");
		}
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};
class BinaryTree
{
protected:
	BinaryNode* root;
public:
	BinaryTree()
		:root(nullptr) {}
	~BinaryTree() {}
	void setRoot(BinaryNode* node)
	{
		root = node;
	}
	BinaryNode* getRoot()
	{
		return root;
	}
	bool isEmpty()
	{
		return root == nullptr; //��������� ����ִ� true
	}
	void preorder(BinaryNode* node)//������ȸ
	{
		std::cout << "[ " << node->getData() << " ]";  //��¸������ְ�! 
		if (node != nullptr)
		{
			if (node->getLeft() != nullptr)
			{
				preorder(node->getLeft());
			}
			if (node->getRight() != nullptr)
			{
				preorder(node->getRight());
			}
		}
	}
	void preorder()//�Ķ���� ���� �� ������ȸ
	{
		std::cout << "preorder: ";
		preorder(root);
	}
	//=====================================================================================
	void levelorder()
	{
		std::cout << "levelorder: ";
		if (!isEmpty())
		{
			CircularQueue q;
			q.enqueue(root);
			while (!q.isEmpty())
			{
				BinaryNode* n = q.dequeue();
				if (n != nullptr)
				{
					std::cout << " [" << n->getData() << "]";
					q.enqueue(n->getLeft());
					q.enqueue(n->getRight());
				}
			}
		}
	}
	//==================================================
	void inorder(BinaryNode* node)//������ȸ
	{
		if (node != nullptr)
		{
			if (node->getLeft() != nullptr)
			{
				inorder(node->getLeft());
			}
			std::cout << "[ " << node->getData() << " ]";
			if (node->getRight() != nullptr)
			{
				inorder(node->getRight());
			}
		}
	}
	void inorder()//�Ķ���� �ȹ޾��� �� ������ ��Ʈ���� �۵��Ѵٰ� ����
	{
		std::cout << "inorder: ";
		inorder(root);
	}
	//=========================================================================
	void postorder(BinaryNode* node)//������ȸ
	{
		if (node != nullptr)
		{
			if (node->getLeft() != nullptr)
			{
				postorder(node->getLeft());
			}
			if (node->getRight() != nullptr)
			{
				postorder(node->getRight());
			}
			std::cout << "[ " << node->getData() << " ]";
		}
	}
	void postorder()//�Ķ���� �ȹ޾��� �� ������ ��Ʈ���� �۵��Ѵٰ� ����
	{
		std::cout << "postorder: ";
		postorder(root);
	}
	//========================================================= �߰�����
	int getCount(BinaryNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			return 1 + getCount(node->getLeft()) + getCount(node->getRight());
			//��� �������� 
			//�̷������� ��ȯ�� ���� ���� ���Ѵٰ� ����
			//		2
			//	1		1		=1 + �ϱ� �ڱ��ڽ�.
			//0		0		0
		}
	}
	int getCount()
	{
		return isEmpty() ? 0 : getCount(root);
	}
	int getLeafCount(BinaryNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		if (node->isLeaf())
		{
			return 1;
		}
		else
		{
			return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
		}
	}
	int getLeafCount()//�ƹ��͵� �ȹ�����
	{
		return isEmpty() ? 0 : getLeafCount(root);
	}
	int getHeight(BinaryNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
	}
	int getHeight()
	{
		return isEmpty() ? 0 : getHeight(root);
	}
	//===============================���� Ʈ�� . ���� ��ȸ�� ���� ���� �뷮���
	//�Ƹ� �̰Ÿ��� ������ȸ�����ɷ� �ٸ��� ����ϱⰡ ������������
	int evaluate(BinaryNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		if (node->isLeaf())
		{
			return node->getData();
		}
		else
		{
			int op1 = evaluate(node->getLeft());
			int op2 = evaluate(node->getRight());
			switch (node->getData())
			{
			case '+':return op1 + op2;
			case'-':return  op1 - op2;
			case '*':return op1 * op2;
			case'/':return  op1 / op2;
			}
			return 0;
		}
	}
	int evaluate()
	{
		return evaluate(root);
	}
	int calSize(BinaryNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return node->getData() + calSize(node->getLeft()) + calSize(node->getRight());
	}
	int calSize()
	{
		return calSize(root);
	}
};
/*
int main()
{
	BinaryTree tree;
	//			1
	//		2		 3
	//	4		5  6		 ���� ���鿹��
	//�� �� a�� �� ù�ٿ� ����� ���������� �翬�� ���� b,c�� �� ����������� �׷��ϱ� �� ������ �����ؾ��Ѵ�.
	BinaryNode* d = new BinaryNode(4, nullptr, nullptr);
	BinaryNode* e = new BinaryNode(5, nullptr, nullptr);
	BinaryNode* b = new BinaryNode(2, d, e);
	BinaryNode* f = new BinaryNode(6, nullptr, nullptr);
	BinaryNode* c = new BinaryNode(3, f, nullptr);
	BinaryNode* a = new BinaryNode(1, b, c); //������ ��忡 ���� ������ ����������Ѵ�
	tree.setRoot(a);
	tree.preorder(); //1-2-4-5-3-6 �� ��µǴµ� �������� ���->����->�������̴ϱ�
	//1����ϰ� ���ʸ��� ���� 2������ ���⼭�� ��¿��� �������̴ϱ� 4���� �� ���� ������
	//2�� ������ 5���ٰ� ���ʿ����ʾ����� ���ư��� 1��  �������� 3��� , 3�� ���� 6
	std::cout << "\n";
	tree.inorder();
	std::cout << "\n";
	tree.postorder();
	std::cout << "\n";
	tree.levelorder();
	std::cout << "\n";

	std::cout << "����� ���� :" << tree.getCount() << "\n";
	std::cout << "�� ����� ����: " << tree.getLeafCount() << "\n";
	std::cout << "Ʈ���� ���� :" << tree.getHeight() << "\n";



	BinaryTree tree2;
	//		+
	//	*		-
	//3	  2   5   6
	BinaryNode* n1 = new BinaryNode(3, nullptr, nullptr); //�������� ������ ���缭 ���� ����
	BinaryNode* n2 = new BinaryNode(2, nullptr, nullptr);
	BinaryNode* n3 = new BinaryNode('*', n1, n2);
	BinaryNode* n4 = new BinaryNode(5, nullptr, nullptr);
	BinaryNode* n5 = new BinaryNode(6, nullptr, nullptr);
	BinaryNode* n6 = new BinaryNode('-', n4, n5);
	BinaryNode* n7 = new BinaryNode('+', n3, n6);
	tree2.setRoot(n7);
	std::cout << "����� : " << tree2.evaluate() << "\n";


	BinaryTree tree3;
	//			ROOT
	//		50		100
	//			  200	500
	BinaryNode* m4 = new BinaryNode(200, nullptr, nullptr); //�������� ������ ���缭 ���� ����
	BinaryNode* m5 = new BinaryNode(500, nullptr, nullptr);
	BinaryNode* m3 = new BinaryNode(100, m4, m5);
	BinaryNode* m2 = new BinaryNode(50, nullptr, nullptr);
	BinaryNode* m1 = new BinaryNode(0, m2, m3);

	tree3.setRoot(m1);
	std::cout << "����� : " << tree3.calSize() << "\n";
	return 0;
}*/