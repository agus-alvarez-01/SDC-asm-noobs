.code16
.section .text
.global _start

_start:
    ljmp $0, $real_start    # Asegura que empecemos a leer en la dirección de memoria correcta

real_start:
    jmp skip_bpb            # Salta un área que la BIOS suele sobrescribir por accidente
    .space 90, 0            # Deja 90 bytes de espacio vacío como medida de seguridad

skip_bpb:
    /* Preparamos la memoria y la pila (stack) */
    xor %ax, %ax            # Pone el registro AX en 0
    mov %ax, %ds            # Segmento de datos en 0
    mov %ax, %es            # Segmento extra en 0
    mov %ax, %ss            # Segmento de pila en 0
    mov $0x7C00, %sp        # Prepara la memoria temporal justo debajo de nuestro código

    /* Preparamos el mensaje */
    mov $msg, %si           # Apunta a la primera letra de nuestro texto
    mov $0x0E, %ah          # Le avisa a la BIOS que queremos mostrar texto en pantalla

loop:
    lodsb                   # Lee una letra y avanza automáticamente a la siguiente
    or %al, %al             # Revisa si la letra es un cero (lo que indica el fin del texto)
    jz halt                 # Si es cero, salta al final y termina
    int $0x10               # Le dice a la BIOS: "¡Imprime esta letra!"
    jmp loop                # Vuelve arriba para procesar la siguiente letra

halt:
    cli                     # Apaga las interrupciones para que nada moleste al sistema
    hlt                     # Congela el procesador para ahorrar energía
    jmp halt                # Bucle infinito por si el procesador se despierta por error

msg:
    .asciz "hello from asm_noobs" # Nuestro texto (la 'z' final le agrega el cero oculto al terminar)