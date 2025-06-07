import csv
import time
import sys

DEVICE_PATH = "/dev/cdd_signals"
CSV_FILE = "signals.csv"

def select_signal(signal_num):
    with open(DEVICE_PATH, "w") as device:
        device.write(str(signal_num))

def read_signal():
    with open(DEVICE_PATH, "r") as device:
        return device.readline().strip()

def acquire_signal(signal_num):
    select_signal(signal_num)
    with open(CSV_FILE, mode="w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["timestamp", "signal"])
        try:
            start_time = time.time()
            while True:
                signal = read_signal()
                timestamp = time.time()
                writer.writerow([timestamp, signal])
                csvfile.flush()
                # sleep to simulate a sampling rate of 10 Hz
                time.sleep(0.1)
                if timestamp - start_time >= 30:
                    print(f"Lectura detenida tras 30 segundos de la señal {signal_num}.")
                    break
        except KeyboardInterrupt:
            print("Lectura detenida por el usuario.")

def main():
    if len(sys.argv) < 2 or sys.argv[1] not in ["1", "2"]:
        print("Uso: python3 app_signal.py [1|2]")
        sys.exit(1)
    signal_num = sys.argv[1]
    acquire_signal(signal_num)

if __name__ == "__main__":
    main()
