#ifndef _NTSTRUCTDEF_H_
#define _NTSTRUCTDEF_H_

// �ڴ���� TAG
#define MEM_TAG 'MEM'

// �ַ�������
#define MAX_STRING_LENGTH			512
#define MAX_PID_LENGTH				32
#define MAX_TIME_LENGTH				20

// ������������
#define REGISTRY_MONITOR_DEVICE		L"\\Device\\_RegistryMonitor"
#define REGISTRY_MONITOR_SYMBOLIC	L"\\??\\_RegistryMonitor"
#define PROCESS_MONITOR_DEVICE		L"\\Device\\_ProcessMonitor"
#define PROCESS_MONITOR_SYMBOLIC	L"\\??\\_ProcessMonitor"


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

#ifndef _NTIFS_

typedef unsigned short WORD;

typedef struct _TIME_FIELDS {
	WORD wYear;
	WORD wMonth;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
	WORD wWeekday;
} TIME_FIELDS;

typedef enum _REG_NOTIFY_CLASS {
	RegNtDeleteKey,
	RegNtPreDeleteKey = RegNtDeleteKey,
	RegNtSetValueKey,
	RegNtPreSetValueKey = RegNtSetValueKey,
	RegNtDeleteValueKey,
	RegNtPreDeleteValueKey = RegNtDeleteValueKey,
	RegNtSetInformationKey,
	RegNtPreSetInformationKey = RegNtSetInformationKey,
	RegNtRenameKey,
	RegNtPreRenameKey = RegNtRenameKey,
	RegNtEnumerateKey,
	RegNtPreEnumerateKey = RegNtEnumerateKey,
	RegNtEnumerateValueKey,
	RegNtPreEnumerateValueKey = RegNtEnumerateValueKey,
	RegNtQueryKey,
	RegNtPreQueryKey = RegNtQueryKey,
	RegNtQueryValueKey,
	RegNtPreQueryValueKey = RegNtQueryValueKey,
	RegNtQueryMultipleValueKey,
	RegNtPreQueryMultipleValueKey = RegNtQueryMultipleValueKey,
	RegNtPreCreateKey,
	RegNtPostCreateKey,
	RegNtPreOpenKey,
	RegNtPostOpenKey,
	RegNtKeyHandleClose,
	RegNtPreKeyHandleClose = RegNtKeyHandleClose,
	//
	// .Net only
	//    
	RegNtPostDeleteKey,
	RegNtPostSetValueKey,
	RegNtPostDeleteValueKey,
	RegNtPostSetInformationKey,
	RegNtPostRenameKey,
	RegNtPostEnumerateKey,
	RegNtPostEnumerateValueKey,
	RegNtPostQueryKey,
	RegNtPostQueryValueKey,
	RegNtPostQueryMultipleValueKey,
	RegNtPostKeyHandleClose,
	RegNtPreCreateKeyEx,
	RegNtPostCreateKeyEx,
	RegNtPreOpenKeyEx,
	RegNtPostOpenKeyEx,
	//
	// new to Windows Vista
	//
	RegNtPreFlushKey,
	RegNtPostFlushKey,
	RegNtPreLoadKey,
	RegNtPostLoadKey,
	RegNtPreUnLoadKey,
	RegNtPostUnLoadKey,
	RegNtPreQueryKeySecurity,
	RegNtPostQueryKeySecurity,
	RegNtPreSetKeySecurity,
	RegNtPostSetKeySecurity,
	//
	// per-object context cleanup
	//
	RegNtCallbackObjectContextCleanup,
	//
	// new in Vista SP2 
	//
	RegNtPreRestoreKey,
	RegNtPostRestoreKey,
	RegNtPreSaveKey,
	RegNtPostSaveKey,
	RegNtPreReplaceKey,
	RegNtPostReplaceKey,
	//
	// new to Windows 10
	//
	RegNtPreQueryKeyName,
	RegNtPostQueryKeyName,

	MaxRegNtNotifyClass //should always be the last enum
} REG_NOTIFY_CLASS;
#endif



typedef struct _PROCESSINFO
{
	TIME_FIELDS			time;						// ʱ��
	HANDLE				hParentProcessId;			// ������ ID
	ULONG				ulParentProcessLength;		// �����̳���
	HANDLE				hProcessId;					// �ӽ��� ID
	ULONG				ulProcessLength;			// �ӽ��̳���
	ULONG				ulCommandLineLength;		// ���������в�������
	UCHAR				uData[1];					// ������
} PROCESSINFO, *PPROCESSINFO;

typedef struct _REGISTRY_EVENT
{
	HANDLE				hProcessId;					// ����ע���Ľ���
	TIME_FIELDS			time;						// ����ʱ��
	REG_NOTIFY_CLASS	enRegistryNotifyClass;		// ���������ͣ��½���ɾ�����޸ĵ�
	ULONG				ulProcessPathLength;		// ����ע�����̵�·������
	ULONG				ulRegistryPathLength;		// ������ע���·������
	ULONG				ulKeyValueType;				// ������޸�ֵ����ʾ�޸ĵ����ݼ�����������
	ULONG				ulDataLength;				// ������޸�ֵ������޸ĵ����ݵĳ���
	UCHAR				uData[1];					// �洢·�����޸ĵ�ֵ�Ŀռ�
} REGISTRY_EVENT, *PREGISTRY_EVENT;

#endif
