#include <windows.h>
#include <string>
#include <vector>

// Add missing Windows API libraries
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

class Element {
public:
	std::wstring name;
	int priority;

	Element(std::wstring name, int priority) : name(name), priority(priority) {}
};

class PriorityQueue {
private:
	std::vector<Element> elements;

	int getMaxPriorityIndex() {
		int maxIndex = 0;
		for (int i = 1; i < elements.size(); i++) {
			if (elements[i].priority > elements[maxIndex].priority) {
				maxIndex = i;
			}
		}
		return maxIndex;
	}

public:
	void push(std::wstring name, int priority) {
		Element newElement(name, priority);
		elements.push_back(newElement);
	}

	void pop() {
		if (!elements.empty()) {
			int maxIndex = getMaxPriorityIndex();
			elements.erase(elements.begin() + maxIndex);
		}
	}

	Element top() {
		if (!elements.empty()) {
			return elements[getMaxPriorityIndex()];
		}
		return Element(L"", -1);
	}

	bool isEmpty() {
		return elements.empty();
	}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HWND hwndName, hwndPriority, hwndPush, hwndPop;
	static PriorityQueue pq;

	switch (msg) {
	case WM_CREATE:
		hwndName = CreateWindowW(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 20, 100, 20, hwnd, (HMENU)1, NULL, NULL);
		hwndPriority = CreateWindowW(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 50, 100, 20, hwnd, (HMENU)2, NULL, NULL);

		// Add labels to the text fields
		CreateWindowW(L"Static", L"Name:", WS_CHILD | WS_VISIBLE, 20, 20, 40, 20, hwnd, NULL, NULL, NULL);
		CreateWindowW(L"Static", L"Priority:", WS_CHILD | WS_VISIBLE, 20, 50, 60, 20, hwnd, NULL, NULL, NULL);
		hwndPush = CreateWindowW(L"Button", L"Push", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 80, 100, 20, hwnd, (HMENU)3, NULL, NULL);
		hwndPop = CreateWindowW(L"Button", L"Pop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 110, 100, 20, hwnd, (HMENU)4, NULL, NULL);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 3) {
			wchar_t name[30], priority[10];
			GetWindowTextW(hwndName, name, 30);
			GetWindowTextW(hwndPriority, priority, 10);
			pq.push(std::wstring(name), _wtoi(priority));
		} else if (LOWORD(wParam) == 4) {
			Element e = pq.top();
			pq.pop();
			std::wstring msg = L"Name: " + e.name + L", Priority: " + std::to_wstring(e.priority);
			MessageBoxW(hwnd, msg.c_str(), L"Pop", MB_OK);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"PriorityQueue";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Priority Queue", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 250, 250, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}