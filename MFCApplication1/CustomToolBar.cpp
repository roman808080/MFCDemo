#include "pch.h"
#include "CustomToolBar.h"
BEGIN_MESSAGE_MAP(CustomToolBar, CToolBar)
	ON_NOTIFY_REFLECT(NM_CLICK, &CustomToolBar::OnNMClick)
END_MESSAGE_MAP()


void CustomToolBar::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCLICK pNMClick = reinterpret_cast<LPNMCLICK>(pNMHDR);

	UINT nButtonID;
	UINT nButtonStyle;
	int iButtonImage;

	GetButtonInfo(0, nButtonID, nButtonStyle, iButtonImage);

	if (nButtonID == pNMClick->dwItemSpec)
	{
		TRACE0("We are here.\n");
	}

	// TODO: Add your control notification handler code here
	*pResult = 0;
}
