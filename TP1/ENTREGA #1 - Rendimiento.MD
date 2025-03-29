# Trabajo Práctico N°1: 
## Parte I - RENDIMIENTO

**Nombres**  
_Jorge A. Arbach_; _Bianca A. Fraga_;  _José López_.


**Grupo**: BJJ
**Universidad Nacional de Córdoba**  
**Sistemas de Computación**

**Fecha** 17/03/2025   

---

### Información de los autores
 
- **Información de contacto**: _jorge.arbach@mi.unc.edu.ar_; 
_bianca.fraga@mi.unc.edu.ar_;
_jose.lopez.sivilat@mi.unc.edu.ar_;

---

# Introducción

El siguiente informe tiene como objetivo analizar y responder una serie de preguntas relacionadas con el uso de benchmarks y el rendimiento de procesadores en tareas específicas. A través de este análisis, se busca comprender cómo los benchmarks pueden ser herramientas útiles para medir y optimizar las tareas diarias, así como evaluar el desempeño de diferentes procesadores en la compilación del kernel de Linux. Además, se incluirán capturas de pantalla como evidencia de la realización del tutorial de **time profiling**, junto con las conclusiones obtenidas sobre el uso del tiempo en las funciones. 

# Desarrollo

## Benchmarks
### 1. Lista de Benchmarks

Para evaluar el rendimiento del sistema en función de las tareas que realizamos a diario, podemos considerar los siguientes benchmarks:  

#### **Benchmarks Útiles para el Desarrollo de Software (Compilación, Testing, Cobertura, Profiling, etc.)**  
- **Phoronix Test Suite** – Suite de pruebas para desarrollo.  
- **Clang-Bench y GCC Compile Bench** – Medición de tiempos de compilación.  
- **Valgrind & Heaptrack** – Análisis de memoria y detección de fugas.  

#### **Benchmarks Útiles para Redes y Comunicación (Sockets, Latencia, Transferencia de Datos, etc.)**  
- **iperf3** – Medición de ancho de banda y latencia de red.  
- **Netperf** – Evaluación del rendimiento de TCP y UDP.  

#### **Benchmarks Útiles para Servidores y Procesamiento de Datos**  
- **Sysbench** – Evaluación de CPU, memoria y bases de datos.  
- **fio** – Benchmark de almacenamiento (lectura/escritura en disco).  

#### **Benchmarks Útiles para Gaming y Gráficos**  
- **3DMark** – Mide rendimiento gráfico y de CPU en juegos.  
- **MSI Afterburner & CapFrameX** – Monitoreo de FPS y latencias en juegos.  
- **Cinebench R23** – Prueba de CPU en renderizado 3D.  
- **PugetBench for Adobe Suite** – Benchmark para edición de video y diseño gráfico.  

#### **Benchmarks Útiles para el Uso Cotidiano y Productividad**  
- **PCMark 10 (Productivity)** – Evalúa tareas de oficina como Office, navegación y multitarea.  
- **UL Procyon Office Benchmark** – Mide rendimiento en Microsoft Office (Word, Excel, PowerPoint).  
- **Speedometer 2.0** – Benchmark para evaluar la rapidez de navegación web.  
- **MotionMark** – Evalúa el rendimiento gráfico en navegadores.  
- **YouTube Playback Benchmark** – Mide rendimiento en reproducción de video.  

### 2. Benchmarks para el día a día

| **Tarea**                                    | **Benchmark Adecuado**                     |  
|----------------------------------------------|--------------------------------------------|  
| **Redes y Comunicación**                     |                                            |  
| Simulación de tráfico y carga en la red      | Pktgen, Netperf                           |  
| **Servidores y Almacenamiento**              |                                            |  
| Rendimiento de almacenamiento en disco       | fio, SPEC Storage, CrystalDiskMark        |  
| **Gaming y Gráficos**                        |                                            |  
| Evaluación de rendimiento en videojuegos     | 3DMark, Unigine Superposition, GFXBench   |  
| Medición de FPS y latencias en juegos        | MSI Afterburner, CapFrameX                |  
| **Renderizado y Diseño 3D**                  |                                            |  
| Edición de video y gráficos                  | PugetBench for Adobe Suite                |  
| **Uso Cotidiano y Productividad**            |                                            |  
| Rendimiento en Microsoft Office (Word, Excel, PowerPoint) | PCMark 10 (Productivity), UL Procyon Office Benchmark |  
| Navegación web (Chrome, Edge, Firefox)       | Speedometer 2.0, JetStream 2, MotionMark  |  
| Multitarea y aplicaciones de oficina         | PCMark 10 (Digital Content Creation)      |  
| Reproducción de video y streaming            | UL Procyon Video Editing, YouTube Playback Benchmark |  
| Consumo energético y autonomía de batería    | MobileMark 25, SPEC Power                 |  

### 3. Rendimiento de los Procesadores para Compilar el Kernel de Linux  

El rendimiento de un sistema es la capacidad que tiene este para realizar la tarea en un determinado tiempo, por lo tanto es necesario contar con los tiempos de ejecución de la tarea para poder calcularlo.

Usando los datos proporcionados en el enlace de referencia [1] y teniendo en cuenta que nos vamos a valer del rendimiento absoluto para calcular la aceleración o speedup:

$$ \text{Rendimiento} = \frac{1}{T} $$

Podemos armar la siguiente tabla:


| Procesador          | Tiempo (s) | Rendimiento absoluto (1/s) |
|---------------------|------------|--------------------|
| Intel i5-13600K    | 83 ± 3     | 0.012             |
| AMD Ryzen 9 5900X  | 97 ± 6     | 0.010             |
| AMD Ryzen 9 7950X  | 53 ± 3     | 0.019             |


Para calcular la aceleración del **AMD Ryzen 9 7950X 16-Core** en comparación con los otros procesadores, usamos la fórmula:  

$$ \text{Speedup} = \frac{Rendimiento Mejorado}{Rendimiento Base} $$

Y como sabemos que el rendimiento, en cuanto a tiempo de compilación, del procesador Ryzen 9 7950X es el mayor de los tres, la fórmula adquiere la siguiente expresión:

$$ \text{Speedup} = \frac{R_{\text{Ryzen 9 7950X}}}{R_{\text{procesador base}}} $$

o, análogamente: 

$$ \text{Speedup} = \frac{T_{\text{procesador base}}}{T_{\text{Ryzen 9 7950X}}} $$

#### **Comparación con Intel Core i5-13600K**  

$$ \text{Speedup} = \frac{83}{53} = 1.566 $$

#### **Comparación con AMD Ryzen 9 5900X**  

$$ \text{Speedup} = \frac{97}{53} = 1.830 $$


#### 4. Aceleración del AMD Ryzen 9 7950X 16-Core  

- El **Ryzen 9 7950X** es aproximadamente **1.57 veces más rápido** que el **i5-13600K** y **1.83 veces más rápido** que el **Ryzen 9 5900X** al compilar el kernel de Linux.  
- Su eficiencia energética (rendimiento por watt) también es la más alta, lo que lo hace más adecuado para tareas intensivas como compilación y servidores.  
- Su balance entre rendimiento y eficiencia refuerza su posición como uno de los procesadores más competitivos para tareas de alto consumo computacional, demostrando ser una inversión sólida tanto en términos de velocidad como de economía de energía.
