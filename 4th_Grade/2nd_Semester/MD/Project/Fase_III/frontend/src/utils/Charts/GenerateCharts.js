import moment from "moment";
import { calculateOverallAQI } from "./AQI";


// generate line chart
export function generateLineChart(cityData, location, timeRange) {
    if (!cityData[location]) {
        throw new Error(`Location "${location}" not found in city data.`);
    }

    if (!cityData[location].records) {
        throw new Error(`No records found for location "${location}".`);
    }

    // determine start and end timestamps for desired time range
    const now = Date.now();
    let start;
    let labelFormat;
    // set start time to the earliest timestamp available in the data when timeRange is 'none'
    if (timeRange === 'none') {
        // set start time to the earliest timestamp available in the data
        const timestamps = Object.values(cityData[location].records).map(record => record.timestamp);
        start = Math.min(...timestamps);
        // display full date and time
        labelFormat = 'MMM D, YYYY, h:mm A';
    } else if (timeRange === 'day') {
        start = now - 24 * 60 * 60 * 1000;
        labelFormat = 'h A'; // display hours with AM/PM format
    } else if (timeRange === 'week') {
        start = now - 7 * 24 * 60 * 60 * 1000;
        labelFormat = 'ddd'; // display day of the week
    } else if (timeRange === 'month') {
        start = now - 30 * 24 * 60 * 60 * 1000;
        // display week of the month
        labelFormat = 'MMM Do';
    }
    else {
        throw new Error(`Invalid time range "${timeRange}".`);
    }

    // create an array of pollutants from 1st record
    const pollutants_record1 = Object.keys(cityData[location].records[Object.keys(cityData[location].records)[0]]);

    if (!pollutants_record1) {
        throw new Error(`There are no pollutants in location "${location}" records.`);
    }

    const datasets = [];
    let chartLabels = [];
    let i = 0;

    // loop through each pollutant
    for (const pollutant of pollutants_record1) {

        const chartData = [];

        // loop through each record for the current pollutant
        for (const recordId in cityData[location].records) {
            const record = cityData[location].records[recordId];
            const valueForPollutant = record[pollutant].value;
            const timestampForPollutant = record[pollutant].timestamp;

            // only include records that fall within desired time range, or include all data if timeRange is 'none'
            if (timeRange === 'none' || timestampForPollutant >= start) {
                // add record to chartData array
                chartData.push({
                    x: timestampForPollutant,
                    y: valueForPollutant,
                });

                // format timestamp for display on x-axis
                const formattedLabel = moment(timestampForPollutant).format(labelFormat);
                if (!chartLabels.includes(formattedLabel)) {
                    chartLabels.push(formattedLabel);
                }
            }
        }

        // sort chartData by timestamp
        chartData.sort((a, b) => a.x - b.x);
        // create array of chart labels from sorted chartData array
        chartLabels = chartData.map(dataPoint => moment(dataPoint.x).format(labelFormat));


        // Generate a pastel color for the line based on the index of the pollutant
        const hue = (i * 137.508) % 360;
        const borderColor = `hsl(${hue}, 60%, 70%)`;
        i++;

        // Add a new dataset to the array for the current pollutant
        datasets.push({
            label: `${pollutant}`,
            data: chartData,
            fill: false,
            borderColor: borderColor,
        });
    }

    // create chart data object
    return {
        labels: chartLabels,
        datasets: datasets,
    };
}

// generate bar chart
// Average concentration of each pollutant across all locations or for specific locations.
// This can help compare the pollutant concentrations across different locations.
export function generateBarChart(cityData, location, timeRange) {
  if (!cityData[location]) {
    throw new Error(`Location "${location}" not found in city data.`);
  }

  if (!cityData[location].records) {
    throw new Error(`No records found for location "${location}".`);
  }

  // determine start and end timestamps for desired time range
  const now = Date.now();
  let start;
  // set start time to the earliest timestamp available in the data when timeRange is 'none'
  if (timeRange === "none") {
    // set start time to the earliest timestamp available in the data
    const timestamps = Object.values(cityData[location].records).map(
      (record) => record.timestamp
    );
    start = Math.min(...timestamps);
  } else if (timeRange === "day") {
    start = now - 24 * 60 * 60 * 1000;
  } else if (timeRange === "week") {
    start = now - 7 * 24 * 60 * 60 * 1000;
  } else if (timeRange === "month") {
    start = now - 30 * 24 * 60 * 60 * 1000;
  } else {
    throw new Error(`Invalid time range "${timeRange}".`);
  }

  // create an array of pollutants from 1st record
  const pollutants_record1 = Object.keys(
    cityData[location].records[Object.keys(cityData[location].records)[0]]
  );

  if (!pollutants_record1) {
    throw new Error(
      `There are no pollutants in location "${location}" records.`
    );
  }

  const datasets = [];
  let i = 0;

  // loop through each pollutant
  for (const pollutant of pollutants_record1) {
    const chartData = [];

    // loop through each record for the current pollutant
    for (const recordId in cityData[location].records) {
      const record = cityData[location].records[recordId];
      const valueForPollutant = record[pollutant].value;
      const timestampForPollutant = record[pollutant].timestamp;

      // only include records that fall within desired time range, or include all data if timeRange is 'none'
      if (timeRange === "none" || timestampForPollutant >= start) {
        // add record to chartData array
        chartData.push(valueForPollutant);
      }
    }
    i += 1;

    // get mean value for each pollutant
    const mean =
      chartData.reduce((acc, val) => acc + val, 0) / chartData.length;

    // Generate a pastel color for the line based on the index of the pollutant
    const hue = (i * 137.508) % 360;
    const backgroundColor = `hsl(${hue}, 60%, 70%)`;

    // Add a new dataset to the array for the current pollutant
    datasets.push({
      label: `${pollutant}`,
      data: [mean],
      backgroundColor: backgroundColor,
      borderRadius: 20,
    });
  }

  // create chart data object
  return {
    labels: ["Average"],
    datasets: datasets,
  };
}

// generate donut chart
// proportion of each pollutant in the total pollution for each location.
export function generateDonutChart(cityData, location, timeRange) {
  if (!cityData[location]) {
    throw new Error(`Location "${location}" not found in city data.`);
  }

  if (!cityData[location].records) {
    throw new Error(`No records found for location "${location}".`);
  }

  // determine start and end timestamps for desired time range
  const now = Date.now();
  let start;
  // set start time to the earliest timestamp available in the data when timeRange is 'none'
  if (timeRange === "none") {
    // set start time to the earliest timestamp available in the data
    const timestamps = Object.values(cityData[location].records).map(
      (record) => record.timestamp
    );
    start = Math.min(...timestamps);
    // display full date and time
  } else if (timeRange === "day") {
    start = now - 24 * 60 * 60 * 1000;
  } else if (timeRange === "week") {
    start = now - 7 * 24 * 60 * 60 * 1000;
  } else if (timeRange === "month") {
    start = now - 30 * 24 * 60 * 60 * 1000;
  } else {
    throw new Error(`Invalid time range "${timeRange}".`);
  }

  // create an array of pollutants from 1st record
  const pollutants_record1 = Object.keys(
    cityData[location].records[Object.keys(cityData[location].records)[0]]
  );

  if (!pollutants_record1) {
    throw new Error(
      `There are no pollutants in location "${location}" records.`
    );
  }

  const proportionData = [];
  const colors = [];
  let i = 0;

  // loop through each pollutant
  for (const pollutant of pollutants_record1) {
      const chartData = [];

      // loop through each record for the current pollutant
      for (const recordId in cityData[location].records) {
          const record = cityData[location].records[recordId];
          const valueForPollutant = record[pollutant].value;
          const timestampForPollutant = record[pollutant].timestamp;

          // only include records that fall within desired time range, or include all data if timeRange is 'none'
          if (timeRange === "none" || timestampForPollutant >= start) {
              // add record to chartData array
              chartData.push(valueForPollutant);
          }
      }
      i += 1;

      // get sum value for each pollutant
      const sum = chartData.reduce((acc, val) => acc + val, 0);
      const proportion = sum / chartData.length;
      proportionData.push(proportion);

      // Generate a pastel color for the line based on the index of the pollutant
      const hue = (i * 137.508) % 360;
      const backgroundColor = `hsl(${hue}, 60%, 70%)`;
      colors.push(backgroundColor);
  }
  // create chart data object
  return {
    labels: pollutants_record1,
    datasets: [
      {
        label: "Pollutant Proportion",
        data: proportionData,
        backgroundColor: colors,
      },
    ],
  };
}

// generate scatter chart combining two or more pollutants
export function generateScatterChart(cityData, location, timeRange, pollutants) {
    if (!cityData[location]) {
        throw new Error(`Location "${location}" not found in city data.`);
    }

    if (!cityData[location].records) {
        throw new Error(`No records found for location "${location}".`);
    }

    if (pollutants.length <= 0) {
        throw new Error(`At least one pollutant must be selected.`);
    }


    // determine start and end timestamps for desired time range
    const now = Date.now();
    let start;
    let labelFormat;
    // set start time to the earliest timestamp available in the data when timeRange is 'none'
    if (timeRange === 'none') {
        // set start time to the earliest timestamp available in the data
        const timestamps = Object.values(cityData[location].records).map(record => record.timestamp);
        start = Math.min(...timestamps);
        // display full date and time
        labelFormat = 'MMM D, YYYY, h:mm A';
    } else if (timeRange === 'day') {
        start = now - 24 * 60 * 60 * 1000;
        labelFormat = 'h:mm A'; // display hours and minutes with AM/PM format
    } else if (timeRange === 'week') {
        start = now - 7 * 24 * 60 * 60 * 1000;
        labelFormat = 'ddd h A'; // display day of the week, hours with AM/PM format
    } else if (timeRange === 'month') {
        start = now - 30 * 24 * 60 * 60 * 1000;
        // display day of the month, hours with AM/PM format
        labelFormat = 'MMM Do, h A';
    }
    else {
        throw new Error(`Invalid time range "${timeRange}".`);
    }

    // create an array of pollutants from 1st record
    const pollutants_record1 = Object.keys(
        cityData[location].records[Object.keys(cityData[location].records)[0]]
    );

    if (!pollutants_record1) {
        throw new Error(
        `There are no pollutants in location "${location}" records.`
        );
    }

    // check if pollutants passed are in the pollutants_record1
    for (const pollutant of pollutants) {
        if (!pollutants_record1.includes(pollutant)) {
            throw new Error(`Pollutant "${pollutant}" not found in pollutants city data.`);
        }
    }

    const datasets = [];
    let chartLabels = [];
    let i = 0;

    // loop through each pollutant
    for (const pollutant of pollutants) {
        const chartData = [];

        // loop through each record for the current pollutant
        for (const recordId in cityData[location].records) {
        const record = cityData[location].records[recordId];
        const valueForPollutant = record[pollutant].value;
        const timestampForPollutant = record[pollutant].timestamp;

            // only include records that fall within desired time range, or include all data if timeRange is 'none'
            if (timeRange === 'none' || timestampForPollutant >= start) {
                // add record to chartData array
                chartData.push({
                    x: timestampForPollutant,
                    y: valueForPollutant,
                });

                // format timestamp for display on x-axis
                const formattedLabel = moment(timestampForPollutant).format(labelFormat);
                if (!chartLabels.includes(formattedLabel)) {
                    chartLabels.push(formattedLabel);
                }
            }
        }

        // sort chartData by timestamp
        chartData.sort((a, b) => a.x - b.x);

        // delete duplicate records
        for (let i = 0; i < chartData.length - 1; i++) {
            if (chartData[i].y === chartData[i + 1].y) {
                chartData.splice(i, 1);
                i--;
            }
        }

        // create array of chart labels from sorted chartData array
        chartLabels = chartData.map(dataPoint => moment(dataPoint.x).format(labelFormat));

        // Generate a pastel color for the line based on the index of the pollutant
        const hue = (i * 137.508) % 360;
        const borderColor = `hsl(${hue}, 60%, 70%)`;
        i++;

        // Add a new dataset to the array for the current pollutant
        datasets.push({
            label: `${pollutant}`,
            data: chartData,
            fill: false,
            borderColor: borderColor,
        });
    }

    // create chart data object
    return {
        labels: chartLabels,
        datasets: datasets,
    };
}

// generate horizontal bar chart with the AQI for each location
export function generateHorizontalBarChart(cityData) {

    if (!cityData) {
        throw new Error(`No city data found.`);
    }

    let chartLabels = [];
    let chartData = [];
    // calculate AQI for each location
    const overallAQI = calculateOverallAQI(cityData);

    // create chart data object
    for (const [location, locationData] of Object.entries(overallAQI)) {
        chartLabels.push(location);
        chartData.push(locationData.aqi);
    }

    return {
        labels: chartLabels,
        datasets: [{
            label: "AQI by location",
            data: chartData,
            backgroundColor: 'rgba(54, 162, 235, 0.5)',
            borderColor: 'rgba(54, 162, 235, 1)',
            borderWidth: 1
        }]
    };
}
