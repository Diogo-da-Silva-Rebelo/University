import styled from 'styled-components';
import { NavLink as Link } from 'react-router-dom';
import { FaBars } from 'react-icons/fa';

export const Nav = styled.nav`
  background: #d3d392;
  height: 80px;
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 50px;
  z-index: 10;

  @media screen and (max-width: 768px) {
    padding: 0 30px;
  }
`;

export const NavLink = styled(Link)`
    color: #fff;
    display: flex;
    align-items: center;
    text-decoration: none;
    padding: 0 1.5rem;
    height: 100%;
    cursor: pointer;
  position: relative;
  &.active {
    color: #fff;
    font-weight: bold;
  }
  &::after {
    content: '';
    position: absolute;
    left: 0;
    bottom: -30px;
    width: 100%;
    height: 6px;
    background-color: #fff;
    opacity: 0;
    transition: opacity 0.3s ease-in-out;
  }
  &:hover::after {
    opacity: 1;
  }
`;

export const Logo = styled.img`
    width: 150px;
    height: 150px;
`;

export const NavRight = styled.div`
    display: flex;
    align-items: center;
`;

export const Bars = styled(FaBars)`
    display: none;
    color: #2C3333;
    @media screen and (max-width: 768px) {
        display: block;
        position: absolute;
        top: 0;
        right: 0;
        transform: translate(-100%, 75%);
        font-size: 1.8rem;
        cursor: pointer;
    }
`;

export const NavMenu = styled.div`
    display: flex;
    align-items: center;
    margin-right: 20px;
    margin-left: auto;
    @media screen and (max-width: 768px) {
        display: none;
    }
`;

export const NavBtn = styled.nav`
    display: flex;
    align-items: center;
    @media screen and (max-width: 768px) {
        display: none;
    }
`;

export const NavBtnLink = styled(Link)`
    border-radius: 4px;
    background: #0E8388;
    padding: 10px 22px;
    color: #fff;
    border: none;
    outline: none;
    cursor: pointer;
    transition: all 0.2s ease-in-out;
    text-decoration: none;
    &:hover {
        transition: all 0.2s ease-in-out;
        background: #fff;
        color: #0E8388;
    }
`;

export const NavBtnLinkHome = styled(Link)`
    border-radius: 4px;
    padding: 10px 22px;
    border: none;
    outline: none;
    cursor: pointer;
    text-decoration: none;
`;
