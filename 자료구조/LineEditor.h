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
	node* getLink() { return next; } // ����ü�� node�� ������� �� next�� �ٷ� ������ ����������
	//��ü���⿡�� �����ϰ� �Լ��� �������ִ°� �´�.
	std::string  getData() { return data; }
	void setLink(node* target) { next = target; }

	void insertNext(node* newnode)
	{
		if (newnode != nullptr)
		{
			newnode->next = next; //a-b()-c�� ���� �� (n)�� �߰��ϱ����� n�� c�� ���� 
			next = newnode;	//b�� n�� ����
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
	return origin.getLink(); //origin�� ���� ��尡 ���� ��� ��尡�ȴ�. �������� �� �տ� ����
}
bool l_hn_s_linked_list::isEmpty()
{
	return getHead() == nullptr;
}
node* l_hn_s_linked_list::getEntry(int pos)
{
	node* n = &origin;
	for (int i = -1; i < pos; i++, n = n->getLink()) // for �� �ȿ��� ���� ������ ����
							//���⼭ ���� i++�� n=n->getLink�� ���� �Ͼ��. 
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
	std::cout << " ��ü �׸��� ��  :" << size() << ", ";
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
	std::cout << " ��ü �׸��� ��  :" << size() << ", ";
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
	std::cout << " �Է��� ��ȣ : " << std::endl;
	std::cin >> position;
	std::cin.sync(); //��������� fflush������  or cin.ignore()�� �ִ�.
	std::cin.clear();
	std::cout << "�Է��� ���� : ";
	getline(std::cin, line);
	insert(position, new node(line));
}
void LineEditor::DeleteLine()
{
	int position;
	std::cout << "������ ��ȣ : ";
	std::cin >> position;
	remove(position);
}
void LineEditor::ReplaceLine()
{
	int position;
	std::string line;
	std::cout << " �Է��� ��ȣ : " << std::endl;
	std::cin >> position;
	std::cin.sync(); //��������� fflush������  or cin.ignore()�� �ִ�.
	std::cin.clear();
	std::cout << "������ ���� : ";
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
		std::cout << " [�޴�����] i=�Է�, d=����, r=����, p=���, l=�����б�, s=����, q=����" << std::endl;
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
