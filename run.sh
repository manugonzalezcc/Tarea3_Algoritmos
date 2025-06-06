#!/bin/bash

if [ "$#" -lt 1 ]; then
  echo "Uso: ./run.sh -f <archivo> --algoritmo --pattern <palabra>"
  echo "Ejemplo: ./run.sh -f docs/doc1.html --kmp --pattern documento"
  exit 1
fi

# Ejecuta desde el directorio raíz del proyecto
./build/program "$@"
