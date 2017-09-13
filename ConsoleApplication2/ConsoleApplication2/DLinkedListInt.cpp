#include "DLinkedListInt.h"

DLinkedListIntIterator DLinkedListInt::GetIterator()
{
	return DLinkedListIntIterator(this, _head);
}

void DLinkedListInt::Remove(DLinkedListIntIterator& itr)
{
	if (0 == itr._node)
		return;

	NodeInt* newNode = itr._node;

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
void DLinkedListInt::InsertAfter(DLinkedListIntIterator& itr, int data)
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
void DLinkedListInt::InsertBefore(DLinkedListIntIterator& itr, int data)
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