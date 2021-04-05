// DemoDialog.cpp : implementation file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/
// Twitter: https://twitter.com/ovidiucucu

#include "stdafx.h"
#include "Demo.h"
#include "DemoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
// Construction
public:
	CAboutDlg();

// Dialog Data
private:
	enum { IDD = IDD_ABOUTBOX };
   CBrush m_brush;

// Overrides
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
   m_brush.CreateSolidBrush(RGB(219, 220, 251));
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
   ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   GetDlgItem(IDC_EDIT_LINKS)->SetWindowText(_T("\r\n")
      _T("   Homepage: http://www.codexpert.ro/\r\n\r\n")
      _T("   Weblog: http://www.codexpert.ro/blog\r\n\r\n")
      _T("   Twitter: https://twitter.com/ovidiucucu"));

   return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   HBRUSH hBrush = NULL; 
   if(pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_LINKS)->GetSafeHwnd())
   {
      hBrush = m_brush;
      pDC->SetTextColor(RGB(0, 0, 255));
      pDC->SetBkColor(RGB(219, 220, 251));
   }
   else
   {
      hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
   }
   return hBrush;
}


// CDemoDialog dialog 


CDemoDialog::CDemoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDialog::IDD, pParent),
     m_crStaticText(RGB(0, 0, 128))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   // load the background bitmap from resource
   VERIFY(m_bmpBack.LoadBitmap(IDB_BACKGROUND));
   // create the background brush
   VERIFY(m_brushBack.CreatePatternBrush(&m_bmpBack));
   // load the image bitmap from resource
   VERIFY(m_bmpEarth.LoadBitmap(IDB_EARTH));
}

void CDemoDialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoDialog, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   //ON_WM_ERASEBKGND()
   ON_WM_CTLCOLOR()
   ON_COMMAND(ID_HELP_ABOUT, &CDemoDialog::OnHelpAbout)
END_MESSAGE_MAP()


// CDemoDialog message handlers

BOOL CDemoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CDemoDialog::OnHelpAbout()
{
   CAboutDlg dlgAbout;
   dlgAbout.DoModal();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// NOTE: Use WM_CTLCOLOR message handler instead.
//BOOL CDemoDialog::OnEraseBkgnd(CDC* pDC)
//{
//   // get clipping rectangle
//   CRect rcClip;
//   pDC->GetClipBox(rcClip);
//   // fill rectangle using a given brush
//   pDC->FillRect(rcClip, &m_brushBack);
//   return TRUE; // returns non-zero to prevent further erasing
//}

HBRUSH CDemoDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   HBRUSH hBrush = NULL;
   switch(nCtlColor)
   {
   case CTLCOLOR_DLG:
      // just return a not NULL brush handle
      hBrush = (HBRUSH)m_brushBack;
      break;
   case CTLCOLOR_STATIC:
      {
         // set text color, transparent back node then 
         pDC->SetTextColor(m_crStaticText);
         pDC->SetBkMode(TRANSPARENT);
         // return a not NULL brush handle
         hBrush = (HBRUSH)m_brushBack;
      }
      break;
   default:
      // do the default processing
      hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
      break;
   }      
   return hBrush;
}

void CDemoDialog::OnPaint()
{
   CPaintDC dc(this); // device context for painting

   CDC dcMem;
   // create memory DC
   dcMem.CreateCompatibleDC(&dc);
   // select the source bitmao into the memory DC
   CBitmap* pOldBitmap = (CBitmap*)dcMem.SelectObject(&m_bmpEarth);
   // get the bitmap data
   BITMAP bmp = {0};
   m_bmpEarth.GetBitmap(&bmp);
   // transfer the bitmap into paint DC using a transparent color  
   dc.TransparentBlt(
      10, 10, bmp.bmWidth, bmp.bmHeight, // destination coordinates and sizes
      &dcMem,                            // source DC
      0, 0, bmp.bmWidth, bmp.bmHeight,   // source coordinates and sizes
      RGB(255, 0, 0));                   // transparent color
   // restore DC / free GDI objects 
   dcMem.SelectObject(pOldBitmap);
}





