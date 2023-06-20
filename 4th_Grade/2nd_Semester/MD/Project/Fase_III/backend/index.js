const express = require('express');
const dataRoutes = require('./routes/dataRoutes');
const {saveData, saveWeatherData} = require("./controllers/dataController");
const app = express();

// npm run devStart
// sudo netstat -plten |grep node
// kill -9 PID

app.use(express.json());

// Middleware to allow CORS
app.use((req, res, next) => {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});


// Define Routes
// Task 1: Handle requests from the client
app.use('/', dataRoutes);

// define threads
// Task 2: get data from Firebase and save them
async function performActions() {
    try {
        // main cities in Portugal
        // define array of cities
        const cities = [
            "Braga",
            "Porto",
            "Lisboa",
            "Évora",
            "Leiria",
            "Santarém",
            "Viseu",
            "Viana do Castelo",
            "Vila Real",
            "Aveiro",
            "Castelo Branco",
            "Faro",
        ];
        const country = 'PT';

        // save data for each city
        for (let i = 0; i < cities.length; i++) {
            await saveData(cities[i], country);
            await saveWeatherData(cities[i], country);
        }
    } catch (err) {
        console.error("Error getting data from Firebase:", err);
    }
}

// Executar imediatamente quando o servidor é iniciado
performActions().then(r => console.log("Data saved!"));

// Executar a cada 30 minutos
setInterval(performActions, 1800000);

// define PORT
const PORT = process.env.PORT || 3001;

// start server
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});

/*
async function main() {
    try {
        const data = {
            "PT01041": {
                "coordinates": {
                    "latitude": 41.549722,
                    "longitude": -8.405833
                },
                "records": {
                    "023192a1-d3cd-4d48-ab7e-1d63939f49fc": {
                        "no2": {
                            "lastUpdated": 1681671600,
                            "timestamp":1683576236000,
                            "value": 16.4
                        },
                        "pm10": {
                            "lastUpdated": 1681671600,
                            "timestamp": 1683576236000,
                            "value": 56
                        }
                    },
                    "03207572-180f-435b-ad34-249ddf3f44cf": {
                        "no2": {
                            "lastUpdated": 1681563600,
                            "timestamp": 1683576237000,
                            "value": 1.2
                        },
                        "pm10": {
                            "lastUpdated": 1681563600,
                            "timestamp": 1683576238000,
                            "value": 1.9
                        },
                    },
                }
            },
            "PT01042": {
                "coordinates": {
                    "latitude": 41.149722,
                    "longitude": -8.610556
                },
                "records": {
                    "023192a1-d3cd-4d48-ab7e-1d63939f49fc": {
                        "no2": {
                            "lastUpdated": 1681671600,
                            "timestamp": 1683576236000,
                            "value": 0
                        },
                    },
                }
            },
        };

      await saveData("Évora", "PT");
      await saveData("Leiria", "PT");
      await saveData("Santarém", "PT");
      await saveData("Viseu", "PT");
      await saveData("Viana do Castelo", "PT");
      await saveData("Vila Real", "PT");
      await saveData("Aveiro", "PT");
      await saveData("Castelo Branco", "PT");
      await saveWeatherData("Évora", "PT");
        await saveWeatherData("Leiria", "PT");
        await saveWeatherData("Santarém", "PT");
        await saveWeatherData("Viseu", "PT");
        await saveWeatherData("Viana do Castelo", "PT");
        await saveWeatherData("Vila Real", "PT");
        await saveWeatherData("Aveiro", "PT");
        await saveWeatherData("Castelo Branco", "PT");

    } catch (error) {
        console.error(error);
    }
}

main();
 */
