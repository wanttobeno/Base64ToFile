// Base64Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Base64UI.h"
#include "Base64UIDlg.h"
#include <string>
#include "base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBase64Dlg 对话框




CBase64UIDlg::CBase64UIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBase64UIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBase64UIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_pEdit);
	DDX_Control(pDX, IDC_STATI_TIP, m_pTip);
}

BEGIN_MESSAGE_MAP(CBase64UIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CBase64UIDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBase64Dlg 消息处理程序

BOOL CBase64UIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_EN);
	radio->SetCheck(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBase64UIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBase64UIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int SaveToFile(const std::string & strData,bool bEncode)
{
	if (strData.empty())
	{
		printf("No File OutPut! \n");
		return -1;
	}

	const wchar_t* pFileName = NULL;
	if (bEncode)
	{
		pFileName = L"Base64加密.dat";
	}
	else
	{
		pFileName = L"Base64解密.dat";
	}
	FILE* pFile = _wfopen(pFileName,L"wb");
	if (pFile)
	{
		fwrite(strData.c_str(),1,strData.length(),pFile);
		fclose(pFile);
		return 0;
	}
	return -1;
}

void CBase64UIDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);

	m_pTip.SetWindowText(L"");
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_EN);
	int m_nEncryption = radio->GetCheck();

	CString strData; 
	m_pEdit.GetWindowText(strData);
	if (strData.IsEmpty())
		return;
	DWORD nLen = m_pEdit.GetTextLength();
	int nMemSize = nLen *2 +10;
	char* pData = (char*)malloc(nMemSize);
	if (pData == NULL)
	{
		return ;
	}
	memset(pData,0,nMemSize);

	int nTextLen = GetWindowTextA(m_pEdit.m_hWnd,pData,nMemSize);
	if (m_nEncryption == 0)
	{
		std::string result = base64_decode(pData);
		if(result.empty())
		{
			AfxMessageBox(L"BASE64解密失败!");
		}
		else
		{
			SaveToFile(result,false);
			m_pTip.SetWindowText(L"解密完成！");
		}
		free(pData);
		pData = NULL;
	}
	else if (m_nEncryption == 1)
	{
		std::string result = base64_encode(pData,nTextLen);
		if(result.empty())
		{
			AfxMessageBox(L"BASE64加密失败!");
		}
		else
		{
			SaveToFile(result,true);
			m_pTip.SetWindowText(L"加密完成！");
		}
		free(pData);
		pData = NULL;
	}
	else
	{
		return ;
	}
	//OnOK();
}
