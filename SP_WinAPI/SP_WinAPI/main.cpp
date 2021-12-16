#include <Windows.h>
#include <string>
#include"resource.h"

CONST CHAR G_SZ_CLASS_NAME[] = "MyWindowClass"; //Имя класса окна

ATOM RegisterWindowClass(WNDPROC WndProc, HINSTANCE hInstance);

HWND CreateWnd(HINSTANCE hInstance);

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
	if (!RegisterWindowClass(WndProc,hInstance))
	{
		DWORD dwMessageID = GetLastError();  //  Получаем код ошибки
		LPSTR lpBuffer = NULL;	//  Создаём буфер, в который сохраним сообщение об ошибке.

		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM
			| FORMAT_MESSAGE_ALLOCATE_BUFFER  //Выделяет память под буфер, в котором будет храниться сообщение об ошибке.
			| FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwMessageID,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&lpBuffer,
			1024,
			NULL
		);
		MessageBox(NULL,lpBuffer, "Error after RegisterWindowClassFunction", MB_OK | MB_ICONERROR);
		LocalFree(lpBuffer);

		//MessageBox(NULL, "Class registration faild", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//  2) Создание окна
	HWND hwnd = CreateWnd(hInstance);
	if (hwnd == NULL)
	{
		DWORD dwMessageID = GetLastError();  //  Получаем код ошибки
		LPSTR lpBuffer = NULL;	//  Создаём буфер, в который сохраним сообщение об ошибке.

		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM
			| FORMAT_MESSAGE_ALLOCATE_BUFFER  //Выделяет память под буфер, в котором будет храниться сообщение об ошибке.
			| FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwMessageID,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&lpBuffer,
			1024,
			NULL
		);
		MessageBox(NULL, lpBuffer, "Error - WindowCreationFaild", MB_OK | MB_ICONERROR);
		LocalFree(lpBuffer);

		//MessageBox(NULL, "Window creation faild", "Error", MB_OK | MB_ICONERROR);
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

ATOM RegisterWindowClass(WNDPROC WndProc, HINSTANCE hInstance)
{
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

	//wc.hCursor = LoadCursor(hInstance, IDC_ARROW);		//  вид курсора 
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(105));		//  вид курсора 
	wc.hCursor = LoadCursorFromFile("Mega Man Working.ani");		//  вид курсора 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//  цвет окна
	wc.lpszClassName = G_SZ_CLASS_NAME;					//  имя класса окна
	wc.lpszMenuName = NULL;								//  имя меню

	ATOM atom = RegisterClassEx(&wc);

	/*if (!atom)
	{
		MessageBox(NULL, "Class registration faild", "Error", MB_OK | MB_ICONERROR);
	}*/
		return atom;

}

HWND CreateWnd(HINSTANCE hInstance)
{
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

	return hwnd;
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
	case WM_MOVE:
	case WM_SIZE:
	{	
		const int SIZE = 256;
		char title[SIZE] = {};
		strcpy(title, G_SZ_CLASS_NAME);

		RECT rect;
		GetWindowRect(hwnd, &rect);
		int h_size = rect.right - rect.left;
		int v_size = rect.bottom - rect.top;

		//Преобразуем размеры в строки
		char sz_h_size[10] = {};
		char sz_v_size[10] = {};
		_itoa(h_size, sz_h_size, 10);
		_itoa(v_size, sz_v_size, 10);

		//Добавляем в строку с заголовком окна:
		strcat(title, " Size: ");
		strcat(title, sz_h_size);
		strcat(title, "x");
		strcat(title, sz_v_size);

		//Добавляем координаты окна
		char sz_x_pos[10] = {};
		char sz_y_pos[10] = {};

		_itoa(rect.left, sz_x_pos,10);
		_itoa(rect.top, sz_y_pos,10);

		strcat(title, " Position: ");
		strcat(title, sz_x_pos);
		strcat(title, " x ");
		strcat(title, sz_y_pos);




		SetWindowText(hwnd, title);
	}
		break;
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