#include "stdafx.h"
#include "xsapi.h"

HRESULT MountXvd(LPCWSTR filepath);
HRESULT UnMountXvd(LPCWSTR filepath);

int _tmain(int argc, _TCHAR* argv[])
{
	if (!InitXsapi())
	{
		printf("Failed to intialize xsapi!\n");
		system("pause");
		return 0;
	}

	if (_tcscmp(argv[1], L"-m") == 0)
	{
		MountXvd(argv[2]);
		system("pause");
	}
	else if (_tcscmp(argv[1], L"-um") == 0)
	{
		UnMountXvd(argv[2]);
		system("pause");
	}
	else
	{
		printf("Invalid Input!\n -m filepath to mount\n -um filepath to unmount\n");
		system("pause");
		return 0;
	}
}

HRESULT MountXvd(LPCWSTR filepath)
{
	// Setup Xvd handle
	HANDLE* XVD = new HANDLE;
	HRESULT result = XvdOpenAdapter(XVD);
	printf("XvdOpenAdapter result = 0x%08X handle = 0x%08X\n", result, XVD);
	
	// \\\\?\\GLOBALROOT\\Device\\Harddisk%ld\\Partition1 where %ld is the disk number ie. 2
	
	// Mount XVD and store the unknowns inside vars so we can debug them later
	BYTE* unk1 = new BYTE[256];
	BYTE* unk2 = new BYTE[256];
	result = XvdMount(unk1, unk2, *XVD, filepath, NULL, NULL, NULL);
	//printf("u1: %s u2: %s\n", unk1, unk2);

	// Check Success or known errors
	if (result == S_OK)
	{
		printf("Successfully mounted Xvd!\n");
	}
	else if (result == 0x80070002)
	{
		printf("Failed to find XVD file!\n");
	}
	else if (result == 0xC0000043)
	{
		printf("Xvd file is already mounted or being used by another process!\n");
	}
	else
	{
		printf("XvdMount result: 0x%08X\n", result);
		printf("Failed to mount xvd!\n");
	}
	// Close adapter since we are done
	XvdCloseAdapter(*XVD);

	// Deallocate the memory we allocted and return the result
	delete XVD;
	delete unk1;
	delete unk2;
	return result;
}

HRESULT UnMountXvd(LPCWSTR filepath)
{
	// Setup XVD Handle
	HANDLE* XVD = new HANDLE;
	HRESULT result = XvdOpenAdapter(XVD);
	printf("XvdOpenAdapter result = 0x%08X handle = 0x%08X\n", result, XVD);

	// UnMount XVD file
	result = XvdUnMountFile(*XVD, filepath);

	//Check for Success or known errors
	if (result == S_OK)
	{
		printf("Successfully Unmounted Xvd!\n");
	}
	else if (result == 0x80070002)
	{
		printf("Failed to find XVD file!\n");
	}
	else
	{
		printf("XvdUnmount result: 0x%08X\n", result);
		printf("Failed to unmount xvd!\n");
	}

	// Close XVD adapter since we are done
	XvdCloseAdapter(*XVD);

	// Deallocate memory and return the result
	delete XVD;
	return result;
}