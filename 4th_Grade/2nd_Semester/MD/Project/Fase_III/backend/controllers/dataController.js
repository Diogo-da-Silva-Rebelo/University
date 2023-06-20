const { fetchData } = require("../services/openaq");
const { fetchWeatherData } = require("../services/weather");
const {
    database,
    ref,
    set,
    update,
    onValue,
    get, orderByChild, limitToLast, query,
} = require("../models/dataModel");

const uuid = require("uuid");

// Save data in Firebase Realtime Database
async function saveData(city, country) {
    try {
        // get data from API and parse it
        const data = await fetchData(city, country);

        for (const locationId in data) {
            // create a reference to the location
            const locationRef = ref(
                database,
                "air-quality-data/" + country + "/" + city + "/" + locationId
            );
            const locationCoord = data[locationId].coordinates;
            const locationMeasures = data[locationId].measurements;
            const records = {};

            // check if location already exists
            const locationSnapshot = await get(locationRef);

            if (locationSnapshot.exists()) {
                // location already exists, add new records to existing object
                const existingLocationData = locationSnapshot.val();
                for (const recordId in existingLocationData.records) {
                    records[recordId] = existingLocationData.records[recordId];
                }
                // add new record to records object with unique ID
                records[uuid.v4()] = locationMeasures;
                // update location object with new records
                await update(locationRef, { records: records });
            } else {
                // location doesn't exist, create new object with coordinates and records
                // generate a unique ID for the record
                const recordId = uuid.v4();
                // add the measurement data to the records object with the unique ID as the key
                records[recordId] = locationMeasures;
                const locationObject = {
                    coordinates: locationCoord,
                    records: records,
                };
                // add location object to Firebase
                await set(locationRef, locationObject);
            }
        }
        console.log("data from OpenAQ API saved successfully in Firebase");
    } catch (error) {
        console.error("Error saving data from OpenAQ API to Firebase:", error);
    }
}

// get data from a specific city in Firebase Realtime Database
function getCityData(city, country) {
    return new Promise((resolve, reject) => {
        try {
            // create a reference to the city
            const cityRef = ref(database, "air-quality-data/" + country + "/" + city);
            // listen for changes to the city data
            onValue(cityRef, (snapshot) => {
                const citySnapshot = snapshot.val();
                console.log(`Data from ${city} in Firebase has been updated`);
                resolve(citySnapshot);
            });
        } catch (error) {
            console.error(`Error getting data from ${city} in Firebase:`, error);
            reject(error);
        }
    });
}

// calculate overall AQI
// Portuguese Environment Agency (APA)
// based on the recommendations of the World Health Organization (WHO)
// and European Union (EU).
function calculateAQI(data) {
    const breakpoints = [
        {
            pollutant: "no2",
            conc: [0, 50, 100, 200, 400, 1000],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "pm10",
            conc: [0, 20, 40, 70, 100, 200],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "o3",
            conc: [0, 54, 70, 85, 105, 200],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "so2",
            conc: [0, 50, 100, 200, 350, 500],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "co",
            conc: [0, 2, 9, 15, 30, 40],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "pm25",
            conc: [0, 10, 20, 25, 50, 800],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "pm1",
            conc: [0, 10, 20, 25, 50, 800],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "um010",
            conc: [0, 20, 40, 60, 80, 100],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "um025",
            conc: [0, 20, 40, 60, 80, 100],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        {
            pollutant: "um100",
            conc: [0, 50, 100, 150, 200, 300],
            aqi: [0, 50, 100, 150, 200, 300, 400],
        },
        // add more pollutants here
    ];

    const aqiForConcentration = (pollutant, conc) => {
        let bp = breakpoints.find((bp) => bp.pollutant === pollutant);

        if (!bp) {
            console.warn(`Breakpoint not found for pollutant: ${pollutant}`);
            conc = 0; // Set concentration to 0 if breakpoint not found
            bp = breakpoints[0]; // Use the first breakpoint as a fallback
        }

        const i = bp.conc.findIndex((c) => c > conc) - 1;
        const cLow = bp.conc[i];
        const cHigh = bp.conc[i + 1];
        const aqiLow = bp.aqi[i];
        const aqiHigh = bp.aqi[i + 1];
        return Math.round(
            ((aqiHigh - aqiLow) / (cHigh - cLow)) * (conc - cLow) + aqiLow
        );
    };

    const overallAQI = {};

    for (const [location, locationData] of Object.entries(data)) {
        // calculate AQI for each pollutant
        overallAQI[location] = {
            aqi: 0,
            details: {},
            coordinates: locationData.coordinates,
        };
        delete locationData.coordinates;
        for (const [pollutant, concentrations] of Object.entries(locationData)) {
            const meanConcentration =
                concentrations.reduce((sum, c) => sum + c, 0) / concentrations.length;

            // Check if conc is undefined
            if (typeof meanConcentration === 'undefined') {
                overallAQI[location].details[pollutant] = 0;
                continue; // Move to the next iteration
            }

            const pollutantAQI = aqiForConcentration(pollutant, meanConcentration);
            overallAQI[location].details[pollutant] = pollutantAQI;

            // if AQI for pollutant is Nan, put to 0
            if (isNaN(pollutantAQI)) {
                overallAQI[location].details[pollutant] = 0;
            }

            overallAQI[location].aqi = Math.max(
                overallAQI[location].aqi,
                pollutantAQI
            );
        }
    }
    // returns an object with the overall AQI for each location
    // and the AQI for each pollutant
    return overallAQI;
}

// get latest record
function getLatestData(data) {
    const latestData = {};

    for (const [location, locationData] of Object.entries(data)) {
        latestData[location] = {};
        // get coordinates
        latestData[location].coordinates = locationData.coordinates;

        const latestRecords = {};
        for (const [, recordData] of Object.entries(locationData.records)) {
            for (const [pollutant, pollutantData] of Object.entries(recordData)) {
                if (
                    !(pollutant in latestRecords) ||
                    pollutantData.timestamp > latestRecords[pollutant].timestamp
                ) {
                    latestRecords[pollutant] = pollutantData;
                }
            }
        }

        for (const [pollutant, pollutantData] of Object.entries(latestRecords)) {
            if (!(pollutant in latestData[location])) {
                latestData[location][pollutant] = [];
            }
            latestData[location][pollutant].push(pollutantData.value);
        }
    }

    return latestData;
}

// get file geo
/*
function getFileContent(filePath) {
    try {
        return fs.readFileSync(filePath, 'utf-8');
    } catch (error) {
        console.error(`Failed to read file ${filePath}: ${error.message}`);
        return null;
    }
}*/

function createGeoJSON(geoJSON, data) {
    for (const [key, value] of Object.entries(data)) {
        const point = {
            type: "Feature",
            geometry: {
                type: "Point",
                coordinates: [value.coordinates.longitude, value.coordinates.latitude],
            },
            properties: {
                id: key,
                ...value,
            },
        };
        geoJSON.features.push(point);
    }
    return geoJSON;
}

// Save data in Firebase Realtime Database
async function saveWeatherData(city, country) {
    try {
        // get data from API and parse it
        const data = await fetchWeatherData(city);

        // create a reference to the location
        const locationRef = ref(database, "weather-data/" + country + "/" + city);
        const cityCoord = [data.coordinates.latitude, data.coordinates.longitude];
        delete data.coordinates;

        const records = {};

        // check if location already exists
        const locationSnapshot = await get(locationRef);

        if (locationSnapshot.exists()) {
            // location already exists, add new records to existing object
            const existingLocationData = locationSnapshot.val();
            for (const recordId in existingLocationData.records) {
                records[recordId] = existingLocationData.records[recordId];
            }
            // add new record to records object with unique ID
            records[uuid.v4()] = data;
            // update location object with new records
            await update(locationRef, { records: records });
        } else {
            // location doesn't exist, create new object with coordinates and records
            // generate a unique ID for the record
            const recordId = uuid.v4();
            // add the measurement data to the records object with the unique ID as the key
            records[recordId] = data;
            const locationObject = {
                coordinates: {
                    latitude: cityCoord[0],
                    longitude: cityCoord[1]
                },
                records: records,
            };
            // add location object to Firebase
            await set(locationRef, locationObject);
        }
        console.log("data from OpenWeather API saved successfully in Firebase");
    } catch (error) {
        console.error("Error saving data from OpenWeather API to Firebase:", error);
    }
}

async function getWeatherMostRecentRecord(location, country) {
    // Fetch coordinates
    const coordinatesRef = ref(database, `weather-data/${country}/${location}/coordinates`);
    const coordinatesSnapshot = await get(coordinatesRef);

    if (!coordinatesSnapshot.exists()) {
        console.error(`There's no coordinate information for ${location}.`)
        return null;
    }

    const coordinates = coordinatesSnapshot.val();

    // Fetch most recent weather data record
    const weatherDataRef = ref(database, `weather-data/${country}/${location}/records`);
    const queryRef = query(weatherDataRef, orderByChild('atualTimestamp'), limitToLast(1));
    const snapshot = await get(queryRef);

    if (!snapshot.exists()) {
        console.error(`There's no weather information for ${location}.`)
        return null;
    }

    const weatherData = snapshot.val();
    const registerKey = Object.keys(weatherData)[0];

    // Remove the register key from the weather data object
    const { [registerKey]: _, ...mostRecentWeatherData } = weatherData[registerKey];

    return { coordinates, weatherData: mostRecentWeatherData };
}


module.exports = {
    saveData,
    getCityData,
    getWeatherMostRecentRecord,
    calculateAQI,
    getLatestData,
    createGeoJSON,
    saveWeatherData,
};
