import CodeExamples from "../components/CodeExamples"
import Iframe from 'react-iframe'
import Navbar from "../components/Navbar"
import React from 'react';
import axios from 'axios';

import { CodeBlock, dracula } from "react-code-blocks";
import { Container, Row, Col, ButtonGroup, Button, Carousel } from "react-bootstrap"


export default class HomePage extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            pianoCode: ""
        };

        this.intro = this.intro.bind(this);
        this.features = this.features.bind(this);
        this.examples = this.examples.bind(this);
    }

    componentDidMount() {
        axios.get('https://raw.githubusercontent.com/airloaf/VSynth/master/examples/SimpleTone/src/main.cpp')
            .then(res => {
                this.setState({ pianoCode: res.data });
            })
            .catch(err => {
            })
    }

    intro() {
        return (
            <header class="masthead">
                <Container className="h-100">
                    <Row className="h-100">

                        <Col lg={6} className="my-auto">
                            <div class="header-content mx-auto">
                                <h1 class="mb-5">
                                    <img src="img/LogoLarge.png" />
                                    </h1>
                                <h2 class="mb-5">
                                    Open source audio synthesizer for SDL2, written in C++
                                </h2>
                                <ButtonGroup>
                                    <Button variant="success">Download</Button>
                                    <Button variant="success">Documentation</Button>
                                    <Button variant="success">Examples</Button>
                                </ButtonGroup>
                            </div>
                        </Col>
                        <Col lg={6} className="my-auto">
                            <h4>
                                MIDI Player made with VSynth! Here are some recorded tracks.
                            </h4>
                            <Iframe
                                width="100%"
                                height="500"
                                scrolling="no"
                                frameborder="no"
                                allow="autoplay"
                                src="https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/playlists/1189056859%3Fsecret_token%3Ds-TDUxda0JASZ&color=%23ff5500&auto_play=false&hide_related=false&show_comments=true&show_user=true&show_reposts=false&show_teaser=true&visual=true"
                            >
                            </Iframe>
                        </Col>
                    </Row>
                </Container>
            </header>
        );
    }

    features() {
        return (
            <React.Fragment>

            </React.Fragment>
        );
    }

    examples() {
        return (
            <React.Fragment>
                <section className="">
                    <Container fluid>
                        <CodeExamples />
                    </Container>
                </section>
            </React.Fragment>
        );
    }

    render() {
        return (
            <React.Fragment>
                <Navbar />
                {this.intro()}
                {this.examples()}

                <section class="download bg-primary text-center" id="download">
                    <div class="container">
                        <div class="row">
                            <div class="col-md-8 mx-auto">
                                <h2 class="section-heading">Discover what all the buzz is about!</h2>
                                <p>Our app is available on any mobile device! Download now to get started!</p>
                                <div class="badges">
                                    <a class="badge-link" href="#"><img src="img/google-play-badge.svg" alt="" /></a>
                                    <a class="badge-link" href="#"><img src="img/app-store-badge.svg" alt="" /></a>
                                </div>
                            </div>
                        </div>
                    </div>
                </section>

                <section class="features" id="features">
                    <div class="container">
                        <div class="section-heading text-center">
                            <h2>Unlimited Features, Unlimited Fun</h2>
                            <p class="text-muted">Check out what you can do with this app theme!</p>
                            <hr />
                        </div>
                        <div class="row">
                            <div class="col-lg-4 my-auto">
                                <div class="device-container">
                                    <div class="device-mockup iphone6_plus portrait white">
                                        <div class="device">
                                            <div class="screen">
                                                {/* <!-- Demo image for screen mockup, you can put an image here, some HTML, an animation, video, or anything else! --> */}
                                                <img src="img/demo-screen-1.jpg" class="img-fluid" alt="" />
                                            </div>
                                            <div class="button">
                                                {/* <!-- You can hook the "home button" to some JavaScript events or just remove it --> */}
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div class="col-lg-8 my-auto">
                                <div class="container-fluid">
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <i class="icon-screen-smartphone text-primary"></i>
                                                <h3>Device Mockups</h3>
                                                <p class="text-muted">Ready to use HTML/CSS device mockups, no Photoshop required!</p>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <i class="icon-camera text-primary"></i>
                                                <h3>Flexible Use</h3>
                                                <p class="text-muted">Put an image, video, animation, or anything else in the screen!</p>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <i class="icon-present text-primary"></i>
                                                <h3>Free to Use</h3>
                                                <p class="text-muted">As always, this theme is free to download and use for any purpose!</p>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <i class="icon-lock-open text-primary"></i>
                                                <h3>Open Source</h3>
                                                <p class="text-muted">Since this theme is MIT licensed, you can use it commercially!</p>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </section>

                <section class="cta">
                    <div class="cta-content">
                        <div class="container">
                            <h2>Stop waiting.<br />Start building.</h2>
                            <a href="#contact" class="btn btn-outline btn-xl js-scroll-trigger">Let's Get Started!</a>
                        </div>
                    </div>
                    <div class="overlay"></div>
                </section>

                <section class="contact bg-primary" id="contact">
                    <div class="container">
                        <h2>We
        <i class="fas fa-heart"></i>
        new friends!</h2>
                        <ul class="list-inline list-social">
                            <li class="list-inline-item social-twitter">
                                <a href="#">
                                    <i class="fab fa-twitter"></i>
                                </a>
                            </li>
                            <li class="list-inline-item social-facebook">
                                <a href="#">
                                    <i class="fab fa-facebook-f"></i>
                                </a>
                            </li>
                            <li class="list-inline-item social-google-plus">
                                <a href="#">
                                    <i class="fab fa-google-plus-g"></i>
                                </a>
                            </li>
                        </ul>
                    </div>
                </section>

                <footer>
                    <div class="container">
                        <p>&copy; Your Website 2020. All Rights Reserved.</p>
                        <ul class="list-inline">
                            <li class="list-inline-item">
                                <a href="#">Privacy</a>
                            </li>
                            <li class="list-inline-item">
                                <a href="#">Terms</a>
                            </li>
                            <li class="list-inline-item">
                                <a href="#">FAQ</a>
                            </li>
                        </ul>
                    </div>
                </footer>
            </React.Fragment>

        );
    }
}