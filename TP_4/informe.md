# Trabajo Practico N°4

## Modulos de Kernel

**Materia:** Sistemas de Computacion  
**Grupo:** asm_noobs  
**Integrantes:** [Fabian Nicolas Hidalgo] · [Juan Manuel Caceres] · [Agustin Alvarez]  
**Repositorio:** [Github](https://github.com/Nick07242000/SDC-asm-noobs/blob/main/TP_4)

---

### Desafio #1 

> ¿Qué es checkinstall y para qué sirve?

Es una herramienta para GNU/Linux que permite instalar software compilado desde código fuente y al mismo tiempo generar un paquete instalable del sistema.

Normalmente, cuando se compila un programa manualmente se usa:

```bash
./configure
make
sudo make install
```

El problema es que `make install` copia archivos al sistema sin que el gestor de paquetes los controle. Luego resulta difícil desinstalar o auditar qué se instaló.

Checkinstall reemplaza `sudo make install` por `sudo checkinstall` y automáticamente registra los archivos instalados, crea un paquete instalable, permite desinstalarlo fácilmente, mantiene el sistema más ordenado y seguro.

> Usarlo para empaquetar un hello world

Para esto generamos un programa en c `hello.c`, el cual compilamos con gcc y luego generamos un makefile parausar con checkinstall.

Ejecutamos el mismo con `sudo checkinstall` y generamos el paquete: 

<img width="947" height="1354" alt="Screenshot from 2026-05-18 23-25-03" src="https://github.com/user-attachments/assets/ee66ae6c-d8ef-4a8a-8c65-81677d1591ff" />

Luego instalamos el paquete con `dpkg` y lo ejecutamos:

<img width="759" height="138" alt="Screenshot from 2026-05-18 23-25-45" src="https://github.com/user-attachments/assets/5a98d893-d4ad-4cee-a4df-9e804546348d" />

> Revisar la bibliografía para impulsar acciones que permitan mejorar la seguridad del kernel.
> Concretamente: evitando cargar módulos que no estén firmados.

Un módulo firmado posee una firma criptográfica verificada por el kernel antes de cargarse. Si la firma no es válida el módulo se rechaza y no puede ejecutarse dentro del kernel.

Si el sistema permite cargar cualquier módulo, un atacante con privilegios puede insertar código malicioso directamente en el kernel.

Para evitar estos modulos no firmados podemos realizar diversas acciones:

1. Activar “Module Signature Verification”: Esto obliga al kernel a aceptar únicamente módulos firmados.
2. Usar Secure Boot: permite que el firmware valide el bootloader, el bootloader valide el kernel y el kernel valide módulos.
3. Deshabilitar carga dinámica de módulos: no se pueden cargar más módulos, incluso siendo root.
4. Restringir herramientas peligrosas: como `insmod`, `modprobe` y `rmmod` solo a administradores confiables.

> ¿ Que son rootkits? 

Un rootkit es software malicioso diseñado para ocultarse, obtener privilegios elevados y modificar el comportamiento del sistema.

Los rootkits de kernel son especialmente peligrosos porque operan con privilegios máximos.

Entre las cosas que pueden realizar encontramos que pueden interceptar syscalls, ocultar procesos, ocultar archivos, ocultar conexiones de red y alterar logs.

### Desafio #2

> ¿Qué funciones tiene disponible un programa y un módulo?

Un programa en espacio de usuario utiliza funciones de bibliotecas (libc, pthread, etc), realiza llamadas al sistema (read, write, fork, socket), posee memoria virtual aislada y tienepermisos restringidos.

Este no tiene acceso directo al hardware.

Por otro lado un módulo del kernel puede acceder directamente al hardware, manipular memoria del kernel, registrar drivers, interceptar llamadas y manejar interrupciones.

Este tiene privilegios totales.

> Espacio de usuario o espacio del kernel.

El espacio de usuario es donde se ejecutan aplicaciones, shells, navegadores y programas comunes.

Se caracteriza por su acceso restringido, aislamiento entre procesos y produce errores menos críticos.

Son las aplicaciones que conocemos como Firefox, Bash, VSCode, etc

El espacio del kernel es donde se ejecuta el kernel y sus módulos.

Se caracteriza por su acceso completo al hardware, posee máxima prioridad, y si produce un error puede colgar todo el sistema.

Por ejemplo el scheduler, los drivers, el sistema de memoria y el filesystem.

> Espacio de datos.

El espacio de datos de un proceso contiene sus variables globales, sus variables estáticas, su heap y su stack.

Se divide típicamente en Text (que es el código ejecutable), Data (las variables inicializadas), BSS (las variables no inicializadas), Heap	(la memoria dinámica) y el Stack (las variables locales y las llamadas).

> Drivers. Investigar contenido de /dev.

Un driver es software que permite al sistema operativo comunicarse con hardware.

Tenemos drivers para el teclado, el disco, la placa de red, la GPU y los puertos USB.

En Linux muchos drivers son módulos del kernel (.ko).

Con respecto a `/dev` Linux lo utiliza para representar dispositivos como archivos.

La idea central de Unix es que todo es un archivo.

Asi por ejemplo tenemos:

| Archivo        | Función                  |
| -------------- | ------------------------ |
| `/dev/sda`     | disco duro               |
| `/dev/tty`     | terminal                 |
| `/dev/null`    | descarta datos           |
| `/dev/zero`    | genera ceros             |
| `/dev/random`  | números aleatorios       |
| `/dev/urandom` | números pseudoaleatorios |
| `/dev/input/*` | dispositivos de entrada  |
| `/dev/snd/*`   | audio                    |

### Modulos

#### Compilado e Instalado

Dentro del directorio `part1` colocamos el Makefile y el archivo `mimodulo.c` provistos para la experiencia.

Con estos podemos compilar el modulo utilizando `make`, lo que nos entrega el archivo `mimodulo.ko`.

<img width="1165" height="336" alt="Screenshot from 2026-05-19 01-16-34" src="https://github.com/user-attachments/assets/c255aa22-740d-43fc-8c57-344f1c3ba47c" />

Luego insertamos el modulo dentro del kernel ejecutando `sudo insmod mimodulo.ko`.

<img width="685" height="42" alt="Screenshot from 2026-05-19 01-17-02" src="https://github.com/user-attachments/assets/f9570caf-eb2d-4d6e-993f-5969c6dee890" />

Finalmente con `sudo dmesg` mostramos el log del kernel donde vemos la carga del modulo en el kernel:

<img width="874" height="54" alt="Screenshot from 2026-05-19 01-19-39" src="https://github.com/user-attachments/assets/18727d58-008f-4d34-9eb2-b1228f12e0d0" />

Observamos como nos informa que el modulo no pertenece al kernel oficial, no esta firmado, y que "manchamos" el kernel incluyendolo.

Finalmente con `lsmod | grep mod` buscamos el modulo en la lista de modulos cargados:

<img width="634" height="116" alt="Screenshot from 2026-05-19 01-21-58" src="https://github.com/user-attachments/assets/13b88b49-ee11-42d2-91d5-3a150d76b93b" />

Aqui vemos el nombre del modulo, el tamaño en memoria, y la cantidad de modulos que lo usan.
 
Para quitarlo podemos ejecutar `sudo rmmod mimodulo` y vemos el resultado nuevamente en los logs:

<img width="653" height="44" alt="Screenshot from 2026-05-19 01-24-14" src="https://github.com/user-attachments/assets/9af5b158-5be7-41b6-8aec-b21c219fedc3" />
<img width="876" height="68" alt="Screenshot from 2026-05-19 01-24-56" src="https://github.com/user-attachments/assets/9d567035-34f1-4c1f-874f-dbf78d89337a" />

Y vemos como ya no esta cargado:

<img width="625" height="103" alt="Screenshot from 2026-05-19 01-25-51" src="https://github.com/user-attachments/assets/ed010e4b-158b-45c8-95e5-59ade8978fd8" />
<img width="716" height="103" alt="Screenshot from 2026-05-19 01-27-05" src="https://github.com/user-attachments/assets/eaf23bb7-f94f-4635-8ef9-168763473475" />

#### Informacion del Modulo

Con `modinfo mimodulo.ko` podemos ver los metadatos del modulo:

<img width="647" height="202" alt="Screenshot from 2026-05-19 01-29-10" src="https://github.com/user-attachments/assets/cc7a5cf9-8e17-440a-be7b-01294517a135" />

`vermagic` nos indica versión del kernel, arquitectura y opciones de compilación compatibles.

Esto lo podemos contrastar con la informacion de un modulo real de kernel usando `modinfo /lib/modules/$(uname -r)/kernel/crypto/des_generic.ko`

<img width="980" height="861" alt="Screenshot from 2026-05-19 01-35-52" src="https://github.com/user-attachments/assets/aae971b9-b719-4f8a-9e82-39b5a55aaead" />

Vemos que la informacion es mucho mas completa que nuestro modulo casero, y particularmente vemos intree Y en el oficial, y N en el nuestro que diferencia justamente eso de pertenecer al kerner oficial.

#### Preguntas

> ¿Qué diferencias se pueden observar entre los dos modinfo ? 

| Característica | Módulo propio           | Módulo oficial del kernel       |
| -------------- | ----------------------- | ------------------------------- |
| `filename`     | ruta local              | ruta dentro del kernel          |
| `intree`       | `N` o ausente           | `Y`                             |
| Firma digital  | generalmente no firmado | firmado                         |
| Autor          | alumno                  | desarrolladores kernel          |
| Licencia       | definida manualmente    | oficial                         |
| Dependencias   | normalmente ninguna     | puede depender de otros módulos |
| Taint          | puede taint el kernel   | normalmente no                  |
| Compatibilidad | compilado localmente    | validado oficialmente           |

> ¿Qué divers/modulos estan cargados en sus propias pc?  

Podemos utilizar lmod para ver los modulos que tenemos en nuestras PCs:

<img width="1003" height="911" alt="Screenshot from 2026-05-19 01-39-36" src="https://github.com/user-attachments/assets/a43dbb80-cab3-46be-ac3c-b601aff2a2ee" />

> Comparar las salidas con las computadoras de cada integrante del grupo. Expliquen las diferencias.

TODO

> Carguen un txt con la salida de cada integrante en el repo y pongan un diff en el informe.

WIP

> ¿Cuales no están cargados pero están disponibles?

Podemos usar `find /lib/modules/$(uname -r) -name "*.ko" | head` para encontrarlos:

<img width="883" height="196" alt="Screenshot from 2026-05-19 01-45-04" src="https://github.com/user-attachments/assets/1a531797-e2c3-4095-893b-eb5f120407ed" />

> Que pasa cuando el driver de un dispositivo no está disponible. 

Si el driver de un dispositivo no esta disponible el sistema operativo no puede controlar el hardware.

El dispositivo puede no funcionar, funcionar parcialmente o usar drivers genéricos.

> Correr hwinfo en una pc real con hw real y agregar la url de la información de hw en el reporte. 

Agregados bajo la nomenclatura `<miembro>_hwinfo.txt`.

> ¿Qué diferencia existe entre un módulo y un programa?

| Programa               | Módulo                   |
| ---------------------- | ------------------------ |
| corre en user space    | corre en kernel space    |
| permisos restringidos  | privilegios totales      |
| usa syscalls           | accede directo al kernel |
| falla aislada          | puede colgar el sistema  |
| `.out`, ELF ejecutable | `.ko`                    |

> ¿Cómo puede ver una lista de las llamadas al sistema que realiza un simple helloworld en c?

Podemos ejecutar la herramienta `strace`:

<img width="943" height="722" alt="Screenshot from 2026-05-19 01-52-54" src="https://github.com/user-attachments/assets/f7ddb6ff-b242-421f-9ecf-f9fdc20a6332" />

Este intercepta las llamadas al sistema y la interacción con el kernel.

> ¿Qué es un segmentation fault?
> ¿Cómo lo maneja el kernel y como lo hace un programa?

Un segmentation fault ocurre cuando un programa accede memoria inválida, usa punteros incorrectos o escribe fuera de límites.

El kernel lo maneja detectando el acceso inválido, enviando una señal SIGSEGV y terminando el proceso.

Un programa puede manejarlo capturando señales, generando core dumps o usando handlers, e.g:

```C
signal(SIGSEGV, handler);
```

> Intentar firmar un módulo de kernel y documentar el proceso?

#### Paso 1:
Primero debemos generar certificados para firmar módulos:
```bash
mkdir ~/module-signing
cd ~/module-signing
openssl req -new -x509 -newkey rsa:2048 \
    -keyout MOK.priv \
    -outform DER \
    -out MOK.der \
    -nodes \
    -days 36500 \
    -subj "/CN=asm_noobs Module Signing Key/"
```
- `-new` genera un nuevo certificado. 
- `-x509` crea directamente un certificado X.509 autofirmado.
- `-newkey rsa:2048` genera una nueva clave RSA de 2048 bits. 
- `-days` indica la canditidad de dias validos.
- `-subj` define el Common Name del certificado

Archivos generados en la carpeta module-signing:

- `MOK.priv`: clave privada
- `MOK.der`: certificado público

#### Paso 2:
> Registrar la clave en MOK (Machine Owner Key)
```bash
sudo mokutil --import ~/module-signing/MOK.der
```
Esto pide una contraseña temporal.

#### Paso 3:
Luego, hay que reiniciar la computadora, y aparecerá la pantalla de MOK Manager, donde se va a registrar el certificado generado.

Pantalla MOK:
-> seleccionar Enroll MOK

----------Enroll-MOK
-> View key 0

Permite ver el certificado que está a punto de registrar en MOK. 

----------view-key 1y2

-> Continue

Confirmar el enroll

-> Yes

----------foto-confirmacion enroll

Colocar clave temporal, generada anteriormente.

-> Password

----------foto clave temporal

-> Reboot

----------foto-fin-reboot

#### Paso 4:
Firmar el módulo, el script de firma viene con el kernel:

> Ejecutar estando en la carpeta donde está mimodulo.ko

```bash
/usr/src/linux-headers-$(uname -r)/scripts/sign-file \
sha256 \
~/module-signing/MOK.priv \
~/module-signing/MOK.der \
mimodulo.ko
```
Verificar la firma

```bash
modinfo mimodulo.ko | grep -E 'signer|sig_key|sig_hashalgo'
```
----------foto firma y comprobacion
#### Paso 5:
Luego hay que cargar la versión firmada:
```bash
sudo insmod mimodulo.ko
```

----------foto-modulo-cargado

> [!NOTE]
> Para poder realizar el proceso, el secure boot debe estar activo. Se puede comprobar con `mokutil --sb-state`, y Platform Mode en User Mode, no en Setup Mode.

...

> Agregar evidencia de la compilación, carga y descarga de su propio módulo imprimiendo el nombre del equipo en los registros del kernel. 

Para imprimir el nombre de nuestro equipo en los registros del kernel, modificamos la linea del `printk()` en `mimodulo.c`
```C
printk(KERN_INFO "Modulo cargado en el kernel, por asm_noobs :).\n");
```
Compilamos nuevamente con `make`, y firmamos nuevamente **(Paso 4)**.
Hay que descargar el modulo anterior, cargar el nuevo y verficar:
```bash
sudo rmmod mimodulo.ko
sudo insmod mimodulo.ko
sudo dmesg
```
FOTO FIRMA_ASM_NOOBS

...

> ¿Que pasa si mi compañero con secure boot habilitado intenta cargar un módulo firmado por mi? 

Un módulo firmado por otro usuario no puede cargarse en un sistema con Secure Boot habilitado salvo que la clave pública correspondiente haya sido previamente registrada en la base de confianza MOK del sistema.

...


> Dada la siguiente [nota](https://arstechnica.com/security/2024/08/a-patch-microsoft-spent-2-years-preparing-is-making-a-mess-for-some-linux-users/)  
> ¿Cuál fue la consecuencia principal del parche de Microsoft sobre GRUB en sistemas con arranque dual (Linux y Windows)?

...

> Dada la siguiente [nota](https://arstechnica.com/security/2024/08/a-patch-microsoft-spent-2-years-preparing-is-making-a-mess-for-some-linux-users/)  
> ¿Qué implicancia tiene desactivar Secure Boot como solución al problema descrito en el artículo?

...

> Dada la siguiente [nota](https://arstechnica.com/security/2024/08/a-patch-microsoft-spent-2-years-preparing-is-making-a-mess-for-some-linux-users/)  
> ¿Cuál es el propósito principal del Secure Boot en el proceso de arranque de un sistema?

...

### Referencias

> [Kernel Redhat](https://access.redhat.com/documentation/es-es/red_hat_enterprise_linux/8/html/managing_monitoring_and_updating_the_kernel/signing-kernel-modules-for-secure-boot_managing-kernel-modules)

> [Kernel Module](https://sysprog21.github.io/lkmpg/#what-is-a-kernel-module)

> [Strace](https://opensource.com/article/19/10/strace)

> [???](https://docs.google.com/presentation/d/1BYES6Zkfx5K85REWyXsFeW-VngBLOzlDzaYCsTVoc0Y/edit#slide=id.g724a4c87a0_0_5 )

> [Sign Kernel](https://askubuntu.com/questions/770205/how-to-sign-kernel-modules-with-sign-file)

> [Dual Boot Issue](https://arstechnica.com/security/2024/08/a-patch-microsoft-spent-2-years-preparing-is-making-a-mess-for-some-linux-users/)
