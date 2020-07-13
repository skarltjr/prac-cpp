#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

#define INF 999
#define MAX_VTXS 256
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
class node
{
private:
	int weight;
	int v1;
	int v2;
	node* next;
public:
	node(int val = INF, int vx1 = -1, int vx2 = -1)//양수만 고려하니까 음수는 간선이 없는경우
	{
		weight = val;
		v1 = vx1;
		v2 = vx2;
		next = nullptr;
	}
	~node() {}
	node* getLink()
	{
		return next;
	}
	int getWeight() { return weight; }
	int getSource() { return v1; }//방향이  있을 때 사용
	int getTarget() { return v2; }//;;
	void setLink(node* target) { next = target; }
	void insertNext(node* newnode)//자기위치 다음에 노드를 넣는 함수
	{
		if (newnode != nullptr)
		{
			newnode->next = next;// ㅁ-next 였을 때 ㅁ-ㅁ-next가 되잖아 그니까 현재노드의 next가 받아온 노드의 next가 
			//되겠지 
			next = newnode;//자기자신의 다음을 새로 받아온 노드로 설정
		}
	}
	node* removeNext()//자기 위치 다음의 노드를 지우는 함수
	{
		node* removed = next;
		if (removed != nullptr)
		{
			next = removed->next;
			return removed;
		}
	}
};
class o_linked_list
{
protected:
	node origin;//시작노드
public:
	o_linked_list() {}
	~o_linked_list() { clear(); }
	void clear()
	{
		while (!isEmpty())
		{
			origin.removeNext();
		}
	}
	bool isEmpty()
	{
		return getHead() == nullptr;
	}
	node* getHead()
	{
		return origin.getLink();//origin의 다음노드가 head list.h참고
	}//첫 노드를 부르는 연산 실제로 노드는 origin다음부터 origin은 가상
	void removeHead()
	{
		origin.removeNext();//getHead로 얻은 값은 다시 못 쓰니까 지우도록
	}
	void orderedInsert(node* n)
	{
		int w = n->getWeight();//8
		node* prev = &origin;
		node* now = getHead();
		while (now != nullptr)
		{
			int now_w = now->getWeight();
			//1 3 7 9 16
			//8을 넣는다 생각하면  1 3 7 8 9 16
			if (now_w >= w)
			{
				prev->insertNext(n);
				return;
			}
			prev = now;
			now = now->getLink();
		}
		//맨 마지막에 삽입하는경우는 
		prev->insertNext(n);
		return;
	}
	size_t size()
	{
		int count = 0;
		for (node* p = getHead(); p != nullptr; p->getLink())
		{
			count++;
		}
		return count;
	}
	void display()
	{
		std::cout << "항목 수: " << size(); "\n";
		for (node* p = getHead(); p != nullptr; p->getLink())
		{
			std::cout << p->getWeight() << " " << p->getSource() << " ";
			std::cout << p->getTarget() << "\n";
		}
	}
};
class VertexSets//사이클이 있는지 확인하기위해
{
protected:
	int parent[MAX_VTXS];
	int size;
public:
	VertexSets(int nSets)
	{
		size = nSets;//맨 처음 사이즈는 전체 노드의 갯수
		for (int i = 0; i < nSets; i++)
		{
			parent[i] = -1;
		}
	}
	bool isRoot(int i)
	{
		return parent[i] < 0;//양수 인덱스만 쓰니까 0보다 작으면 그건 루트
	}
	int findSet(int vertex)
	{
		int id = vertex;
		while (!isRoot(id))
		{
			id = parent[id];
		}
		return id;
	}
	void unionSets(int s1, int s2)
	{
		parent[s1] = s2;
		size--;
	}
};
class WGraph :public AdjMatGraph
{
	//따로 변수필요 x
public:
	WGraph() {}
	~WGraph() {}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }//최대값보다 크면 간선이없는거다
	void insertEdge(int u, int v, int weight)
	{
		if (weight >= INF) { weight = INF; }//간선이 없는경우
		setEdge(u, v, weight); //가중치가 최대값보다 작으면 간선이 있는것
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
				insertEdge(i, j, val);//가중치가 있을 땐 당연히 val가중치추가
			}//다시 행 바뀌면 이번엔 B 
		}ifs.close();
	}
};
class WGraphMST :public WGraph
{
public:
	//Kruskal MST
	void Kruskal()
	{
		o_linked_list o_edgelist;
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (hasEdge(i, j))
				{
					o_edgelist.orderedInsert(new node(getEdge(i, j), i, j));//노드 생성자에 가중치,정점1,정점2
				}
			}
		}
		VertexSets set(size);
		int edgeAccepted = 0;
		while (edgeAccepted < size - 1)
		{
			node* e = o_edgelist.getHead();
			int uset = set.findSet(e->getSource());
			int vset = set.findSet(e->getTarget());;
			if (uset != vset)
			{
				std::cout << "An edge added to MST" << getVertex(e->getSource());
				std::cout << " " << getVertex(e->getTarget()) << " " << e->getWeight() << "\n";
				set.unionSets(uset, vset);
				edgeAccepted++;
			}
			o_edgelist.removeHead();
		}
	}
	void Prim()
	{
		bool selected[MAX_VTXS];
		int dist[MAX_VTXS];
		int source_vertex[MAX_VTXS];//선택으로 이어진 정점들 중 그 다음 노드를 정할 때 어디서 거리를 잰건지 알기위해
		for (int i = 0; i < size; i++)
		{
			dist[i] = INF;
			selected[i] = false;
			source_vertex[i] = 0;//다 초기화해두고
		}
		dist[0] = 0;
		for (int i = 0; i < size; i++)
		{
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] >= INF) { return; }//가장 작은 점을 골랐는데 간선이 없으면 이상한경우
			if (u != source_vertex[u])
			{
				std::cout << "An edge added to MST" << getVertex(u) << " ";
				std::cout << getVertex(source_vertex[u]) << " " << getEdge(u, source_vertex[u]) << "\n";
			}
			for (int v = 0; v < size; v++)
			{
				if (getEdge(u, v) != INF)
				{
					if (!selected[v], getEdge(u, v) < dist[v])
					{
						dist[v] = getEdge(u, v);
						source_vertex[v] = u;
					}
				}
			}
		}
	}
	int getMinVertex(bool* selected, int* dist)//prim에서 이어진 정점들로 부터 가장 가까운 정점, 가중치 낮은 정점을 택하도록
	{
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v < size; v++)
		{
			if (!selected[v] && dist[v] < mindist)//selected는 아직 고르지 않은 정점중에 그 거리가 
				//지금까지의 가장 가까운 거리 mindistance 보다 작으면 
			{
				mindist = dist[v];
				minv = v;
			}
		}
		return minv;
	}
};

class WgraphDijkstra : public WGraph//prim 알고리즘과 비슷
{
protected:
	int path[MAX_VTXS];//어떤 노드를 거쳐서 이 최소경로가 나왔는지 의미.자기자신 바로 전꺼만 저장하면된다.
	int dist[MAX_VTXS];//그 시점에서의 거리 배열 
	bool found[MAX_VTXS];
public:
	WgraphDijkstra() {}
	~WgraphDijkstra() {}
	void PrintDistance()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << dist[i] << " ";
		}
	}
	void PrintPath(int start, int end)
	{
		std::cout << "Shortest path " << getVertex(end) << "->" << getVertex(start) << ": ";
		std::cout << getVertex(end);
		while (path[end] != start)
		{
			std::cout << "-" << getVertex(path[end]);
			end = path[end];
		}
		std::cout << "-" << getVertex(start) << "\n";
	}
	int chooseVertex()
	{
		int min = INF;//처음에 젤 큰값을 줘야 둘이 비교해서 더 작은 값을 택하니까
		int minpos = -1;//거리가 최소인 노드의 인덱스
		for (int i = 0; i < size; i++)
		{
			if (dist[i] < min && !found[i])//이전 거리가 지금까지 찾은 최단경로보다 작고 S그룹에 들어가있지 않다면
			{
				min = dist[i];
				minpos = i;
			}
		}
		return minpos;
	}
	void ShortestPath(int start)
	{
		for (int i = 0; i < size; i++)
		{
			dist[i] = getEdge(start, i);
			path[i] = start;
			found[i] = false;
		}
		found[start] = true;
		dist[start] = 0;

		for (int i = 0; i < size - 1; i++)//start는 이미 추가가 되어있으니 아직 안 고른 노드 중에서 최단거리인 노드를 뽑는것
		{
			std::cout << "STEP " << i + 1 << " ";
			PrintDistance();
			int u = chooseVertex();//최소거리를 골라주는 
			found[u] = true;//찾아 줬으면 true로 바꿔주고
			for (int w = 0; w < size; w++)
			{
				if (!found[w])//아직 찾지않은 노드일 때
				{
					if (dist[u] + getEdge(u, w) < dist[w])//기존의 최단거리라고 알고있던 dist[w]보다 새로찾은게 거리가짧으면
					{
						dist[w] = dist[u] + getEdge(u, w);
						path[w] = u;//w로 가는 길에 u가 추가된다
					}
				}
			}
			std::cout << "\n";
		}
	}


};
class WGraphFloyd :public WGraph
{
protected:
	int A[MAX_VTXS][MAX_VTXS];
	int path[MAX_VTXS][MAX_VTXS];
public:
	void ShortestPathFloyd()
	{
		for (int i = 0; i < size; i++)//초기화
		{
			for (int j = 0; j < size; j++)
			{
				A[i][j] = getEdge(i, j);
				path[i][j] = j;

			}
		}
		for (int k = 0; k < size; k++)//3중 루프
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (A[i][k] + A[k][j] < A[i][j])//새로운 루트 가 기존의 루트 A[i][j]보다 작다면 교체
					{
						A[i][j] = A[i][k] + A[k][j];
						path[i][j] = path[i][k];
					}
				}
			}
			printA();
		}
	}
	void printA()
	{
		std::cout << "Shortest path length matrix: \n";
		for (int i = 0; i < size; i++)//초기화
		{
			for (int j = 0; j < size; j++)
			{
				if (A[i][j] == INF)
				{
					std::cout << "INF";
				}
				else
				{
					std::cout << A[i][j] << " ";
				}
			}
			std::cout << "\n";
		}
	}
	void PrintPath(int start, int end)
	{
		std::cout << "Shortest path " << getVertex(start) << "->" << getVertex(end) << ": ";
		std::cout << getVertex(start);
		while (path[start][end] != end)
		{
			std::cout << "-" << getVertex(path[start][end]);
			start = path[start][end];
		}
		std::cout << "-" << getVertex(end) << "\n";
	}
};
int main()
{
	WgraphDijkstra g;

	g.load("graph5.txt");
	std::cout << "File loaded\n";
	g.display();
	std::cout << "Shortest Path By Dijkstra Algorithm\n";
	g.ShortestPath(0);
	std::cout << "Finding completed\n";
	for (int i = 0; i < 7; i++) {
		g.PrintPath(0, i);
	}

	for (int j = 0; j < 7; j++) {
		g.ShortestPath(j);
		std::cout << "Finding completed\n";
		for (int i = 0; i < 7; i++) {
			g.PrintPath(j, i);
		}
	}

	/*WGraphFloyd g2;
	g2.load("graph5.txt");
	g2.display();
	std::cout << "Shortest Path By Floyd Algorithm\n";
	g2.ShortestPathFloyd();
	for (int i = 0; i < 7; i++)
	{
		g2.PrintPath(0,i);
	}*/

	return 0;
}