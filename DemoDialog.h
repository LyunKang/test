// DemoDialog.h : header file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/
// Twitter: https://twitter.com/ovidiucucu

#pragma once

// CDemoDialog dialog
class CDemoDialog : public CDialog
{
// Construction
public:
	CDemoDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
private:
   CBitmap m_bmpBack;
   CBrush m_brushBack;
   CBitmap m_bmpEarth;
   COLORREF m_crStaticText;
   
	enum { IDD = IDD_DEMO_DIALOG };
   HICON m_hIcon;

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   virtual BOOL OnInitDialog();

// Message Handlers
protected:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnHelpAbout();
};
