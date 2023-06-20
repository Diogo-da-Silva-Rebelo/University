require('dotenv').config();
async function fetchTrafficData(city, resolution) {
    try {
        const KEY = process.env.TOMTOM_API_KEY;
        const BASE_URL = 'api.tomtom.com';
        const SEC_URL = 'traffic/services/4/flowSegmentData';
        const RASTER_FLOW_STYLE = 'relative';
        const ZOOM = 10;
        const FORMAT = 'json';
        let POINTS = {};
        const UNIT = 'KMPH';
        const THICKNESS = 10;
        const flag = 0;

        switch (city) {
            case 'Braga':
                POINTS = {
                    'CENTER': [41.545083, -8.413310],
                    'NORTH': [41.586103, -8.434237],
                    'SOUTH': [41.509086, -8.440044],
                    'EAST': [41.540188, -8.338420],
                    'WEST': [41.548282, -8.482616],
                }
                break;
            default:
                break;
        }

        // check if resolution is number
        if (!resolution || resolution === 0) {
            // error
            console.error('Error: resolution is not a number')
        }

        let dataT = {};

        // build url
        // make request per point
        if (flag === 0) {
            for (const [key, value] of Object.entries(POINTS)) {
                const url = `https://${BASE_URL}/${SEC_URL}/${RASTER_FLOW_STYLE}/${ZOOM}/${FORMAT}?key=${KEY}&resolution=${resolution}&point=${value}&unit=${UNIT}&thickness=${THICKNESS}`
                const response = await fetch(url);
                dataT = await response.json();
                console.log(`Fetched traffic data for ${key}:\n ${JSON.stringify(dataT)}`)
                await new Promise(resolve => setTimeout(resolve, 1000)); // wait 1 second before making the next request
            }
        }
        return dataT;
    } catch (error){
        console.log('ERRO')
    }
}

module.exports = {
    fetchTrafficData,
};
