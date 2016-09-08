#ifndef __LISTENTRY_H__
#define __LISTENTRY_H__

#include <ntifs.h>
#include "NtStructDef.h"

KSPIN_LOCK	g_Lock;			// �����������
KEVENT		g_Event;		// ����֪ͨ���¼�
LIST_ENTRY	g_ListHead;		// ����ͷ

// ������̵�����
typedef struct
{
	LIST_ENTRY		list_entry;
	PPROCESSINFO	pProcessInfo;
} PROCESSNODE, *PPROCESSNODE;


PPROCESSNODE	InitListNode();
VOID			DestroyList();

#endif // !__LISTENTRY_H__


