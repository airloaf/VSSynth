import React from 'react';
import { CodeBlock, dracula } from "react-code-blocks";
import axios from 'axios';

export default class CodeViewer extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            code: ""
        }
    }

    componentDidMount() {
        axios.get(this.props.fileURL)
            .then(res => {
                this.setState({ code: res.data });
            })
            .catch(err => {
            })
    }

    render() {
        return (
            <React.Fragment>
                <CodeBlock
                    language="C++"
                    text={this.state.code}
                    showLineNumbers={true}
                    theme={dracula}
                    wrapLines={true}
                    codeBlock
                />
            </React.Fragment>
        );

    }
}