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
                                    <img
                                        src="img/LogoLarge.png"
                                    />
                                </h1>
                                <h2 class="mb-5">
                                    An open source audio synthesizer library for SDL2, written in C++
                                </h2>
                                <ButtonGroup>
                                    <Button variant="info" href="https://github.com/airloaf/VSynth/releases">Download</Button>
                                    <Button variant="info" href="https://airloaf.github.io/VSynth/html/annotated.html">Documentation</Button>
                                    <Button variant="info" href="https://github.com/airloaf/VSynth/"><i class="fab fa-github"></i>{" GitHub"}</Button>
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
                {/* <Navbar /> */}
                {this.intro()}

                <section class="features" id="features">
                    <div class="container">
                        <div class="section-heading text-center">
                            <h2>Features</h2>
                            <p>With VSynth you have access to many of these features and more!</p>
                            <hr />
                        </div>
                        <div class="row">
                            <div class="col my-auto">
                                <div class="container-fluid">
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/Waves.png"}/>
                                                <h3>Basic Waveforms</h3>
                                                <p>All your basic waveforms included! (Sine, Triangle, Square, Sawtooth, Pulse and Noise)</p>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/ADSR.png"}/>
                                                <h3>ADSR Envelopes</h3>
                                                <p>Control waveform amplitudes with ADSR envelopes!</p>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/Polyphony.png"}/>
                                                <h3>Polyphony</h3>
                                                <p>Play multiple notes, sounds, instruments, etc!</p>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/WAV.png"}/>
                                                <h3>WAV file output</h3>
                                                <p>Save your synthesized audio to .WAV files!</p>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </section>

                <hr /> 
                {this.examples()}

            </React.Fragment>

        );
    }
}