#pragma once
#include <string>

DWORD ReadRegistryDWORD(HKEY hRootKey, const std::wstring& subKeyPath, const std::wstring& valueName, DWORD defaultValue);