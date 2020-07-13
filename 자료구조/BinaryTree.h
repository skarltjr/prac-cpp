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
			std::cout << "탐색 성공, key: " << key << "\n";
		}
		else//nullptr가 리턴된거는 탐색을 하고도 못찾은거니까
		{
			std::cout << "탐색 실패 key: " << key << "\n";
		}
		return node;
	}
	BinaryNode* search(BinaryNode* n, int key)//실제 탐색은 이 함수가 하는거고 위에껀 루트부터 하도록해주는거
	{
		if (n == nullptr)
		{
			return nullptr;
		}
		if (key == n->getData())//노드는 변수로 왼쪽연결 , 데이터 , 오른쪽연결을 갖고있다
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
			root = n;//비어있으면 첫번째로 넣는 노드가 루트노드
		}
		else
		{
			insert(root, n);//루트부터 시작한다
		}
	}
	void insert(BinaryNode* r, BinaryNode* n)//r은 현재 탐색하고있는 노드고 n은 새로 삽입할 노드
	{
		if (n->getData() == r->getData())//중복을 허용하지않으니까
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
	void remove(int data)//key값이  data인 노드삭제
	{
		if (isEmpty())
		{
			return;
		}
		BinaryNode* parent = nullptr;
		BinaryNode* node = root;//현재노드 루트부터 시작이니까 루트의 부모노드는 없다
		while (node != nullptr && node->getData() != data)
		{
			parent = node;
			node = (data < node->getData()) ? node->getLeft() : node->getRight();
		}
		if (node == nullptr)
		{
			std::cout << "key " << data << " 는 존재하지 않습니다\n";
		}
		else//key가 존재하면
		{
			remove(parent, node);//360p에서 parent는 루트 node는 지울려고한느 18번
		} 
	}//이건 지울위치를 찾는 함수고
	void remove(BinaryNode* parent, BinaryNode* node)//진짜 노드를 지우는 함수
	{
		//1 번케이스 : 삭제위치가 단말노드(leaf node)인 경우
		if (node->isLeaf())
		{
			if (parent == nullptr)//루트노드일때
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
		//2번 케이스: 삭제위치의 한쪽 서브트리만 있는경우
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
		//3번케이스: 양쪽 서브트리가 다 있는 경우
		//오른쪽 트리를 기준으로 작업하는 것으로
		else//양쪽 서브트리가 다있다면
		{							
			BinaryNode* succp = node;//succ parent 계승자의 바로 위 부모노드
			BinaryNode* succ = node->getRight();
			while (succ->getLeft() != nullptr)//왼쪽인 이유는 오른쪽 트리를 기준으로 한다고 했으니까
											//부모기준 오른쪽에서 제일 작은 값 찾을려면 맨아래 맨 왼쪽값
			{
				succp = succ;
				succ = succ->getLeft();//오른쪽 트리에서 가장 작은값을 불러온다  
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

	// 삽입 연산 테스트
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

	std::cout << "노드의 수: " << tree.getCount() << "\n";
	std::cout << "단말의 수: " << tree.getLeafCount() << "\n";
	std::cout << "트리의 높이: " << tree.getHeight() << "\n";

	tree.inorder();
	tree.preorder();
	tree.postorder();
	tree.levelorder();

	tree.search(26);
	tree.search(25);
	/*
	// 삭제 연산 테스트
	std::cout << "삭제 case 1: 노드 3 삭제\n";
	tree.remove(3);
	tree.inorder();
	std::cout << "삭제 case 2: 노드 68 삭제\n";
	tree.remove(68);
	tree.inorder();
	std::cout << "삭제 case 3: 노드 18 삭제\n";
	tree.remove(18);
	tree.inorder();
	std::cout << "삭제 case 3: 노드 35 (루트 노드) 삭제\n";
	tree.remove(35);
	tree.inorder();

	// 최종 트리 정보 출력
	std::cout << "노드의 수: " << tree.getCount() << "\n";
	std::cout << "단말의 수: " << tree.getLeafCount() << "\n";
	std::cout << "트리의 높이: " << tree.getHeight() << "\n";*/
	return 0;
}