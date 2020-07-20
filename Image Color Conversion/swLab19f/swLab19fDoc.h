﻿
// swLab19fDoc.h: CswLab19fDoc 클래스의 인터페이스
//


#pragma once


class CswLab19fDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CswLab19fDoc() noexcept;
	DECLARE_DYNCREATE(CswLab19fDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CswLab19fDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void On_FOpen01();
	afx_msg void On_FOpen02();
	afx_msg void OnPopUpIM01();
	afx_msg void OnPopUpIM02();
	afx_msg void OnPopUpIMR();
	afx_msg void OnSaveImage();
};
