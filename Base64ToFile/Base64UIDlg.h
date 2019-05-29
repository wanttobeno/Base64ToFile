// Base64Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBase64Dlg 对话框
class CBase64UIDlg : public CDialog
{
// 构造
public:
	CBase64UIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BASE64_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CRichEditCtrl m_pEdit;
	CStatic m_pTip;
};
