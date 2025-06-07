import sys
import pandas as pd
import matplotlib.pyplot as plt

VCC = 3.3  # Ajusta según tu hardware

if len(sys.argv) > 1 and sys.argv[1] in ["1", "2"]:
    signal_num = sys.argv[1]
else:
    signal_num = "?"

df = pd.read_csv("signals.csv")
df["time"] = df["timestamp"] - df["timestamp"].iloc[0]
df["signal"] = df["signal"].astype(int) * VCC

plt.figure(figsize=(10, 4))
plt.step(df["time"], df["signal"], where="post")
plt.xlabel("Tiempo (s)")
plt.ylabel("Voltaje (V)")
plt.title(f"Señal {signal_num} (GPIO{signal_num}) vs Tiempo")
plt.grid(True)
plt.tight_layout()
plt.show()
