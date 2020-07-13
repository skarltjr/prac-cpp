#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

#define INF 999
#define MAX_VTXS 256
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
class node
{
private:
	int weight;
	int v1;
	int v2;
	node* next;
public:
	node(int val = INF, int vx1 = -1, int vx2 = -1)//����� ����ϴϱ� ������ ������ ���°��
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
	int getSource() { return v1; }//������  ���� �� ���
	int getTarget() { return v2; }//;;
	void setLink(node* target) { next = target; }
	void insertNext(node* newnode)//�ڱ���ġ ������ ��带 �ִ� �Լ�
	{
		if (newnode != nullptr)
		{
			newnode->next = next;// ��-next ���� �� ��-��-next�� ���ݾ� �״ϱ� �������� next�� �޾ƿ� ����� next�� 
			//�ǰ��� 
			next = newnode;//�ڱ��ڽ��� ������ ���� �޾ƿ� ���� ����
		}
	}
	node* removeNext()//�ڱ� ��ġ ������ ��带 ����� �Լ�
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
	node origin;//���۳��
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
		return origin.getLink();//origin�� ������尡 head list.h����
	}//ù ��带 �θ��� ���� ������ ���� origin�������� origin�� ����
	void removeHead()
	{
		origin.removeNext();//getHead�� ���� ���� �ٽ� �� ���ϱ� ���쵵��
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
			//8�� �ִ´� �����ϸ�  1 3 7 8 9 16
			if (now_w >= w)
			{
				prev->insertNext(n);
				return;
			}
			prev = now;
			now = now->getLink();
		}
		//�� �������� �����ϴ°��� 
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
		std::cout << "�׸� ��: " << size(); "\n";
		for (node* p = getHead(); p != nullptr; p->getLink())
		{
			std::cout << p->getWeight() << " " << p->getSource() << " ";
			std::cout << p->getTarget() << "\n";
		}
	}
};
class VertexSets//����Ŭ�� �ִ��� Ȯ���ϱ�����
{
protected:
	int parent[MAX_VTXS];
	int size;
public:
	VertexSets(int nSets)
	{
		size = nSets;//�� ó�� ������� ��ü ����� ����
		for (int i = 0; i < nSets; i++)
		{
			parent[i] = -1;
		}
	}
	bool isRoot(int i)
	{
		return parent[i] < 0;//��� �ε����� ���ϱ� 0���� ������ �װ� ��Ʈ
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
	//���� �����ʿ� x
public:
	WGraph() {}
	~WGraph() {}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }//�ִ밪���� ũ�� �����̾��°Ŵ�
	void insertEdge(int u, int v, int weight)
	{
		if (weight >= INF) { weight = INF; }//������ ���°��
		setEdge(u, v, weight); //����ġ�� �ִ밪���� ������ ������ �ִ°�
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
				insertEdge(i, j, val);//����ġ�� ���� �� �翬�� val����ġ�߰�
			}//�ٽ� �� �ٲ�� �̹��� B 
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
					o_edgelist.orderedInsert(new node(getEdge(i, j), i, j));//��� �����ڿ� ����ġ,����1,����2
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
		int source_vertex[MAX_VTXS];//�������� �̾��� ������ �� �� ���� ��带 ���� �� ��� �Ÿ��� ����� �˱�����
		for (int i = 0; i < size; i++)
		{
			dist[i] = INF;
			selected[i] = false;
			source_vertex[i] = 0;//�� �ʱ�ȭ�صΰ�
		}
		dist[0] = 0;
		for (int i = 0; i < size; i++)
		{
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] >= INF) { return; }//���� ���� ���� ����µ� ������ ������ �̻��Ѱ��
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
	int getMinVertex(bool* selected, int* dist)//prim���� �̾��� ������� ���� ���� ����� ����, ����ġ ���� ������ ���ϵ���
	{
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v < size; v++)
		{
			if (!selected[v] && dist[v] < mindist)//selected�� ���� ���� ���� �����߿� �� �Ÿ��� 
				//���ݱ����� ���� ����� �Ÿ� mindistance ���� ������ 
			{
				mindist = dist[v];
				minv = v;
			}
		}
		return minv;
	}
};

class WgraphDijkstra : public WGraph//prim �˰���� ���
{
protected:
	int path[MAX_VTXS];//� ��带 ���ļ� �� �ּҰ�ΰ� ���Դ��� �ǹ�.�ڱ��ڽ� �ٷ� ������ �����ϸ�ȴ�.
	int dist[MAX_VTXS];//�� ���������� �Ÿ� �迭 
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
		int min = INF;//ó���� �� ū���� ��� ���� ���ؼ� �� ���� ���� ���ϴϱ�
		int minpos = -1;//�Ÿ��� �ּ��� ����� �ε���
		for (int i = 0; i < size; i++)
		{
			if (dist[i] < min && !found[i])//���� �Ÿ��� ���ݱ��� ã�� �ִܰ�κ��� �۰� S�׷쿡 ������ �ʴٸ�
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

		for (int i = 0; i < size - 1; i++)//start�� �̹� �߰��� �Ǿ������� ���� �� �� ��� �߿��� �ִܰŸ��� ��带 �̴°�
		{
			std::cout << "STEP " << i + 1 << " ";
			PrintDistance();
			int u = chooseVertex();//�ּҰŸ��� ����ִ� 
			found[u] = true;//ã�� ������ true�� �ٲ��ְ�
			for (int w = 0; w < size; w++)
			{
				if (!found[w])//���� ã������ ����� ��
				{
					if (dist[u] + getEdge(u, w) < dist[w])//������ �ִܰŸ���� �˰��ִ� dist[w]���� ����ã���� �Ÿ���ª����
					{
						dist[w] = dist[u] + getEdge(u, w);
						path[w] = u;//w�� ���� �濡 u�� �߰��ȴ�
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
		for (int i = 0; i < size; i++)//�ʱ�ȭ
		{
			for (int j = 0; j < size; j++)
			{
				A[i][j] = getEdge(i, j);
				path[i][j] = j;

			}
		}
		for (int k = 0; k < size; k++)//3�� ����
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (A[i][k] + A[k][j] < A[i][j])//���ο� ��Ʈ �� ������ ��Ʈ A[i][j]���� �۴ٸ� ��ü
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
		for (int i = 0; i < size; i++)//�ʱ�ȭ
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