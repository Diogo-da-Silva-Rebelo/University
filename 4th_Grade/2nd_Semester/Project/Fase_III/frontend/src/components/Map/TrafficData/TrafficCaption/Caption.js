import React from 'react';
import './Caption.css';

const Caption = () => {
    return (
        <div className="caption caption-show">
           <div className="caption-title">Traffic Flow Levels</div>
            <div className="caption-item">
                <div className="caption-color green-light"></div>
                <div className="catpion-label">Free</div>
            </div>
            <div className="caption-item">
                <div className="caption-color green-dark"></div>
                <div className="caption-label">Less Free</div>
            </div>
            <div className="caption-item">
                <div className="caption-color yellow"></div>
                <div className="caption-label">Moderate</div>
            </div>
            <div className="caption-item">
                <div className="caption-color orange"></div>
                <div className="caption-label">Moderate Congestion</div>
            </div>
            <div className="caption-item">
                <div className="caption-color red"></div>
                <div className="caption-label">Heavy Congestion</div>
            </div>
        </div>
    );
};

export default Caption;
