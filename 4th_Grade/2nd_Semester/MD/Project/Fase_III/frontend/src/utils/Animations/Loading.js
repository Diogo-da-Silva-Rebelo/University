import React, { useState, useEffect } from 'react';
import './Loading.css';

function Loading() {
    const [show, setShow] = useState(false);

    useEffect(() => {
        const timer = setTimeout(() => setShow(true), 500); // show the loading animation after 500ms

        return () => clearTimeout(timer);
    }, []);

    if (!show) {
        return null; // don't render anything if loading animation is not ready to be shown
    }

    return (
        <div className="loading">
            <div className="loading-spinner"></div>
            <div className="loading-text">Loading...</div>
        </div>
    );
}

export default Loading;
