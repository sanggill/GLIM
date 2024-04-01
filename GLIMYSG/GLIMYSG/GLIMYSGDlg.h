
// GLIMYSGDlg.h: 헤더 파일
//

#pragma once

#include<iostream>
// CGLIMYSGDlg 대화 상자
class CGLIMYSGDlg : public CDialogEx
{
// 생성입니다.
public:
	CGLIMYSGDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMYSG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
private:
	CImage m_Image;
	CEdit m_Editloadcenter;
	CEdit m_Editloadsttxy;
	CEdit m_startpoint;
	CEdit m_endpoint;
	CEdit m_radius;
	void ImageLaod();
	void UpdateDisplay();
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void CenterMarking(int nRadius, int nCenterX, int nCenterY, int nWidth, int nHeight, int nPitch);
	void drawImage(int nSttx, int nStty, int nEndx, int nEndy, int nRadius);
	void moveImage(int nSttx, int nStty, int nEndx, int nEndy, int nRadius);
	bool moveCircle(int nStty, int nSttx, int nCenterY, int nCenterX, int nRadius, unsigned char* fm); 
	int saveImage(int savePoint);
	void selectCircle();
	void TexttoInt(CString strBtnname);
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnDrawing();
	
	
};
