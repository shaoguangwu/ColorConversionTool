
// ColorConversionToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColorConversionTool.h"
#include "ColorConversionToolDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static UINT indicators[] = {
	IDS_STRING_STATUS,
};


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();


// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
private:
	CStatic m_stcNameAndVer;
	CStatic m_stcCopyright;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->SetWindowText(_T("����..."));

#ifdef _UNICODE
	WCHAR str[64];
#else
	CHAR str[64];
#endif
	wsprintf(str, _T("%s V%d.%d.%d"), APP_NAME, MAJOR_VERSION, MINOR_VERSION, REVERSION);
	m_stcNameAndVer.SetWindowText(str);

	wsprintf(str, COPYRIGHT);
	m_stcCopyright.SetWindowText(str);

	return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME_AND_VER, m_stcNameAndVer);
	DDX_Control(pDX, IDC_STATIC_COPYRIGHT, m_stcCopyright);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CColorConversionToolDlg �Ի���



CColorConversionToolDlg::CColorConversionToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColorConversionToolDlg::IDD, pParent),
	m_colorRGB(RGB(255, 255, 255)),
	m_colorHEX(RGB(255, 255, 255))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorConversionToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORG_RGB, m_edtOrgRgb);
	DDX_Control(pDX, IDC_EDIT_ORG_HEX, m_edtOrgHex);
	DDX_Control(pDX, IDC_EDIT_TRNS_HEX, m_edtTransHex);
	DDX_Control(pDX, IDC_EDIT_TRNS_RGB, m_edtTransRgb);
	DDX_Control(pDX, IDC_EDIT_COLOR_RGB, m_edtColorRgb);
	DDX_Control(pDX, IDC_EDIT_COLOR_HEX, m_edtColorHex);
}

BEGIN_MESSAGE_MAP(CColorConversionToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_2_HEX, &CColorConversionToolDlg::OnBnClickedBtn2Hex)
	ON_BN_CLICKED(IDC_BTN_2_RGB, &CColorConversionToolDlg::OnBnClickedBtn2Rgb)
	ON_BN_CLICKED(IDC_BTN_CP_HEX, &CColorConversionToolDlg::OnBnClickedBtnCpHex)
	ON_BN_CLICKED(IDC_BTN_CP_RGB, &CColorConversionToolDlg::OnBnClickedBtnCpRgb)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CColorConversionToolDlg ��Ϣ�������

BOOL CColorConversionToolDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);		

	setWindowTitle();
	initStatusBar();

#ifdef SET_PLACE_HOLDER_TEXT
	setPlaceHolderText();
#endif


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CColorConversionToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CColorConversionToolDlg::OnPaint()
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
HCURSOR CColorConversionToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CColorConversionToolDlg::setWindowTitle()
{
#ifdef _UNICODE
	WCHAR str[64];
#else
	CHAR str[64];
#endif
	wsprintf(str, _T("%s V%d.%d.%d"), APP_NAME, MAJOR_VERSION, MINOR_VERSION, REVERSION);

	this->SetWindowText(str);
}

void CColorConversionToolDlg::initStatusBar()
{
	CRect rect;
	GetClientRect(rect);

	m_startusBar.Create(this);
	m_startusBar.SetIndicators(indicators, 1);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_startusBar.SetPaneText(0, TIPS_00);
	m_startusBar.SetPaneInfo(0, m_startusBar.GetDlgCtrlID(), SBPS_NORMAL, rect.Width());
}

void CColorConversionToolDlg::setPlaceHolderText()
{
	m_edtOrgRgb.SetWindowText(_T("255, 255, 255"));
	m_edtTransHex.SetWindowText(_T("#FFFFFF"));
	m_edtOrgHex.SetWindowText(_T("#FFFFFF"));
	m_edtTransRgb.SetWindowText(_T("255, 255, 255"));
}

std::string CColorConversionToolDlg::color_rgb2hex(char* pszRGB, COLORREF &color)
{
	if (pszRGB == NULL)
		return  "";
	char *next_token = NULL;
	char *ptr = NULL;
	static const char seps[] = ",";
	std::vector<int> vec_rgb;

	static const std::regex reg("^[0-9] +$");
	int value = 0;

	ptr = strtok_s(pszRGB, seps, &next_token);
	if (ptr != NULL)
	{
		for (size_t i = 0; i < strlen(ptr); ++i)
		{
			if (ptr[i] != ' ' && (ptr[i] < '0' || ptr[i] > '9'))
				return "";
		}
		value = atoi(ptr);
		if (value < 0 || value > 255)
			return "";
		vec_rgb.push_back(value);
	}

	while (NULL != ptr)
	{
		ptr = strtok_s(NULL, seps, &next_token);
		if (ptr != NULL)
		{
			for (size_t i = 0; i < strlen(ptr); ++i)
			{
				if (ptr[i] != ' ' && (ptr[i] < '0' || ptr[i] > '9'))
					return "";
			}
			value = atoi(ptr);
			if (value < 0 || value > 255)
				return "";
			vec_rgb.push_back(atoi(ptr));
		}
	}

	if (vec_rgb.size() < 3)
		return "";

	int r = vec_rgb[0];
	int g = vec_rgb[1];
	int b = vec_rgb[2];
	color = RGB(r, g, b);
	char szBuff[8] = "";
	sprintf_s(szBuff, 8, "#%02x%02x%02x", r, g, b);

	return szBuff;
}

std::string CColorConversionToolDlg::color_hex2rgb(char* pszHEX, COLORREF &color)
{
	if (pszHEX == NULL)
		return "";
	char *next_token = NULL;
	char *ptr = NULL;
	static const char seps[] = "#";
	ptr = strtok_s(pszHEX, seps, &next_token);
	if (ptr == NULL)
		return "";
	if (strlen(ptr) != 6)
		return "";

	static const std::regex reg("^[0-9a-fA-F]+$");
	if (!std::regex_match(ptr, reg))
		return "";

	std::stringstream ss;
	char szBuff[2] = "";

	int r = 0;
	int g = 0;
	int b = 0;

	// ��ȡRGBֵ
	szBuff[0] = ptr[0];
	szBuff[1] = ptr[1];
	sscanf_s(szBuff, "%x", &r);
	szBuff[0] = ptr[2];
	szBuff[1] = ptr[3];
	sscanf_s(szBuff, "%x", &g);
	szBuff[0] = ptr[4];
	szBuff[1] = ptr[5];
	sscanf_s(szBuff, "%x", &b);
	ss << r << ", " << g << ", " << b;
	color = RGB(r, g, b);

	return ss.str();
}

// RGBת��Ϊ16������ɫ��
void CColorConversionToolDlg::OnBnClickedBtn2Hex()
{
	CString source;
	m_edtOrgRgb.GetWindowText(source);

	int nLength = source.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, source, nLength, NULL, 0, NULL, NULL);
	char* sourceContext = new char[nBytes + 1];
	memset(sourceContext, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, source, nLength, sourceContext, nBytes, NULL, NULL);
	sourceContext[nBytes] = '\0';

	std::string hex = color_rgb2hex(sourceContext, m_colorRGB);

	CString strHex(hex.c_str());
	strHex.MakeUpper();
	m_edtTransHex.SetWindowText(strHex);

	Invalidate();

	if (sourceContext)
	{
		delete[]sourceContext;
		sourceContext = NULL;
	}
}

// ʮ������ת��ΪRGB
void CColorConversionToolDlg::OnBnClickedBtn2Rgb()
{
	CString source;
	m_edtOrgHex.GetWindowText(source);
	source.MakeLower();

	int nLength = source.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, source, nLength, NULL, 0, NULL, NULL);
	char* sourceContext = new char[nBytes + 1];
	memset(sourceContext, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, source, nLength, sourceContext, nBytes, NULL, NULL);
	sourceContext[nBytes] = '\0';

	std::string rgb = color_hex2rgb(sourceContext, m_colorHEX);

	CString strRgb(rgb.c_str());
	m_edtTransRgb.SetWindowText(strRgb);

	Invalidate();

	if (sourceContext)
	{
		delete []sourceContext;
		sourceContext = NULL;
	}
}

// ����ʮ������ֵ
void CColorConversionToolDlg::OnBnClickedBtnCpHex()
{
	CString source;
	m_edtTransHex.GetWindowText(source);

	int nLength = source.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, source, nLength, NULL, 0, NULL, NULL);
	char* sourceContext = new char[nBytes + 1]; 
	memset(sourceContext, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, source, nLength, sourceContext, nBytes, NULL, NULL);
	sourceContext[nBytes] = '\0';

	if (OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char* buffer = NULL;
		::EmptyClipboard();
		clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nLength + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy_s(buffer, nLength + 1, sourceContext);
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_TEXT, clipbuffer);
		::CloseClipboard();
	}

	delete []sourceContext;
	sourceContext = NULL;
}

// ����RGBֵ
void CColorConversionToolDlg::OnBnClickedBtnCpRgb()
{
	CString source;
	m_edtTransRgb.GetWindowText(source);

	int nLength = source.GetLength();

	int nBytes = WideCharToMultiByte(CP_ACP, 0, source, nLength, NULL, 0, NULL, NULL);
	char* sourceContext = new char[nBytes + 1];
	memset(sourceContext, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, source, nLength, sourceContext, nBytes, NULL, NULL);
	sourceContext[nBytes] = '\0';

	if (OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char* buffer = NULL;
		::EmptyClipboard();
		clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nLength + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy_s(buffer, nLength + 1, sourceContext);
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_TEXT, clipbuffer);
		::CloseClipboard();
	}

	delete []sourceContext;
	sourceContext = NULL;
}


HBRUSH CColorConversionToolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_COLOR_RGB)
	{
		pDC->SetBkColor(m_colorRGB);
		HBRUSH b = CreateSolidBrush(m_colorRGB);
		return b;
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EDIT_COLOR_HEX)
	{
		pDC->SetBkColor(m_colorHEX);
		HBRUSH b = CreateSolidBrush(m_colorHEX);
		return b;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
