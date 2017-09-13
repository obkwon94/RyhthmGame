#include <stdio.h>

#include "DLinkedList.h"

#define TEST_BEGIN(a) printf("\n-----------------");printf(a);printf(" Begin-----------------\n");{
#define TEST_END(a) }printf("\n------------------");printf(a);printf(" END------------------\n")

int main()
{
	/*Array2D<int> ar2d(4, 4);

	ar2d.GetArray(0, 0)=1;
	ar2d.GetArray(0, 1)=2;
	ar2d.GetArray(0, 2)=3;

	ar2d.GetArray(1, 0)=11;
	ar2d.GetArray(1, 1)=12;
	ar2d.GetArray(1, 2)=13;

	ar2d.GetArray(2, 0) = 21;
	ar2d.GetArray(2, 1) = 22;
	ar2d.GetArray(2, 2) = 23;
	
	
	printf("%d %d %d\n", ar2d.GetArray(0, 0), ar2d.GetArray(0, 1), ar2d.GetArray(0, 2));
	printf("%d %d %d\n", ar2d.GetArray(1, 0), ar2d.GetArray(1, 1), ar2d.GetArray(1, 2));
	printf("%d %d %d\n", ar2d.GetArray(2, 0), ar2d.GetArray(2, 1), ar2d.GetArray(2, 2));
	printf("\n");

	ar2d.SaveData("KOB.dat");

	Array2D<int> tar2d(4, 4);

	tar2d.LoadData("KOB.dat");

	printf("%d %d %d\n", tar2d.GetArray(0, 0), tar2d.GetArray(0, 1), tar2d.GetArray(0, 2));
	printf("%d %d %d\n", tar2d.GetArray(1, 0), tar2d.GetArray(1, 1), tar2d.GetArray(1, 2));
	printf("%d %d %d\n", ar2d.GetArray(2, 0), ar2d.GetArray(2, 1), ar2d.GetArray(2, 2));
	printf("\n");*/
	/*
	//Append();
	printf("-----------------Append Begin-----------------\n");
	{
		DLinkedListInt dll;

		for (int i = 0; i < 5; i++)
			dll.Append(i);

		NodeInt* node = dll._head;
		NodeInt* next;

		while (NULL != node)
		{
			next = node->next;
			printf("%d\n", node->_data);

			node = next;
		}
	}
	printf("-----------------End-----------------\n");

	//Prepend();
	printf("-----------------Prepend Begin-----------------\n");
	{
		DLinkedListInt dll;

		for (int i = 0; i < 5; i++)
			dll.Prepend(i);

		NodeInt* node = dll._head;
		NodeInt* next;

		while (NULL != node)
		{
			next = node->next;
			printf("%d\n", node->_data);

			node = next;
		}
	}
	printf("-----------------End-----------------\n");
	
	//Remove to head and tail;
	printf("\n-----------------RemoveHead Begin-----------------\n");
	{
		DLinkedListInt dll;

		for (int i = 0; i < 5; i++)
			dll.Prepend(i);

		int count = 0;

		NodeInt* node = dll._head;
		NodeInt* next;

		while (NULL != node)
		{
			next = node->next;
			printf("Prepend : %d\n", node->_data);

			node = next;

			count++;
		}
		printf("Original Count %d\n", count);

		dll.RemoveHead();
		{
			int count = 0;

			NodeInt* node = dll._head;
			NodeInt* next;

			while (NULL != node)
			{
				next = node->next;
				printf("RemoveHead : %d\n", node->_data);

				node = next;

				count++;
			}
			printf("Count After RemoveHead %d\n", count);
		}
		printf("-----------------End-----------------\n");

		printf("\n-----------------RemoveTail Begin-----------------\n");

		dll.RemoveTail();
		{
			int count = 0;
			NodeInt* node = dll._head;
			NodeInt* next;
			while (NULL != node)
			{
				next = node->next;
				printf("RemoveTail : %d\n", node->_data);

				node = next;

				count++;
			}
			printf("Count After RemoveTail %d\n", count);
		}
	}
	printf("-----------------End-----------------\n");

	//Iterator();
	printf("\n-----------------반복자(Iterator) 기본 원리 Begin-----------------\n");
	{
		DLinkedListInt dll;

		for (int i = 0; i < 5; i++)
			dll.Prepend(i);

		NodeInt* itr = dll._head;
		while (NULL != itr)
		{
			printf("%d\n", itr->_data);

			itr = itr->next;
		}

		itr = dll._tail;
		

		while (NULL != itr)
		{
			printf("%d\n", itr->_data);

			itr = itr->prev;
		}
	}
	printf("-----------------End-----------------\n");
	*/
	//IntIterator Remove();
	TEST_BEGIN("IntIterator and Remove");
	
		DLinkedList<int> dll;

		for (int i = 0; i < 5; i++)
			dll.Prepend(i);

		DLinkedListIterator<int> itr = dll.GetIterator();

		for (itr.Start(); itr.Valid(); itr.Forth())
			printf("%d\n", itr.Item());

		itr.Start();
		while (itr.Valid())
		{
			dll.Remove(itr);
		}
		printf("count : %d\n", dll._count);
	
	TEST_END("IntIterator and Remove");

	/*
	//IntIterator InsertBefore();
	
	TEST_BEGIN("IntIterator and InsertBefore");
	
		DLinkedListInt dll;

		for (int i = 0; i < 5; i++)
			dll.Prepend(i);

		DLinkedListIntIterator itr = dll.GetIterator();

		for (itr.Start(); itr.Valid(); itr.Forth())
			printf("%d\n", itr.Item());

		itr.Start();

		dll.InsertBefore(itr, 1000);

		for (itr.Start(); itr.Valid(); itr.Forth())
			printf("InsertBefore : %d\n", itr.Item());

		printf("count : %d\n", dll._count);

	TEST_END("IntIterator and InsertBefore");


	//IntIterator InsertAfter();
	TEST_BEGIN("IntIterator and InsertAfter");
	
		DLinkedListInt dll;

		for (int i = 0; i < 5; i++)
			dll.Prepend(i);

		DLinkedListIntIterator itr = dll.GetIterator();

		for (itr.Start(); itr.Valid(); itr.Forth())
			printf("%d\n", itr.Item());

		itr.Start();

		dll.InsertAfter(itr, 1000);

		for (itr.Start(); itr.Valid(); itr.Forth())
			printf("InsertAfter : %d\n", itr.Item());

		printf("count : %d\n", dll._count);

		
	
	TEST_END("IntIterator and InsertAfter");

	//Save();
	TEST_BEGIN("Save");

	DLinkedListInt dll;

	for (int i = 0; i < 5; i++)
		dll.Prepend(i);

	DLinkedListIntIterator itr = dll.GetIterator();

	for (itr.Start(); itr.Valid(); itr.Forth())
		printf("%d\n", itr.Item());

	dll.Save("Save.dat");

	TEST_END("Save");

	
	TEST_BEGIN("Load");

	DLinkedListInt dll;

	dll.Load("Save.dat");

	DLinkedListIntIterator itr = dll.GetIterator();

	for (itr.Start(); itr.Valid(); itr.Forth())
		printf("%d\n", itr.Item());

	TEST_END("Load");
	
	//template();
	TEST_BEGIN("template");
	DLinkedList<float> dll;

	for (int i = 0; i < 5; i++)
		dll.Prepend((float)(i*0.5f));

	DLinkedListIterator<float> itr = dll.GetIterator();

	for (itr.Start(); itr.Valid(); itr.Forth())
		printf("%0.1f\n", itr.Item());

	TEST_END("template");
	return 0;
	*/
}