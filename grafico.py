import pandas as pd
import matplotlib.pyplot as plt

kmp = pd.read_csv('resultados_kmp.csv')
bm = pd.read_csv('resultados_bm.csv')
sa = pd.read_csv('resultados_shiftand.csv')

kmp_group = kmp.groupby('archivo')['tiempo_ms'].mean()
bm_group = bm.groupby('archivo')['tiempo_ms'].mean()
sa_group = sa.groupby('archivo')['tiempo_ms'].mean()

archivos = kmp_group.index 

plt.plot(archivos, kmp_group.values, marker='o', label='KMP')
plt.plot(archivos, bm_group.values, marker='o', label='Boyer-Moore')
plt.plot(archivos, sa_group.values, marker='o', label='Shift-And')

plt.xlabel('Archivo')
plt.ylabel('Tiempo de ejecución (ms)')
plt.title('Evolución del tiempo de ejecución según el archivo')
plt.legend()
plt.xticks(rotation=30)
plt.tight_layout()
plt.savefig('evolucion_tiempo.png', dpi=300)
plt.show()