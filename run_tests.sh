#!/bin/bash

# Configuración del archivo y patrón
ARCHIVO="docs/doc2.html"
PATRON="texto"

# Verifica que el archivo exista
if [ ! -f "$ARCHIVO" ]; then
  echo "Error: No se encuentra el archivo $ARCHIVO"
  exit 1
fi

echo "===== PRUEBAS AUTOMÁTICAS ====="
echo "Archivo: $ARCHIVO"
echo "Patrón: $PATRON"
echo ""

echo "➡️  Ejecutando KMP..."
./build/program -f "$ARCHIVO" --kmp --pattern "$PATRON"
echo ""

echo "➡️  Ejecutando Boyer-Moore..."
./build/program -f "$ARCHIVO" --bm --pattern "$PATRON"
echo ""

echo "➡️  Ejecutando Shift-And..."
./build/program -f "$ARCHIVO" --algoritmo3 --pattern "$PATRON"
echo ""

echo "✅ Pruebas completadas. Resultados guardados en:"
echo "  - resultados_kmp.csv"
echo "  - resultados_bm.csv"
echo "  - resultados_shiftand.csv"
