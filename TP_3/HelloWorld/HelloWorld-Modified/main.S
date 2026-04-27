.code16
    /* 1. Inicializamos los segmentos a 0 para que hardware real no lea basura */
    xor %ax, %ax            # ax = 0 (es la forma más rápida de poner un registro en 0)
    mov %ax, %ds            # ds = 0
    mov %ax, %es            # es = 0

    mov $msg, %si           # Cargamos la dirección del mensaje en SI
    mov $0x0E, %ah          # Función BIOS para imprimir carácter
    
bucle:                      # (Cambié el nombre de la etiqueta 'loop' por 'bucle' porque 'loop' es una instrucción x86)
    lodsb                   # Carga un byte de DS:SI en AL y avanza SI
    or %al, %al             # Verificamos si llegamos al final del string (byte 0)
    jz halt                 # Si es 0, terminamos
    int $0x10               # Imprime el carácter
    jmp bucle               # Vuelve a repetir

halt:
    cli                     # 2. Clear Interrupts: Ignoramos el reloj del sistema y otros hardwares
    hlt                     # Detenemos el CPU
    jmp halt                # 3. Bucle infinito: Si por un milagro se despierta, vuelve a halt

msg:
    .asciz "Hello, World!"