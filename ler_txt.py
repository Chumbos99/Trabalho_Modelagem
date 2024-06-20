import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt


def ler_dados_arquivo(nome_arquivo):
    """ Função para ler dados do arquivo de texto """
    with open(nome_arquivo, 'r') as arquivo:
        linha = arquivo.readline()
        # Dividir a linha em valores, ignorar o primeiro número e converter os restantes para float
        return np.array([float(valor) for valor in linha.split()])


pontos = ler_dados_arquivo('dados_arduino.txt')
pontos -= pontos[0]
# Passo entre os pontos
passo = 0.733
tempos = np.arange(0, len(pontos) * passo, passo)
tempos = tempos[0: len(pontos)]

k = pontos[-1]


def superamortecida(t, T):
    """ Função que representa a resposta ao degrau unitário """
    return k*(1-np.exp(-t/T))


# Ajuste da curva
popt, pcov = curve_fit(superamortecida, tempos, pontos)
T, = popt

print(f'k: {k}')
print(f'T: {T}')

# Plotagem para visualizar o ajuste
plt.scatter(tempos, pontos, label='Dados')
plt.plot(tempos, superamortecida(tempos, *popt), label='Ajuste', color='red')
plt.xlabel('Tempo (s)')
plt.ylabel('Resposta')
plt.legend()
plt.show()