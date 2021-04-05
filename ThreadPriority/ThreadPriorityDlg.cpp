
// ThreadPriorityDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "ThreadPriority.h"
#include "ThreadPriorityDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CThreadPriorityDlg



CThreadPriorityDlg::CThreadPriorityDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadPriorityDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadPriorityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, CheckBox1);
	DDX_Control(pDX, IDC_CHECK2, CheckBox2);
	DDX_Control(pDX, IDC_SLIDER_TH_1, SliderControl1);
	DDX_Control(pDX, IDC_SLIDER_TH_2, SliderControl2);
	DDX_Control(pDX, IDC_BUTTON_START, btnControl);
	DDX_Control(pDX, IDC_PROGRESS_TH_1, ProgressControl1);
	DDX_Control(pDX, IDC_PROGRESS_TH_2, ProgressControl2);
}

BEGIN_MESSAGE_MAP(CThreadPriorityDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CThreadPriorityDlg::OnBnClickedButtonExit)
	ON_WM_TIMER(ID_TIMER_0, &CThreadPriorityDlg::OnTimer)
	ON_BN_CLICKED(IDC_BUTTON_START, &CThreadPriorityDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_CHECK1, &CThreadPriorityDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CThreadPriorityDlg::OnBnClickedCheck2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// обработчики сообщений CThreadPriorityDlg

BOOL CThreadPriorityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	SetProcessAffinityMask(GetCurrentProcess(), 1);						// Маска ядра
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);		// Установка максимального приоритета потока окна

	SliderControl1.SetRange(THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_HIGHEST);			// установка диапазона значений от THREAD_PRIORITY_LOWEST (самый низкий приоритет) до THREAD_PRIORITY_HIGHEST (самый высокий приоритет)
	SliderControl1.SetPos(THREAD_PRIORITY_NORMAL);										// установка позиции ползунка на значении THREAD_PRIORITY_NORMAL (нормальный приоритет)
	SliderControl1.SetTicFreq(1);														// установка шага SliderControl
	SliderControl2.SetRange(THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_HIGHEST);
	SliderControl2.SetPos(THREAD_PRIORITY_NORMAL);
	SliderControl2.SetTicFreq(1);

	SetTimer(ID_TIMER_0, 500, NULL);													// настройка таймера (срабатывание каждые 500 мс)

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CThreadPriorityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CThreadPriorityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Функция, выполняющая какую-либо работу. В ней можно написать что угодно.
int Work()
{
	double A, B, C;

	A = rand();
	B = rand();
	C = A / B;

	return 0;
}

// WINAPI функция, которую будут вызывать потоки
DWORD WINAPI Task(CONST LPVOID lpParam)
{
	CThreadPriorityDlg::THControl* data = (CThreadPriorityDlg::THControl*)lpParam;	// указатель на параметр

	while (true)
	{
		Work();						// выполняется что-либо

		data->counter++;			// чтобы считать, чколько раз выполнилась Work()

		if (data->isSleep)			// если нужно вызвать Sleep(0)
		{
			Sleep(0);				// 0 - значит оставшееся у потока его процессорное время перейдёт другому потоку (после Windows XP)
		}
	}
}


// Кнопка Выход
void CThreadPriorityDlg::OnBnClickedButtonExit()
{
	exit(0);
}


// Событие "тика" таймера
void CThreadPriorityDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!threadsStarted) return;					// если потоки не запущены - выйти

	double workloadPercent1 = (double)thC1.counter / (double)(1 + thC1.counter + thC2.counter) * 100;	// рассчёт количества работы, выполненной потоками
	double workloadPercent2 = (double)thC2.counter / (double)(1 + thC1.counter + thC2.counter) * 100;

	ProgressControl1.SetPos(workloadPercent1);		// обновление информации на ProgressControl
	ProgressControl2.SetPos(workloadPercent2);

	CString label1, label2;
	label1.Format(L"%.2lf", workloadPercent1);		// подготовка информации для label
	label2.Format(L"%.2lf", workloadPercent2);
	label1 += "%";
	label2 += "%";

	SetDlgItemText(IDC_STATIC1, label1);			// вывод информации в label
	SetDlgItemText(IDC_STATIC2, label2);

	thC1.counter = 0;								// обнуление счётчиков
	thC2.counter = 0;

	CDialogEx::OnTimer(nIDEvent);					// передача управления родительскому классу
}


// Кнопка запуска/остановки потоков
void CThreadPriorityDlg::OnBnClickedButtonStart()
{
	if (!threadsStarted)
	{
		hThread1 = CreateThread(NULL, 0, &Task, (void*)&thC1, 0, NULL);		// создание потоков
		hThread2 = CreateThread(NULL, 0, &Task, (void*)&thC2, 0, NULL);
		
		threadsStarted = true;
		btnControl.SetWindowTextW(L"Остановка");
	}
	else
	{
		TerminateThread(hThread1, 0);										// завершение потоков
		TerminateThread(hThread2, 0);

		threadsStarted = false;
		btnControl.SetWindowTextW(L"Запуск");
		ProgressControl1.SetPos(0);
		ProgressControl2.SetPos(0);
		SetDlgItemText(IDC_STATIC1, L"0.00%");
		SetDlgItemText(IDC_STATIC2, L"0.00%");
	}
}


// Если пользователь кликнул по CheckBox1
void CThreadPriorityDlg::OnBnClickedCheck1()
{
	if (CheckBox1.GetCheck()) thC1.isSleep = true;
	else thC1.isSleep = false;
}


// Если пользователь кликнул по CheckBox2
void CThreadPriorityDlg::OnBnClickedCheck2()
{
	if (CheckBox2.GetCheck()) thC2.isSleep = true;
	else thC2.isSleep = false;
}


// При изменении положения "ползунка"
void CThreadPriorityDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (*pScrollBar == SliderControl1 && threadsStarted)		// если событие произошло для нужного SliderControl и потоки запущены
	{
		SetThreadPriority(hThread1, SliderControl1.GetPos());
	}
	if (*pScrollBar == SliderControl2 && threadsStarted)
	{
		SetThreadPriority(hThread2, SliderControl2.GetPos());
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);			// передача управления родительскому классу
}