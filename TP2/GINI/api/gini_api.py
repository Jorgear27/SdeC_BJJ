import requests
import json
import subprocess

def obtener_gini(pais="ARG"):
    url = f"https://api.worldbank.org/v2/en/country/{pais}/indicator/SI.POV.GINI?format=json&date=2011:2020&per_page=500&page=1"
    response = requests.get(url)
    data = response.json()
    
    # Buscar el primer valor no nulo
    for item in data[1]:
        if item['value'] is not None:
            gini = item['value']
            break
    
    print(f"GINI recibido: {gini}")
    # Llamada al programa en C
    resultado = subprocess.run(
        ["../build/calcular_gini", str(gini)],
        capture_output=True,
        text=True
    )
    print("Resultado final:", resultado.stdout.strip())

if __name__ == "__main__":
    obtener_gini("ARG")  # Cambiar el código ISO si se desea otro país
