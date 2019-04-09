
// ColorConversionToolDlg.h : 头文件
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

#define APP_NAME		_T("RGB颜色值与十六进制颜色码转换工具")
#define COPYRIGHT		_T("Copyright (C) 2019 by Shaoguang.")
#define TIPS_00			_T("Tips : RGB颜色值输入以 \",\" 隔开！如: 255, 255, 255。")

//#define SET_PLACE_HOLDER_TEXT

// CColorConversionToolDlg 对话框
class CColorConversionToolDlg : public CDialogEx
{
// 构造
public:
	CColorConversionToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COLORCONVERSIONTOOL_DIALOG };

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
	// pszRGB : 255, 255, 255 或 255,255,255
	// return : #FFFFFF
	std::string color_rgb2hex(char* pszRGB, COLORREF &color);
	// pszHEX : #FFFFFF 或 FFFFFF
	// return : 255, 255, 255
	std::string color_hex2rgb(char* pszHEX, COLORREF &color);

public:
	// RGB转十六进制
	afx_msg void OnBnClickedBtn2Hex();
	// 十六进制转RGB
	afx_msg void OnBnClickedBtn2Rgb();
	// 复制16进制颜色值
	afx_msg void OnBnClickedBtnCpHex();
	// 复制RGB颜色值
	afx_msg void OnBnClickedBtnCpRgb();
	//
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CEdit m_edtColorRgb;
public:
	CEdit m_edtColorHex;
};
