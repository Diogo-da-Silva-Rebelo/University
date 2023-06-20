import React from 'react'

import {
    Nav,
    NavLink,
    Bars,
    NavMenu,
    NavBtn,
    NavBtnLink,
    NavBtnLinkHome,
} from "./NavbarElements";


function Index() {
    return (
        <>
            <Nav>
                <NavBtnLinkHome to="/"> </NavBtnLinkHome>
                <Bars/>
                <NavMenu>
                    <NavLink to="/maps">
                        Mapa
                    </NavLink>
                    <NavLink to="/prediction">
                        Previsão e Modelo
                    </NavLink>
                </NavMenu>
            </Nav>
        </>
    );
}

export default Index
