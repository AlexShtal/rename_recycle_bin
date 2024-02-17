#include <winreg.h>

int main(){
    HKEY recycleBinHKey;
    LPCSTR registrySubkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
    const BYTE * pnewValue = (const BYTE *) "—Ë·¿ƒ»";
    int newValueLen = 15;

    RegOpenKeyExA(HKEY_CURRENT_USER, registrySubkey, 0, KEY_SET_VALUE, &recycleBinHKey);
    RegSetValueExA(recycleBinHKey, NULL, 0, REG_SZ, pnewValue, newValueLen);
    RegCloseKey(recycleBinHKey);
}