﻿#include <iostream>
#include<string>
using namespace std;

class cat
{
private:
	static int in;
	int id;
	string name;
	string diagnosis;
public:
	cat(string nm, string dg) : name(nm), diagnosis(dg)
	{
		id = in;
		in++;
	}
	cat()
	{
		id = 0;
		in++;
		name = "-";
		diagnosis = "-";
	}
	void input()
	{
		cout << "\nВведите имя котика" << endl;
		getline(cin, name);
		cout << "\nВведите дигноз" << endl;
		getline(cin, diagnosis);

	}
	void output()
	{
		cout << "\nId - " << id << "\nИмя - " << name << "\nДиагноз - " << diagnosis << endl;
	}
	bool operator< (cat& c2) const
	{
		return (name[0] < c2.name[0]) ? true : false;
	}
	bool operator> (cat& c2) const
	{
		return (name[0] > c2.name[0]) ? true : false;
	}
	bool operator== (cat& c2) const
	{
		return (name[0] == c2.name[0]) ? true : false;
	}
	friend ostream& operator<<(ostream& out, const cat c);
};
int cat::in = 1;
ostream& operator<<(ostream& out, const cat c)
{
	out << "\nId - " << c.id << "\nИмя - " << c.name << "\nДиагноз - " << c.diagnosis << endl;
	return out;
}

class Exception
{
};


//void my_terminate()
//{
//	cerr << "\nTerminate handler called" << endl;
//	abort();
//}
//void my_unexpected()
//{
//	cerr << "\nUnexpected exception" << endl;
//	terminate();
//}


template <typename T>
class  Node
{
public:
	T data;
	Node* next;
	Node() : data(), next(nullptr) { }
	Node(T d) : data(d), next(nullptr) { }
};


template<class T>
class Ring
{
private:
	Node<T>* head;
	int size;
public:
	Ring() :head(nullptr), size(0) {}
	void push(T x)
	{
		if (head == nullptr)
		{
			Node<T>* element = new Node<T>(x);
			head = new Node<T>(x);
			element->next = head;
			head = element;
			size++;
		}
		else
		{
			Node<T>* tmp = head;
			int i = 0;
			while (i < size - 1)
			{
				tmp = tmp->next;
				i++;
			}
			tmp->next = new Node<T>(x);
			tmp->next->next = head;
			size++;
		}
	}
	void pop()
	{
		if (size == 0)
			throw Exception();
		Node<T>* tmp = head;
		head = head->next;
		delete tmp;
		size--;
		Node<T>* t = head;
		int i = 0;
		while (i < size - 1)
		{
			t = t->next;
			i++;
		}
		t->next = head;
	}
	void output()
	{
		if (size == 0)
			throw Exception();
		Node<T>* tmp = head;
		int i = 0;
		while (i < size)
		{
			cout << "   " << tmp->data;
			tmp = tmp->next;
			i++;
		}
	}
	Node<T>* get_node() {
		return head;
	}
	int get_size() {
		return size;
	}
	friend ostream& operator<<(ostream& out, const Node<T>& node);
};

template<class T>
class Iterator
{
private:
	Node<T>* node;
	int size;
	int current;
public:
	friend Ring<T>;
	Iterator(Ring<T>* element) : current(0)
	{
		node = element->get_node();
		size = element->get_size();
	}
	void begin()
	{
		if (size == 0)
			throw Exception();
		if (current != 0)
		{
			while (current < size)
			{
				current++;
				node = node->next;
			}
			current = 0;
		}

	}
	void search(T x)
	{
		if (size == 0)
			throw Exception();
		int i = 0;
		while (i < size)
		{
			if (x == node->data)
			{
				cout << "\nДанные найдены\n " << x << endl;
				return;
			}
			if (current == size - 1)
				current = 0;
			else
				current++;
			node = node->next;
			i++;
		}
		cout << "Данные не найдены" << endl;
	}
	Iterator& operator++()
	{
		if (size == 0)
			throw Exception();
		if (size == 1)
			current = 0;
		else
			current++;
		node = node->next;
		return *this;
	}
	T operator*() {
		return node->data;
	}
	void operator = (T x)
	{
		if (size == 0)
			throw Exception();
		node->data = x;
	}
	Iterator& operator[](int index)
	{
		if (size == 0)
			throw Exception();
		Node<T>* tmp = node;
		while (1)
		{
			if (current == index)
			{
				node = tmp;
				return *this;
			}
			tmp = tmp->next;
			if (current == size - 1)
				current = 0;
			else
				current++;
		}
	}
	void shell()
	{
		if (size == 0)
			throw Exception();
		T tmp;
		int step, i, j;
		for (step = size / 2; step > 0; step /= 2)
			for (i = step; i < size; i++)
				for (j = i - step; j >= 0 && (*this)[j].node->data > (*this)[j + step].node->data; j -= step)
				{
					tmp = (*this)[j].node->data;
					(*this)[j].node->data = (*this)[j + step].node->data;
					(*this)[j + step].node->data = tmp;
				}
	}
};



int main()
{
	setlocale(LC_ALL, "Russian");
	//set_terminate(my_terminate);
	//set_unexpected(my_unexpected);
	Ring<cat> ring;
	try
	{
		ring.pop();
	}
	catch (Exception)
	{
		cerr << "\nКольцо не содержит элементов\n";
	}
	cout << "\n-----------------------------------------------------------------------------------\n";
	cat c1("Макс", "головная боль");
	ring.push(c1);
	ring.push(cat("Барсик", "зубная боль"));
	ring.push(cat("Дружок", "проблемы с желудком"));
	cat c4("Лизка", "катаракта");
	ring.push(c4);
	ring.push(cat("Мурка", "проблемы с сердцем"));
	try
	{
		ring.output();
		cout << "\n-----------------------------------------------------------------------------------\n";
		Iterator<cat> I(&ring);
		cout << "\nСортировка по именам" << endl;
		cout << "\n-----------------------------------------------------------------------------------\n";
		I.begin();
		I.shell();
		ring.output();
		cout << "\n-----------------------------------------------------------------------------------\n";
		ring.pop();
		ring.output();
		cout << "\n-----------------------------------------------------------------------------------\n";
		ring.pop();
		ring.output();
		cout << "\n-----------------------------------------------------------------------------------\n";
		I.begin();
		I.search(c4);
		I.search(c1);
	}
	catch (Exception)
	{
		cerr << "\nКольцо не содержит элементов\n";
	}

}