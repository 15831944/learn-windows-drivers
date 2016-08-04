#include <ntifs.h>

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

VOID DriverUnLoad(PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("DriverUnLoad"));
}

VOID EnumDrivers(PDRIVER_OBJECT pDriverObject)
{
	LDR_DATA_TABLE_ENTRY	*pDataTableEntry, *pTmpDataTableEntry;
	LIST_ENTRY				*pListEntry;

	pDataTableEntry = (LDR_DATA_TABLE_ENTRY*)pDriverObject->DriverSection;
	if (!pDataTableEntry)
	{
		return;
	}

	pListEntry = pDataTableEntry->InLoadOrderLinks.Flink;

	// ���� pDataTableEntry �����е����������ṹ����ӡ���ǵ�����
	while (pListEntry != &pDataTableEntry->InLoadOrderLinks)
	{
		// �ṹ���һ����Ա���׵�ַ��ṹ����һ���ģ�����ֱ��ǿת�ṹ������
		pTmpDataTableEntry = (LDR_DATA_TABLE_ENTRY*)pListEntry;
		KdPrint(("%wZ", &pTmpDataTableEntry->FullDllName));
		pListEntry = pListEntry->Flink;
	}
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	KdPrint(("DriverEntry"));
	EnumDrivers(pDriverObject);
	pDriverObject->DriverUnload = DriverUnLoad;
	return STATUS_SUCCESS;
}