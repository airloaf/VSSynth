import CodeExamples from "../components/CodeExamples"
import Iframe from 'react-iframe'
import React from 'react';

import { Container, Row, Col, ButtonGroup, Button } from "react-bootstrap"


export default class HomePage extends React.Component {
    constructor(props) {
        super(props);

        this.dataflow = this.dataflow.bind(this);
        this.examples = this.examples.bind(this);
        this.features = this.features.bind(this);
        this.intro = this.intro.bind(this);
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
                                        src="https://raw.githubusercontent.com/airloaf/VSSynth/master/branding/LogoLarge.png"
                                    />
                                </h1>
                                <h2 class="mb-5">
                                    An open source audio synthesizer library for SDL2, written in C++
                                </h2>
                                <ButtonGroup>
                                    <Button variant="info" href="https://github.com/airloaf/VSSynth/releases">Download</Button>
                                    <Button variant="info" href="https://airloaf.github.io/VSSynth/doxygen/annotated.html">Documentation</Button>
                                    <Button variant="info" href="https://github.com/airloaf/VSSynth/"><i class="fab fa-github"></i>{" GitHub"}</Button>
                                </ButtonGroup>
                            </div>
                        </Col>
                        <Col lg={6} className="my-auto">
                            <h4>
                                MIDI Player made with VSSynth! Here are some recorded tracks.
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
                <section class="features" id="features">
                    <div class="container">
                        <div class="section-heading text-center">
                            <h2>Features</h2>
                            <p>With VSSynth you have access to these features and many more!</p>
                            <hr />
                        </div>
                        <div class="row">
                            <div class="col my-auto">
                                <div class="container-fluid">
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/Waves.png"} />
                                                <h3>Basic Waveforms</h3>
                                                <p>All your basic waveforms included! (Sine, Triangle, Square, Sawtooth, Pulse and Noise)</p>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/ADSR.png"} />
                                                <h3>ADSR Envelopes</h3>
                                                <p>Control waveform amplitudes with ADSR envelopes!</p>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/Polyphony.png"} />
                                                <h3>Polyphony</h3>
                                                <p>Play multiple notes, sounds, instruments, etc!</p>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="feature-item">
                                                <img src={"img/WAV.png"} />
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
            </React.Fragment>
        );
    }

    dataflow() {
        return (
            <React.Fragment>
                <section className="bg-info">
                    <Container fluid>
                        <div class="section-heading text-center">
                            <h2>How it works</h2>
                            <p>VSSynth is separated into 3 modules:</p>
                            <br />
                            <Row>
                                <Col lg={4}>
                                    <div class="feature-item">
                                        <h3>Middleware</h3>
                                        <p>
                                            Optional component which processes sound data before it reaches the speakers.
                                            Useful for many things such as: outputting to a WAV file, filters, transforms, etc.
                                        </p>
                                    </div>
                                </Col>
                                <Col lg={4}>
                                    <div class="feature-item">
                                        <h3>Synthesizer</h3>
                                        <p>
                                            Main building block of VSSynth.
                                            Creates a new thread and samples each of
                                            its sound generators at the given sampling rate.
                                            The sum of the samples are then processed
                                            by its middleware prior to reaching
                                            the hardware speakers.
                                        </p>
                                    </div>
                                </Col>
                                <Col lg={4}>
                                    <div class="feature-item">
                                        <h3>Sound Generator</h3>
                                        <p>
                                            Generates sound data. Think of instruments, sequencers, tones, etc.
                                        </p>
                                    </div>
                                </Col>
                            </Row>
                            <hr />
                        </div>
                        <img
                            src="img/VSSynthDataFlow.svg"
                        />
                    </Container>
                </section>
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
                {this.intro()}

                {this.features()}
                {this.dataflow()}
                {this.examples()}
            </React.Fragment>
        );
    }
}