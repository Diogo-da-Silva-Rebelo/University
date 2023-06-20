import React from "react";
import BackImage from "../Background/BackImage";
import InfoSection from "../InfoSection";
import {homeObjOne} from "../InfoSection/Data";
function Home () {
    return (
        <>
            <BackImage/>
            <InfoSection {...homeObjOne} />
        </>
    );
}

export default Home;