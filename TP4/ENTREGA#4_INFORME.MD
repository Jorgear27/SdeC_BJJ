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
