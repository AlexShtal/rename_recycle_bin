#include <Windows.h>
#include <Shlobj.h>

int main(){
    HKEY recycleBinHKey;
    LPCSTR registrySubkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
    const BYTE * pnewValue = (const BYTE *) "NewName";
    int newValueLen = 8;

    RegOpenKeyExA(HKEY_CURRENT_USER, registrySubkey, 0, KEY_SET_VALUE, &recycleBinHKey);
    RegSetValueExA(recycleBinHKey, NULL, 0, REG_SZ, pnewValue, newValueLen);
    RegCloseKey(recycleBinHKey);

    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, NULL, NULL);
    return 0;
}
