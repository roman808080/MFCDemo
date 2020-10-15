#pragma once
#include <afxext.h>
class CustomToolBar :
    public CToolBar
{
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
};

