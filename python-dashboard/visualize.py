import serial
import matplotlib.pyplot as plt
import time

SERIAL_PORT = "COM6"  # Change to /dev/ttyUSB0 on Linux/Mac
BAUD = 115200

ser = serial.Serial(SERIAL_PORT, BAUD)

timestamps = []
rssi_data = []
loss_data = []

plt.ion()
fig, ax = plt.subplots()

print("Python Dashboard Started...")

while True:
    line = ser.readline().decode().strip()
    print(line)

    if "RSSI" in line:
        try:
            rssi = int(line.split("RSSI:")[1].split("dBm")[0])
            loss = float(line.split("Loss:")[1].split("%")[0])

            timestamps.append(time.time())
            rssi_data.append(rssi)
            loss_data.append(loss)

            ax.clear()
            ax.plot(timestamps, rssi_data, label="RSSI (dBm)")
            ax.plot(timestamps, loss_data, label="Packet Loss (%)")

            ax.set_xlabel("Time")
            ax.set_ylabel("Values")
            ax.set_title("ESP32 Anti-Jamming Dashboard")

            ax.legend()
            plt.pause(0.05)

        except:
            pass
