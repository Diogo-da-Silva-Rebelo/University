import React, {useState, useEffect, useRef, useMemo} from 'react';
import tt, {services} from '@tomtom-international/web-sdk-maps';
import '@tomtom-international/web-sdk-maps/dist/maps.css';
import '@tomtom-international/web-sdk-plugin-searchbox';
import './TrafficData/TrafficButton/TrafficLayerButton.css'
import './TrafficData/RotationButton/RotationButton.css'
import faRoad from '@fortawesome/fontawesome-free-solid/faRoad';
import { faLungs } from '@fortawesome/free-solid-svg-icons';
import {FontAwesomeIcon} from '@fortawesome/react-fontawesome';
import SearchBox from "@tomtom-international/web-sdk-plugin-searchbox";
import Caption from "../Map/TrafficData/TrafficCaption/Caption";
import HeatCaption from "../Map/HeatData/HeatCaption/HeatCaption";
import {faAdjust, faArrowsAlt, faFlag} from "@fortawesome/fontawesome-free-solid";
import {CreateMarkers} from "./Markers/CreateMarkers";
import predData from './HeatData/predition.js';

//const ADDRESS = 'http://air-visual.azurewebsites.net';
 const ADDRESS = 'http://localhost:3001';
 const TOMTOM_KEY= 'dBUez1ApxtAcqGPmPUKmKMFTE7SiKgba';

function Map() {
    const [map, setMap] = useState(null);
    const mapElement = useRef(null);
    const [trafficLayerIsVisible, setTrafficLayerIsVisible] = useState(false);
    const [showTrafficCaption, setShowTrafficCaption] = useState(false);
    const [is2D, setIs2D] = useState(false);
    const [heatmapLayerIsVisible, setHeatmapLayerIsVisible] = useState(false);
    const [showHeatmapCaption, setShowHeatmapCaption] = useState(false);
    const [markersLayerIsVisible, setMarkersLayerIsVisible] = useState(true);
    const [heatmapLayer, setHeatmapLayer] = useState();
    const [preditionLayer, setPreditionLayer] = useState(false);
    const [markers, setMarkers] = useState([]);
    const [preditionLayerIsVisible, setPreditionLayerIsVisible] = useState(false);
    const [bragaWeatherData, setBragaWeatherData] = useState({});
    const [portoWeatherData, setPortoWeatherData] = useState({});
    const [lisboaWeatherData, setLisboaWeatherData] = useState({});
    const [faroWeatherData, setFaroWeatherData] = useState({});
    const [evoraWeatherData, setEvoraWeatherData] = useState({});
    const [leiriaWeatherData, setLeiriaWeatherData] = useState({});
    const [santaremWeatherData, setSantaremWeatherData] = useState({});
    const [viseuWeatherData, setViseuWeatherData] = useState({});
    const [vianaWeatherData, setVianaWeatherData] = useState({});
    const [vilaRealWeatherData, setVilaRealWeatherData] = useState({});
    const [aveiroWeatherData, setAveiroWeatherData] = useState({});
    const [casteloBrancoWeatherData, setCasteloBrancoWeatherData] = useState({});

    useEffect(() => {

        const map = tt.map({
                key: TOMTOM_KEY,
                container: mapElement.current,
                basePath: '/sdk',
                theme: {
                    style: 'main',
                    layer: 'basic',
                },
                center: [-8.4229, 41.55176],
                zoom: 6,
                pitch: 60,
                refresh: 300000,
            }
        );


        const searchOptions = {
            key: TOMTOM_KEY,
            language: "en-GB",
            limit: 20,
            idxSet: 'POI'
        };

        const searchBoxOptions = {
            minNumberOfCharacters: 2, // minimum number of characters required before suggestions are shown
            searchOptions: searchOptions, // types of locations to search for (optional)
            autocompleteOptions: {
                key: TOMTOM_KEY,
                language: "en-GB",
            },
        };

        const ttSearchBox = new SearchBox(services, searchBoxOptions);

        ttSearchBox.on("tomtom.searchbox.resultselected", handleSearchResultSelection);

        // controls
        map.addControl(new tt.NavigationControl());
        map.addControl(new tt.ScaleControl());
        map.addControl(new tt.GeolocateControl());
        //map.addControl(ttSearchBox, "top-left");

        // on load
        map.on("load", function () {
            setMap(map);
            setTrafficLayerIsVisible(false);
            setShowTrafficCaption(false);
            setIs2D(false);
            setHeatmapLayerIsVisible(false);
            setShowHeatmapCaption(false);
            setMarkersLayerIsVisible(true);
            setPreditionLayerIsVisible(false);
        });
    }, []);

    useEffect(() => {
        if (map &&
            bragaWeatherData &&
            portoWeatherData &&
            lisboaWeatherData &&
            faroWeatherData &&
            evoraWeatherData &&
            leiriaWeatherData &&
            santaremWeatherData &&
            viseuWeatherData &&
            vianaWeatherData &&
            vilaRealWeatherData &&
            aveiroWeatherData &&
            casteloBrancoWeatherData) {
            if (markersLayerIsVisible) {
                const weatherData = {
                    bragaWeatherData,
                    portoWeatherData,
                    lisboaWeatherData,
                    faroWeatherData,
                    evoraWeatherData,
                    leiriaWeatherData,
                    santaremWeatherData,
                    viseuWeatherData,
                    vianaWeatherData,
                    vilaRealWeatherData,
                    aveiroWeatherData,
                    casteloBrancoWeatherData
                }
                if (markers.length === 0) {
                    const createdMarkers = CreateMarkers(map, weatherData);
                    setMarkers(createdMarkers);
                }
                // add markers to map
                markers.forEach(marker => marker.addTo(map));
            } else {
                markers.forEach(marker => marker.remove());
                setMarkers([]);
            }
        }
    }, [map,
        bragaWeatherData,
        portoWeatherData,
        lisboaWeatherData,
        faroWeatherData,
        evoraWeatherData,
        leiriaWeatherData,
        santaremWeatherData,
        viseuWeatherData,
        vianaWeatherData,
        vilaRealWeatherData,
        aveiroWeatherData,
        casteloBrancoWeatherData,
        markersLayerIsVisible,
    ]);

    // create Prediction layer
    useEffect(() => {

        if (map && predData) {
            const PredHeatMapLayer = {
                id: 'predictions',
                source: {
                    type: 'geojson',
                    data: {
                        type: 'FeatureCollection',
                        features: predData.features,
                    },
                },
                type: 'heatmap',
                paint: {
                    'heatmap-radius': [
                        'interpolate',
                        ['linear'],
                        ['zoom'],
                        0, 10,
                        14, 100,
                        22, 200
                    ],
                    'heatmap-weight': {
                        type: 'exponential',
                        property: 'AQI',
                        stops: [
                            [0, 0],
                            [50, 1],
                            [100, 2],
                            [150, 3],
                            [200, 4],
                            [300, 5],
                            [500, 6],
                        ],
                    },
                    'heatmap-color': [
                        'interpolate',
                        ['linear'],
                        ['heatmap-density'],
                        0, 'rgba(0, 255, 0, 0)',
                        0.1, 'rgba(0, 255, 0, 1)',
                        0.2, 'rgba(255, 255, 0, 1)',
                        0.3, 'rgba(255, 165, 0, 1)',
                        0.4, 'rgba(255, 69, 0, 1)',
                        0.5, 'rgba(128, 0, 0, 1)',
                        1, 'rgba(128, 0, 0, 1)'
                    ]
                },
            };

            setPreditionLayer(PredHeatMapLayer);

            // Add the heatmap layer to the map
            if (map && !map.getSource('predictions')) {
                map.addLayer(PredHeatMapLayer);
                map.setLayoutProperty('predictions', 'visibility', 'none');
            }
        }
    }, [map, predData]);


    // create Heatmap layer
    useEffect(() => {
        fetch(`${ADDRESS}/map`)
            .then(res => res.json())
            .then(data => {
                // create Layer and setLayer
                const HeatMapLayer = {
                    id: 'density',
                    source: {
                        type: 'geojson',
                        data,
                    },
                    type: 'heatmap',
                    paint: {
                        'heatmap-radius': [
                            "interpolate",
                            ["linear"],
                            ["zoom"],
                            0, 10,
                            14, 100,
                            22, 200
                        ],
                        'heatmap-weight': {
                            type: 'exponential',
                            property: 'aqi',
                            stops: [
                                [0, 0],
                                [50, 1],
                                [100, 2],
                                [150, 3],
                                [200, 4],
                                [300, 5],
                                [500, 6],
                            ],
                        },
                        'heatmap-color': [
                            'interpolate',
                            ['linear'],
                            ['heatmap-density'],
                            0, 'rgba(0, 255, 0, 0)',
                            0.1, 'rgb(0, 255, 0)',
                            0.2, 'rgb(255, 255, 0)',
                            0.3, 'rgb(255, 165, 0)',
                            0.4, 'rgb(255, 69, 0)',
                            0.5, 'rgb(128, 0, 0)',
                            1, 'rgb(128, 0, 0)'
                        ]
                    },
                };
                setHeatmapLayer(HeatMapLayer);
                // Add the heatmap layer to the map
                if (map && !map.getSource('density')) {
                    map.addLayer(HeatMapLayer);
                    map.setLayoutProperty('density', 'visibility', 'none');
                }
            })
            .catch(err => {
                console.error(err);
            });

        // Fetch data every 30 minutes
        const intervalId = setInterval(() => {
            fetch(`${ADDRESS}/map`)
                .then(res => res.json())
                .then(data => {
                    // Update Layer and setLayer
                    const HeatMapLayer = {
                        ...heatmapLayer,
                        source: {
                            type: 'geojson',
                            data,
                        },
                    };
                    setHeatmapLayer(HeatMapLayer);
                    // Update the heatmap layer on the map
                    // check if the layer is created before set the data
                    map.getSource('density').setData(data);
                })
                .catch(err => {
                    console.error(err);
                });
        }, 30 * 60 * 1000); // 30 minutes in milliseconds

        // Clear the interval on unmount
        return () => clearInterval(intervalId);
    }, [map]);

    // toggle traffic layer effect
    useEffect(() => {
        if (map && trafficLayerIsVisible) {
            map.showTrafficFlow();
            setShowTrafficCaption(true)
        } else if (map) {
            map.hideTrafficFlow();
            setShowTrafficCaption(false)
        }
    }, [map, trafficLayerIsVisible]);


    // toggle 2D/3D effect
    useEffect(() => {
        if (map && is2D) {
            map.setPitch(0);
        } else if (map) {
            map.setPitch(60);
        }
    }, [is2D]);

    // toggle heatmap layer effect
    useEffect(() => {
        if (map && heatmapLayerIsVisible && map.getSource('density')) {
            map.setLayoutProperty('density', 'visibility', 'visible');
            setShowHeatmapCaption(true);
        } else if (map && map.getSource('density'))  {
            map.setLayoutProperty('density', 'visibility', 'none');
            setShowHeatmapCaption(false);
        }
    }, [map, heatmapLayerIsVisible]);


    // toggle prediction layer effect
    useEffect(() => {
        if (map && preditionLayerIsVisible) {
            map.setLayoutProperty('predictions', 'visibility', 'visible');
        } else if (map) {
            map.setLayoutProperty('predictions', 'visibility', 'none');
        }
    }, [map, preditionLayerIsVisible]);


    useEffect(() => {
        const fetchCityWeatherData = async () => {
            try {
                const response = await fetch(
                    `${ADDRESS}/maps/weather`
                );
                const citiesWeatherData = await response.json();

                // set air data variables
                setBragaWeatherData(citiesWeatherData['Braga']);
                setPortoWeatherData(citiesWeatherData['Porto']);
                setLisboaWeatherData(citiesWeatherData['Lisboa']);
                setFaroWeatherData(citiesWeatherData['Faro']);
                setEvoraWeatherData(citiesWeatherData['Évora']);
                setLeiriaWeatherData(citiesWeatherData['Leiria']);
                setSantaremWeatherData(citiesWeatherData['Santarém']);
                setViseuWeatherData(citiesWeatherData['Viseu']);
                setVianaWeatherData(citiesWeatherData['Viana do Castelo']);
                setVilaRealWeatherData(citiesWeatherData['Vila Real']);
                setAveiroWeatherData(citiesWeatherData['Aveiro']);
                setCasteloBrancoWeatherData(citiesWeatherData['Castelo Branco']);
            } catch (error) {
                console.error("Error fetching weather data: " + error);
            }
        }

        // fetch data on mount
        fetchCityWeatherData().then(() => console.log("Weather data fetched"));

        // fetch data every 30 minutes
        const intervalId = setInterval(fetchCityWeatherData, 30 * 60 * 1000);

        // clear interval on unmount
        return () => clearInterval(intervalId);
    }, []);


    const toggleTrafficLayer = () => {
        setTrafficLayerIsVisible(!trafficLayerIsVisible);
        setShowTrafficCaption(!showTrafficCaption);
    };

    const toggleHeatMap = () => {
        setHeatmapLayerIsVisible(!heatmapLayerIsVisible);
        setShowHeatmapCaption(!showHeatmapCaption);
    };

    const toggleMarkers = () => {
        setMarkersLayerIsVisible(!markersLayerIsVisible);
    };

    const to2D = () => {
        setIs2D(!is2D);
    };

    const togglePredictMap = () => {
        setPreditionLayerIsVisible(!preditionLayerIsVisible);
    };

    function handleSearchResultSelection(event) {
        const { data } = event;
        const { position } = data.results[0];
        map.flyTo(position, { zoom: 15 });
    }


    return (
        <div>
            <div ref={mapElement} style={{ width: '100%', height: '1000px' }} />
            <div style={{ position: 'absolute', top: '226px', right: '8px' }}>
                <button className="traffic-button" onClick={toggleTrafficLayer}>
                    <FontAwesomeIcon icon={faRoad} size="lg" color={trafficLayerIsVisible ? '#00b4d8' : '#6c757d'} />
                </button>
                <button className="rotation-button" onClick={to2D}>
                    <FontAwesomeIcon icon={faArrowsAlt} size="lg" color={is2D ? '#00b4d8' : '#6c757d'} />
                </button>
                {showTrafficCaption && <Caption />}
                <button className="rotation-button" onClick={toggleHeatMap}>
                    <FontAwesomeIcon icon={faAdjust} size="lg" color={heatmapLayerIsVisible ? '#00b4d8' : '#6c757d'} />
                </button>
                {showHeatmapCaption && <HeatCaption />}
                <button className='rotation-button' onClick={toggleMarkers}>
                    <FontAwesomeIcon icon={faFlag} size="lg" color={markersLayerIsVisible ? '#00b4d8' : '#6c757d'} />
                </button>
                <button className='rotation-button' onClick={togglePredictMap}>
                    <FontAwesomeIcon icon={faLungs} size="lg" color={preditionLayerIsVisible ? '#00b4d8' : '#6c757d'} />
                </button>
            </div>
        </div>
    );
}

export default Map;