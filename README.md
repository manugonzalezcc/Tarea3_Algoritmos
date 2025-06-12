# Tarea 3 - Algoritmos 💻

**Grupo 3**  
- Diego Sanhueza  
- Claudio Matulich  
- Manuel González  

---

## Descripción del Proyecto 🤔

En este proyecto, implementamos y analizamos algoritmos de procesamiento de texto y búsqueda de patrones. El objetivo es desarrollar un sistema eficiente capaz de:

- Indexar grandes volúmenes de texto  
- Realizar búsquedas rápidas y precisas dentro de documentos  
- Analizar textos para extraer información relevante  

Además, evaluamos el rendimiento de los algoritmos implementados para entender su eficiencia y aplicabilidad en contextos reales.

---

## 📁 Contenido del Repositorio

- Implementaciones de algoritmos de búsqueda y procesamiento de texto  
- Scripts para pruebas y evaluación de rendimiento  
- Archivos de documentación y ayuda  

---

## 🚀 Cómo Ejecutar el Programa

### Compilación ⚙️

- Antes de ejecutar el proyecto, debemos compilarlo, para ello debemos usar el comando:

```bash
make
```

### Interfaz de ayuda 💻

- Podemos ver todas las opciones disponibles ejecutando el comando:

```bash
make run
```

### 1️⃣ Dar permisos de ejecución (una sola vez)

Antes de ejecutar el programa, se debe otorgar permisos a los scripts:

```bash
chmod +x run.sh
chmod +x run_tests.sh  
```

### 2️⃣ Ejecutar el programa con opciones

El comando base para ejecutar el programa es:

```bash
./run.sh [opciones]
```

---

## 🧪 Ejemplo de Uso

```bash
./run.sh -f docs/doc1.html --kmp --pattern "algoritmo eficiente"
```

🔍 Este comando busca el patrón `"algoritmo eficiente"` usando el algoritmo **Knuth-Morris-Pratt** en el archivo `doc1.html`.

---

## 🧾 Opciones Disponibles

| Comando | Descripción |
|--------|-------------|
| `-f <archivo> --in <palabra>` | Detecta si la palabra está en el texto. |
| `-f <archivo> --kmp --word <palabra>` | Busca una palabra exacta con el algoritmo especificado. |
| `-f <archivo> --(kmp|bm|shift_and) --pattern "<patrón>"` | Busca un patrón en el texto (usar comillas dobles). |
| `--compare <archivo1> <archivo2>` | Compara el contenido de dos documentos. |
| `-f <archivo> --detect` | Detecta palabras clave dentro del archivo. |
| `-f <archivo> --proximity <palabra> --tolerance <n>` | Busca palabras cercanas con margen de error (proximidad). |
| `-f <archivo> --index` | Muestra el índice invertido del archivo. |
| `--ranking <palabra>` | Muestra un ranking de relevancia según la palabra ingresada en documentos de `docs/`. |
| `-h`, `--help` | Muestra esta ayuda del sistema. |

---