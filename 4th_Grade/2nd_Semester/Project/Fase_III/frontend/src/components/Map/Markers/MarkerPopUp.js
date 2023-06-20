import React from 'react';
import './MarkerPopUp.css';
function MarkerPopUp({ title, position, locationName, weather }) {

    const [lon, lat] = position;
    function renderValue(value) {
        if (typeof value === 'object') {
            return (
                <ul>
                    {Object.entries(value).map(([key, val]) => (
                        <li key={key}>
                            {key}: {renderValue(val)}
                        </li>
                    ))}
                </ul>
            );
        } else {
            return {value};
        }
    }

    return (
        <div className="marker-popup">
            <h3>{title} for {locationName}</h3>
            <p>Coordinates: {lat}, {lon}</p>
            <ul>
                <li>
                    <img src="icon-main-weather.svg" alt="main weather" />{' '}
                    Main: {weather.mainWeather.description}
                </li>
                <li>
                    <img src="icon-cloudiness.svg" alt="cloudiness" />{' '}
                    Cloudiness: {weather.cloudiness} %
                </li>
                <li>
                    <img src="icon-humidity.svg" alt="precipitation" />{' '}
                    Humidity: {weather.humidity} %
                </li>
                <li>
                    <img src="icon-pressure.svg" alt="pressure" />{' '}
                    Pressure: {weather.pressure} hPa
                </li>
                <li>
                    <img src="icon-temp.svg" alt="temperature" />{' '}
                    Temperature: {weather.temp.min} - {weather.temp.max} °C
                </li>
                <li>
                    <img src="icon-wind.svg" alt="wind" />{' '}
                    Wind: {weather.wind.direction}°, {weather.wind.speed} m/s
                </li>
            </ul>
            <p>Last Update: {new Date(weather.atualTimestamp).toLocaleString()}</p>
        </div>
    );
}

export default MarkerPopUp;
