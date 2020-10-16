#include "pch.h"
#include "CustomToolBar.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CustomToolBar, CToolBar)
	ON_NOTIFY_REFLECT(NM_CLICK, &CustomToolBar::OnNMClick)
END_MESSAGE_MAP()


namespace
{
	const int kToolbarButton = 0;
}


CustomToolBar::CustomToolBar()
	: bActive(false)
{}

void CustomToolBar::InitElements()
{
	ModifyStyle(NULL, TBSTYLE_LIST | TBBS_AUTOSIZE);
	bool result = LoadBitmapW(MAKEINTRESOURCE(IDB_UNCHECKED));
	if (!result)
	{
		TRACE0("Failed to load the bitmap.\n");
	}

	UINT nButtonID;
	UINT nButtonStyle;
	int iButtonImage;

	GetButtonInfo(kToolbarButton, nButtonID, nButtonStyle, iButtonImage);
	SetButtonInfo(kToolbarButton, nButtonID, TBBS_CHECKBOX | TBBS_AUTOSIZE | BTNS_SHOWTEXT, iButtonImage);

	SetButtonText(kToolbarButton, TEXT("Mark Takeoff Complete"));
}

void CustomToolBar::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCLICK pNMClick = reinterpret_cast<LPNMCLICK>(pNMHDR);

	UINT nButtonID;
	UINT nButtonStyle;
	int iButtonImage;

	GetButtonInfo(0, nButtonID, nButtonStyle, iButtonImage);

	if (nButtonID != pNMClick->dwItemSpec)
	{
		*pResult = 0;
		return;
	}

	if (bActive)
	{
		LoadBitmapW(MAKEINTRESOURCE(IDB_UNCHECKED));
		bActive = false;

		*pResult = 0;
		return;
	}

	LoadBitmapW(MAKEINTRESOURCE(IDB_CHECKED));
	bActive = true;

	IFileDialog* pfd;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

	DWORD dwOptions = 0;
	if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
	{
		pfd->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
	}

	pfd->Show(NULL);
	if (SUCCEEDED(hr))
	{
		// Delete window size, MRU and other saved data for testing initial case
		pfd->ClearClientData();
		pfd->Release();
	}

	*pResult = 0;
}
