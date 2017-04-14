#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		switch (wParam) {
		case(WM_LBUTTONDOWN):
			printf("Left Button Down\n");
			break;
		case(WM_RBUTTONDOWN):
			printf("Right Button Down\n");
			break;
		case(WM_LBUTTONUP):
			printf("Left Button Up\n");
			break;
		case(WM_RBUTTONUP):
			printf("Right Button Up\n");
			break;
		}
	}
	
	/*
	https://msdn.microsoft.com/en-us/library/ms644974.aspx <- According to this, the first parameter to CallNextHookEx, is ignored
	*/
	return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI MouseClickThread()
{
	SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

int main() {
	//HHOOK hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);

	CreateThread(NULL, 0, MouseClickThread, NULL, 0, 0);

	Sleep(20000);
	
	return 0;
}