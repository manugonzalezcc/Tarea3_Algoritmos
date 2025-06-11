import pandas as pd
import matplotlib.pyplot as plt

bm = pd.read_csv("resultados_bm.csv")
kmp = pd.read_csv("resultados_kmp.csv")
shift = pd.read_csv("resultados_shiftand.csv")

df = pd.concat([bm, kmp, shift], ignore_index=True)

patrones = df['patron'].unique()
algoritmos = df['algoritmo'].unique()

metricas = ['comparaciones', 'accesos_memoria', 'tiempo_ms']
titulos = {
    'comparaciones': 'Comparaciones por Algoritmo y Patrón',
    'accesos_memoria': 'Accesos a Memoria por Algoritmo y Patrón',
    'tiempo_ms': 'Tiempo de Ejecución (ms) por Algoritmo y Patrón'
}
colores = {
    'boyermoore': 'red',
    'kmp': 'blue',
    'shiftand': 'green'
}

for metrica in metricas:
    plt.figure(figsize=(10, 6))
    for algoritmo in algoritmos:
        df_alg = df[df['algoritmo'] == algoritmo]
        valores = []
        for patron in patrones:
            valor = df_alg[df_alg['patron'] == patron][metrica].values
            valores.append(valor[0] if len(valor) > 0 else 0)
        plt.plot(patrones, valores, label=algoritmo, color=colores[algoritmo], marker='o')

    plt.title(titulos[metrica])
    plt.xlabel('Patrón')
    plt.ylabel(metrica.replace("_", " ").capitalize())
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"grafico_{metrica}.png")
    plt.show()
