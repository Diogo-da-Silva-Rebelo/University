// create HeatMap Caption
import React from 'react';
import './HeatCaption.css';

const HeatCaption = () => {
    return (
        <div className="heat-caption heat-caption-show">
            <div className="heat-caption-title">AQI Levels by EPA</div>
            <div className="heat-caption-item">
                <div className="heat-caption-color heat-green-light"></div>
                <div className="catpion-label">Good (0-50)</div>
            </div>
            <div className="heat-caption-item">
                <div className="heat-caption-color heat-green-dark"></div>
                <div className="heat-caption-label">Moderate (51-100)</div>
            </div>
            <div className="heat-caption-item">
                <div className="heat-caption-color heat-yellow"></div>
                <div className="caption-label">Unhealthy for Sensitive Groups (101-150)</div>
            </div>
            <div className="heat-caption-item">
                <div className="heat-caption-color heat-orange"></div>
                <div className="caption-label">Unhealthy (151-200)</div>
            </div>
            <div className="heat-caption-item">
                <div className="heat-caption-color heat-red"></div>
                <div className="caption-label">Very Unhealthy (201-300)</div>
            </div>
            <div className="heat-caption-item">
                <div className="heat-caption-color heat-maroon"></div>
                <div className="caption-label">Hazardous (301-500)</div>
            </div>
        </div>
    );
};

export default HeatCaption;
