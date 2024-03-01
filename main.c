#include <Windows.h>
#include <Shlobj.h>
#include <string.h>
#include <stdio.h>

#include "resource.h"

char startup_path[MAX_PATH];
char filename[MAX_PATH];

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
    LPCSTR registrySubkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
    const BYTE * pnewValue = (const BYTE *) "SIBADI";
    RegOpenKeyExA(HKEY_CURRENT_USER, registrySubkey, 0, KEY_SET_VALUE, &recycleBinHKey);
    RegSetValueExA(recycleBinHKey, NULL, 0, REG_SZ, pnewValue, strlen(pnewValue));
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
    RegCloseKey(recycleBinHKey);
}

void get_startup_path(void)
{
    char *exename;

    GetModuleFileName(NULL, filename, MAX_PATH);
    exename = strrchr(filename, '\\');

    if (exename != NULL) {
        exename++;
    } else {
        exename = filename;
    }

    sprintf(startup_path, "%%USERPROFILE%%\\"
            "AppData\\Roaming\\"
            "Microsoft\\Windows\\"
            "Start Menu\\Programs\\Startup\\%s",
            exename);
}

void copy_to_startup(void)
{
    char command[345];

    sprintf(command, "copy \"%s\" \"%s\"", filename, startup_path);
    system(command);
}

void swap_icon(void)
{
    LPCSTR iconRegistryKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon";
    char iconPath[256];
    HKEY recycleBinIconHKey;

    sprintf(iconPath, "%s,-%d", startup_path, IDI_REPLACEMENT);
    RegOpenKeyExA(HKEY_CURRENT_USER, iconRegistryKey, 0, KEY_SET_VALUE, &recycleBinIconHKey);
    RegSetValueExA(recycleBinIconHKey, "full", 0, REG_EXPAND_SZ, (const BYTE*)iconPath, strlen(iconPath));
    RegSetValueExA(recycleBinIconHKey, "empty", 0, REG_EXPAND_SZ, (const BYTE*)iconPath, strlen(iconPath));
    RegSetValueExA(recycleBinIconHKey, NULL, 0, REG_EXPAND_SZ, (const BYTE*)iconPath, strlen(iconPath));
    RegCloseKey(recycleBinIconHKey);
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
}
