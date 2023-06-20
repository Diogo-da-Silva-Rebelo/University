const express = require('express');
const router = express.Router();
const { getCityData, getLatestData, calculateAQI, createGeoJSON, getWeatherMostRecentRecord} = require('../controllers/dataController');


router.get('/cities/:city', async (req, res) => {
    // get city name from URL
    const country = 'PT';
    const city = req.params.city;

    try {
        const cityData = await getCityData(city, country);

        if (Object.keys(cityData).length === 0) {
            res.status(404).send(`No data found in the database`);
        } else {
        res.status(200).json(cityData);
        }
    } catch (error) {
        console.error(error);
        res.status(500).send(`Error getting data for ${city}!`);
    }
});


router.get('/map', async (req, res) => {
    // get city name from URL
    const country = 'PT';
    const cities = ['Braga', 'Porto', 'Lisboa', 'Faro', 'Évora', 'Leiria', 'Santarém', 'Viseu', 'Viana do Castelo', 'Vila Real', 'Aveiro', 'Castelo Branco'];
    let geojson = {
        type: 'FeatureCollection',
        name: 'Cities AQI Data',
        crs: {
            type: 'name',
            properties: {
                name: 'urn:ogc:def:crs:OGC:1.3:CRS84'
            }
        },
        features: []
    };

    try {
        for (const city of cities) {
            // get data from database for heatmap
            const cityData = await getCityData(city, country);
            const latestData = getLatestData(cityData);
            const AQIs = calculateAQI(latestData);
            geojson = createGeoJSON(geojson, AQIs);
        }

        // check if dict is empty
        if (Object.keys(geojson).length === 0) {
            res.status(404).send(`No data found in the database`);
        } else {
            res.status(200).json(geojson);
        }
    } catch (error) {
        console.error(error);
        res.status(500).send(`Error getting data for heatmap!`);
    }
});

router.get('/maps/weather', async (req, res) => {
    // get city name from URL
    const country = 'PT';
    const cities = ['Braga', 'Porto', 'Lisboa', 'Faro', 'Évora', 'Leiria', 'Santarém', 'Viseu', 'Viana do Castelo', 'Vila Real', 'Aveiro', 'Castelo Branco']
    const weatherData = {}
    let currentCity = undefined;

    try {
        for (const city of cities) {
            currentCity = city;
            weatherData[city] = await getWeatherMostRecentRecord(city, country);
        }
        res.json(weatherData);
    } catch (error) {
        console.error(error);
        res.status(500).send(`Error getting data for ${currentCity}!`);
    }
});


router.get('/maps/air', async (req, res) => {
    // get city name from URL
    const country = 'PT';
    const cities = ['Braga', 'Porto', 'Lisboa', 'Faro']
    const airData = {}
    let currentCity = undefined;

    try {
        for (const city of cities) {
            currentCity = city;
            airData[city] = calculateAQI((getLatestData(await getCityData(city,country))));
        }
        res.json(airData);
    } catch (error) {
        console.error(error);
        res.status(500).send(`Error getting data for ${currentCity}!`);
    }
});

module.exports = router;
