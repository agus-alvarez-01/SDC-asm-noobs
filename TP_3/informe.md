# Trabajo Practico N°3

## Calculadora de Indices

**Materia:** Sistemas de Computación  
**Grupo:** asm_noobs  
**Integrantes:** [Fabian Nicolas Hidalgo] · [Juan Manuel Caceres] · [Agustin Alvarez]  
**Repositorio:** [Github](https://github.com/Nick07242000/SDC-asm-noobs/blob/main/TP_3)

---

### Desafio: BIOS, UEFI y Coreboot

...

---

### Desafio: Linker y Hello World Bare-Metal

**¿Qué es un linker y qué hace?**
El linker (enlazador), como `ld` de GNU, es la herramienta que realiza el paso final en la creación de un binario. Su función es combinar múltiples archivos objeto y archivos de archivo (.a), relocalizar sus datos y resolver las referencias a símbolos (como etiquetas de funciones o variables). El linker se guía por un "Linker Script" que describe cómo deben organizarse las secciones de código y datos en el archivo de salida final para que el hardware pueda interpretarlas correctamente.

**¿Qué es la dirección que aparece en el script del linker? ¿Por qué es necesaria?**
En el script, el símbolo `.` representa el "location counter" (contador de ubicación). Al asignarle el valor `0x7c00`, le estamos indicando al linker que la dirección virtual de memoria (VMA) de nuestro código comienza exactamente ahí. 

Esta dirección es crítica debido a una decisión de diseño que data de la IBM PC 5150 (1981). Los desarrolladores de la BIOS eligieron `0x7c00` porque, en máquinas que entonces tenían solo 32KB de RAM, esta dirección permitía cargar el sector de arranque lo suficientemente alto para no sobrescribir la Tabla de Vectores de Interrupción (IVT) en la parte baja, pero dejando espacio suficiente arriba para que el sistema operativo cargara su propio código y manejara su pila (stack) sin colisiones. Si no definimos esto en el linker, las referencias a datos dentro de nuestro ensamblador serían calculadas desde la dirección `0x0`, y el programa fallaría al intentar leer variables una vez cargado en la RAM real.

**Comparación de la salida de objdump con hd.**
La comparación nos permite ver el programa desde dos perspectivas:
* **objdump -S:** Nos muestra la vista lógica, relacionando las instrucciones de ensamblador con sus direcciones de memoria y los opcodes resultantes (por ejemplo, ver que la instrucción `hlt` se traduce al byte `f4`).
* **hd (hexdump):** Nos muestra la vista física del archivo `.img`. Aquí verificamos que los bytes estén en el orden exacto y que la firma de arranque `55 AA` ocupe los bytes 511 y 512 del sector. Al contrastarlos, confirmamos que el linker colocó cada sección en el offset correcto para que la BIOS lo reconozca como un disco booteable.

**¿Para qué se utiliza la opción --oformat binary en el linker?**
Se utiliza para generar un archivo binario "plano" (flat binary). Por defecto, los linkers modernos generan archivos en formato ELF o PE, que contienen encabezados complejos con metadatos para el sistema operativo. En un entorno bare-metal, no hay un sistema operativo para leer esos encabezados; el procesador simplemente empieza a ejecutar bytes uno tras otro. La opción `--oformat binary` elimina toda esa estructura extra y deja únicamente las instrucciones de máquina puras, que es lo único que el CPU puede procesar en modo real.

---

### Depuracion con GDB + QEMU

...

---

### Desafio: Modo Protegido

...

---
