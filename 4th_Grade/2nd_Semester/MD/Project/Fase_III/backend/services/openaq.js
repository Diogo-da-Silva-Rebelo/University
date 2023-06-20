// Fetch data from API OpenAQ
async function fetchData(city,country) {
    try {
        const url = `https://api.openaq.org/v2/latest?limit=100&page=1&offset=0&sort=desc&radius=1000&country_id=${country}&city=${city}&order_by=lastUpdated&dumpRaw=false`;
        const response = await fetch(url);
        const data = await response.json();
        const openAQData = {};

        data.results.forEach(result => {
            const locationId = result.location;
            if (!openAQData[locationId]) {
                openAQData[locationId] = {
                    coordinates: {
                        latitude: result.coordinates.latitude,
                        longitude: result.coordinates.longitude
                    },
                    measurements: {}
                };
            }

            result.measurements.forEach(measurement => {
                openAQData[locationId].measurements[measurement.parameter] = {
                    value: measurement.value,
                    lastUpdated: Date.parse(measurement.lastUpdated) / 1000,
                    timestamp: Date.now()
                };
            });
        });
        return openAQData;
    } catch (error) {
        console.error('Error fetching data from OpenAQ API:', error);
    }
}

module.exports = {
    fetchData,
};
