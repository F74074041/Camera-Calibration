
// HW2_2Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "HW2_2.h"
#include "HW2_2Dlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\opencv.hpp"
#include "iostream"
#include "sstream"
#include "Tchar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace cv;

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CHW2_2Dlg 對話方塊



CHW2_2Dlg::CHW2_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HW2_2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHW2_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHW2_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CHW2_2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CHW2_2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHW2_2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CHW2_2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHW2_2Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CHW2_2Dlg 訊息處理常式

BOOL CHW2_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CHW2_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CHW2_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CHW2_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


Mat img[15], in, out,cameramatrix, distcoeffs;
Size image_size;
vector<Point2f> corners;
vector<Point3f> dstcorners;
vector<vector<Point2f>> srcpoint;
vector<vector<Point3f>> dstpoint;
vector<Mat> rvecs, tvecs;
Mat rotation;
Mat translation;
Mat extrinsicMat;
void CHW2_2Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString s;
	int i = 0, j = 0;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(s);
	int y = _wtoi(s);
	y -= 1;
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	//cout << y << endl;
	Rodrigues(rvecs[y], rotation);
	extrinsicMat = Mat(3, 4, CV_64F);
	translation = Mat(3, 1, CV_64F);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < extrinsicMat.channels() * rotation.cols; j++) {
			extrinsicMat.at<double>(i, j) = rotation.at<double>(i, j);
		}
	}
	for (i = 0; i < 3; i++)
		translation.at<double>(i) = tvecs[y].at<double>(i,0);
	for (i = 0; i < 3; i++)
		extrinsicMat.at<double>(i, 3) = translation.at<double>(i);
	cout << Mat(extrinsicMat) << endl;
	//cout << tvecs[y].at<double>(2, 0) << endl;
	FreeConsole();

}



stringstream ss;
void CHW2_2Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	
	
	int i = 0, j = 0,k=0;
	float max = 0.0f;
	bool ret;
	srcpoint.clear(); dstpoint.clear(); corners.clear(); dstcorners.clear();
	for (i = 0; i < Size(8, 11).height; i++) {
		for (j = 0; j< Size(8, 11).width; j++) {
			dstcorners.push_back(Point3f(i, j, 0.0f));
		}
	}

	for (i = 0; i < 15; i++) {
		ss << i+1;
		img[i] = imread("./Q2_Image/"+ss.str()+".bmp", CV_LOAD_IMAGE_COLOR);

		ret = findChessboardCorners(img[i], Size(8, 11), corners);
		cvtColor(img[i], out, COLOR_BGR2GRAY);

		ss.str("");
		ss.clear();

		TermCriteria p(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1);
		cornerSubPix(out, corners, Size(11, 11), Size(-1, -1), p);

		dstpoint.push_back(dstcorners);
		srcpoint.push_back(corners);

		drawChessboardCorners(img[i], Size(8, 11),  corners, ret);

		namedWindow("2-1", 0); 
		imshow("2-1", img[i]);
		waitKey(500);	
		
	}
	image_size.width = img[0].cols;
	image_size.height = img[0].rows;

	
	calibrateCamera(dstpoint, srcpoint, image_size, cameramatrix, distcoeffs, rvecs, tvecs);
	
}


void CHW2_2Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	cout << Mat(cameramatrix)<<endl;
	FreeConsole();

}


void CHW2_2Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	cout << Mat(distcoeffs) << endl;
	FreeConsole();
}


void CHW2_2Dlg::OnBnClickedButton5()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	
	Mat out2;
	int i = 0;
	for (i = 0; i < 15; i++) {
		ss << i+1;
		img[i] = imread("./Q2_Image/" + ss.str() + ".bmp", CV_LOAD_IMAGE_COLOR);
		undistort(img[i], out, cameramatrix, distcoeffs);
		ss.str("");
		ss.clear();
		resize(img[i], in, Size(512, 512));
		resize(out, out2, Size(512, 512));
		int width = in.cols + out2.cols;
		int height = max(in.rows, out2.rows);
		Mat two = Mat::zeros(Size(width, height), in.type());

		Rect r1(0, 0, in.cols, in.rows);
		Rect r2(0, 0, out2.cols, out2.rows);
		r2.x = in.cols;

		in.copyTo(two(r1));
		out2.copyTo(two(r2));

		imshow("two images demo", two);
		waitKey(500);
	}
	
	/*resize(img[i], in, Size(512, 512)); // Create a window for display.
	imshow("origin", in);
	resize(out, out2, Size(512, 512));
	imshow("undistort", out2);*/

}
