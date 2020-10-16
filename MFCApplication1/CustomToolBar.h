#pragma once
#include <afxext.h>
class CustomToolBar :
    public CToolBar
{
public:
    CustomToolBar();

    void InitElements();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);

private:
    bool bActive;
};

