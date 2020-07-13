#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"CircularQueue.h"

#define MAX_VTXS 256
class Node//�� ��帶�� ���Ḯ��Ʈ�� ������ ���Ḯ��Ʈ Ŭ������ ������ش�
{
protected:
	int id;
	Node* link;
public:
	Node(int i, Node* l = nullptr)
		:id(i), link(l) {}
	~Node()
	{
		if (link != nullptr)
		{
			delete link;
		}
	}
	int getId()
	{
		return id;
	}
	Node* getLink() { return link; }
	void setLink(Node* l) { link = l; }//���� ��� ����
};
class AdjListGraph
{
protected:
	int size; //��ü �׷����� ������
	std::string vertices[MAX_VTXS]; //��  vertex�� �̸�
	Node* adj[MAX_VTXS];
public:
	AdjListGraph(void) :size(0) { }
	~AdjListGraph(void) { reset(); }
	std::string getVertex(int i) { return vertices[i]; }//i�� ° vertex�� ��������
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	void reset()
	{
		for (int i = 0; i < size; i++)
		{
			if (adj != nullptr) { delete adj[i]; }
		}
		size = 0;
	}
	void insertVertex(std::string name)
	{
		if (!isFull())
		{
			vertices[size] = name;
			adj[size++] = nullptr;
		}
		else { std::cout << "�ִ� ������ �̻��� �Է��� �� ����"; }
	}
	void insertEdge(int u, int v)
	{
		//adj[u] = new Node(v, adj[u]);
		//�ڡ� �̹� adj[u]�� B->A�� ����ִٰ� �غ��� �׷� new Node�ؼ� ������ָ�
		//���θ������ Node�� link�� B->A�� ������ִ� ��
		//���θ��� ����̸��� C��� �̰� ���θ�������� c�� ��ũ�κп� b-a�� �ִ�.
		//���� adj[u]=c-b-a���ȴ�.

		 //���� Adj Matrix�Ͱ��� ������ ����� ������
		if (adj[u] == nullptr) {
			adj[u] = new Node(v, adj[u]);//id�� v�̰� ��ũ�� adj[u]�� ��嵥���͸� adj[u]�� ����.
		}
		else {
			Node* p = adj[u];
			while (p->getLink() != nullptr) {//�� p��� ��� ������ Ž�� ������� ���� B->A->null���� ������ A���� Ž��
				p = p->getLink();//�������� �Ѿ��
			}
			p->setLink(new Node(v, nullptr));//�� �ڿ� ������߰����ش�.B->A->C->NULL �����̷��ʿ����. 
		}
	}
	void display()
	{
		std::cout << size << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << getVertex(i) << " ";//���ѷ� �ऱ���� A B C D�̷��� ������
			for (Node* v = adj[i]; v != nullptr; v = v->getLink())//adj[0]�� ù��° ������ ��ȸ �״��� adj[1]....
			{
				std::cout << getVertex(v->getId()) << " ";//v�� nullptr�϶������ϱ� a-b-có�� �Ǿ�������
			}std::cout << "\n";								//a������b�״��� �� ��������� c���� ���ش��� �� ����
		}													//adj[1]�� �Ѿ�°�
	}
	void load(std::string filename)
	{
		std::ifstream ifs(filename);//���Ϻҷ�����
		std::string line;
		std::getline(ifs, line);
		std::stringstream ls(line);//���� ������ ��� ���� �ްԵȴ�
		int n;
		ls >> n;//ù�ٿ� ������ �����ִϱ� ������ ���
		for (int i = 0; i < n; i++)
		{
			std::getline(ifs, line);
			std::string str;
			int val;
			std::stringstream ls(line);//��������ϱ� ó���� A 0 1 0 1 �̶�� ls�� A����
			ls >> str;//A�� str�� �ű��
			insertVertex(str);//�̷��� ��� A �״��� �������� B..�� ���ܳ���.
			for (int j = 0; j < n; j++)
			{
				ls >> val;
				if (val != 0)
				{
					insertEdge(i, j);
				}
			}
		}ifs.close();
	}
};
class AdjMatGraph
{
protected:
	int size; //��ü �׷����� ������
	std::string vertices[MAX_VTXS]; //��  vertex�� �̸�
	int adj[MAX_VTXS][MAX_VTXS];//�������
public:
	AdjMatGraph() { reset(); }
	~AdjMatGraph() {}
	std::string getVertex(int i) { return vertices[i]; }//i�� ° vertex�� ��������
	int getEdge(int i, int j) { return adj[i][j]; }//i��j���̿� edge�� �ִ��� ������ 1 ������ 0
	void setEdge(int i, int j, int val) { adj[i][j] = val; }//�� val�� ����ġ�� �ִ� �׷������� ���
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	void reset()
	{
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
			{
				setEdge(i, j, 0);
			}
		}
	}
	void insertVertex(std::string name)
	{
		if (!isFull()) { vertices[size++] = name; }//������� 3���� �ְ�ʹ��ϸ�
		//index�� 0���ͽ����̴ϱ� vertices[2] 0,1,2 ������ �׷��ϱ� size++�� �����ִ°�
		else { std::cout << "�ִ� ������ �̻��� �Է��� �� ����"; }
	}
	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1);//1�� ������ ����ġ�������� �� ������ 1�θ����.
		setEdge(v, u, 1);//����ġ�� ������ ��Ī���
	}
	void display()
	{
		std::cout << size << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << getVertex(i) << " ";
			for (int j = 0; j < size; j++)
			{
				std::cout << getEdge(i, j) << " ";
			}std::cout << "\n";
		}
	}
	void load(std::string filename)
	{
		std::ifstream ifs(filename);//������ �Է¹ް�
		std::string line;
		std::getline(ifs, line);//line�� ���Ͽ��ִ� ���ڿ��� �� �پ� �޾ƿ����ϰ�.
		std::stringstream ls(line);//A0101�� �� �ٷ� �� ��Ʈ���� ��������� ���
		int n;
		ls >> n; //ù �ٿ� std::cout << size << "\n";�ϱ� size�� 4�� ���������Ŵϱ� �� ù��4�� n�� ����
		for (int i = 0; i < n; i++)//��ü�׷����� ������  ��ķ� ��Ÿ���� ������ ABCD�ϱ� size�� 4�� �̶� ���� . ���� 4
		{
			std::getline(ifs, line);// �� ��4 ���� �� ���� �ޱ����� �ٽ� 2��° �ٺ��� getline
			std::string str;
			int val;
			std::stringstream ls(line);//��������� �����ϱ� A 0 1 0 1 �϶�
			ls >> str;//�̰�  A B C Dó�� vertex�̸� ��������� �� �տ��� ��� ó���� A
			insertVertex(str);
			for (int j = 0; j < n; j++)
			{
				ls >> val;//�� ���� �� ���� 0 1 0 1 
				if (val != 0)
				{
					insertEdge(i, j);
				}
			}//�ٽ� �� �ٲ�� �̹��� B 
		}ifs.close();
	}
	void store(std::string filename)//display�� �Ȱ���
	{
		std::ofstream ofs(filename);
		ofs << size << "\n";
		for (int i = 0; i < MAX_VTXS; i++)
		{
			ofs << getVertex(i) << " ";
			for (int j = 0; j < MAX_VTXS; j++)
			{
				ofs << getEdge(i, j) << " ";
			}ofs << "\n";
		}ofs.close();
	}
};

class SrchAMGraph :public AdjMatGraph
{
protected:
	bool visited[MAX_VTXS];
public:
	void resetVisited()
	{
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
	}
	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }
	void DFS(int v)//������ v or �ڱ��ڽ� v
	{
		visited[v] = true;
		std::cout << getVertex(v) << " ";
		for (int w = 0; w < size; w++)
		{
			if (isLinked(v, w) && visited[w] == false)///������v�� �ٸ� �� ���� w�� ����Ǿ��ְ� ���� w�� �湮�����ʾ�����
			{
				DFS(w);
			}
		}
	}
	void BFS(int v)
	{
		visited[v] = true;
		std::cout << getVertex(v) << " ";
		CircularQueue que;
		que.enqueue(v);
		while (!que.isEmpty())
		{
			int v = que.dequeue();//���Լ����� �����غ��� 
			for (int w = 0; w < size; w++)
			{
				if (isLinked(v, w) && visited[w] == false)//������v�� �ٸ� �� ���� w�� ����Ǿ��ְ� ���� w�� �湮�����ʾ�����
				{
					visited[w] = true;
					std::cout << getVertex(w) << " ";
					que.enqueue(w);
				}
			}
		}
	}

};
class SrchALGraph :public AdjListGraph
{
protected:
	bool visited[MAX_VTXS];
public:
	void resetVisited()
	{
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
	}
	bool isLinked(int u, int v)
	{
		for (Node* p = adj[u]; p != nullptr; p = p->getLink())//������p
		{
			if (p->getId() == v) { return true; }
		}
		return false;
	}
	void DFS(int v)//������ v or �ڱ��ڽ� v
	{
		visited[v] = true;
		std::cout << getVertex(v) << " ";
		for (Node* p = adj[v]; p != nullptr; p = p->getLink())
		{
			if (visited[p->getId()] == false)
			{
				DFS(p->getId());
			}
		}
	}
	void BFS(int v)
	{
		visited[v] = true;
		std::cout << getVertex(v) << " ";
		CircularQueue que;
		que.enqueue(v);
		while (!que.isEmpty())
		{
			int v = que.dequeue();
			for (Node* w = adj[v]; w != nullptr; w = w->getLink())
			{
				int id = w->getId();
				if (visited[id] == false)//������v�� �ٸ� �� ���� w�� ����Ǿ��ְ� ���� w�� �湮�����ʾ�����
				{
					visited[id] = true;
					std::cout << getVertex(id) << " ";
					que.enqueue(id);
				}
			}
		}
	}
};

class ConnectedComponentGraph : public SrchAMGraph
{
protected:
	int label[MAX_VTXS];
public:
	void labelDFS(int v, int color)
	{
		visited[v] = true;
		label[v] = color;//���Ἲ�г��� �������� ����
		std::cout << getVertex(v) << " ";
		for (int w = 0; w < size; w++)
		{
			if (isLinked(v, w) && visited[w] == false)
			{
				labelDFS(w, color);
			}
		}
	}
	void findConnectedComponent()
	{
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (visited[i] == false)//���� ���Ἲ�г����� ���� ũ���� count�� ���� ��
			{
				labelDFS(i, ++count);
			}
		}
		std::cout << "\n���� ������ ���� : " << count << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << getVertex(i) << ":" << label[i] << " ";
		}
		std::cout << "\n";
	}

};

/*
���������̶� ������ �ִ� �׷����� ���� �������� ���� ������ �������� �����鼭 ��� ������ �����ϴ� ��
*/
class ToposortGraph :public AdjListGraph//���⼺�� �����Ѵ�
{
public:
	ToposortGraph() {}
	~ToposortGraph() {}
	void insertDirEdge(int u, int v)//u���������ؼ� v�� �����ϴ� ������ �����
	{
		adj[u] = new Node(v, adj[u]);
	}
	void TopoSort()
	{
		CircularQueue q;
		int* inDeg = new int[size];//��� ������ in-degree(���� ����)�� ��� ����
		for (int i = 0; i < size; i++)
		{
			inDeg[i] = 0;
		}
		for (int i = 0; i < size; i++)
		{
			Node* node = adj[i];
			while (node != nullptr)
			{
				inDeg[node->getId()]++;//��
				node = node->getLink();//���� ���� �Ѿ��
			}
		}
		for (int i = 0; i < size; i++)
		{
			if (inDeg[i] == 0) { q.enqueue(i); }
		}
		while (q.isEmpty() == false)
		{
			int w = q.dequeue();
			std::cout << getVertex(w) << " ";
			Node* node = adj[w];
			while (node != nullptr)
			{
				int u = node->getId();
				inDeg[u]--;//���� ��ǥ�� ���غ��� ���� ť�� �����ͳִ°Ű� �̰� �����°Ű�
				if (inDeg[u] == 0)
				{
					q.enqueue(u);
				}
				node = node->getLink();//���� ���� �Ѿ��
			}
		}
		std::cout << "\n";
		delete[] inDeg;//�ڡ�
	}
};/*
int main()
{
	ToposortGraph g;
	for (int i = 0; i < 6; i++)
	{
		g.insertVertex(std::string(1, 'A' + i));//'A'+1 �ƽ�Ű�ڵ�� �ٲټ� �ٽ� 'B' ó��
	}
	g.insertDirEdge(0, 2);
	g.insertDirEdge(0, 3);

	g.insertDirEdge(1, 3);
	g.insertDirEdge(1, 4);

	g.insertDirEdge(2, 3);
	g.insertDirEdge(2, 5);

	g.insertDirEdge(3, 5);

	g.insertDirEdge(4, 5);

	std::cout << " �������� ����:";
	g.TopoSort();
	return 0;
}*/