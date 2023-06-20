import requests
import csv
import time

# Definir as ruas entre as quais queremos fazer os pedidos
origin = "Rua da Estrada Nova, 4715-165 Braga" 
destination = "Braga Parque, Bairro da Quinta dos Congregados, 4710-427 Braga" 

# Definir os intervalos de tempo:
# 8h-10h: 30 minutos
# 10h-12h: 1 hora
# 12h-14h: 30 minutos
# 14h-18h: 1 hora
# 18h-20h: 30 minutos
# 20h-8h: 4 horas
intervals = {
    "8-10": 1800,
    "10-12": 3600,
    "12-14": 1800,
    "14-18": 3600,
    "18-20": 1800,
    "20-8": 14400,
}

# Definir o CSV para onde queremos escrever os dados
filename = "routes.csv"
headers = ["Timestamp", "Duration (s)", "Distance (m)"]

# Abrir o CSV para escrita
with open(filename, "w", newline="") as csvfile:
    # Criar o objeto para escrever no CSV
    writer = csv.writer(csvfile)

    # Escrever os cabeçalhos
    writer.writerow(headers)

    #  Iterar sobre os intervalos de tempo
    for key, value in intervals.items():
        start_hour, end_hour = key.split("-")

        # Loop through the time range for the current interval
        for hour in range(int(start_hour), int(end_hour)):
            if hour < 10:
                hour_str = f"0{hour}"
            else:
                hour_str = str(hour)

            # Loop through the minutes for the current interval
            for minute in range(0, 60, int(value / 60)):
                if minute < 10:
                    minute_str = f"0{minute}"
                else:
                    minute_str = str(minute)

                # Construct the current timestamp
                timestamp = f"2023-05-03T{hour_str}:{minute_str}:00Z"

                key='AIzaSyBFzQRR1MO5OR-jXNgV7RqRpqSnEpUy-XI'

                # Make the API request
                url = f"https://maps.googleapis.com/maps/api/directions/json?origin={origin}&destination={destination}&key={key}&departure_time={timestamp}"
                response = requests.get(url)
                data = response.json()

                # Extract the duration and distance from the response
                duration = data["routes"][0]["legs"][0]["duration"]["value"]
                distance = data["routes"][0]["legs"][0]["distance"]["value"]

                # Write the data to the CSV file
                writer.writerow([timestamp, duration, distance])

                # Wait for the specified time interval before making the next request
                time.sleep(value)