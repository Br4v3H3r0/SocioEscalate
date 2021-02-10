// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxw
#include<Windows.h>
#include<stdio.h>

void DialogDisplay()
{
	while(true)
	{
		int msgboxID = MessageBoxW(
	        NULL,
	        (LPCWSTR)L"Crtical Error #2348FA3000032:30 \nNeed to Fix some Drives",
	        (LPCWSTR)L"Dwwin.exe - Dll Initialization Failed",
	        MB_ICONHAND | MB_OKCANCEL   
	    );

	    
		if(msgboxID==IDOK)
		{
			// UAC prompt
			break;
		}

		Sleep(1000);
    }
}
	


int main()
{
	DialogDisplay();
	return 0;
}
