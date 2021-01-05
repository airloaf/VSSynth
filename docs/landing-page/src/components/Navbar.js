import React from 'react';
import Navbar from 'react-bootstrap/Navbar'

export default class VSynthNavbar extends React.Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Navbar bg="dark" variant="dark" fixed="top">
                <Navbar.Brand href="#home">
                    <img
                        alt=""
                        src="img/LogoSmall.png"
                        width="30"
                        height="30"
                        className="d-inline-block align-top"
                    />{' '}
                    VSynth
                </Navbar.Brand>
            </Navbar>

        );
    }
}