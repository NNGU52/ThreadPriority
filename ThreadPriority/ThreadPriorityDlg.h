
// ThreadPriorityDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CThreadPriorityDlg
class CThreadPriorityDlg : public CDialogEx
{
// Создание
public:
	CThreadPriorityDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_THREADPRIORITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


public:
	// Структура для хранения результатов работы потока и управления им
	struct THControl {
		unsigned long long int counter = 0;
		bool isSleep = false;
	};

// Реализация
protected:
	HICON m_hIcon;

	bool threadsStarted = false;

	HANDLE hThread1;		// Указатель на первый поток
	HANDLE hThread2;		// Указатель на второй поток

	THControl thC1;			// Структура для работы с первым потоком
	THControl thC2;			// Структура для работы со вторым потоком

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CButton CheckBox1;
	CButton CheckBox2;
	// Переменная верхнего Slider
	CSliderCtrl SliderControl1;
	// Переменная нижнего Slider
	CSliderCtrl SliderControl2;
	// Переменная кнопки управления
	CButton btnControl;
	// Переменная верхнего ProgressControl
	CProgressCtrl ProgressControl1;
	// Переменная нижнего ProgressControl
	CProgressCtrl ProgressControl2;
};
