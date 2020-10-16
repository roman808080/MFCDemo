
// MFCApplicationDlg.h : header file
//

#pragma once
#include "CustomToolBar.h"

class IToolbarListener
{
public:
	virtual void ChosenDirectory(LPWSTR directoryPath) = 0;
	virtual void ResetDirectory() = 0;
	virtual ~IToolbarListener() {}
};

// CMFCApplicationDlg dialog
class CMFCApplicationDlg : public CDialogEx, public IToolbarListener
{
// Construction
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// standard constructor

	virtual void ChosenDirectory(LPWSTR directoryPath) override;
	virtual void ResetDirectory() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// My toolbar
	CustomToolBar m_wndToolBar;
	BOOL butD;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void InitToolbar();
	void SetFilesAmountToLabel(int filesAmount);
};
