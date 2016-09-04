
// SystemMonitorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "RegistryMonitor.h"
#include "ProcessMonitor.h"
#include "MonitorListCtrl.h"


// CSystemMonitorDlg �Ի���
class CSystemMonitorDlg : public CDialogEx
{
// ����
public:
	CSystemMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CSystemMonitorDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMMONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CMonitorListCtrl			m_listCtrl;
	CRegistryMonitor*			m_RegistryMonitor;
	CProcessMonitor*			m_ProcessMonitor;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
