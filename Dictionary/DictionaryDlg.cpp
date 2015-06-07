
// DictionaryDlg.cpp : ʵ���ļ�
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

int get_dict_size(FILE *pfile)//�õ��ֵ��ļ��д�������
{
	if (pfile == NULL)
		return 0;

	int i = 0;
	char buf[2048];
	while (!feof(pfile))
	{
		fgets(buf, sizeof(buf), pfile);
		fgets(buf, sizeof(buf), pfile);
		i++;//��ȡ���к󣬼�������1
	}
	return i;
}

//���ֵ��ļ�������ȡ�ļ�����
int open_dict(struct dict **p, const char *dict_filename)
{
	FILE *pfile = fopen(dict_filename, "r");
	if (pfile == NULL)
		return 0;//���ļ�ʧ�ܣ���������

	int size = get_dict_size(pfile);//�õ��ֵ��ļ��д�������
	if (size == 0)
		return 0;

	*p = (struct dict *)malloc(sizeof(struct dict) * size);//�����ֵ��ļ��������������ڴ�
	memset(*p, 0, sizeof(struct dict) * size);//�������ڴ��ʼ��Ϊ0

	struct dict *pD = *p;//pDָ������p���׵�ַ

	char buf[2048] = { 0 };
	size_t len = 0;
	int i = 0;
	fseek(pfile, 0L, SEEK_SET);//���ö�ȡλ��Ϊ�ֵ��ļ���ʼ
	while (!feof(pfile))//ѭ����ȡ�ļ���ֱ���ļ�ĩβ
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);//��ȡ�ļ�һ��
		len = strlen(buf);//�õ���ȡ���ַ�������
		if (len > 0)
		{
			pD[i].key = (char *)malloc(len);//�����ַ������ȷ����ڴ�
			memset(pD[i].key, 0, len);
			strcpy(pD[i].key, &buf[1]);//����ȡ�������ݿ�����key��
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
	fclose(pfile);//�ر��ֵ��ļ�

	return i;//���ض�ȡ�����ֵ������
}

//���ݹؼ���key,���ֵ��в�������
int search_dict(const struct dict *p, int size, const char *key, char *content)
{
	int i = 0;
	for (i = 0; i < size; i++)//�����ֵ�
	{
		if ((p[i].key == NULL) || (p[i].content == NULL))
			continue;

		if (strncmp(p[i].key, key, strlen(key)) == 0)
		{
			strcpy(content, p[i].content);
			return 1;//�ҵ�����������¼������1
		}
	}
	return 0;//û���ҵ�����������¼������0
}

//�ͷ��ڴ�
void free_dict(struct dict *p, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)//ѭ���ͷ�key��content��Ա�ڴ�
	{
		if (p[i].key)
			free(p[i].key);
		if (p[i].content)
			free(p[i].content);
	}
	free(p);//�ͷ�p�ڴ�
}

struct dict *p = NULL;
int dict_size = 0;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDictionaryDlg �Ի���



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


// CDictionaryDlg ��Ϣ�������

BOOL CDictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	dict_size = open_dict(&p, "dict.txt");//���������е�һ��������Ϊ�ֵ��ļ��������ֵ��ļ�
	if (dict_size == 0)
		exit(0);//���ֵ��ļ�ʧ�ܣ������˳�


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDictionaryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDictionaryDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	char key[2048];
	char content[2048];
	memset(key, 0, sizeof(key));
	memset(content, 0, sizeof(content));

	UpdateData(TRUE); // ���û���edit�ؼ�����������ַ���text1���������
	CStringA key_a(text1); // ������ת��ΪGDK��ʽ���ַ���
	strcpy(key, key_a);
	if (search_dict(p, dict_size, key, content)) {
		label1 = content;
	}
	else {
		label1 = L"�Ҳ���";
	}
	UpdateData(FALSE); // ������label1������ͬ�����ؼ���

}


void CDictionaryDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	free_dict(p, dict_size);//�ͷ��ڴ�
	CDialogEx::OnCancel();
}
