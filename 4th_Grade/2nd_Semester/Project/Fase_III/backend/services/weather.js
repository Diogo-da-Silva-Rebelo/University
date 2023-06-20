// Fetch data from API OpenAQ
// example of data
/*
{
  "coord": {
    "lon": 10.99,
    "lat": 44.34
  },
  "weather": [
    {
      "id": 501,
      "main": "Rain",
      "description": "moderate rain",
      "icon": "10d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 298.48,
    "feels_like": 298.74,
    "temp_min": 297.56,
    "temp_max": 300.05,
    "pressure": 1015,
    "humidity": 64,
    "sea_level": 1015,
    "grnd_level": 933
  },
  "visibility": 10000,
  "wind": {
    "speed": 0.62,
    "deg": 349,
    "gust": 1.18
  },
  "rain": {
    "1h": 3.16
  },
  "clouds": {
    "all": 100
  },
  "dt": 1661870592,
  "sys": {
    "type": 2,
    "id": 2075663,
    "country": "IT",
    "sunrise": 1661834187,
    "sunset": 1661882248
  },
  "timezone": 7200,
  "id": 3163858,
  "name": "Zocca",
  "cod": 200
}
 */
require('dotenv').config();
async function fetchWeatherData(city) {
    let weatherData;
    try {
        const API_key = process.env.OPEN_WEATHER_KEY;
        let lat, lon;
        switch (city) {
            case 'Braga':
                lat = 41.5472749;
                lon = -8.4114212;
                break;
            case 'Porto':
                lat = 41.162768;
                lon = -8.622642;
                break;
            case 'Lisboa':
                lat = 38.7435977;
                lon = -9.2426044;
                break;
            case 'Faro':
                lat = 37.0177766;
                lon = -7.9873127;
                break;
            case 'Évora':
                lat = 38.5666667;
                lon = -7.9;
                break;
            case 'Leiria':
                lat = 39.74362;
                lon = -8.80705;
                break;
            case 'Santarém':
                lat = 39.2333333;
                lon = -8.6833333;
                break;
            case 'Viseu':
                lat = 40.661014;
                lon = -7.909714;
                break;
            case 'Viana do Castelo':
                lat = 41.69345;
                lon = -8.83268;
                break;
            case 'Vila Real':
                lat = 41.3000000;
                lon = -7.7500000;
                break;
            case 'Aveiro':
                lat = 40.640502;
                lon = -8.653753;
                break;
            case 'Castelo Branco':
                lat = 39.822191;
                lon = -7.490869;
                break;
            default:
                break;
        }

        const url = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=${API_key}&units=metric`;
        const response = await fetch(url);
        const data = await response.json();

        const coordinates = data.coord;
        const latitude = coordinates.lat;
        const longitude = coordinates.lon;
        const atualTimestamp = Date.now();
        const lastUpdated = data.dt * 1000 ;
        const mainWeather = data.weather[0];
        const mainCondition = mainWeather.main;
        const description = mainWeather.description;
        const temp = data.main;
        const tempMin = temp.temp_min;
        const tempMax = temp.temp_max;
        const pressure = temp.pressure;
        const humidity = temp.humidity;
        const wind = data.wind;
        const windSpeed = wind.speed;
        const windDirection = wind.deg;
        const rain = data.rain || {};
        const rain1h = rain["1h"] || null;
        const rain3h = rain["3h"] || null;
        const cloudiness = data.clouds.all;

        weatherData = {
            coordinates: {
                latitude: latitude,
                longitude: longitude
            },
            atualTimestamp: atualTimestamp,
            lastUpdated: lastUpdated,
            mainWeather: {
                mainCondition: mainCondition,
                description: description
            },
            temp: {
                min: tempMin,
                max: tempMax
            },
            pressure: pressure,
            humidity: humidity,
            wind: {
                speed: windSpeed,
                direction: windDirection
            },
            rain: {
                "1h": rain1h,
                "3h": rain3h
            },
            cloudiness: cloudiness
        };
        return weatherData;
    } catch (error) {
        console.error('Error fetching data from OpenAQ API:', error);
    }
}

module.exports = {
    fetchWeatherData,
};
