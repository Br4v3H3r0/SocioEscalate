//https://www.codeproject.com/Articles/320748/Elevating-During-Runtime
//https://docs.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shellexecuteinfoa
// SIGN CERT
//https://stackoverflow.com/questions/84847/how-do-i-create-a-self-signed-certificate-for-code-signing-on-windows
// http://www.rohitab.com/discuss/topic/39662-patching-avs/?pid=10089791#entry10089791
#include<Windows.h>
#include<stdio.h>
#include <string>
using namespace std;
void UAC_prompt()
{

    std::string lpFile = "demo.exe";
	LPCTSTR lpFileptr = lpFile.c_str();

	std::string lpVerb = "runas";
	LPCTSTR lpVerbptr = lpVerb.c_str();

	while(true)
	{
		SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = lpVerbptr;
        sei.lpFile = lpFileptr;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&sei))
        {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED)
            {
            	printf("The user refused to allow privileges elevation\n");
            	Sleep(1000);
            }
        }
        else
        {
            printf("The user allowed privileges elevation\n");
            _exit(1);  
        }
	}
    

}

int main()
{
	UAC_prompt();
	return 0;
}