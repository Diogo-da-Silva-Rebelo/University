
// calculate overall AQI
// Portuguese Environment Agency (APA)
// based on the recommendations of the World Health Organization (WHO)
// and European Union (EU).
// noinspection DuplicatedCode

export function calculateOverallAQI(data) {

    // Define the breakpoints for each AQI category
    const breakpointsScale = {
        "good": [0, 50],
        "moderate": [51, 100],
        "unhealthy-sensitive": [101, 150],
        "unhealthy": [151, 200],
        "very-unhealthy": [201, 300],
        "hazardous": [301, Infinity],
    };

    // break points for each pollutant
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

    // Loop through each location
    const results = {};

    const firstLocation = Object.values(data)[0]; // get the first location
    const firstRecordId = Object.keys(firstLocation.records)[0]; // get the first record ID
    const pollutants = Object.keys(firstLocation.records[firstRecordId]); // get the pollutants of the first record

    // find the most recent record
    const recentRecords = {};
    for (const [location, locationData] of Object.entries(data)) {
        recentRecords[location] = Object.values(locationData.records).reduce((prev, current) => {
            return (prev.timestamp > current.timestamp) ? prev : current
        });
    }

    // Calculate the AQI for each pollutant of the record
    const aqiValues = {};

    // for each record, calculate the AQI for each pollutant
    for (const [location, record] of Object.entries(recentRecords)) {
        aqiValues[location] = {};
        for (const pollutant of pollutants) {
            // check if the pollutant is in the record
            if (!record[pollutant]) {
                continue;
            }
            // get the concentration of the pollutant
            const concentration = record[pollutant].value;
            // find the breakpoints for the pollutant
            const bp = breakpoints.find((bp) => bp.pollutant === pollutant);
            // find the breakpoints for the pollutant
            const aqi = calculateAqi(
                concentration,
                bp.conc[0],
                bp.conc[bp.conc.length - 1],
                bp.aqi[0],
                bp.aqi[bp.aqi.length - 1]
            );
            aqiValues[location][pollutant] = aqi;
        }
    }

    // Calculate the overall AQI
    for (const [location, aqi] of Object.entries(aqiValues)) {
        // find the highest AQI value
        const aqiValues = Object.values(aqi);
        const maxAqi = Math.max(...aqiValues);
        // find the category of the highest AQI value
        const category = Object.keys(breakpointsScale).find((category) => {
            const bp = breakpointsScale[category];
            return maxAqi >= bp[0] && maxAqi <= bp[1];
        });
        results[location] = {
            aqi: maxAqi,
            category: category,
        };
    }

    return results;
    // result is like: {"PT01041":{"aqi":4,"category":"good"},"PT01042":{"aqi":0,"category":"good"}}
}

// Function to calculate the AQI based on the concentration and breakpoints
function calculateAqi(concentration, bpLow, bpHigh, aqiLow, aqiHigh) {
    const aqi =
        ((aqiHigh - aqiLow) / (bpHigh - bpLow)) * (concentration - bpLow) + aqiLow;
    return Math.round(aqi);
}