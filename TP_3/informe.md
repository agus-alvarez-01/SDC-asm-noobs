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

**Grabar la imagen en un pendrive y probarla en una PC**

Para llevar nuestro código bare-metal a un entorno físico, el primer paso es compilar y enlazar el código fuente. Desde nuestra terminal en Linux, ejecutamos la siguiente secuencia:

* **Ensamblado:** `as -g -o main.o main.S`
    Este comando utiliza el GNU Assembler para traducir nuestro código fuente (`main.S`) a código objeto (`main.o`), incluyendo información de depuración mediante la bandera `-g`.
* **Enlazado:** `ld --oformat binary -o main.img -T link.ld main.o`
    El GNU Linker toma el archivo objeto y, aplicando las reglas matemáticas de nuestro script `link.ld`, ubica el código en la dirección de memoria correcta (`0x7c00`), generando un archivo binario puro (`main.img`).

Una vez obtenida la imagen booteable, procedemos a transferirla al pendrive. Es fundamental desmontar la unidad previamente para evitar conflictos con el sistema operativo:

* **Desmontaje:** `sudo umount /dev/sdb1`
* **Escritura a bajo nivel:** `sudo dd if=main.img of=/dev/sdb status=progress`
    La herramienta `dd` toma nuestra imagen y escribe sus bytes exactos directamente en el primer sector físico del USB (`/dev/sdb`), ignorando cualquier sistema de archivos previo y convirtiendo al dispositivo en un disco de arranque válido (MBR).

![Captura de terminal con los comandos de compilación y flasheo](Screenshot_20260426_225116.png)

Finalmente, procedimos a probar el pendrive booteable. Para sortear las restricciones del firmware UEFI de las notebooks modernas, utilizamos una computadora de escritorio. Las placas madre de escritorio suelen ofrecer módulos CSM (Compatibility Support Module) más robustos, permitiendo emular a la perfección el arranque *Legacy* de 16 bits. 

Al encender el equipo y seleccionar el pendrive en el menú de arranque, el procesador inició en modo real, ejecutó nuestras instrucciones nativamente y logró imprimir la cadena de texto con éxito antes de entrar en un estado de detención controlada (`hlt`).

![Monitor mostrando el texto Hello World! (a medias) ejecutándose en el hardware físico](20260426_231746.jpg)

---

### Depuracion con GDB + QEMU

...

---

### Desafio: Modo Protegido

...

---
