import React from 'react';
import { createRoot } from 'react-dom/client';
import tt from '@tomtom-international/web-sdk-maps';
import MarkerPopUp from "./MarkerPopUp";

export function CreateMarkers(map, weatherData) {

      const markers = [];

      for (const locationName in weatherData) {
            const locationData = weatherData[locationName];

            if (!locationData.coordinates || !locationData.coordinates.latitude || !locationData.coordinates.longitude) {
                  console.error(`Missing coordinates for location ${locationName}`);
                  continue;
            }

            const position = [locationData.coordinates.longitude, locationData.coordinates.latitude];
            const title = 'Weather';
            const weatherDataObj = locationData.weatherData;
            const name = locationName.replace("WeatherData", "");
            // make 1st letter upper
            const nameCapitalized = name.charAt(0).toUpperCase() + name.slice(1);

            const weatherPopup = (
                  <MarkerPopUp
                         title={title}
                         position={position}
                         locationName={nameCapitalized}
                         weather={weatherDataObj}
                   />
              );

            // wrap the marker in a div html element
            const popupNode = document.createElement('div');
            createRoot(popupNode).render(weatherPopup);

            let marker = new tt.Marker({
                  anchor: "bottom",
                  draggable: false,
                  markerRadius: 20,
            }).setLngLat(position).setPopup(new tt.Popup({offset: 30}).setDOMContent(popupNode)).addTo(map);

            // add marker object to the array
            markers.push(marker);
      }
      return markers;
}
