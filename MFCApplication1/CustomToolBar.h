#pragma once
#include <afxext.h>

class IToolbarListener;

class CustomToolBar :
    public CToolBar
{
public:
    CustomToolBar();

    void InitElements();
    void SetToolBarListener(IToolbarListener* toolbarListener);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);

private:
    bool m_bActive;
    IToolbarListener* m_toolbarListener;
};

