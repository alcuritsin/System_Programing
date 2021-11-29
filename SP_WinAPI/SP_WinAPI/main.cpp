#include <Windows.h>
#include"resource.h"

CONST CHAR G_SZ_CLASS_NAME[] = "MyWindowClass"; //Имя класса окна

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	/*
	---
	hInstance	- *.exe-модуль или *.dll-модуль программы
	hPrevInst	- используется, когда приложение запущено несколько раз
	lpCmdLine	- параметры командной строки, с которыми запущено приложение.
				здесь могут быть открываемые файлы, ключи запуска и т.д.
	nCmdShow	- состояние окна при запуске (свернуто на панель задач, развернуто на весь экран и т.д.)
	---
	*/

	//  1) Регистрация класса окна:
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);						//  cb - count bytes - Размер окна
	wc.style = 0;										//  Стиль окна (0-игнориуется)
	wc.lpfnWndProc = WndProc;							//  LongPointer to Function (Указатель на функцию)
	wc.cbClsExtra = 0;									//  Дополнительная память для класса и для окна
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;							//  Какому exe-модулю будет принадлежать окно.

	wc.hIcon = (HICON)LoadImage(NULL, "Palm-tree.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);			//  иконка окна в баре
	wc.hIconSm = (HICON)LoadImage(NULL, "Ico-zilla.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);		//  иконка окна на окне
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE( IDI_ICON1));		//  иконка окна
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE( IDI_ICON2));	//  иконка окна
	//wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);					//  иконка окна
	//wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);				//  иконка окна

	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);		//  вид курсора 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//  цвет окна
	wc.lpszClassName = G_SZ_CLASS_NAME;					//  имя класса окна
	wc.lpszMenuName = NULL;								//  имя меню

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration faild", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//  2) Создание окна
	int screen_width = GetSystemMetrics(SM_CXSCREEN);		//  Получаем разрешение экрана по ширене
	int screen_heigth = GetSystemMetrics(SM_CYSCREEN);		//  Получаем разрешения экрана по высоте 
	int window_width = screen_width - screen_width / 4;
	int window_hwigth = screen_heigth - screen_heigth / 4;

	HWND hwnd = CreateWindowEx
		//  Возвращает HWND созданного окна
		//  если окно не создалось, функция возвращает NULL
		(
			WS_EX_CLIENTEDGE,
			G_SZ_CLASS_NAME,		//  Имя класса окна
			G_SZ_CLASS_NAME,		//  Заголовок окна
			WS_OVERLAPPEDWINDOW,	//  Стиль окна WS_OVERLAPPEDWINDOW - это главное окно приложения
			screen_width / 8, screen_heigth / 8,	//  Начальная позиция
			window_width, window_hwigth,			//  Размер окна в пикселях
			//0, 0,					//  Начальная позиция
			//800, 600,				//  Размер окна в пикселях
			NULL,					//  Родительское окно
			NULL,					//  Меню окна
			hInstance,
			NULL					//  lParam
		);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation faild", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//  3) The message loop
	MSG msg;	//сообщение
	while (GetMessageW(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		//Создаёт и инициализирует элементы окна
		break;
	case WM_CLOSE:
		//Закрывает окно
	{
		int answer = MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_ICONWARNING | MB_YESNO);
		if (answer == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	}
	case WM_DESTROY:
		//Деактивирует окно и убирает фокус с указанного окна
		//Фокус часть окна, которая принимает команды с клавиатуры
		MessageBox(hwnd, "Ну, и ладно...", "Info", MB_OK);
		PostQuitMessage(0); //Сигнализирует системе, что поток (процесс) завершается
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}