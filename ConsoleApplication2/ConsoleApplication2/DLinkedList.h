#pragma once
#include <stdio.h>
template <class T> class Node;
template <class T> class DLinkedList;
template <class T> class DLinkedListIterator;

template <class T>
class Node
{
public:
	T _data;
	Node<T>* next;
	Node<T>* prev;

	void InsertAfter(T data)
	{
		Node<T>* newNode = new Node<T>();
		newNode->_data = data;

		newNode->prev = this;
		newNode->next = next;
		if (0 != next)
			next->prev = newNode;
		next = newNode;
	}
	void InsertBefore(T data)
	{
		Node* newNode = new Node();
		newNode->_data = data;

		newNode->next = this;
		newNode->prev = prev;
		if (0 != prev)
			prev->next = newNode;
		prev = newNode;
	}

	void DeLink()
	{
		if (0 != prev)
			prev->next = prev;
		if (0 != next)
			next->prev = next;
	}
};

template <class T>
class DLinkedList
{
public:
	Node<T>* _head;
	Node<T>* _tail;
	int _count;

	DLinkedList()
	{
		_head = 0;
		_tail = 0;
		_count = 0;
	}
	~DLinkedList()
	{
		Node<T>* node = _head;
		Node<T>* next;
		while (0 != node)
		{
			next = node->next;
			delete node;
			node = next;
		}
	}

	void Append(T data) //링크드리스트 맨 마지막에 새로운 노드를 붙이는 함수
	{
		if (0 == _head)
		{
			Node<T>* newNode = new Node<T>();
			_head = newNode;
			_tail = newNode;
			_head->_data = data;
			_head->next = 0;
			_tail->prev = 0;
			_count++;
		}
		else
		{
			_tail->InsertAfter(data);
			_tail = _tail->next;

			_count++;
		}

	}
	void Prepend(T data)
	{
		if (0 == _head)
		{
			Node<T>* newNode = new Node<T>();
			_head = newNode;
			_tail = newNode;
			_head->_data = data;
			_head->next = 0;
			_tail->prev = 0;
			_count++;
		}
		else
		{
			_head->InsertBefore(data);
			_head = _head->prev;

			_count++;
		}
	}

	void RemoveHead()
	{
		Node<T>* node = new Node<T>();
		node = _head->next;
		delete _head;
		_head = node;
		
		if (0 == _head)
		{
			_tail = 0;
			_count--;
		}
		else
		{
			_head->prev = 0;
			_count--;
		}
	}
	void RemoveTail()
	{
		Node<T>* node = new Node<T>();
		node = _tail->prev;
		delete _tail;
		_tail = node;

		if (0 == _tail)
		{
			_head = 0;
			_count--;
		}
		else
		{
			_tail->next = 0;
			_count--;
		}
	}

	DLinkedListIterator<T> GetIterator()
	{
		return DLinkedListIterator<T>(this, _head);
	}

	void Remove(DLinkedListIterator<T>& itr)
	{
		if (0 == itr._node)
			return;

		Node<T>* newNode = itr._node;

		if (itr._node == _head)
			_head = _head->next;
		else if (itr._node == _tail)
			_tail = _tail->prev;

		itr.Forth();
		newNode->DeLink();
		delete newNode;

		if (0 == _head)
			_tail = 0;

		_count--;
	}
	void InsertAfter(DLinkedListIterator<T>& itr, int data)
	{
		if (0 != itr._node)
		{
			itr._node->InsertAfter(data);
			if (itr._node == _tail)
				_tail = itr._node->next;
		}
		else
			Append(data);
		_count++;
	}
	void InsertBefore(DLinkedListIterator<T>& itr, int data)
	{
		if (0 != itr._node)
		{
			itr._node->InsertBefore(data);
			if (itr._node == _head)
				_head = itr._node->prev;
		}
		else
			Prepend(data);
		_count++;
	}

	bool Save(const char* filename)
	{
		FILE* fp = fopen(filename, "wb");
		if (0 == fp)
		{
			printf("Can't Save!!\n");
			return false;
		}
		printf("Saving\n");
		fwrite(&_count, sizeof(T), 1, fp);

		Node<T>* node = _head;
		while (0 != node)
		{
			fwrite(&node->_data, sizeof(T), 1, fp);
			node = node->next;
		}
		fclose(fp);
		printf("Saved\n");

		return true;
	}

	bool Load(const char* filename)
	{
		FILE* fp = fopen(filename, "rb");
		if (0 == fp)
		{
			printf("Can't Load!!\n");
			return false;
		}
		printf("Loading\n");
		int count;
		fread(&count, sizeof(T), 1, fp);

		while (0 < count)
		{
			T buffer;
			fread(&buffer, sizeof(T), 1, fp);
			Append(buffer);
			count--;
		}
		fclose(fp);
		printf("Loaded\n");

		return true;
	}
};

template <class T>
class DLinkedListIterator
{
public:
	DLinkedList<T>* _dll;
	Node<T>* _node;

	DLinkedListIterator<T>(DLinkedList<T>* dll, Node<T>* node)
	{
		_dll = dll;
		_node = node;
	}
	void Start()
	{
		if(0 != _dll)
			_node = _dll->_head;
	}
	void End()
	{
		if (0 != _dll)
			_node = _dll->_tail;
	}
	void Forth()
	{
		if (0 != _node)
			_node = _node->next;
	}
	void Back()
	{
		if (0 != _node)
			_node = _node->prev;
	}
	bool Valid()
	{
		if (0 != _node)
			return true;

		return false;
	}
	T Item()
	{
		return _node->_data;
	}
};