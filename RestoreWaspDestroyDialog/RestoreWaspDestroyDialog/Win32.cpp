#include "pch.h"
#include "Win32.h"

DWORD ReadRegistryDWORD(HKEY hRootKey, const std::wstring& subKeyPath, const std::wstring& valueName, DWORD defaultValue)
{
	HKEY hKey;
	DWORD value = defaultValue;
	DWORD dataType = 0;
	DWORD data = 0;
	DWORD dataSize = sizeof(DWORD);

	LONG result = RegOpenKeyExW(hRootKey, subKeyPath.c_str(), 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS) {
		return defaultValue;
	}

	result = RegQueryValueExW(hKey, valueName.c_str(), nullptr, &dataType, reinterpret_cast<LPBYTE>(&data), &dataSize);
	if (result == ERROR_SUCCESS && dataType == REG_DWORD) {
		value = data;
	}

	RegCloseKey(hKey);
	return value;
}