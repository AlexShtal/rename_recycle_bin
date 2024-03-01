#include <Windows.h>
#include <Shlobj.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>

#include "resource.h"

#define RECYCLE_BIN_KEY \
    L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\" \
    L"CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}"

static LPCWSTR szRecycleBinKey = RECYCLE_BIN_KEY;
static LPCWSTR szRecycleBinIconKey = RECYCLE_BIN_KEY L"\\DefaultIcon";

WCHAR startup_path[MAX_PATH];
WCHAR filename[MAX_PATH];

void rename_trash(void);
void get_startup_path(void);
void copy_to_startup(void);
void swap_icon(void);

int main(int argc, char* argv[]) {
    rename_trash();
    get_startup_path();
    copy_to_startup();
    swap_icon();

    return 0;
}

void rename_trash(void)
{
    HKEY recycleBinHKey;
    WCHAR newValue[] = L"СИБАДИ";
    DWORD newValueSize;

    newValueSize = sizeof(newValue);

    RegOpenKeyExW(HKEY_CURRENT_USER, szRecycleBinKey, 0, KEY_SET_VALUE, &recycleBinHKey);
    RegSetValueExW(recycleBinHKey, NULL, 0, REG_SZ, (const BYTE *)newValue, newValueSize);
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
    RegCloseKey(recycleBinHKey);
}

void get_startup_path(void)
{
    WCHAR *exename;

    GetModuleFileNameW(NULL, filename, MAX_PATH);
    exename = wcsrchr(filename, L'\\');

    if (exename != NULL) {
        exename++;
    } else {
        exename = filename;
    }

    swprintf(startup_path, MAX_PATH, L"%%USERPROFILE%%\\"
            L"AppData\\Roaming\\"
            L"Microsoft\\Windows\\"
            L"Start Menu\\Programs\\Startup\\%ls",
            exename);

}

void copy_to_startup(void)
{
    WCHAR startup_path_exp[MAX_PATH+1];

    /* Since CopyFile requires expanded path, we should call
     * ExpandEnvironmentStrings.
     */
    ExpandEnvironmentStringsW(startup_path, startup_path_exp, MAX_PATH+1);
    CopyFileW(filename, startup_path_exp, FALSE);
}

void swap_icon(void)
{
    WCHAR iconPath[MAX_PATH + 4];
    DWORD iconPathSize;
    HKEY recycleBinIconHKey;

    swprintf(iconPath, MAX_PATH + 4, L"%ls,-%d", startup_path, IDI_REPLACEMENT);
    iconPathSize = wcslen(iconPath) * sizeof(WCHAR);

    RegOpenKeyExW(HKEY_CURRENT_USER, szRecycleBinIconKey, 0, KEY_SET_VALUE, &recycleBinIconHKey);
    RegSetValueExW(recycleBinIconHKey, L"full", 0, REG_EXPAND_SZ, (const BYTE*)iconPath, iconPathSize);
    RegSetValueExW(recycleBinIconHKey, L"empty", 0, REG_EXPAND_SZ, (const BYTE*)iconPath, iconPathSize);
    RegSetValueExW(recycleBinIconHKey, NULL, 0, REG_EXPAND_SZ, (const BYTE*)iconPath, iconPathSize);
    RegCloseKey(recycleBinIconHKey);
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
}
