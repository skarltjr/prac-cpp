#pragma once
//빈 노드가 있으니까 바로바로 연결해주도록 
#include<iostream>

class ThreadedBinaryNode
{
protected:
	int data;
	ThreadedBinaryNode* left;
	ThreadedBinaryNode* right;
public:
	bool bThread;
	ThreadedBinaryNode(int val = 0, ThreadedBinaryNode* l = nullptr, ThreadedBinaryNode* r = nullptr, bool bTh = false)
		:data(val), left(l), right(r), bThread(bTh) {}
	~ThreadedBinaryNode() {}
	void setData(int val)
	{
		data = val;
	}
	void setLeft(ThreadedBinaryNode* l)
	{
		left = l;
	}
	void setRight(ThreadedBinaryNode* r)
	{
		right = r;
	}
	int getData()
	{
		return data;
	}
	ThreadedBinaryNode* getLeft()
	{
		return left;
	}
	ThreadedBinaryNode* getRight()
	{
		return right;
	}
	bool isLeaf()  //마지막 자식인지 확인
	{
		return left == nullptr && right == nullptr;
	}
};
class ThreadedBinTree
{
private:
	ThreadedBinaryNode* root;
public:
	ThreadedBinTree()
		:root(nullptr) {}
	~ThreadedBinTree() {}
	void setRoot(ThreadedBinaryNode* node)
	{
		root = node;
	}
	ThreadedBinaryNode* getRoot()
	{
		return root;
	}
	bool isEmpty()
	{
		return root == nullptr; //비어있으면 비어있다 true
	}
	void threadedInorder()
	{
		if (!isEmpty())
		{
			std::cout << "Threaded Binary Tree Inorder:";
			ThreadedBinaryNode* q = root;
			while (q->getLeft())
			{
				q = q->getLeft();
			}
			do
			{
				std::cout << " [" << q->getData() << "]";
				q = findSuccessor(q);
			} while (q);
			std::cout << "\n";
		}
	}
	ThreadedBinaryNode* findSuccessor(ThreadedBinaryNode* p)//후속자
	{
		ThreadedBinaryNode* q = p->getRight();//오른쪽 자식포인터저장
		if (q == nullptr || p->bThread)
		{
			return q;
		}
		while (q->getLeft() != nullptr)
		{
			q = q->getLeft();
		}
		return q;
	}
};/*
int main()
{
	ThreadedBinTree tree;
	//			7
	//		3		6
	//	1	   2  4		5   1은 마지막노드니까 3번으로가고 2는 7번으로가고 4는 6으로가는스레드링크
	ThreadedBinaryNode* n1 = new ThreadedBinaryNode(1, nullptr, nullptr, true);
	ThreadedBinaryNode* n2 = new ThreadedBinaryNode(2, nullptr, nullptr, true);
	ThreadedBinaryNode* n3 = new ThreadedBinaryNode(3, n1, n2, false);
	ThreadedBinaryNode* n4 = new ThreadedBinaryNode(4, nullptr, nullptr, true);
	ThreadedBinaryNode* n5 = new ThreadedBinaryNode(5, nullptr, nullptr, false);
	ThreadedBinaryNode* n6 = new ThreadedBinaryNode(6, n4, n5, false);
	ThreadedBinaryNode* n7 = new ThreadedBinaryNode(7, n3, n6, false);
	tree.setRoot(n7);
	//스레드 설정
	n1->setRight(n3);
	n2->setRight(n7);
	n4->setRight(n6);
	tree.threadedInorder();
	return 0;
}*/
