
// GLIMYSGDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIMYSG.h"
#include "GLIMYSGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGLIMYSGDlg 대화 상자



CGLIMYSGDlg::CGLIMYSGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMYSG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMYSGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EID_Center, m_Editloadcenter);
	DDX_Control(pDX, IDC_EID_STTXY, m_Editloadsttxy);

	DDX_Control(pDX, IDC_EID_Startpoint, m_startpoint);
	DDX_Control(pDX, IDC_EID_Endpoint, m_endpoint);
	DDX_Control(pDX, IDC_EID_RADIUS, m_radius);
}

BEGIN_MESSAGE_MAP(CGLIMYSGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Drawing, &CGLIMYSGDlg::OnBnClickedBtnDrawing)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGLIMYSGDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_Load, &CGLIMYSGDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGLIMYSGDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CGLIMYSGDlg 메시지 처리기

BOOL CGLIMYSGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMYSGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGLIMYSGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}

	else
	{
		CDialogEx::OnPaint();
		//화면 업로드
		ImageLaod();
	}
}


HCURSOR CGLIMYSGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGLIMYSGDlg::ImageLaod()
{
	int nWidth = 800;
	int nHeight = 500;
	int nBpp = 8;
	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_Image.SetColorTable(0, 256, rgb);
		}
	}
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);
	UpdateDisplay();
}

void CGLIMYSGDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

void CGLIMYSGDlg::OnBnClickedBtnDrawing()
{
	m_Image.Destroy();
	ImageLaod();
	CString strBtnname = _T("Drawing");
	TexttoInt(strBtnname);
}

void CGLIMYSGDlg::drawImage(int nSttx, int nStty, int nEndx, int nEndy, int nRadius)
{
	int nGray = 80;
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	int nCenterX = nSttx + nRadius;
	int nCenterY = nStty + nRadius;
	int nEndCenterX = nEndx + nRadius;
	int nEndCenterY = nEndy + nRadius;
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);
	if (nCenterX + nRadius > nWidth || nCenterY + nRadius > nHeight || nEndCenterX + nRadius > nWidth || nEndCenterY + nRadius > nHeight) {
		MessageBox(_T("영역을 벗어났습니다.."), _T("에러!!"), MB_OK | MB_ICONERROR);
		return;
	}
	for (int j = nStty; j <= nStty + nRadius * 2 && j < m_Image.GetHeight(); j++) 
	{
		for (int i = nSttx; i <= nSttx + nRadius * 2 && i < m_Image.GetWidth(); i++) 
		{
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
			{
				fm[j * nPitch + i] = nGray;
			}	
			
		}
	}
	UpdateDisplay();
}

bool CGLIMYSGDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;
	if (dDist <= nRadius * nRadius) 
	{
		bRet = true;
	}
	return bRet;
}

void CGLIMYSGDlg::OnBnClickedBtnAction()
{
	CString strBtnname = _T("Action");
	TexttoInt(strBtnname);
}

void CGLIMYSGDlg::TexttoInt(CString strBtnname)
{
	CString strStratXY;
	CString strEndXY;
	CString strStratX;
	CString strStratY;
	CString strEndX;
	CString strEndY;
	GetDlgItemText(IDC_EID_Startpoint, strStratXY);
	GetDlgItemText(IDC_EID_Endpoint, strEndXY);
	AfxExtractSubString(strStratX, strStratXY, 0, ',');
	AfxExtractSubString(strStratY, strStratXY, 1, ',');
	AfxExtractSubString(strEndX, strEndXY, 0, ',');
	AfxExtractSubString(strEndY, strEndXY, 1, ',');
	int nRadius = GetDlgItemInt(IDC_EID_RADIUS);
	if (nRadius == 0)
	{
		nRadius = 50;
	}
	int nSttx = _ttoi(strStratX);
	int nStty = _ttoi(strStratY);
	int nEndx = _ttoi(strEndX);
	int nEndy = _ttoi(strEndY);
	if (strBtnname == "Action")
	{
		moveImage(nSttx, nStty, nEndx, nEndy, nRadius);
	}
	else if (strBtnname == "Drawing") 
	{
		drawImage(nSttx, nStty, nEndx, nEndy, nRadius);
	}
}

void CGLIMYSGDlg::moveImage(int nSttx, int nStty, int nEndx, int nEndy, int nRadius)
{	
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nSttCenterX = nSttx + nRadius;
	int nSttCenterY = nStty + nRadius;
	int nEndCenterX = nEndx + nRadius;
	int nEndCenterY = nEndy + nRadius;
	int nSavePoint=0;

	while (true)
	{
		memset(fm, 0xff, nWidth* nHeight);
	
		if (moveCircle(nStty, nSttx, nSttCenterY, nSttCenterX, nRadius,fm))
		{

			if (nSttCenterY == nEndCenterY && nSttCenterX == nEndCenterX)
			{
				break;
			}

			if (nSttCenterX < nEndCenterX )
			{
				nSttCenterX += 10;
				if (nSttCenterX > nEndCenterX )
				{
					nSttCenterX = nEndCenterX;
				}
			}

			else if (nSttCenterX > nEndCenterX)
			{
				nSttCenterX -= 10;
				nSttx -= 10;
				if (nSttCenterX < nEndCenterX)
				{
					nSttCenterX = nEndCenterX;
					nStty = nEndCenterX - nRadius;
				}
			}

			if (nSttCenterY < nEndCenterY)
			{
				nSttCenterY += 10;
				if (nSttCenterY > nEndCenterY )
				{
					nSttCenterY = nEndCenterY;
				}
			}

			else if (nSttCenterY > nEndCenterY)
			{
				nSttCenterY -= 10;
				nStty -= 10;
				if (nSttCenterY < nEndCenterY)
				{
					nSttCenterY = nEndCenterY;
					nStty = nEndCenterY - nRadius;
				}
			}
		}

		else
		{
			break;
		}
		Sleep(100);
		UpdateDisplay();
		nSavePoint = saveImage(nSavePoint);
	}	
}

bool CGLIMYSGDlg::moveCircle(int nStty, int nSttx, int nCenterY, int nCenterX, int nRadius, unsigned char* fm)
{
	int nGray = 80;
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	
	if (nCenterX + nRadius > nWidth || nCenterY + nRadius > nHeight) {
		MessageBox(_T("영역을 벗어났습니다.."), _T("에러!!"), MB_OK | MB_ICONERROR);
		return false;
	}
	for (int j = nStty; j <= nCenterY + nRadius && j  < m_Image.GetHeight(); j++) 
	{
		for (int i = nSttx; i <= nCenterX + nRadius && i< m_Image.GetWidth(); i++) 
		{
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius)) 
			{
				fm[j * nPitch + i] = nGray;
			}
		}
	}

	UpdateDisplay();
	return true;
}

int CGLIMYSGDlg::saveImage(int savePoint)
{
	CString strFilename;
	strFilename.Format(_T(".\\image\\ImageSave%d.bmp"), savePoint);
	m_Image.Save(strFilename);
	return savePoint += 1;
}

void CGLIMYSGDlg::OnBnClickedBtnLoad()
{
	CString strCurrentDir;
	CString strImagefile = _T("\\image");
	DWORD dwResult = GetCurrentDirectory(MAX_PATH, strCurrentDir.GetBuffer(MAX_PATH));
	strCurrentDir.ReleaseBuffer();
	strCurrentDir += strImagefile;
	m_startpoint.SetWindowText(NULL);
	m_endpoint.SetWindowText(NULL);
	m_radius.SetWindowText(NULL);
	
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap Files (*.bmp)|*.bmp||"), this);
	dlg.m_ofn.lpstrInitialDir = strCurrentDir; 

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		m_Image.Destroy();
		m_Image.Load(strPathName);
		selectCircle();
		UpdateDisplay();
	}
}


void CGLIMYSGDlg::selectCircle()
{
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	int nGray = 80;
	int nMinsttx = nWidth;
	int nMinstty = nHeight;
	int nMaxsttx= 0;
	int nMaxstty = 0;

	CString strRadius;
	CString strCenter;
	CString strSttxy;
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			if (fm[j * nPitch + i] == nGray)
			{
				if (i < nMinsttx)
				{
					nMinsttx = i;
					
				}
				if (i >nMaxsttx)
				{
					nMaxsttx = i;
				
				}
				if (j < nMinstty)
				{
					 nMinstty = j;
				}
				if (j > nMaxstty)
				{
					 nMaxstty = j;
				}
			}
		}
	}
	int nRadius = (nMaxsttx - nMinsttx) / 2 ;
	int nCenterX = nMinsttx + nRadius;
	int nCenterY = nMinstty + nRadius;
	strCenter.Format(_T("%d,%d"), nCenterX, nCenterY);
	strSttxy.Format(_T("%d,%d"), nMinsttx, nMinstty);
	m_Editloadcenter.SetWindowText(strCenter);
	m_Editloadsttxy.SetWindowText(strSttxy);
	CenterMarking(nRadius, nCenterX, nCenterY, nWidth, nHeight, nPitch);
	std::cout << "좌표X:" << nCenterX << std::endl;
	std::cout << "좌표Y:" << nCenterY << std::endl;
	std::cout << "반지름:" << nRadius << std::endl;
	std::cout << std::endl;
}

void CGLIMYSGDlg::CenterMarking(int nRadius, int nCenterX, int nCenterY, int nWidth, int nHeight, int nPitch)
{
	int nWhite = 255;
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nSize = nRadius / 5;
	int nSttx = nCenterX - nSize;
	int nEndx = nCenterX + nSize;
	
	for (int y = nCenterY - nSize; y <= nCenterY + nSize; ++y) 
	{
		for (int x = nCenterX - nSize; x <= nCenterX + nSize; ++x) 
		{
			if (x == nSttx || x == nEndx)
			{
				fm[y * nPitch + x -1] = nWhite;
				fm[y * nPitch + x] = nWhite;
				fm[y * nPitch + x +1] = nWhite;
			}
		}
		if (y < nCenterY)
		{
			nSttx++;
			nEndx--;
		}
		else
		{
			nSttx--;
			nEndx++;
		}
		
	}
}
void CGLIMYSGDlg::OnBnClickedBtnReset()
{
	m_Image.Destroy();
	ImageLaod();
}
