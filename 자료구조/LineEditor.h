#pragma once
#include<iostream>
#include<fstream>
#include<string>
inline void error(const char* str)
{
	std::cerr << str << std::endl;
	exit(1);
}
class line
{
protected:
	std::string data;

public:
	line(std::string line = "")
	{
		data = line;
	}
	void read(std::istream* is = &std::cin)
	{
		std::getline(*is, data);
	}
	void display(std::ostream* os = &std::cout)
	{
		*os << data << "\n";
	}
	bool hasData(std::string str)
	{
		return str == data;
	}
};
class node : public line
{
private:
	node* next;
public:
	node(std::string str = "")
		:line(str)
	{
		next = nullptr;
	}
	node* getLink() { return next; } // 구조체로 node를 만들었을 땐 next에 바로 접근이 가능했지만
	//객체지향에선 안전하게 함수로 리턴해주는게 맞다.
	std::string  getData() { return data; }
	void setLink(node* target) { next = target; }

	void insertNext(node* newnode)
	{
		if (newnode != nullptr)
		{
			newnode->next = next; //a-b()-c가 있을 때 (n)에 추가하기위해 n을 c와 연결 
			next = newnode;	//b와 n을 연결
		}
	}
	node* removeNext()
	{
		node* removed = next;
		if (removed != nullptr)
		{
			next = removed->next;
		}
		return removed;
	}
};
class l_hn_s_linked_list
{
protected:
	node origin;
public:
	l_hn_s_linked_list()
		:origin("head node") {}
	~l_hn_s_linked_list() { clear(); }
	void clear();
	node* getHead();
	bool isEmpty();
	node* getEntry(int pos);
	void insert(int pos, node* n);
	node* remove(int pos);
	node* find(std::string value);
	void replace(int pos, node* n);
	size_t size();
	void display();

};
void l_hn_s_linked_list::clear()
{
	while (!isEmpty())
	{
		delete remove(0);
	}
}
node* l_hn_s_linked_list::getHead()
{
	return origin.getLink(); //origin의 다음 노드가 실제 헤드 노드가된다. 오리진은 그 앞에 가상
}
bool l_hn_s_linked_list::isEmpty()
{
	return getHead() == nullptr;
}
node* l_hn_s_linked_list::getEntry(int pos)
{
	node* n = &origin;
	for (int i = -1; i < pos; i++, n = n->getLink()) // for 문 안에서 연산 여러개 가능
							//여기서 부터 i++랑 n=n->getLink가 같이 일어난다. 
	{
		if (n == nullptr)
		{
			break;
		}
	}
	return n;
}
void l_hn_s_linked_list::insert(int pos, node* n)
{
	node* prev = getEntry(pos - 1);
	if (prev != nullptr)
	{
		prev->insertNext(n);
	}
}
node* l_hn_s_linked_list::remove(int pos)
{
	node* prev = getEntry(pos - 1);
	if (prev != nullptr)
	{
		return prev->removeNext();
	}
}
node* l_hn_s_linked_list::find(std::string value)
{
	for (node* p = getHead(); p != nullptr; p->getLink())
	{
		if (p->getData() == value)
		{
			return p;
		}
	}return nullptr;
}
void l_hn_s_linked_list::replace(int pos, node* n)
{
	node* prev = getEntry(pos - 1);
	if (prev != nullptr)
	{
		delete prev->removeNext();
		prev->insertNext(n);
	}
}
size_t l_hn_s_linked_list::size()
{
	int count = 0;
	for (node* p = getHead(); p != nullptr; p->getLink())
	{
		count++;
	}
	return count;
}
void l_hn_s_linked_list::display()
{
	int count = 0;
	std::cout << " 전체 항목의 수  :" << size() << ", ";
	for (node* p = getHead(); p != nullptr; p->getLink())
	{
		std::cout << p->getData() << " ";
	}
}
class LineEditor : public l_hn_s_linked_list
{
public:
	void Display(std::ostream* os);
	void InsertLine();
	void DeleteLine();
	void ReplaceLine();
	void LoadFile(std::string fname);
	void SaveFile(std::string fname);
};
void LineEditor::Display(std::ostream* os = &std::cout)
{
	int i = 0;
	std::cout << " 전체 항목의 수  :" << size() << ", ";
	for (node* p = getHead(); p != nullptr; p->getLink(), i++)
	{
		std::cerr << i << " ";
		p->display(os);
	}
}
void LineEditor::InsertLine()
{
	int position;
	std::string line;
	std::cout << " 입력행 번호 : " << std::endl;
	std::cin >> position;
	std::cin.sync(); //버퍼지우기 fflush같은거  or cin.ignore()가 있다.
	std::cin.clear();
	std::cout << "입력할 내용 : ";
	getline(std::cin, line);
	insert(position, new node(line));
}
void LineEditor::DeleteLine()
{
	int position;
	std::cout << "삭제행 번호 : ";
	std::cin >> position;
	remove(position);
}
void LineEditor::ReplaceLine()
{
	int position;
	std::string line;
	std::cout << " 입력행 번호 : " << std::endl;
	std::cin >> position;
	std::cin.sync(); //버퍼지우기 fflush같은거  or cin.ignore()가 있다.
	std::cin.clear();
	std::cout << "변경할 내용 : ";
	getline(std::cin, line);
	replace(position, new node(line));
}
void LineEditor::LoadFile(std::string fname)
{
	std::ifstream ifs(fname);
	std::string line;
	while (std::getline(ifs, line))
	{
		insert(size(), new node(line));
	}
	ifs.close();
}
void LineEditor::SaveFile(std::string fname)
{
	std::ofstream ofs(fname);
	if (ofs.good())
	{
		Display(&ofs);
		ofs.close();
	}
}
/*int main()
{
	LineEditor editor;
	char command;
	do
	{
		std::cout << " [메뉴선택] i=입력, d=삭제, r=변경, p=출력, l=파일읽기, s=저장, q=종료" << std::endl;
		command = std::getchar();
		std::cin.sync();
		switch (command)
		{
		case 'd':
			editor.DeleteLine();
			break;
		case 'i':
			editor.InsertLine();
			break;
		case 'r':
			editor.ReplaceLine();
			break;
		case 'l':
			editor.LoadFile("test.txt");
			break;
		case 's':
			editor.SaveFile("test.txt");
			break;
		case 'p':
			editor.Display();
			break;
		case 'q':
			break;
		}
	} while (command != 'q');

	return 0;
}*/
