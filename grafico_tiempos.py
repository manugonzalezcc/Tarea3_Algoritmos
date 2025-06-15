# grafico_comparativo.py
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Cargar los CSV
kmp = pd.read_csv('resultados_kmp.csv')
bm = pd.read_csv('resultados_bm.csv')
sa = pd.read_csv('resultados_shiftand.csv')

# Encontrar patrones comunes
patrones_kmp = set(kmp['patron'])
patrones_bm = set(bm['patron'])
patrones_sa = set(sa['patron'])
patrones_comunes = sorted(list(patrones_kmp & patrones_bm & patrones_sa))

# Selecciona solo los patrones más representativos (máx 5 para claridad)
if len(patrones_comunes) > 5:
    patrones_comunes = patrones_comunes[:5]

# Prepara los datos
def mean_metric(df, patrones, columna):
    return [df[df['patron'] == p][columna].mean() for p in patrones]

tiempos = {
    'KMP': mean_metric(kmp, patrones_comunes, 'tiempo_ms'),
    'Boyer-Moore': mean_metric(bm, patrones_comunes, 'tiempo_ms'),
    'Shift-And': mean_metric(sa, patrones_comunes, 'tiempo_ms')
}
comparaciones = {
    'KMP': mean_metric(kmp, patrones_comunes, 'comparaciones'),
    'Boyer-Moore': mean_metric(bm, patrones_comunes, 'comparaciones'),
    'Shift-And': mean_metric(sa, patrones_comunes, 'comparaciones')
}

x = np.arange(len(patrones_comunes))
width = 0.25

# Gráfico de tiempo de ejecución
fig, ax = plt.subplots(figsize=(8,5))
ax.bar(x - width, tiempos['KMP'], width, label='KMP')
ax.bar(x, tiempos['Boyer-Moore'], width, label='Boyer-Moore')
ax.bar(x + width, tiempos['Shift-And'], width, label='Shift-And')
ax.set_ylabel('Tiempo de ejecución (ms)')
ax.set_xlabel('Patrón')
ax.set_title('Comparación de tiempo de ejecución')
ax.set_xticks(x)
ax.set_xticklabels(patrones_comunes, rotation=30)
ax.legend()
plt.tight_layout()
plt.savefig('tiempos_algoritmos.png', dpi=300)
plt.close()

# Gráfico de comparaciones
fig, ax = plt.subplots(figsize=(8,5))
ax.bar(x - width, comparaciones['KMP'], width, label='KMP')
ax.bar(x, comparaciones['Boyer-Moore'], width, label='Boyer-Moore')
ax.bar(x + width, comparaciones['Shift-And'], width, label='Shift-And')
ax.set_ylabel('Comparaciones')
ax.set_xlabel('Patrón')
ax.set_title('Comparación de número de comparaciones')
ax.set_xticks(x)
ax.set_xticklabels(patrones_comunes, rotation=30)
ax.legend()
plt.tight_layout()
plt.savefig('comparaciones_algoritmos.png', dpi=300)
plt.close()