
// ColorConversionToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>
#include <vector>
#include <sstream>
#include <regex>

#define MAJOR_VERSION	1
#define MINOR_VERSION	0
#define REVERSION		0

#define APP_NAME		_T("RGB��ɫֵ��ʮ��������ɫ��ת������")
#define COPYRIGHT		_T("Copyright (C) 2019 by Shaoguang.")
#define TIPS_00			_T("Tips : RGB��ɫֵ������ \",\" ��������: 255, 255, 255��")

//#define SET_PLACE_HOLDER_TEXT

// CColorConversionToolDlg �Ի���
class CColorConversionToolDlg : public CDialogEx
{
// ����
public:
	CColorConversionToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COLORCONVERSIONTOOL_DIALOG };

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
	CStatic m_stcColorRgb;
	CStatic m_stcColorHex;
	CEdit m_edtOrgRgb;
	CEdit m_edtOrgHex;
	CEdit m_edtTransHex;
	CEdit m_edtTransRgb;
private:
	CStatusBar m_startusBar;
	COLORREF   m_colorRGB;
	COLORREF   m_colorHEX;

	void setPlaceHolderText();
	void setWindowTitle();
	void initStatusBar();
	// pszRGB : 255, 255, 255 �� 255,255,255
	// return : #FFFFFF
	std::string color_rgb2hex(char* pszRGB, COLORREF &color);
	// pszHEX : #FFFFFF �� FFFFFF
	// return : 255, 255, 255
	std::string color_hex2rgb(char* pszHEX, COLORREF &color);

public:
	// RGBתʮ������
	afx_msg void OnBnClickedBtn2Hex();
	// ʮ������תRGB
	afx_msg void OnBnClickedBtn2Rgb();
	// ����16������ɫֵ
	afx_msg void OnBnClickedBtnCpHex();
	// ����RGB��ɫֵ
	afx_msg void OnBnClickedBtnCpRgb();
	//
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CEdit m_edtColorRgb;
public:
	CEdit m_edtColorHex;
};
