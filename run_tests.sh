#!/usr/bin/env bash
# =========================================================
#  run_tests.sh – Test suite completo para el motor de búsqueda
# =========================================================
# Requiere bash 4+.  Asegúrate de dar permisos: chmod +x run_tests.sh
# Ejecuta cada prueba y muestra ✔ (verde) o ✘ (rojo) según corresponda.
# El script finaliza con código de salida 0 si TODO pasa.
# =========================================================

set -e                      # Salir si un comando devuelve error
shopt -s expand_aliases
alias color="sed -e 's/\x1b\[[0-9;]*m//g'"   # Para contar líneas sin escapes

RED="\e[31m"; GREEN="\e[32m"; YELLOW="\e[33m"; RESET="\e[0m"

pass() { echo -e "${GREEN}✔ $1${RESET}"; }
fail() { echo -e "${RED}✘ $1${RESET}"; exit 1; }

# ---------------------------------------------------------
echo -e "${YELLOW}==> 1. Compilación limpia${RESET}"
make clean >/dev/null 2>&1
CFLAGS="-Wall -Wextra -O2" make >/dev/null
pass "Compilación exitosa con -Wall -Wextra -O2"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 2. Limpieza de artefactos previos${RESET}"
rm -f docs/*.idx resultados_*.csv
pass "Borrados .idx y .csv anteriores"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 3. Búsqueda exacta (--in) y generación de índice${RESET}"
./build/program -f docs/doc2.html --in sistema | color
[[ -f docs/doc2.html.idx ]] && pass ".idx generado en primera búsqueda" || fail ".idx no generado"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 4. Reutilización de índice (segunda ejecución rápida)${RESET}"
start=$(date +%s%N)
./build/program -f docs/doc2.html --in sistema >/dev/null
end=$(date +%s%N)
elapsed_ms=$(( (end - start)/1000000 ))
[[ $elapsed_ms -lt 10 ]] && pass "Búsqueda usando índice en ${elapsed_ms} ms" || fail "Búsqueda tardó demasiado (${elapsed_ms} ms)"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 5. Algoritmo KMP + CSV${RESET}"
./build/program -f docs/doc2.html --kmp --word sistema | color
[[ -s resultados_kmp.csv ]] && lines=$(grep -c '^' resultados_kmp.csv) && \
     [[ $lines -ge 2 ]] && pass "resultados_kmp.csv creado (líneas=$lines)" \
                        || fail "CSV KMP vacío" \
  || fail "CSV KMP no encontrado"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 6. Algoritmo Boyer-Moore + CSV${RESET}"
./build/program -f docs/doc2.html --bm --pattern "texto" | color
[[ -s resultados_bm.csv ]] && lines=$(grep -c '^' resultados_bm.csv) && \
     [[ $lines -ge 2 ]] && pass "resultados_bm.csv creado (líneas=$lines)" \
                        || fail "CSV BM vacío" \
  || fail "CSV BM no encontrado"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 7. Algoritmo Shift-And + CSV${RESET}"
./build/program -f docs/doc2.html --algoritmo3 --pattern "texto" | color
[[ -s resultados_shiftand.csv ]] && lines=$(grep -c '^' resultados_shiftand.csv) && \
     [[ $lines -ge 2 ]] && pass "resultados_shiftand.csv creado (líneas=$lines)" \
                        || fail "CSV Shift-And vacío" \
  || fail "CSV Shift-And no encontrado"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 8. Búsqueda tolerante (--proximity)${RESET}"
./build/program -f docs/doc2.html --proximity sistem --tolerance 1 | color | grep -q "Total de palabras similares" \
  && pass "Proximidad OK" || fail "Proximidad no devolvió resultado esperado"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 9. Top palabras (--detect)${RESET}"
./build/program -f docs/doc2.html --detect | color | grep -q "Frecuencia" \
  && pass "--detect muestra tabla" || fail "--detect falló"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 10. Comparación de documentos (--compare)${RESET}"
cmp_out=$(./build/program --compare docs/doc1.html docs/doc2.html | color)
echo "$cmp_out" | grep -q "Similitud:" && pass "Comparación OK" || fail "Comparación falló"

# ---------------------------------------------------------
echo -e "${YELLOW}\n==> 11. Manejo de errores CLI${RESET}"
./build/program -f docs/doc2.html --bm >/dev/null 2>&1 && fail "CLI no detectó falta de patrón" || pass "Error detectado sin patrón"
./build/program -f docs/doc2.html --pattern >/dev/null 2>&1 && fail "CLI no exigió argumento" || pass "Error de argumento faltante detectado"

# ---------------------------------------------------------
echo -e "${GREEN}\n========================="
echo    "   ¡TODAS LAS PRUEBAS PASARON! "
echo -e "=========================${RESET}"
exit 0
