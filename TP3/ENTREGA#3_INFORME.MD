# Trabajo Práctico N°3: 
## MODO PROTEGIDO

**Nombres**  
_Jorge A. Arbach_; _Bianca A. Fraga_; _José I. López Sivilat_

**Grupo**: BJJ  
**Universidad Nacional de Córdoba**  
**Sistemas de Computación**

**Fecha**: 28/04/2025

---

### Información de los autores

- **Información de contacto**:  
  _jorge.arbach@mi.unc.edu.ar_;  
  _bianca.fraga@mi.unc.edu.ar_;  
  _jose.lopez.sivilat@mi.unc.edu.ar_.

---

# Introducción

Los procesadores x86 presentan una evolución en su forma de operar. Inicialmente trabajaban en **modo real**, donde las direcciones de memoria eran gestionadas de forma sencilla pero limitada. Con la introducción del **modo protegido**, se incorporaron mejoras fundamentales para la gestión de la memoria, la protección entre procesos y la posibilidad de trabajar con multitarea de forma más segura. Este modo introduce conceptos avanzados como segmentación, paginación y privilegios de ejecución, fundamentales en los sistemas modernos.

En este trabajo práctico se explorarán los conceptos asociados al modo protegido, respondiendo una serie de preguntas para afianzar los conocimientos teóricos.

---

# DESARROLLO

En primer lugar, debimos clonar un repositorio e iniciar los submódulos, tal como lo indica el README de dicho repositorio:

https://gitlab.com/sistemas-de-computacion-2021/protected-mode-sdc

Al ingresar a dicho enlace, nos encontramos con tres comandos a seguir:

```
git clone (url of this repo)
git submodule init
git submodule update
```
Y obtuvimos como resultado, lo siguiente: 

![Figura 1](imagen/Figura1.jpeg)

A continuación, se explica lo que significa cada comando:

* `git clone:` Descarga un repositorio completo desde una URL remota.
* `git submodule init:` Inicializa los submódulos en el repositorio. Los submódulos en Git son repositorios dentro de otros repositorios. A veces, un proyecto principal depende de otros proyectos más pequeños o módulos.
* `git submodule update:` Actualiza los submódulos a la última versión. Esto descargará los cambios más recientes en los submódulos y los vinculará correctamente al proyecto principal.

En la presentación de clase, tenemos el paso a paso de cómo hacer un **MBR (Master Boot Record)** con la creación de una imagen de disco con una instrucción `hlt`, tal como se muestra a continuación:

![Figura 2](imagen/Figura2.jpeg)

Los comandos que se observan en la imagen anterior, tienen el siguiente significado:

```
# Crear un archivo llamado main.img y escribir una secuencia específica de bytes
printf '\364%509s\125\252' > main.img

Donde:

* `\364` en octal es equivalente a `0xf4` en hexadecimal, que representa la instrucción `hlt` en lenguaje ensamblador. La instrucción `hlt` detiene la ejecución del procesador.
* `%509s` producir 509 espacios en blanco. Esto es necesario para completar la imagen hasta el byte 510. Siendo que desde el byte 510 hasta el 511, es donde se almacena la firma de arranque.
* `\125\252` en octal es equivalente a `0x55 0xAA` en hexadecimal. Estos valores son requisitos para que la imagen sea interpretada como un registro maestro de arranque (MBR) válido.

# Crear un archivo llamado a.S y escribir la instrucción "hlt" en él
echo hlt > a.S

# Ensamblar el archivo a.S y generar un archivo objeto llamado a.o
as -o a.o a.S

# Desensamblar el archivo objeto a.o y mostrar el código ensamblador original
objdump -S a.o

# Mostrar el contenido hexadecimal del archivo main.img
hd main.img
``` 

## OBJETIVOS

1. Correr la imagen: Instalar y correr qemu con la imagen en cuestión

```
sudo apt install qemu-system-x86
qemu-system-x86_64 --drive file=main.img,format=raw,index=0,media=disk`
```


## Preguntas y Respuestas

### 1. ¿Qué diferencia principal existe entre el modo real y el modo protegido?

En **modo real**, el procesador puede acceder directamente a un espacio de memoria de hasta 1 MB, utilizando un direccionamiento basado en segmentos de 16 bits. No existen mecanismos de protección entre procesos, lo que permite que cualquier programa pueda sobrescribir memoria ajena.

En **modo protegido**, en cambio, se introduce un esquema de gestión de memoria más robusto, donde:
- Se pueden direccionar hasta 4 GB de memoria mediante registros de 32 bits.
- Se implementan niveles de privilegio (rings) para proteger el acceso a la memoria y los recursos del sistema.
- Se utilizan estructuras como la **GDT** (Global Descriptor Table) para definir segmentos y sus permisos.

### 2. ¿Qué estructuras principales maneja el modo protegido para la administración de memoria?

Las estructuras principales son:
- **GDT (Global Descriptor Table)**: define segmentos globales para todo el sistema.
- **LDT (Local Descriptor Table)**: define segmentos específicos para cada proceso.
- **PDT (Page Directory Table)** y **Page Tables**: usadas en la paginación de memoria virtual.

Estas estructuras permiten separar de manera lógica y segura los espacios de memoria para cada proceso.

### 3. ¿Qué es la GDT y para qué sirve?

La **GDT** es una tabla que contiene descriptores de segmentos. Cada descriptor define un segmento con:
- Su dirección base.
- Su tamaño (límite).
- Sus atributos de acceso (lectura, escritura, ejecución, nivel de privilegio).

El procesador utiliza la GDT para validar los accesos a memoria y asegurar que cada programa trabaje en su espacio de direcciones asignado.

### 4. ¿Cómo se identifica en el procesador que se está trabajando en modo protegido?

Se identifica a través del bit **PE (Protection Enable)** ubicado en el registro **CR0**. Cuando este bit está activo, el procesador interpreta las instrucciones y la memoria de acuerdo con las reglas del modo protegido.

### 5. ¿Qué sucede si se intenta acceder a un segmento de memoria de manera no autorizada en modo protegido?

El procesador genera una excepción o "fault". Estas excepciones son manejadas a través de un sistema de interrupciones, donde un manejador específico (generalmente definido en la IDT) se encarga de gestionar el error de acceso, que puede llevar a terminar el proceso que lo causó o intentar una recuperación controlada.

---

# Desafíos

## 1. UEFI y Coreboot

### ¿Qué es UEFI? ¿Cómo puedo usarlo? Función de ejemplo.

La **Unified Extensible Firmware Interface (UEFI)** es una especificación que define una interfaz entre el sistema operativo y el firmware. UEFI reemplaza la antigua BIOS tradicional, soporta particiones GPT, es independiente de la arquitectura de CPU y ofrece una interfaz gráfica amigable.

Para usar UEFI, se necesita:
- Una placa base compatible con UEFI.
- Un sistema operativo moderno compatible con UEFI.

**Pasos para acceder al firmware UEFI:**
- Encender la computadora y presionar una tecla específica (F2, F10, F12, Esc o Supr) para entrar en el menú de configuración.
- Acceder a la sección de configuración del firmware UEFI.
- Explorar opciones de arranque, seguridad, gestión de dispositivos, entre otros.

**Función de ejemplo**: Desde UEFI se podría llamar a una función de arranque seguro (**Secure Boot**) para validar firmas de los sistemas operativos.

### ¿Casos de bugs de UEFI explotables?

Se han detectado vulnerabilidades críticas en implementaciones UEFI. Un ejemplo es el bug denominado **SMM Callout (Privilege Escalation)**, donde código malicioso puede aprovechar el modo de gestión del sistema (SMM) para ejecutar instrucciones no autorizadas con el máximo privilegio. Esto puede eludir medidas de seguridad e instalar malware persistente que sobreviva reinstalaciones del sistema operativo.

### ¿Qué es CSME y MEBx?

- **CSME (Converged Security and Management Engine)**:  
  Es un controlador basado en hardware aislado de la CPU. Se encarga de:
  - Inicialización de silicio.
  - Administración remota y local del sistema.
  - Funciones de seguridad como autenticación de firmware y protección de claves.

- **Intel MEBx (Management Engine BIOS Extension)**:  
  Es una extensión de BIOS que permite configurar opciones de la Intel Management Engine, como seguridad, administración de energía y conectividad para administración remota.

### ¿Qué es Coreboot? ¿Qué productos lo incorporan? ¿Ventajas?

**Coreboot** (antes llamado LinuxBIOS) es un proyecto dirigido a reemplazar el firmware no libre de los BIOS propietarios, encontrados en la mayoría de los computadores, por un BIOS libre y ligero diseñado para realizar solamente el mínimo de tareas necesarias para cargar y correr un sistema operativo moderno de 32 bits o de 64 bits. 

Se integra en una variedad de productos, incluyendo computadoras portátiles, de escritorio, servidores y dispositivos embebidos, especialmente en _Chromebooks_ y otros productos de ChromeOS. También se utiliza en proyectos como _Libreboot_ y en algunas placas base de hardware libre.

**Productos que incorporan Coreboot**

* Dispositivos ChromeOS: todos los Chromebooks, Chromeboxes, Chromebits, etc., desde 2012. 
* Computadoras portátiles y de escritorio: algunas marcas como System76, StarLabs y Librem ofrecen opciones con Coreboot. 
* Placas base: ofrece soporte para algunas placas base de marca como Asus, Asrock, Gigabyte, MSI, entre otras. 
* Servidores: coreboot se utiliza para reducir el tiempo de arranque en servidores. 
* Dispositivos embebidos: también se puede utilizar en dispositivos con arquitecturas como ARM, ARM64 y RISC-V, así como en plataformas de software en un chip.

**Ventajas de su utilización**:
- Transparencia total: código abierto y auditable.
- Control sobre el hardware, sin restricciones de proveedores.
- Mayor seguridad y privacidad.
- Personalización flexible.

**Productos que lo incorporan**: Algunas Chromebooks, servidores de alta seguridad, y laptops de marcas especializadas en hardware libre como System76 o Purism.

---

## 2. Linker

### ¿Qué es un linker? ¿Qué hace?

Un **linker** es una herramienta utilizada para unir múltiples archivos objeto (.o) en un solo archivo ejecutable o en una biblioteca compartida. Su función principal es:
- Combinar archivos objeto.
- Resolver referencias cruzadas entre funciones y variables.

### ¿Qué es la dirección que aparece en el script del linker? ¿Por qué es necesaria?

En el script del linker suele aparecer la dirección **0x7C00**.  
Esta dirección es fundamental porque:
- El BIOS carga el primer sector de arranque de un disco exactamente en **0x7C00**.
- El código debe estar ubicado ahí para que, al encender el sistema, el BIOS transfiera correctamente el control de ejecución al cargador de arranque.

Si no se especifica correctamente esta dirección, el sistema no podrá arrancar de manera esperada.

---

# Conclusiones

El modo protegido representó un salto cualitativo en la arquitectura de los procesadores x86, permitiendo la implementación de sistemas operativos multitarea y seguros. Gracias a sus mecanismos de segmentación, paginación y control de privilegios, se logró una administración más eficiente y confiable de los recursos del sistema, sentando las bases de la computación moderna.

Asimismo, comprender el funcionamiento de tecnologías como UEFI, CSME y Coreboot, así como los procesos de linking a bajo nivel, resulta indispensable para entender el funcionamiento interno de los sistemas actuales y garantizar su seguridad y correcto desempeño.


