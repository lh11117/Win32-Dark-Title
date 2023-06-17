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
	HWND hWnd = hwnd; // ��ȡ�����ھ��
	DWORD dwAttribute = DWMWA_USE_IMMERSIVE_DARK_MODE; // ���ð�ɫģʽ����
	BOOL bValue = TRUE; // ���ð�ɫģʽ
	DwmSetWindowAttribute(hWnd, dwAttribute, &bValue, sizeof(bValue)); // ���ô�������
}



void set_light_title(HWND hwnd){
	HWND hWnd = hwnd; // ��ȡ�����ھ��
	DWORD dwAttribute = DWMWA_USE_IMMERSIVE_DARK_MODE; // ���ð�ɫģʽ����
	BOOL bValue = FALSE; // ���ð�ɫģʽ
	DwmSetWindowAttribute(hWnd, dwAttribute, &bValue, sizeof(bValue)); // ���ô�������
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
	        value = -1;    // ��Ҫ�ٶ��ü�������ڣ�����Ҳ���������Ĭ��ֵ
	    }
	    RegCloseKey(hKey);
	}
	
	if (value == 0)
	{
	    // ��ǰʹ�ð�ɫ����
	    return WIN32_DARK();
	}
	else if (value == 1)
	{
	    // ��ǰʹ����ɫ����
	    return WIN32_LIGHT();
	}
	else
	{
	    // �޷�ȷ����ǰ����
	    return CAN_NOT_GET_THEME();
	}
}


HWND int2hwnd(int hwnd){
	return (HWND)hwnd;
}
