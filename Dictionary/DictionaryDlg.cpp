
// DictionaryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dictionary.h"
#include "DictionaryDlg.h"
#include "afxdialogex.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct dict
{
	char *key;
	char *content;
};

int get_dict_size(FILE *pfile)//得到字典文件中词条总数
{
	if (pfile == NULL)
		return 0;

	int i = 0;
	char buf[2048];
	while (!feof(pfile))
	{
		fgets(buf, sizeof(buf), pfile);
		fgets(buf, sizeof(buf), pfile);
		i++;//读取两行后，计数器加1
	}
	return i;
}

//打开字典文件，并读取文件内容
int open_dict(struct dict **p, const char *dict_filename)
{
	FILE *pfile = fopen(dict_filename, "r");
	if (pfile == NULL)
		return 0;//打开文件失败，函数返回

	int size = get_dict_size(pfile);//得到字典文件中词条总数
	if (size == 0)
		return 0;

	*p = (struct dict *)malloc(sizeof(struct dict) * size);//根据字典文件词条总数分配内存
	memset(*p, 0, sizeof(struct dict) * size);//将分配内存初始化为0

	struct dict *pD = *p;//pD指向数组p的首地址

	char buf[2048] = { 0 };
	size_t len = 0;
	int i = 0;
	fseek(pfile, 0L, SEEK_SET);//设置读取位置为字典文件开始
	while (!feof(pfile))//循环读取文件，直到文件末尾
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);//读取文件一行
		len = strlen(buf);//得到读取到字符串长度
		if (len > 0)
		{
			pD[i].key = (char *)malloc(len);//根据字符串长度分配内存
			memset(pD[i].key, 0, len);
			strcpy(pD[i].key, &buf[1]);//将读取到的内容拷贝到key中
		}

		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);
		len = strlen(buf);
		if (len > 0)
		{
			pD[i].content = (char *)malloc(len);
			memset(pD[i].content, 0, len);
			strcpy(pD[i].content, &buf[6]);
		}
		i++;
	}
	fclose(pfile);//关闭字典文件

	return i;//返回读取到的字典词条数
}

//根据关键字key,在字典中查找内容
int search_dict(const struct dict *p, int size, const char *key, char *content)
{
	int i = 0;
	for (i = 0; i < size; i++)//遍历字典
	{
		if ((p[i].key == NULL) || (p[i].content == NULL))
			continue;

		if (strncmp(p[i].key, key, strlen(key)) == 0)
		{
			strcpy(content, p[i].content);
			return 1;//找到符合条件记录，返回1
		}
	}
	return 0;//没有找到符合条件记录，返回0
}

//释放内存
void free_dict(struct dict *p, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)//循环释放key与content成员内存
	{
		if (p[i].key)
			free(p[i].key);
		if (p[i].content)
			free(p[i].content);
	}
	free(p);//释放p内存
}

struct dict *p = NULL;
int dict_size = 0;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDictionaryDlg 对话框



CDictionaryDlg::CDictionaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDictionaryDlg::IDD, pParent)
	, text1(_T(""))
	, label1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDictionaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, text1);
	DDX_Text(pDX, IDC_STATIC1, label1);
}

BEGIN_MESSAGE_MAP(CDictionaryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDictionaryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDictionaryDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDictionaryDlg 消息处理程序

BOOL CDictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	dict_size = open_dict(&p, "dict.txt");//根据命令行第一个参数做为字典文件名，打开字典文件
	if (dict_size == 0)
		exit(0);//打开字典文件失败，程序退出


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDictionaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDictionaryDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDictionaryDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	char key[2048];
	char content[2048];
	memset(key, 0, sizeof(key));
	memset(content, 0, sizeof(content));

	UpdateData(TRUE); // 将用户在edit控件中输入的文字放入text1这个变量中
	CStringA key_a(text1); // 将宽码转化为GDK形式的字符串
	strcpy(key, key_a);
	if (search_dict(p, dict_size, key, content)) {
		label1 = content;
	}
	else {
		label1 = L"找不到";
	}
	UpdateData(FALSE); // 将变量label1的内容同步到控件上

}


void CDictionaryDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	free_dict(p, dict_size);//释放内存
	CDialogEx::OnCancel();
}
