
// ImageProcessingDoc.h : CImageProcessingDoc 클래스의 인터페이스
//

#pragma once

class CImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// 특성입니다.
public:
	inline CxImage *GetImage() { return m_pImage; }

private:
	CxImage * m_pImage;

// 작업입니다.
public:
	CString FindExtension(const CString& name);
	CString RemoveExtension(const CString& name);
	int FindType(const CString& ext);

// 재정의입니다.
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현입니다.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnProcessComposite();

	DECLARE_MESSAGE_MAP()	
	
public:
};

