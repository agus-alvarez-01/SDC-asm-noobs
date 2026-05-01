# Trabajo Practico N°3A

## Uefi Security

**Materia:** Sistemas de Computacion  
**Grupo:** asm_noobs  
**Integrantes:** [Fabian Nicolas Hidalgo] · [Juan Manuel Caceres] · [Agustin Alvarez]  
**Repositorio:** [Github](https://github.com/Nick07242000/SDC-asm-noobs/blob/main/uefi_security_lab)

---

### Exploración del entorno UEFI y la Shell

**Objetivo:** Explorar cómo UEFI abstrae el hardware y gestiona la configuración antes de la carga del sistema operativo.

#### Arranque en el entorno virtual

A diferencia del BIOS Legacy que simplemente leía el primer sector de un disco (MBR), UEFI es un entorno completo con su propio gestor de memoria, red y consola.

Utilizamos QEMU para iniciar una máquina virtual de arquitectura de 64 bits, configurada con 512 MB de memoria RAM, arranque mediante firmware UEFI y sin ninguna conexión a la red.

```bash
qemu-system-x86_64 -m 512 -bios /usr/share/ovmf/OVMF.fd -net none
```

- qemu-system-x86_64: arquitectura de hardware x86 de 64 bits.
- -m 512: Asigna 512 megabytes de memoria RAM a esta máquina virtual.
- -bios /usr/share/ovmf/OVMF.fd: Cambia el firmware de arranque por defecto usando OVMF.fd en lugar de BIOS. 
- -net none: Deshabilita por completo el hardware de red, VM totalmente desconectada de internet y de red local.

> [!NOTE]
> OVMF (Open Virtual Machine Firmware) es una implementación de código abierto que permite a la máquina virtual arrancar usando UEFI.

Esta combinación de parámetros nos da un entorno ligero, de arranque rápido y completamente aislado por seguridad. 
Como no se especifica ningún disco duro o imagen ISO, la máquina enciende en la consola interactiva de UEFI (la UEFI Shell).

> [!IMPORTANT]
> Screenshot de QEMU UEFI startup aqui

### Desarrollo, compilación y análisis de seguridad

...

### Ejecución en Hardware Físico (Bare Metal)

...

### Referencias

> ...
