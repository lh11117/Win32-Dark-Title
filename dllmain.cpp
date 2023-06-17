#include <windows.h>
#include <dwmapi.h>

extern "C" __declspec(dllexport) void set_dark_title(HWND);
extern "C" __declspec(dllexport) void set_light_title(HWND);
extern "C" __declspec(dllexport) int is_dark();
extern "C" __declspec(dllexport) HWND int2hwnd(int);


extern "C" __declspec(dllexport) int WIN32_DARK();
extern "C" __declspec(dllexport) int WIN32_LIGHT();
extern "C" __declspec(dllexport) int CAN_NOT_GET_THEME();


int WIN32_DARK(){return 0;}
int WIN32_LIGHT(){return 1;}
int CAN_NOT_GET_THEME(){return -1;}


#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif


void set_dark_title(HWND hwnd){
	HWND hWnd = hwnd; // 获取主窗口句柄
	DWORD dwAttribute = DWMWA_USE_IMMERSIVE_DARK_MODE; // 设置暗色模式属性
	BOOL bValue = TRUE; // 启用暗色模式
	DwmSetWindowAttribute(hWnd, dwAttribute, &bValue, sizeof(bValue)); // 设置窗口属性
}



void set_light_title(HWND hwnd){
	HWND hWnd = hwnd; // 获取主窗口句柄
	DWORD dwAttribute = DWMWA_USE_IMMERSIVE_DARK_MODE; // 设置暗色模式属性
	BOOL bValue = FALSE; // 启用暗色模式
	DwmSetWindowAttribute(hWnd, dwAttribute, &bValue, sizeof(bValue)); // 设置窗口属性
}


int is_dark(){
	HKEY hKey;
	const char* subKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";
	const char* valueName = "AppsUseLightTheme";
	DWORD value = -1;
	DWORD valueSize = sizeof(DWORD);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
	    HRESULT hr = RegGetValue(hKey, nullptr, valueName, RRF_RT_REG_DWORD, nullptr, &value, &valueSize);
	    if (hr != S_OK)
	    {
	        value = -1;    // 不要假定该键必须存在，如果找不到将返回默认值
	    }
	    RegCloseKey(hKey);
	}
	
	if (value == 0)
	{
	    // 当前使用暗色主题
	    return WIN32_DARK();
	}
	else if (value == 1)
	{
	    // 当前使用亮色主题
	    return WIN32_LIGHT();
	}
	else
	{
	    // 无法确定当前主题
	    return CAN_NOT_GET_THEME();
	}
}


HWND int2hwnd(int hwnd){
	return (HWND)hwnd;
}
