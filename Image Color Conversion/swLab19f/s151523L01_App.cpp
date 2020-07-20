#include "stdafx.h"
#include "swLab19fDoc.h"
#include "swLab19fView.h"
#include "MainFrm.h"
#include "s151523L01_Mfc.h"
#include "s151523L01_ext.h" 
#include "CDIB.H"

void SWL01::DarkenGrayscaleImage(void) {	string s1 = "8UC1";
	string st = type2str((m_MatR).type());
	string st3 = type2str((m_Mat1).type());	if (SWL01_inst.readImageF1 == false) {		AfxMessageBox(L"Read image1 first!", MB_OK, 0);		return;	}	
	if (st3.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;	}	(m_MatR).release();	m_MatR = Mat(m_height1, m_width1, CV_8UC1);	unsigned char *pMatData = (m_MatR).data;
	unsigned char *pDibData = (m_dibFile1).m_lpImage;	for (int p = 0; p < m_height1 * m_width1 * (m_MatR).channels(); p++) {
		*pMatData = *pDibData / 2;
		*pMatData++;
		*pDibData++;
	}	flip((m_MatR), (m_MatR), 0);	Create_bmiInfoHeader(&m_MatR);	processedF = true;	g_pView->Invalidate();}void SWL01::BrightenGrayscaleImage(void) {	string s1 = "8UC1";
	string st = type2str((m_MatR).type());
	string st3 = type2str((m_Mat1).type());	if (SWL01_inst.readImageF1 == false) {		AfxMessageBox(L"Read image1 first!", MB_OK, 0);		return;	}	if (st3.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;	}
	(m_MatR).release();	m_MatR = Mat(m_height1, m_width1, CV_8UC1);	int max = 255;	int tmp;	unsigned char *pMatData = (m_MatR).data;
	unsigned char *pDibData = (m_dibFile1).m_lpImage;	for (int p = 0; p < m_height1 * m_width1 * (m_MatR).channels(); p++) {
		tmp = *pDibData * 2;

		if (tmp > 255)
			*pMatData = (uchar)max;
		else
			*pMatData = (uchar)tmp;
		
		*pMatData++;
		*pDibData++;
	}	flip((m_MatR), (m_MatR), 0);	Create_bmiInfoHeader(&m_MatR);	processedF = true;	g_pView->Invalidate();}void SWL01::Color24toGrayscale(void) {		string s1 = "8UC1";
	string s3 = "8UC3";
	string st = type2str((m_MatR).type());
	string st3 = type2str((m_Mat1).type());	if (SWL01_inst.readImageF1 == false) {		AfxMessageBox(L"Read image1 first!", MB_OK, 0);		return;	}	
	if (st3.compare(s3) != 0) {
		AfxMessageBox(L"Only 24bit can be shown!", MB_OK, 0);
		return;	}

	if (st.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;	}		(m_MatR).release();	m_MatR = Mat(m_height1, m_width1, CV_8UC1);	unsigned char *pMatData = (m_MatR).data;
	unsigned char *pDibData = (m_dibFile1).m_lpImage;	for (int p = 0; p < m_height1 * m_width1; p++) {
		(*pMatData) = (*pDibData)*0.299 + (*pDibData+1)*0.587 + (*pDibData+2)*0.114;
		*pMatData++;
		*pDibData++;
		*pDibData++;
		*pDibData++;
	}	flip((m_MatR), (m_MatR), 0);	Create_bmiInfoHeader(&m_MatR);	processedF = true;	g_pView->Invalidate();}void SWL01::Color16toGrayscale(void) {	string s1 = "8UC1";
	string s2 = "16UC1";
	string st = type2str((m_MatR).type());
	string st2 = type2str((m_Mat1).type());	if (SWL01_inst.readImageF1 == false) {		AfxMessageBox(L"Read image1 first!", MB_OK, 0);		return;	}
	if (st2.compare(s2) != 0) {
		AfxMessageBox(L"Only 16bit can be shown!", MB_OK, 0);
		return;	}

	if (st.compare(s1) != 0) {
		AfxMessageBox(L"Only 8bit grayscale can be shown!", MB_OK, 0);
		return;	}	(m_MatR).release();	m_MatR = Mat(m_height1, m_width1, CV_8UC1);	unsigned short tmp;	unsigned char *pMatData = (m_MatR).data;
	unsigned short *pDibData = (ushort*)(m_dibFile1).m_lpImage;	for (int p = 0; p < m_height1 * m_width1; p++) {

		tmp = (((*pDibData) & 31744) >> 10) *0.299;
		tmp = tmp + (((*pDibData) & 992) >> 5) *0.587;
		tmp = tmp + ((*pDibData) & 31) *0.114;
		(*pMatData) = (uchar)tmp*255/31;
		*pMatData++;
		*pDibData++;

	}	flip((m_MatR), (m_MatR), 0);	Create_bmiInfoHeader(&m_MatR);	processedF = true;	g_pView->Invalidate();}