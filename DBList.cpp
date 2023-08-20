
/* 	Radio Shack DBF File Reading Library
	DBList.cpp

	Note: Most of this code is from examples from my C++ class in school.
	No need to reinvent the wheel here! I've decided on using a linked
	list because technically there is no telling how big the database
	file can be. In all seriousness, most scanners supported by the
	Scanner Loader application have no more than 400 channels.
*/

/* for Microsoft Visual C++ only */
#include "stdafx.h"

#include "DBList.h"

/* DBList constructor is defined in DBList.h */

/* DBList destructor */

DBList::DBList()
{
	head = NULL;
}

DBList::~DBList()
{
	DBNode *p;
	while (head != NULL) {
		p = head;
		head = head -> next;
		delete p;
	}
}

void DBList::Insert(DBEntry entry)
{
	DBNode *p = head, *prev = NULL, *newNode;
	while (p != NULL)
	{
		prev = p;
		p = p -> next;
	}
	newNode = new DBNode(entry, p);
	if (prev != NULL)
		prev -> next = newNode;
	else
		head = newNode;
}

DBEntry DBList::GetEntry(int index)
{
	DBNode *p = head;
	int count = 0;

	while (p != NULL && count < index)
	{
		p = p -> next;
		count++;
	}
	return p->data;
}


