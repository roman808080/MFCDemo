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
	: m_bActive(false)
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
	// By default the result is ok.
	*pResult = 0;

	LPNMCLICK pNMClick = reinterpret_cast<LPNMCLICK>(pNMHDR);

	UINT nButtonID;
	UINT nButtonStyle;
	int iButtonImage;

	GetButtonInfo(kToolbarButton, nButtonID, nButtonStyle, iButtonImage);

	if (nButtonID != pNMClick->dwItemSpec)
	{
		return;
	}

	if (m_bActive)
	{
		LoadBitmapW(MAKEINTRESOURCE(IDB_UNCHECKED));
		m_bActive = false;
		return;
	}

	LoadBitmapW(MAKEINTRESOURCE(IDB_CHECKED));
	m_bActive = true;

	IFileDialog* pFileDirectory;

	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDirectory));
	if (!SUCCEEDED(hr))
	{
		return;
	}

	DWORD dwOptions = 0;
	if (SUCCEEDED(pFileDirectory->GetOptions(&dwOptions)))
	{
		pFileDirectory->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
	}

	pFileDirectory->Show(NULL);
	if (SUCCEEDED(hr))
	{
		// Delete window size, MRU and other saved data for testing initial case
		pFileDirectory->ClearClientData();
		pFileDirectory->Release();
	}
}
