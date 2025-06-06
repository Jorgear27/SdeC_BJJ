# Trabajo Práctico N°4: 
## MÓDULOS DE KERNEL Y LLAMADAS A SISTEMA

**Nombres**  
_Jorge A. Arbach_; _Bianca A. Fraga_; _José I. López Sivilat_

**Grupo**: BJJ  
**Universidad Nacional de Córdoba**  
**Sistemas de Computación**

**Fecha**: 19/05/2025

---

### Información de los autores

- **Información de contacto**:  
  _jorge.arbach@mi.unc.edu.ar_;  
  _bianca.fraga@mi.unc.edu.ar_;  
  _jose.lopez.sivilat@mi.unc.edu.ar_.

---

# Introducción

El lenguaje C es poderoso, flexible y esencial en el desarrollo de sistemas operativos. A medida que profundizamos en su aplicación, nos encontramos con la necesidad de interactuar directamente con el núcleo de Linux, el corazón del sistema operativo. Aquí es donde entran en juego los módulos del núcleo: piezas clave que permiten extender sus capacidades sin necesidad de reconstruir y reiniciar el sistema.

En este informe exploraremos qué son los módulos del núcleo, cómo funcionan y por qué son fundamentales en la arquitectura del kernel. Desde los controladores de dispositivos hasta las extensiones de funcionalidad, estos módulos nos permiten adaptar el sistema a nuestras necesidades de manera eficiente y dinámica. Pero con gran poder viene gran responsabilidad: un solo error puede comprometer la estabilidad del sistema. Por eso, comprender su diseño y funcionamiento es esencial para cualquier desarrollador que busque optimizar y expandir el alcance del kernel de Linux.

# Desarrollo

Para el desarrollo y compilación de módulos del núcleo en Linux, es imprescindible contar con un sistema operativo Linux instalado junto con sus fuentes o, al menos, los headers correspondientes. La descarga de estos archivos puede tomar algunos minutos, dependiendo del ancho de banda disponible en la conexión a internet.

En esta primera etapa, trabajaremos con los programas fuente y archivos de configuración (`Makefiles`) necesarios. Para ello, debemos realizar un **fork** del repositorio disponible, seguido de la clonación de nuestra copia del repositorio. Posteriormente, instalaremos las dependencias requeridas para la compilación. A continuación, se detallan los comandos utilizados:

```bash
fork https://gitlab.com/sistemas-de-computacion-unc/kenel-modules.git 
git clone (su propia url… empieza con SU nombre de usuario)
sudo apt-get install build-essential checkinstall kernel-package linux-source
```
Tras ejecutar estos comandos, el sistema descargará y configurará las herramientas necesarias para el desarrollo de módulos del núcleo. 

Este proceso nos proporciona el entorno adecuado para comenzar la implementación del módulo correspondiente dentro de la carpeta `tp4`, asegurando que contamos con todas las herramientas necesarias para su desarrollo y prueba.

## Desafío 1

### _¿Qué es checkinstall y para qué sirve?_

**Checkinstall** es un programa para sistemas operativos tipo _Unix_ que facilita la instalación y desinstalación de software compilado desde el código fuente. Permite que el software instalado desde el código fuente sea gestionado por un sistema de gestión de paquetes, como `apt` o `yum`, haciendo que sea más fácil actualizar o eliminar el software en el futuro. 
En esencia, **Checkinstall** actúa como un puente entre el proceso de compilación de software desde el código fuente y los sistemas de gestión de paquetes. En lugar de simplemente copiar los archivos a su ubicación final, Checkinstall crea un paquete (como un archivo `.deb` o `.rpm`) que luego puede ser instalado y gestionado por el sistema de gestión de paquetes. 

Sus utilidades son:

**1. Facilita la desinstalación:** Permite eliminar el software de manera limpia usando el gestor de paquetes del sistema.

**2. Genera paquetes compartibles:** Se pueden instalar en varias computadoras sin necesidad de recompilar el código.

**3. Mantiene el sistema organizado:** Evita conflictos entre archivos del sistema y software instalado manualmente.

**4. Simplifica actualizaciones:** Permite actualizar el software sin perder el control sobre los archivos instalados.

### _Uso de CheckInstall para la instalación de paquetes_

Para instalar un programa compilado desde código fuente de manera organizada y reversible, seguimos los siguientes pasos con **CheckInstall**:

**1. Compilación del programa:** ejecutamos los comandos habituales para compilar el código fuente:

```bash
./configure
make
```
**2. Instalación con Chekinstall:** en lugar de `make install`, utilizamos:

```bash
sudo chekinstall
```

**3. Creación de documentación:** `checkInstall` nos preguntará si queremos crear un directorio para almacenar documentación relevante para el paquete. Aceptamos ingresando `y` (Sí) y continuamos.

**4. Descripción del paquete:** luego, se nos solicitará ingresar una descripción breve del paquete, la cual aparecerá en el campo **Resumen** cuando se consulte la información del paquete.

**5. Confirmación de detalles y configuración de dependencias:** en la última pantalla, CheckInstall mostrará un resumen con todos los detalles del paquete antes de su creación. Aquí, podemos establecer **dependencias**, es decir, otros paquetes que el software necesita para funcionar correctamente.
Para definir dependencias, se pueden agregar manualmente en el campo correspondiente o utilizar la opción  --requires` en la línea de comandos. Por ejemplo:

```bash
sudo chekinstall --requires="libc6, libncurses5"
```
Esto asegura que el paquete generado indique que necesita `libc6` y `libncurses5` para su correcto funcionamiento.

Una vez completado el proceso, el paquete estará listo para ser instalado y administrado con el gestor de paquetes del sistema.

### _Uso de checkinstall para empaquetar un hello world_

Este informe describe el proceso de empaquetado de un programa simple en C, utilizando `checkinstall` para generar un paquete `.deb`. El objetivo es instalar el programa de manera organizada, permitiendo su fácil administración y desinstalación.

En primer lugar, se creó un archivo llamado `helloWorld.c` con un programa básico que imprime un mensaje en la consola:

![Figura 1](imagenes/Figura1.jpeg)

Luego, para automatizar la compilación e instalación, se creó un `Makefile` con las siguientes reglas:

![Figura 2](imagenes/Figura2.jpeg)

Este archivo permite compilar (`make`), instalar (`make install`) y limpiar (`make clean`) el programa. 

Para empaquetar el programa **Hello World** utilizando `checkinstall`, primero se compila el código fuente con `make`, lo que genera el ejecutable `helloWorld`. Luego, en lugar de instalarlo manualmente, se usa `checkinstall`, que crea un paquete `.deb` compatible con sistemas **Debian/Ubuntu**. Durante el proceso, se solicita una descripción del paquete y se generan archivos importantes, como `description-pak`, que contiene información del programa, y el `.deb`, que facilita su instalación y gestión.

Una vez generado el paquete, se instala con `dpkg -i`, permitiendo que el programa pueda ejecutarse desde cualquier ubicación en la terminal. Si en algún momento es necesario desinstalarlo, `dpkg -r` elimina el paquete sin dejar archivos residuales en el sistema. A continuación, se muestran las figuras comprobando lo que se explicó anteriormente: 

![Figura 3](imagenes/Figura3.jpeg)

![Figura 4](imagenes/Figura4.jpeg)


