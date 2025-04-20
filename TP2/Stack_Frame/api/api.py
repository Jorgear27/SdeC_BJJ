from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

# Historial de cálculos
historial = []

@app.route('/calculo', methods=['POST'])
def hacer_calculo():
    data = request.get_json()

    try:
        a = str(data['a'])
        b = str(data['b'])
        operacion = data['operacion']
    except KeyError:
        return jsonify({"error": "Faltan parámetros. Se espera 'a', 'b' y 'operacion'."}), 400

    # Ejecutar el binario C que llama a la rutina ASM
    try:
        resultado = subprocess.run(
            ["../build/calcular", a, b, operacion],
            capture_output=True,
            text=True,
            check=True
        )
        resultado_final = int(resultado.stdout.strip())
        # Guardar en el historial
        historial.append({
            "a": int(a),
            "b": int(b),
            "operacion": operacion,
            "resultado": resultado_final
        })
        return jsonify({
            "a": int(a),
            "b": int(b),
            "operacion": operacion,
            "resultado": resultado_final
        })
    except subprocess.CalledProcessError as e:
        return jsonify({"error": "Error en el programa C/ASM", "detalle": e.stderr}), 500

@app.route('/historial', methods=['GET'])
def obtener_historial():
    return jsonify(historial), 200

@app.route('/instrucciones', methods=['GET'])
def instrucciones():
    return jsonify({
        "endpoints": {
            "/calculo (POST)": "Realiza un cálculo. Enviar JSON con 'a', 'b' y 'operacion'.",
            "/historial (GET)": "Obtiene el historial de cálculos realizados.",
            "/ (GET)": "Muestra un mensaje de bienvenida."
        },
        "ejemplo_calculo": {
            "a": 10,
            "b": 5,
            "operacion": "suma"
        }
    }), 200

@app.route('/')
def index():
    return jsonify({"mensaje": "API para realizar cálculos con ASM"}), 200

if __name__ == '__main__':
    app.run(debug=True)