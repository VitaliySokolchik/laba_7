#pragma once
#include <iostream>
#include <string>

using namespace std;

class Exception
{
protected:
	int error;
public:
	Exception()
	{
		error = 0;
	}
	Exception(int _error)
	{
		error = _error;
	}
	~Exception()
	{

	};
	void Print()
	{
		if (this->error == 1)
		{
			cout << "Input error! Enter int!" << endl;
		}
		if (this->error == 2)
		{
			cout << "Input error! Enter double!" << endl;
		}
		if (this->error == 3)
		{
			cout << "The stack is empty!" << endl;
		}
	}
};

template<typename T>
class Node
{
public:
	Node<T>* pNext;
	T data;
	Node(T data = T(), Node* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
};

template<typename T>
class Iterator : public Node<T>
{
	Node<T>* pointer;
public:
	Iterator()
	{
		this->pointer = nullptr;
	}
	Iterator(Node<T>* element)
	{
		this->pointer = element;
	}
	~Iterator()
	{
		this->pointer = nullptr;
	}
	Iterator operator+(int n)
	{
		return *(pointer + n);
	}
	Iterator operator++(int n)
	{
		return *pointer++;
	}
	Iterator operator*()
	{
		return *pointer;
	}
	bool operator!= (const Iterator& it)
	{
		return pointer != it.pointer;
	}
};


template<typename T>
class Stack :public Node<T>
{
public:
	Stack();
	~Stack();
	void pop();
	void clear();
	int GetSize()
	{
		return Size;
	}
	T& operator[](const int index);
	void push(T data);
	Iterator<T> begin()
	{
		return (this->head);
	}
	Iterator<T> end()
	{
		Node<T>* current = this->head;
		for (int i = 0; i < Size + 1; i++)
		{
			current = current->pNext;
		}
		return current;
	}
private:
	int Size;
	Node<T>* head;
	friend ostream& operator<<(ostream& out, const Node<T>& node);
};
