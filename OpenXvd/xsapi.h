#include "stdafx.h"

typedef int(__cdecl* XvdOpenAdapterExp)(HANDLE* handle);
typedef int(__cdecl* XvdCloseAdapterExp)(HANDLE handle);
typedef int(__cdecl* XvdMountExp)(void* unknownReturnValue1, void* unknownReturnValue2, HANDLE xvdHandle, LPCWSTR filePath, long long setToZero, long long setToZero2, int setToZero3);
typedef int(__cdecl* XvdUnmountFileExp)(HANDLE xvdHandle, LPCWSTR filePath);
typedef int(__cdecl* XsCreateConvertVhd2XVDExp)(LPCWSTR lpFileName, LPCWSTR lpFileName2, __int64 unk1, __int64 unk2, __int64 unk3);
typedef int(__cdecl* XvdVmMountExp)(void* unknownReturnValue1, void* unknownReturnValue2, HANDLE xvdHandle, LPCWSTR filePath, long long setToZero, long long setToZero2, int setToZero3);
typedef int(__cdecl* XsReadXvcInfoXVDExp)(LPCWSTR filename, void* data, int32_t* dataSize);

HMODULE xsapi;

// XvdOpenAdapter(HANDLE* handle)
XvdOpenAdapterExp			XvdOpenAdapter;
// XvdCloseAdapter(HANDLE handle)
XvdCloseAdapterExp			XvdCloseAdapter;
// XvdMount(void* unknownReturnValue1, void* unknownReturnValue2, HANDLE xvdHandle, LPCWSTR filePath, long long setToZero, long long setToZero2, int setToZero3)
XvdMountExp					XvdMount;
// XvdUnmountFile(HANDLE xvdHandle, LPCWSTR filePath)
XvdUnmountFileExp			XvdUnMountFile;
// XvdVmMount(void* unknownReturnValue1, void* unknownReturnValue2, HANDLE xvdHandle, LPCWSTR filePath, long long setToZero, long long setToZero2, int setToZero3)
XvdVmMountExp				XvdVmMount;
// XsCreateConvertVhd2XVD(LPCWSTR lpFileName, LPCWSTR lpFileName2, __int64 unk1, __int64 unk2, __int64 unk3)
XsCreateConvertVhd2XVDExp	XsCreateConvertVhd2XVD;
// XsReadXvcInfoXVD(LPCWSTR filename, void* data, int32_t* dataSize)
XsReadXvcInfoXVDExp			XsReadXvcInfoXVD;



bool isDllLoaded(LPCSTR path, HMODULE &module)
{
	module = LoadLibraryA(path);
	if (module == 0)
	{
		_tprintf(_T("Failed to load xsapi.dll! Install the SDK! Error code: %d\n"), GetLastError());
		return false;
	}
	return true;
}

void GetFunctions()
{
	XvdOpenAdapter			= (XvdOpenAdapterExp)GetProcAddress(xsapi, "XvdOpenAdapter");
	XvdCloseAdapter			= (XvdCloseAdapterExp)GetProcAddress(xsapi, "XvdCloseAdapter");
	XvdMount				= (XvdMountExp)GetProcAddress(xsapi, "XvdMount");
	XvdUnMountFile			= (XvdUnmountFileExp)GetProcAddress(xsapi, "XvdUnmountFile");
	XvdVmMount				= (XvdVmMountExp)GetProcAddress(xsapi, "XvdVmMount");
	XsCreateConvertVhd2XVD	= (XsCreateConvertVhd2XVDExp)GetProcAddress(xsapi, "XsCreateConvertVhd2XVD");
	XsReadXvcInfoXVD		= (XsReadXvcInfoXVDExp)GetProcAddress(xsapi, "XsReadXvcInfoXVD");
}

bool InitXsapi()
{
	if (!isDllLoaded("C:\\Program Files (x86)\\Microsoft Durango XDK\\bin\\xsapi.dll", xsapi))
	{
		return false;
	}

	GetFunctions();
	return true;
}