# Trabajo Practico N°4

## Modulos de Kernel

**Materia:** Sistemas de Computacion  
**Grupo:** asm_noobs  
**Integrantes:** [Fabian Nicolas Hidalgo] · [Juan Manuel Caceres] · [Agustin Alvarez]  
**Repositorio:** [Github](https://github.com/Nick07242000/SDC-asm-noobs/blob/main/TP_4)

---

### Desafio #1 

> ¿Qué es checkinstall y para qué sirve?

...

> Usarlo para empaquetar un hello world

...

> Revisar la bibliografía para impulsar acciones que permitan mejorar la seguridad del kernel.
> Concretamente: evitando cargar módulos que no estén firmados.

... 

> ¿ Que son rootkits? 

...

### Desafio #2

> ¿Qué funciones tiene disponible un programa y un módulo?

...

> Espacio de usuario o espacio del kernel.

...

> Espacio de datos.

...

> Drivers. Investigar contenido de /dev.

...

### Modulos

que hace esto?

```bash
cd part1
make
sudo insmod mimodulo.ko
sudo dmesg
lsmod | grep mod
```

describir resultado y poner imagen de ejecucion

que hace esto?

```bash
sudo rmmod mimodulo
sudo dmsg
lsmod | grep mod
cat /proc/modules  | grep mod
```

describir resultado y poner imagen de ejecucion

que hace esto?

```bash
modinfo mimodulo.ko 
modinfo /lib/modules/$(uname -r)/kernel/crypto/des_generic.ko
```

describir resultado y poner imagen de ejecucion

> ¿Qué diferencias se pueden observar entre los dos modinfo ? 

...

> ¿Qué divers/modulos estan cargados en sus propias pc?  
> Comparar las salidas con las computadoras de cada integrante del grupo.  
> Expliquen las diferencias.  
> Carguen un txt con la salida de cada integrante en el repo y pongan un diff en el informe.

...

> ¿Cuales no están cargados pero están disponibles?  
> Que pasa cuando el driver de un dispositivo no está disponible. 

...

> Correr hwinfo en una pc real con hw real y agregar la url de la información de hw en el reporte. 

...

> ¿Qué diferencia existe entre un módulo y un programa?

...

> ¿Cómo puede ver una lista de las llamadas al sistema que realiza un simple helloworld en c?

...

> ¿Qué es un segmentation fault?
> ¿Cómo lo maneja el kernel y como lo hace un programa?

...

> Intentar firmar un módulo de kernel y documentar el proceso?

...

> Agregar evidencia de la compilación, carga y descarga de su propio módulo imprimiendo el nombre del equipo en los registros del kernel. 

...

> ¿Que pasa si mi compañero con secure boot habilitado intenta cargar un módulo firmado por mi? 

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
