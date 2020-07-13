#pragma once
#include<iostream>
#define MAX_QUEUE_SIZE 100

inline void error(const char* str) {
	std::cerr << str << "\n"; // 에러의 경우는 std::cerr로 출력합니다.
	exit(1);
};

//======================================= level 순회 연산하기위해서 원형큐가 필요함
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
	bool isLeaf()  //마지막 자식인지 확인
	{
		return left == nullptr && right == nullptr;
	}
};
class CircularQueue {
protected:
	int front; // 가장 앞 (데이터를 꺼내는 위치)
	int rear; // 가장 뒤 (데이터를 넣는 위치)
	BinaryNode* data[MAX_QUEUE_SIZE];
public:
	CircularQueue() { front = rear = 0; }
	~CircularQueue() {}
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; } // 나머지 연산으로 위치를 찾습니다.
	void enqueue(BinaryNode* val) { // 큐 맨 뒤에 데이터를 추가
		if (isFull()) {
			error(" Error: 큐가 포화상태입니다\n");
		}
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = val;
		}
	}
	BinaryNode* dequeue() { // 큐 맨 앞에서 데이터를 꺼냄
		if (isEmpty()) {
			error(" Error: 큐가 공백상태입니다\n");
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
		return root == nullptr; //비어있으면 비어있다 true
	}
	void preorder(BinaryNode* node)//전위순회
	{
		std::cout << "[ " << node->getData() << " ]";  //출력먼저해주고! 
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
	void preorder()//파라미터 없을 때 전위순회
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
	void inorder(BinaryNode* node)//중위순회
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
	void inorder()//파라미터 안받았을 때 무조건 루트부터 작동한다고 가정
	{
		std::cout << "inorder: ";
		inorder(root);
	}
	//=========================================================================
	void postorder(BinaryNode* node)//중위순회
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
	void postorder()//파라미터 안받았을 때 무조건 루트부터 작동한다고 가정
	{
		std::cout << "postorder: ";
		postorder(root);
	}
	//========================================================= 추가연산
	int getCount(BinaryNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			return 1 + getCount(node->getLeft()) + getCount(node->getRight());
			//계속 내려가면 
			//이런식으로 순환을 통해 개수 구한다고 생각
			//		2
			//	1		1		=1 + 니까 자기자신.
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
	int getLeafCount()//아무것도 안받으면
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
	//===============================수식 트리 . 후위 순회를 통한 폴더 용량계산
	//아마 이거말고 전위순회같은걸로 다른거 계산하기가 나오지않을까
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
	//	4		5  6		 형태 만들예정
	//이 때 a를 맨 첫줄에 만들면 오류가난다 당연히 아직 b,c가 안 만들어졌으니 그러니까 이 순서도 생각해야한다.
	BinaryNode* d = new BinaryNode(4, nullptr, nullptr);
	BinaryNode* e = new BinaryNode(5, nullptr, nullptr);
	BinaryNode* b = new BinaryNode(2, d, e);
	BinaryNode* f = new BinaryNode(6, nullptr, nullptr);
	BinaryNode* c = new BinaryNode(3, f, nullptr);
	BinaryNode* a = new BinaryNode(1, b, c); //각각의 노드에 대한 정보를 지정해줘야한다
	tree.setRoot(a);
	tree.preorder(); //1-2-4-5-3-6 이 출력되는데 따져보면 출력->왼쪽->오른쪽이니까
	//1출력하고 왼쪽먼저 가서 2간다음 여기서도 출력왼쪽 오른쪽이니까 4가고 그 다음 없으니
	//2의 오른쪽 5갔다가 왼쪽오른쪽없으니 돌아가서 1의  오른쪽인 3출력 , 3의 왼쪽 6
	std::cout << "\n";
	tree.inorder();
	std::cout << "\n";
	tree.postorder();
	std::cout << "\n";
	tree.levelorder();
	std::cout << "\n";

	std::cout << "노드의 개수 :" << tree.getCount() << "\n";
	std::cout << "잎 노드의 개수: " << tree.getLeafCount() << "\n";
	std::cout << "트리의 높이 :" << tree.getHeight() << "\n";



	BinaryTree tree2;
	//		+
	//	*		-
	//3	  2   5   6
	BinaryNode* n1 = new BinaryNode(3, nullptr, nullptr); //후위수식 계산법에 맞춰서 순서 배정
	BinaryNode* n2 = new BinaryNode(2, nullptr, nullptr);
	BinaryNode* n3 = new BinaryNode('*', n1, n2);
	BinaryNode* n4 = new BinaryNode(5, nullptr, nullptr);
	BinaryNode* n5 = new BinaryNode(6, nullptr, nullptr);
	BinaryNode* n6 = new BinaryNode('-', n4, n5);
	BinaryNode* n7 = new BinaryNode('+', n3, n6);
	tree2.setRoot(n7);
	std::cout << "계산결과 : " << tree2.evaluate() << "\n";


	BinaryTree tree3;
	//			ROOT
	//		50		100
	//			  200	500
	BinaryNode* m4 = new BinaryNode(200, nullptr, nullptr); //후위수식 계산법에 맞춰서 순서 배정
	BinaryNode* m5 = new BinaryNode(500, nullptr, nullptr);
	BinaryNode* m3 = new BinaryNode(100, m4, m5);
	BinaryNode* m2 = new BinaryNode(50, nullptr, nullptr);
	BinaryNode* m1 = new BinaryNode(0, m2, m3);

	tree3.setRoot(m1);
	std::cout << "계산결과 : " << tree3.calSize() << "\n";
	return 0;
}*/