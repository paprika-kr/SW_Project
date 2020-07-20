#include "stdafx.h"
#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MainFrm.h"
#include "s151523L01_Mfc.h"
#include "s151523L01_ext.h" 
#include "CDIB.H"

void SWL01::DarkenGrayscaleImage(void) {
	string st = type2str((m_MatR).type());
	string st3 = type2str((m_Mat1).type());
	if (st3.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;
	unsigned char *pDibData = (m_dibFile1).m_lpImage;
		*pMatData = *pDibData / 2;
		*pMatData++;
		*pDibData++;
	}
	string st = type2str((m_MatR).type());
	string st3 = type2str((m_Mat1).type());
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;

	unsigned char *pDibData = (m_dibFile1).m_lpImage;
		tmp = *pDibData * 2;

		if (tmp > 255)
			*pMatData = (uchar)max;
		else
			*pMatData = (uchar)tmp;
		
		*pMatData++;
		*pDibData++;
	}
	string s3 = "8UC3";
	string st = type2str((m_MatR).type());
	string st3 = type2str((m_Mat1).type());
	if (st3.compare(s3) != 0) {
		AfxMessageBox(L"Only 24bit can be shown!", MB_OK, 0);
		return;

	if (st.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;
	unsigned char *pDibData = (m_dibFile1).m_lpImage;
		(*pMatData) = (*pDibData)*0.299 + (*pDibData+1)*0.587 + (*pDibData+2)*0.114;
		*pMatData++;
		*pDibData++;
		*pDibData++;
		*pDibData++;
	}
	string s2 = "16UC1";
	string st = type2str((m_MatR).type());
	string st2 = type2str((m_Mat1).type());
	if (st2.compare(s2) != 0) {
		AfxMessageBox(L"Only 16bit can be shown!", MB_OK, 0);
		return;

	if (st.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;
	unsigned short *pDibData = (ushort*)(m_dibFile1).m_lpImage;

		tmp = (((*pDibData) & 31744) >> 10) *0.299;
		tmp = tmp + (((*pDibData) & 992) >> 5) *0.587;
		tmp = tmp + ((*pDibData) & 31) *0.114;
		(*pMatData) = (uchar)tmp*255/31;
		*pMatData++;
		*pDibData++;

	}