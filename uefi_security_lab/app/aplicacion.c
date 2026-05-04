#include <efi.h>
#include <efilib.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) 
{
    InitializeLib(ImageHandle, SystemTable);
    
    // Envolvemos la llamada directa al protocolo
    uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"Iniciando analisis de seguridad...\r\n");
    
    // Inyección de un software breakpoint (INT3)
    unsigned char code[] = { 0xCC };
    if (code[0] == 0xCC) 
    {
        uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"Breakpoint estatico alcanzado.\r\n");
    }
    
    return EFI_SUCCESS;
}