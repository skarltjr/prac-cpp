#pragma once
//�� ��尡 �����ϱ� �ٷιٷ� �������ֵ��� 
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
	bool isLeaf()  //������ �ڽ����� Ȯ��
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
		return root == nullptr; //��������� ����ִ� true
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
	ThreadedBinaryNode* findSuccessor(ThreadedBinaryNode* p)//�ļ���
	{
		ThreadedBinaryNode* q = p->getRight();//������ �ڽ�����������
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
	//	1	   2  4		5   1�� ���������ϱ� 3�����ΰ��� 2�� 7�����ΰ��� 4�� 6���ΰ��½����帵ũ
	ThreadedBinaryNode* n1 = new ThreadedBinaryNode(1, nullptr, nullptr, true);
	ThreadedBinaryNode* n2 = new ThreadedBinaryNode(2, nullptr, nullptr, true);
	ThreadedBinaryNode* n3 = new ThreadedBinaryNode(3, n1, n2, false);
	ThreadedBinaryNode* n4 = new ThreadedBinaryNode(4, nullptr, nullptr, true);
	ThreadedBinaryNode* n5 = new ThreadedBinaryNode(5, nullptr, nullptr, false);
	ThreadedBinaryNode* n6 = new ThreadedBinaryNode(6, n4, n5, false);
	ThreadedBinaryNode* n7 = new ThreadedBinaryNode(7, n3, n6, false);
	tree.setRoot(n7);
	//������ ����
	n1->setRight(n3);
	n2->setRight(n7);
	n4->setRight(n6);
	tree.threadedInorder();
	return 0;
}*/
