#include "IODeviceControl.h"

NTSTATUS CreateDevice(PDRIVER_OBJECT pDriverObject)
{
	NTSTATUS status;
	PDEVICE_OBJECT pDeviceObject;
	UNICODE_STRING usDeviceName;
	UNICODE_STRING usSymbolicName;

	RtlInitUnicodeString(&usDeviceName, PROCESS_MONITOR_DEVICE);

	status = IoCreateDevice(
		pDriverObject,
		0,
		&usDeviceName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		TRUE,
		&pDeviceObject);
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	RtlInitUnicodeString(&usSymbolicName, PROCESS_MONITOR_SYMBOLIC);

	status = IoCreateSymbolicLink(&usSymbolicName, &usDeviceName);
	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(pDeviceObject);
		return status;
	}

	return STATUS_SUCCESS;
}

NTSTATUS RemoveDevice(PDRIVER_OBJECT pDriverObject)
{
	NTSTATUS		status;
	UNICODE_STRING	usSymbolicName;

	RtlInitUnicodeString(&usSymbolicName, PROCESS_MONITOR_SYMBOLIC);

	// ɾ���������Ӻ��豸����
	if (NULL != pDriverObject->DeviceObject)
	{
		status = IoDeleteSymbolicLink(&usSymbolicName);
		IoDeleteDevice(pDriverObject->DeviceObject);
		KdPrint(("Unload driver success..\r\n"));
	}

	return status;
}

NTSTATUS CreateCompleteRoutine(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS CloseCompleteRoutine(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS ReadCompleteRoutine(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS WriteCompleteRoutine(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS DeviceControlCompleteRoutine(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	NTSTATUS			status = STATUS_SUCCESS;
	PIO_STACK_LOCATION	pIrpsp = IoGetCurrentIrpStackLocation(pIrp);
	ULONG				uLength = 0;

	PVOID pBuffer = pIrp->AssociatedIrp.SystemBuffer;
	ULONG ulInputlength = pIrpsp->Parameters.DeviceIoControl.InputBufferLength;
	ULONG ulOutputlength = pIrpsp->Parameters.DeviceIoControl.OutputBufferLength;

	do
	{
		switch (pIrpsp->Parameters.DeviceIoControl.IoControlCode)
		{
		case CWK_DVC_SEND_STR:			// ���յ�������������
			{
				ASSERT(pBuffer != NULL);
				ASSERT(ulInputlength > 0);
				ASSERT(ulOutputlength == 0);
			}
			break;
		case CWK_DVC_RECV_STR:			// ���յ���ȡ��������
			{
				ASSERT(ulInputlength == 0);

				// ����һ��ѭ�������ϴ����������Ƿ��нڵ�
				while (TRUE)
				{
					PPROCESSNODE pNode = (PPROCESSNODE)ExInterlockedRemoveHeadList(&g_ListHead, &g_Lock);

					// ����õ��˽ڵ㣬�򴫸�Ӧ�ò㣬ֱ���� pBuffer ���渳ֵ��Ӧ�ò� DeviceIoControl �����յ�����
					if (NULL != pNode)
					{
						PPROCESSINFO	pOutputBuffer = (PPROCESSINFO)pBuffer;
						SIZE_T			ulNumberOfBytes = sizeof(PROCESSINFO) +							// �ṹ���С
							pNode->pProcessInfo->ulParentProcessLength +								// ������·������
							pNode->pProcessInfo->ulProcessLength +										// �ӽ���·������
							pNode->pProcessInfo->ulCommandLineLength;									// �����в�������

						KdPrint(("ulNumberOfBytes = %ld, ulParentProcessLength = %ld, ulProcessLength = %ld, ulCommandLineLength = %ld\r\n",
							ulNumberOfBytes,
							pNode->pProcessInfo->ulParentProcessLength,
							pNode->pProcessInfo->ulProcessLength,
							pNode->pProcessInfo->ulCommandLineLength));

						if (NULL != pNode->pProcessInfo)
						{
							if (ulOutputlength >= ulNumberOfBytes)
							{
								RtlCopyBytes(pOutputBuffer, pNode->pProcessInfo, ulNumberOfBytes);
								ExFreePoolWithTag(pNode->pProcessInfo, MEM_TAG);
								ExFreePoolWithTag(pNode, MEM_TAG);
							}
							else
							{
								ExInterlockedInsertHeadList(&g_ListHead, (PLIST_ENTRY)pNode, &g_Lock);
							}
						}

						uLength = (ULONG)ulNumberOfBytes;
						break;
					}
					else
					{
						KeWaitForSingleObject(&g_Event, Executive, KernelMode, 0, 0);
					}
				}
			}
			break;
		default:
			{
				status = STATUS_INVALID_PARAMETER;
			}
			break;
		}
	} while (FALSE);


	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = uLength;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}
