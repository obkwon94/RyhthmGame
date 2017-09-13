#pragma once
#include <stdio.h>

class DLinkedListIntIterator;

class NodeInt
{
public:
	int _data;
	NodeInt* next;
	NodeInt* prev;

	void InsertAfter(int data)
	{
		NodeInt* newNode = new NodeInt();
		newNode->_data = data;

		newNode->prev = this;
		newNode->next = next;
		if (0 != next)
			next->prev = newNode;
		next = newNode;
	}
	void InsertBefore(int data)
	{
		NodeInt* newNode = new NodeInt();
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

class DLinkedListInt
{
public:
	NodeInt* _head;
	NodeInt* _tail;
	int _count;

	DLinkedListInt()
	{
		_head = 0;
		_tail = 0;
		_count = 0;
	}
	~DLinkedListInt()
	{
		NodeInt* node = _head;
		NodeInt* next;
		while (0 != node)
		{
			next = node->next;
			delete node;
			node = next;
		}
	}

	void Append(int data) //링크드리스트 맨 마지막에 새로운 노드를 붙이는 함수
	{
		if (0 == _head)
		{
			NodeInt* newNode = new NodeInt();
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
	void Prepend(int data)
	{
		if (0 == _head)
		{
			NodeInt* newNode = new NodeInt();
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
		NodeInt* node = new NodeInt();
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
		NodeInt* node = new NodeInt();
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

	bool Save(const char* filename)
	{
		FILE* fp = fopen(filename, "wb");
		if (0 == fp)
		{
			printf("Can't Save!!\n");
			return false;
		}
		printf("Saving\n");
		fwrite(&_count, sizeof(int), 1, fp);

		NodeInt* node = _head;
		while (0 != node)
		{
			fwrite(&node->_data, sizeof(int), 1, fp);
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
		fread(&count, sizeof(int), 1, fp);

		while (0 < count)
		{
			int buffer;
			fread(&buffer, sizeof(int), 1, fp);
			Append(buffer);
			count--;
		}
		fclose(fp);
		printf("Loaded\n");

		return true;
	}

	DLinkedListIntIterator GetIterator();

	void Remove(DLinkedListIntIterator& itr);
	void InsertAfter(DLinkedListIntIterator& itr, int data);
	void InsertBefore(DLinkedListIntIterator& itr, int data);

};

class DLinkedListIntIterator
{
public:
	DLinkedListInt* _dll;
	NodeInt* _node;

	DLinkedListIntIterator(DLinkedListInt* dll, NodeInt* node)
	{
		_dll = dll;
		_node = node;
	}
	void Start()
	{
		if (0 != _dll)
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
	int Item()
	{
		return _node->_data;
	}
};


