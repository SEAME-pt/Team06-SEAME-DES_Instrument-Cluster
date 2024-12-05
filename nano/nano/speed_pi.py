from gpiozero import Button
from signal import pause
import time

# Configurações
SENSOR_PIN = 17
RODA_DIAMETRO = 0.065  # Diâmetro da roda em metros
FUROS = 36

# Variáveis globais
pulsos = 0
ultimo_tempo = time.time()

def pulso_detectado():
    global pulsos
    pulsos += 1

def calcular_velocidade(pulsos, tempo):
    voltas = pulsos / FUROS
    distancia = voltas * (RODA_DIAMETRO * 3.14159)  # Distância em metros
    velocidade_ms = distancia / tempo
    velocidade_kmh = velocidade_ms * 3.6
    return velocidade_kmh

# Configuração do sensor
sensor = Button(SENSOR_PIN, pull_up=True)
sensor.when_pressed = pulso_detectado

try:
    print("Aguardando leitura de velocidade. Pressione Ctrl+C para encerrar.")
    while True:
        if time.time() - ultimo_tempo >= 1:
            kmh = calcular_velocidade(pulsos, 1)
            print(f"Velocidade: {kmh:.2f} km/h")
            pulsos = 0
            ultimo_tempo = time.time()
        time.sleep(0.1)  # Reduz o uso da CPU
except KeyboardInterrupt:
    print("Encerrando...")
