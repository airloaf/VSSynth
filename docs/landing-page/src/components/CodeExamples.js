import CodeViewer from "../components/CodeViewer"
import React from "react"
import axios from 'axios';

import { Button, Col, Row, Container, Carousel } from "react-bootstrap"
import { CodeBlock, dracula } from "react-code-blocks";

const NUM_EXAMPLES = 3;

const RAW_FILE_URLS = [
    "https://raw.githubusercontent.com/airloaf/VSynth/master/examples/SimpleTone/src/main.cpp",
    "https://raw.githubusercontent.com/airloaf/VSynth/master/examples/piano/src/main.cpp",
    "https://raw.githubusercontent.com/airloaf/VSynth/master/examples/sequenced_beat/src/main.cpp"
]

const FILE_URLS = [
    "https://github.com/airloaf/VSynth/tree/master/examples/SimpleTone",
    "https://github.com/airloaf/VSynth/tree/master/examples/piano",
    "https://github.com/airloaf/VSynth/tree/master/examples/sequenced_beat"
]

const TITLES = [
    "Simple Sine Wave",
    "Piano with an ADSR envelope",
    "Sequencer playing Piano"
]

const WAVES = [
    "audio/RecordTone.wav",
    "audio/Piano.wav",
    "audio/SequencedBeat.wav"
]

const DESCRIPTIONS = [
    "Sine wave playing Middle-C",
    "Piano controllable by the keyboard keys. Here the C major scale is being played. Using prebuilt patches that came with VSynth, you can get an instrument up and running fast!",
    "Sequencer playing a tune in the background. Piano keys are playable as well, but I didn't play them while recording the sequencer beat."
]

export default class CodeExamples extends React.Component {

    constructor(props) {
        super(props)

        this.state = {
            activeExample: 0
        }

        this.changeExample = this.changeExample.bind(this);
        this.createCarouselItems = this.createCarouselItems.bind(this);
    }

    componentDidMount() {

    }

    changeExample(amount) {
        const nextExample = (this.state.activeExample + amount) % NUM_EXAMPLES;
        this.setState({ activeExample: nextExample });
    }

    createCarouselItems() {
        var items = []

        for (var i = 0; i < NUM_EXAMPLES; i++) {

            items.push(
                <Carousel.Item>
                    <Row>
                        <Col lg={6} style={
                            {
                                overflowY: "scroll",
                                maxHeight: "50vh"

                            }
                        }>
                            <CodeViewer
                                fileURL={RAW_FILE_URLS[i]}
                            />
                        </Col>
                        <Col lg={6}>
                            <h2 class="mb-5" align={"center"}>{TITLES[i]}</h2>
                            <h3>{DESCRIPTIONS[i]}</h3>
                            <h4><a href={FILE_URLS[i]}><i class="fab fa-github"></i>View on GitHub!</a></h4>
                            <div align={"center"}>
                                <audio controls>
                                    <source src={WAVES[i]} type="audio/wav" />
                                </audio>
                            </div>
                        </Col>
                    </Row>
                </Carousel.Item>
            );
        }
        return items;
    }

    render() {
        return (
            <React.Fragment>
                <h1 class="mb-5">Code Examples</h1>
                <Carousel interval={null} indicators={false} controls={false} align={"left"} activeIndex={this.state.activeExample} >
                    {this.createCarouselItems()}
                </Carousel>
                <Row>
                    <Col lg={2}>
                        <Button onClick={() => { this.changeExample(NUM_EXAMPLES - 1) }} block>Previous</Button>
                    </Col>
                    <Col lg={8}>
                    </Col>
                    <Col lg={2}>
                        <Button onClick={() => { this.changeExample(1) }} block>Next</Button>
                    </Col>
                </Row>
            </React.Fragment>
        );
    }
}