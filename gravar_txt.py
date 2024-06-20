import serial
import time

# Configure a porta serial (ajuste 'COM3' para a porta correta no seu sistema)
ser = serial.Serial('COM5', 9600)
time.sleep(2)  # Aguarde 2 segundos para estabilizar a conexão

# Nome do arquivo para salvar os dados
filename = 'dados_arduino.txt'

try:
    with open(filename, 'a') as file:
        while True:
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8').strip()
                print(data)
                file.write(data + " ")
except KeyboardInterrupt:
    print("Interrupção pelo usuário. Finalizando...")
except Exception as e:
    print(f"Ocorreu um erro: {e}")
finally:
    ser.close()
