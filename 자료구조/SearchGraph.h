#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"CircularQueue.h"

#define MAX_VTXS 256
class Node//각 노드마다 연결리스트가 있으니 연결리스트 클래스를 만들어준다
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
	void setLink(Node* l) { link = l; }//다음 노드 연결
};
class AdjListGraph
{
protected:
	int size; //전체 그래프의 사이즈
	std::string vertices[MAX_VTXS]; //각  vertex의 이름
	Node* adj[MAX_VTXS];
public:
	AdjListGraph(void) :size(0) { }
	~AdjListGraph(void) { reset(); }
	std::string getVertex(int i) { return vertices[i]; }//i번 째 vertex를 가져오는
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
		else { std::cout << "최대 정점수 이상을 입력할 수 없다"; }
	}
	void insertEdge(int u, int v)
	{
		//adj[u] = new Node(v, adj[u]);
		//★★ 이미 adj[u]에 B->A가 들어있다고 해보자 그럼 new Node해서 만들어주면
		//새로만들어진 Node의 link에 B->A가 담겨져있다 즉
		//새로만든 노드이름이 C라면 이걸 새로만들었으니 c의 링크부분에 b-a가 있다.
		//이제 adj[u]=c-b-a가된다.

		 //만약 Adj Matrix와같은 순서로 만들고 싶으면
		if (adj[u] == nullptr) {
			adj[u] = new Node(v, adj[u]);//id가 v이고 링크가 adj[u]인 노드데이터를 adj[u]에 대입.
		}
		else {
			Node* p = adj[u];
			while (p->getLink() != nullptr) {//이 p라는 노드 끝까지 탐색 예를들어 지금 B->A->null까지 있으면 A까지 탐색
				p = p->getLink();//다음껄로 넘어가고
			}
			p->setLink(new Node(v, nullptr));//맨 뒤에 새노드추가해준다.B->A->C->NULL 굳이이럴필욘없다. 
		}
	}
	void display()
	{
		std::cout << size << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << getVertex(i) << " ";//구ㅡ럼 행ㅁ마다 A B C D이렇게 나오고
			for (Node* v = adj[i]; v != nullptr; v = v->getLink())//adj[0]은 첫번째 노드부터 순회 그다음 adj[1]....
			{
				std::cout << getVertex(v->getId()) << " ";//v가 nullptr일때까지니까 a-b-c처럼 되어있으면
			}std::cout << "\n";								//a나오고b그다음 안 비어있으니 c까지 해준다음 그 다음
		}													//adj[1]로 넘어가는것
	}
	void load(std::string filename)
	{
		std::ifstream ifs(filename);//파일불러오고
		std::string line;
		std::getline(ifs, line);
		std::stringstream ls(line);//공백 단위로 끊어서 값을 받게된다
		int n;
		ls >> n;//첫줄에 사이즈 던져주니까 사이즈 얻고
		for (int i = 0; i < n; i++)
		{
			std::getline(ifs, line);
			std::string str;
			int val;
			std::stringstream ls(line);//공백단위니까 처음에 A 0 1 0 1 이라면 ls에 A들어가고
			ls >> str;//A를 str에 옮기고
			insertVertex(str);//이렇게 노드 A 그다음 루프에서 B..가 생겨난다.
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
	int size; //전체 그래프의 사이즈
	std::string vertices[MAX_VTXS]; //각  vertex의 이름
	int adj[MAX_VTXS][MAX_VTXS];//인접행렬
public:
	AdjMatGraph() { reset(); }
	~AdjMatGraph() {}
	std::string getVertex(int i) { return vertices[i]; }//i번 째 vertex를 가져오는
	int getEdge(int i, int j) { return adj[i][j]; }//i와j사이에 edge가 있는지 있으면 1 없으면 0
	void setEdge(int i, int j, int val) { adj[i][j] = val; }//이 val은 가중치가 있는 그래프에서 사용
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
		if (!isFull()) { vertices[size++] = name; }//예를들어 3번에 넣고싶다하면
		//index가 0부터시작이니까 vertices[2] 0,1,2 에들어간다 그러니까 size++로 맞춰주는것
		else { std::cout << "최대 정점수 이상을 입력할 수 없다"; }
	}
	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1);//1인 이유는 가중치가없으니 다 동일한 1로맞춘다.
		setEdge(v, u, 1);//가중치가 없으니 대칭행렬
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
		std::ifstream ifs(filename);//파일을 입력받고
		std::string line;
		std::getline(ifs, line);//line에 파일에있는 문자열을 한 줄씩 받아오게하고.
		std::stringstream ls(line);//A0101을 한 줄로 즉 스트링을 공백단위로 끊어서
		int n;
		ls >> n; //첫 줄에 std::cout << size << "\n";니까 size인 4만 적혀있을거니까 이 첫줄4가 n에 들어가고
		for (int i = 0; i < n; i++)//전체그래프의 사이즈  행렬로 나타내면 맨위에 ABCD니까 size가 4줄 이라 생각 . 행이 4
		{
			std::getline(ifs, line);// 맨 위4 다음 한 줄을 받기위해 다시 2번째 줄부터 getline
			std::string str;
			int val;
			std::stringstream ls(line);//공백단위로 끊으니까 A 0 1 0 1 일때
			ls >> str;//이건  A B C D처럼 vertex이름 공백단위로 맨 앞에꺼 밭고 처음엔 A
			insertVertex(str);
			for (int j = 0; j < n; j++)
			{
				ls >> val;//그 다음 열 따라 0 1 0 1 
				if (val != 0)
				{
					insertEdge(i, j);
				}
			}//다시 행 바뀌면 이번엔 B 
		}ifs.close();
	}
	void store(std::string filename)//display랑 똑같다
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
	void DFS(int v)//시작점 v or 자기자신 v
	{
		visited[v] = true;
		std::cout << getVertex(v) << " ";
		for (int w = 0; w < size; w++)
		{
			if (isLinked(v, w) && visited[w] == false)///시작점v와 다른 한 정점 w가 연결되어있고 아직 w를 방문하지않았으면
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
			int v = que.dequeue();//선입선출을 생각해봐라 
			for (int w = 0; w < size; w++)
			{
				if (isLinked(v, w) && visited[w] == false)//시작점v와 다른 한 정점 w가 연결되어있고 아직 w를 방문하지않았으면
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
		for (Node* p = adj[u]; p != nullptr; p = p->getLink())//시작점p
		{
			if (p->getId() == v) { return true; }
		}
		return false;
	}
	void DFS(int v)//시작점 v or 자기자신 v
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
				if (visited[id] == false)//시작점v와 다른 한 정점 w가 연결되어있고 아직 w를 방문하지않았으면
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
		label[v] = color;//연결성분끼리 구분짓기 위해
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
			if (visited[i] == false)//같은 연결성분끼리는 같은 크기의 count를 갖을 것
			{
				labelDFS(i, ++count);
			}
		}
		std::cout << "\n연결 성분의 수는 : " << count << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << getVertex(i) << ":" << label[i] << " ";
		}
		std::cout << "\n";
	}

};

/*
위상정렬이란 방향이 있는 그래프에 대해 정점들의 선행 순서를 위배하지 않으면서 모든 정점을 나열하는 것
*/
class ToposortGraph :public AdjListGraph//방향성이 존재한다
{
public:
	ToposortGraph() {}
	~ToposortGraph() {}
	void insertDirEdge(int u, int v)//u에서시작해서 v에 도착하는 간선을 만든다
	{
		adj[u] = new Node(v, adj[u]);
	}
	void TopoSort()
	{
		CircularQueue q;
		int* inDeg = new int[size];//모든 정점의 in-degree(진입 차수)를 담는 변수
		for (int i = 0; i < size; i++)
		{
			inDeg[i] = 0;
		}
		for (int i = 0; i < size; i++)
		{
			Node* node = adj[i];
			while (node != nullptr)
			{
				inDeg[node->getId()]++;//★
				node = node->getLink();//다음 노드로 넘어가기
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
				inDeg[u]--;//★위 별표와 비교해보면 위는 큐에 데이터넣는거고 이건 빼오는거고
				if (inDeg[u] == 0)
				{
					q.enqueue(u);
				}
				node = node->getLink();//다음 노드로 넘어가기
			}
		}
		std::cout << "\n";
		delete[] inDeg;//★★
	}
};/*
int main()
{
	ToposortGraph g;
	for (int i = 0; i < 6; i++)
	{
		g.insertVertex(std::string(1, 'A' + i));//'A'+1 아스키코드로 바꾸서 다시 'B' 처럼
	}
	g.insertDirEdge(0, 2);
	g.insertDirEdge(0, 3);

	g.insertDirEdge(1, 3);
	g.insertDirEdge(1, 4);

	g.insertDirEdge(2, 3);
	g.insertDirEdge(2, 5);

	g.insertDirEdge(3, 5);

	g.insertDirEdge(4, 5);

	std::cout << " 위상정렬 수행:";
	g.TopoSort();
	return 0;
}*/