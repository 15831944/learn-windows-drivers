#pragma once

// �ڴ���� TAG
#define MEM_TAG 'MEM'

// �ַ�������
#define MAX_STRING_LENGTH 512

// ��Ӧ�ò����������һ���ַ�����
#define  CWK_DVC_SEND_STR \
	(ULONG)CTL_CODE( \
	FILE_DEVICE_UNKNOWN, \
	0x911,METHOD_BUFFERED, \
	FILE_WRITE_DATA)

// ��������ȡһ���ַ���
#define  CWK_DVC_RECV_STR \
	(ULONG)CTL_CODE( \
	FILE_DEVICE_UNKNOWN, \
	0x912,METHOD_BUFFERED, \
	FILE_READ_DATA)

typedef struct _PROCESSINFO
{
	HANDLE	hParentId;
	HANDLE	hProcessId;
	WCHAR	wsProcessPath[MAX_STRING_LENGTH];
	WCHAR	wsProcessCommandLine[MAX_STRING_LENGTH];
} PROCESSINFO, *PPROCESSINFO;
