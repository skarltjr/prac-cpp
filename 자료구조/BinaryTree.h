#pragma once
#include<iostream>
#include"BinaryNode.h"

class BinSrchTree :public BinaryTree
{
public:
	BinSrchTree() {}
	~BinSrchTree() {}

	BinaryNode* search(int key)
	{
		BinaryNode* node = search(root, key);//recursive 
		if (node != nullptr)
		{
			std::cout << "Ž�� ����, key: " << key << "\n";
		}
		else//nullptr�� ���ϵȰŴ� Ž���� �ϰ� ��ã���Ŵϱ�
		{
			std::cout << "Ž�� ���� key: " << key << "\n";
		}
		return node;
	}
	BinaryNode* search(BinaryNode* n, int key)//���� Ž���� �� �Լ��� �ϴ°Ű� ������ ��Ʈ���� �ϵ������ִ°�
	{
		if (n == nullptr)
		{
			return nullptr;
		}
		if (key == n->getData())//���� ������ ���ʿ��� , ������ , �����ʿ����� �����ִ�
		{
			return n;
		}
		else if (key < n->getData())
		{
			return search(n->getLeft(), key);
		}
		else if (key > n->getData())
		{
			return search(n->getRight(), key);
		}
	}
	void insert(BinaryNode* n)
	{
		if (n == nullptr)
		{
			return;
		}
		if (isEmpty())
		{
			root = n;//��������� ù��°�� �ִ� ��尡 ��Ʈ���
		}
		else
		{
			insert(root, n);//��Ʈ���� �����Ѵ�
		}
	}
	void insert(BinaryNode* r, BinaryNode* n)//r�� ���� Ž���ϰ��ִ� ���� n�� ���� ������ ���
	{
		if (n->getData() == r->getData())//�ߺ��� ������������ϱ�
		{
			return;
		}
		else if (n->getData() < r->getData())
		{
			if (r->getLeft() == nullptr)
			{
				r->setLeft(n);
			}
			else
			{
				insert(r->getLeft(), n);
			}
		}
		else
		{
			if (r->getRight() == nullptr)
			{
				r->setRight(n);
			}
			else
			{
				insert(r->getRight(), n);
			}
		}
	}
	void remove(int data)//key����  data�� ������
	{
		if (isEmpty())
		{
			return;
		}
		BinaryNode* parent = nullptr;
		BinaryNode* node = root;//������ ��Ʈ���� �����̴ϱ� ��Ʈ�� �θ���� ����
		while (node != nullptr && node->getData() != data)
		{
			parent = node;
			node = (data < node->getData()) ? node->getLeft() : node->getRight();
		}
		if (node == nullptr)
		{
			std::cout << "key " << data << " �� �������� �ʽ��ϴ�\n";
		}
		else//key�� �����ϸ�
		{
			remove(parent, node);//360p���� parent�� ��Ʈ node�� ��������Ѵ� 18��
		} 
	}//�̰� ������ġ�� ã�� �Լ���
	void remove(BinaryNode* parent, BinaryNode* node)//��¥ ��带 ����� �Լ�
	{
		//1 �����̽� : ������ġ�� �ܸ����(leaf node)�� ���
		if (node->isLeaf())
		{
			if (parent == nullptr)//��Ʈ����϶�
			{
				root = nullptr;
			}
			else
			{
				if (parent->getLeft() == node)
				{
					parent->setLeft(nullptr);
				}
				else
				{
					parent->setRight(nullptr);
				}
			}
		}
		//2�� ���̽�: ������ġ�� ���� ����Ʈ���� �ִ°��
		else if (node->getLeft() == nullptr || node->getRight() == nullptr)
		{
			BinaryNode* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
			if (node == root)
			{
				root = child;
			}
			else
			{
				if (parent->getLeft() == node)
				{
					parent->setLeft(child);
				}
				else
				{
					parent->setRight(child);
				}

			}
		}
		//3�����̽�: ���� ����Ʈ���� �� �ִ� ���
		//������ Ʈ���� �������� �۾��ϴ� ������
		else//���� ����Ʈ���� ���ִٸ�
		{							
			BinaryNode* succp = node;//succ parent ������� �ٷ� �� �θ���
			BinaryNode* succ = node->getRight();
			while (succ->getLeft() != nullptr)//������ ������ ������ Ʈ���� �������� �Ѵٰ� �����ϱ�
											//�θ���� �����ʿ��� ���� ���� �� ã������ �ǾƷ� �� ���ʰ�
			{
				succp = succ;
				succ = succ->getLeft();//������ Ʈ������ ���� �������� �ҷ��´�  
			}
			if (succp->getLeft() == succ)
			{
				succp->setLeft(succ->getRight());
			}
			else
			{
				succp->setRight(succ->getRight());
			}
			node->setData(succ->getData());
			node = succ;
		}
		delete node;
	}
};
int main()
{
	BinSrchTree tree;

	// ���� ���� �׽�Ʈ
	tree.insert(new BinaryNode(35));
	tree.insert(new BinaryNode(18));
	tree.insert(new BinaryNode(7));
	tree.insert(new BinaryNode(26));
	tree.insert(new BinaryNode(12));
	tree.insert(new BinaryNode(3));
	tree.insert(new BinaryNode(68));
	tree.insert(new BinaryNode(22));
	tree.insert(new BinaryNode(30));
	tree.insert(new BinaryNode(99));

	std::cout << "����� ��: " << tree.getCount() << "\n";
	std::cout << "�ܸ��� ��: " << tree.getLeafCount() << "\n";
	std::cout << "Ʈ���� ����: " << tree.getHeight() << "\n";

	tree.inorder();
	tree.preorder();
	tree.postorder();
	tree.levelorder();

	tree.search(26);
	tree.search(25);
	/*
	// ���� ���� �׽�Ʈ
	std::cout << "���� case 1: ��� 3 ����\n";
	tree.remove(3);
	tree.inorder();
	std::cout << "���� case 2: ��� 68 ����\n";
	tree.remove(68);
	tree.inorder();
	std::cout << "���� case 3: ��� 18 ����\n";
	tree.remove(18);
	tree.inorder();
	std::cout << "���� case 3: ��� 35 (��Ʈ ���) ����\n";
	tree.remove(35);
	tree.inorder();

	// ���� Ʈ�� ���� ���
	std::cout << "����� ��: " << tree.getCount() << "\n";
	std::cout << "�ܸ��� ��: " << tree.getLeafCount() << "\n";
	std::cout << "Ʈ���� ����: " << tree.getHeight() << "\n";*/
	return 0;
}