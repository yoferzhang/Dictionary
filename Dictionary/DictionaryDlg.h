
// DictionaryDlg.h : 头文件
//

#pragma once


// CDictionaryDlg 对话框
class CDictionaryDlg : public CDialogEx
{
// 构造
public:
	CDictionaryDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DICTIONARY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString text1;
	CString label1;
	afx_msg void OnBnClickedCancel();
};
