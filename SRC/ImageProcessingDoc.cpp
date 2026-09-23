
// ImageProcessingDoc.cpp : Implement a CImageProcessingDoc Class
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "DlgCompositeOption.h"
#include "Composite.h"

#include "ImageProcessingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_PROCESS_COMPOSITE, &CImageProcessingDoc::OnProcessComposite)
END_MESSAGE_MAP()


// CImageProcessingDoc Contruction/Destuction

CImageProcessingDoc::CImageProcessingDoc()
{
	m_pImage = NULL;
}

CImageProcessingDoc::~CImageProcessingDoc()
{
	if (NULL != m_pImage)
		delete m_pImage;
}

BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	m_pImage = new CxImage;
	m_pImage->Load(lpszPathName, FindType(lpszPathName));


	return TRUE;
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//// SDI documents will reuse this article

	return TRUE;
}


// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


// CImageProcessingDoc diagnosis

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc command

CString CImageProcessingDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}

CString CImageProcessingDoc::RemoveExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(0,i);
		}
	}
	return name;
}

int CImageProcessingDoc::FindType(const CString& ext)
{
	return CxImage::GetTypeIdFromName(ext);
}

void CImageProcessingDoc::OnProcessComposite()
{
	// Composite the active image with a second open image.
	// Squid Game: open all three images, then on the head image
	//   1. Composite "+" with squid_body
	//   2. Composite "-" with squid_points
	if (m_pImage == NULL)
		return;

	DlgCompositeOption dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CxImage* pSecondImage = dlg.GetSecondImage();
	if (pSecondImage == NULL || pSecondImage == m_pImage) {
		AfxMessageBox(_T("Please select a different image as the second image."));
		return;
	}

	switch (dlg.GetCompositeOperatorID()) {
	case 0:		// "+"
		CompositeAdd(m_pImage, pSecondImage);
		break;
	case 1:		// "-"
		CompositeSubtract(m_pImage, pSecondImage);
		break;
	default:	// "x" and "/" are not part of this project
		AfxMessageBox(_T("Only + and - are supported."));
		return;
	}

	UpdateAllViews(NULL);
}
