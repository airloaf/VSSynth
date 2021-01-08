(this["webpackJsonplanding-page"]=this["webpackJsonplanding-page"]||[]).push([[0],{56:function(e,t,a){},57:function(e,t,a){},86:function(e,t,a){"use strict";a.r(t);var s=a(1),c=a(0),n=a.n(c),i=a(16),r=a.n(i),l=(a(56),a.p,a(57),a(12)),o=a(13),h=a(8),j=a(15),d=a(14),u=a(21),b=a(23),m=a.n(b),x=function(e){Object(j.a)(a,e);var t=Object(d.a)(a);function a(e){var s;return Object(l.a)(this,a),(s=t.call(this,e)).state={code:""},s}return Object(o.a)(a,[{key:"componentDidMount",value:function(){var e=this;m.a.get(this.props.fileURL).then((function(t){e.setState({code:t.data})})).catch((function(e){}))}},{key:"render",value:function(){return Object(s.jsx)(n.a.Fragment,{children:Object(s.jsx)(u.a,{language:"C++",text:this.state.code,showLineNumbers:!0,theme:u.b,wrapLines:!0,codeBlock:!0})})}}]),a}(n.a.Component),O=a(94),p=a(89),f=a(90),g=a(91),v=["https://raw.githubusercontent.com/airloaf/VSynth/master/examples/SimpleTone/src/main.cpp","https://raw.githubusercontent.com/airloaf/VSynth/master/examples/LowFrequencyOscillator/src/main.cpp","https://raw.githubusercontent.com/airloaf/VSynth/master/examples/piano/src/main.cpp","https://raw.githubusercontent.com/airloaf/VSynth/master/examples/SequencedBeat/src/main.cpp"],y=["https://github.com/airloaf/VSynth/tree/master/examples/SimpleTone","https://github.com/airloaf/VSynth/tree/master/examples/LowFrequencyOscillator","https://github.com/airloaf/VSynth/tree/master/examples/piano","https://github.com/airloaf/VSynth/tree/master/examples/SequencedBeat"],w=["Simple Sine Wave","Low frequency Oscillator on a sawtooth wave","Piano with an ADSR envelope","Sequencer playing Piano"],S=["audio/RecordTone.wav","audio/LFO.wav","audio/Piano.wav","audio/SequencedBeat.wav"],k=["Sine wave playing Middle-C","Sawtooth with a low frequency oscillator attached! All waveforms, except for noise(), have a 3rd parameter representing the phase shift/offset. You can attach another waveform to this parameter to create low frequency oscillation.","Piano controllable by the keyboard keys. Here the C major scale is being played. Using prebuilt patches that came with VSynth, you can get an instrument up and running fast!","Sequencer playing a tune in the background. Piano keys are playable as well, but I didn't play them while recording the sequencer beat."],V=function(e){Object(j.a)(a,e);var t=Object(d.a)(a);function a(e){var s;return Object(l.a)(this,a),(s=t.call(this,e)).state={activeExample:0},s.changeExample=s.changeExample.bind(Object(h.a)(s)),s.createCarouselItems=s.createCarouselItems.bind(Object(h.a)(s)),s}return Object(o.a)(a,[{key:"componentDidMount",value:function(){}},{key:"changeExample",value:function(e){var t=(this.state.activeExample+e)%4;this.setState({activeExample:t})}},{key:"createCarouselItems",value:function(){for(var e=[],t=0;t<4;t++)e.push(Object(s.jsx)(O.a.Item,{children:Object(s.jsxs)(p.a,{children:[Object(s.jsx)(f.a,{lg:6,style:{overflowY:"scroll",maxHeight:"50vh"},children:Object(s.jsx)(x,{fileURL:v[t]})}),Object(s.jsxs)(f.a,{lg:6,children:[Object(s.jsx)("h2",{class:"mb-5",align:"center",children:w[t]}),Object(s.jsx)("h3",{children:k[t]}),Object(s.jsx)("h4",{children:Object(s.jsxs)("a",{href:y[t],children:[Object(s.jsx)("i",{class:"fab fa-github"}),"View on GitHub!"]})}),Object(s.jsx)("div",{align:"center",children:Object(s.jsx)("audio",{controls:!0,children:Object(s.jsx)("source",{src:S[t],type:"audio/wav"})})})]})]})}));return e}},{key:"render",value:function(){var e=this;return Object(s.jsxs)(n.a.Fragment,{children:[Object(s.jsx)("h1",{class:"mb-5",children:"Code Examples"}),Object(s.jsx)(O.a,{interval:null,indicators:!1,controls:!1,align:"left",activeIndex:this.state.activeExample,children:this.createCarouselItems()}),Object(s.jsxs)(p.a,{children:[Object(s.jsx)(f.a,{lg:2,children:Object(s.jsx)(g.a,{onClick:function(){e.changeExample(3)},block:!0,variant:"outline-success",children:"Previous"})}),Object(s.jsx)(f.a,{lg:8}),Object(s.jsx)(f.a,{lg:2,children:Object(s.jsx)(g.a,{onClick:function(){e.changeExample(1)},block:!0,variant:"outline-success",children:"Next"})})]})]})}}]),a}(n.a.Component),C=a(49),F=a(92),A=a(93),D=function(e){Object(j.a)(a,e);var t=Object(d.a)(a);function a(e){var s;return Object(l.a)(this,a),(s=t.call(this,e)).dataflow=s.dataflow.bind(Object(h.a)(s)),s.examples=s.examples.bind(Object(h.a)(s)),s.features=s.features.bind(Object(h.a)(s)),s.intro=s.intro.bind(Object(h.a)(s)),s}return Object(o.a)(a,[{key:"intro",value:function(){return Object(s.jsx)("header",{class:"masthead",children:Object(s.jsx)(F.a,{className:"h-100",children:Object(s.jsxs)(p.a,{className:"h-100",children:[Object(s.jsx)(f.a,{lg:6,className:"my-auto",children:Object(s.jsxs)("div",{class:"header-content mx-auto",children:[Object(s.jsx)("h1",{class:"mb-5",children:Object(s.jsx)("img",{src:"img/LogoLarge.png"})}),Object(s.jsx)("h2",{class:"mb-5",children:"An open source audio synthesizer library for SDL2, written in C++"}),Object(s.jsxs)(A.a,{children:[Object(s.jsx)(g.a,{variant:"info",href:"https://github.com/airloaf/VSynth/releases",children:"Download"}),Object(s.jsx)(g.a,{variant:"info",href:"https://airloaf.github.io/VSynth/doxygen/annotated.html",children:"Documentation"}),Object(s.jsxs)(g.a,{variant:"info",href:"https://github.com/airloaf/VSynth/",children:[Object(s.jsx)("i",{class:"fab fa-github"})," GitHub"]})]})]})}),Object(s.jsxs)(f.a,{lg:6,className:"my-auto",children:[Object(s.jsx)("h4",{children:"MIDI Player made with VSynth! Here are some recorded tracks."}),Object(s.jsx)(C.a,{width:"100%",height:"500",scrolling:"no",frameborder:"no",allow:"autoplay",src:"https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/playlists/1189056859%3Fsecret_token%3Ds-TDUxda0JASZ&color=%23ff5500&auto_play=false&hide_related=false&show_comments=true&show_user=true&show_reposts=false&show_teaser=true&visual=true"})]})]})})})}},{key:"features",value:function(){return Object(s.jsx)(n.a.Fragment,{children:Object(s.jsx)("section",{class:"features",id:"features",children:Object(s.jsxs)("div",{class:"container",children:[Object(s.jsxs)("div",{class:"section-heading text-center",children:[Object(s.jsx)("h2",{children:"Features"}),Object(s.jsx)("p",{children:"With VSynth you have access to these features and many more!"}),Object(s.jsx)("hr",{})]}),Object(s.jsx)("div",{class:"row",children:Object(s.jsx)("div",{class:"col my-auto",children:Object(s.jsxs)("div",{class:"container-fluid",children:[Object(s.jsxs)("div",{class:"row",children:[Object(s.jsx)("div",{class:"col-lg-6",children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("img",{src:"img/Waves.png"}),Object(s.jsx)("h3",{children:"Basic Waveforms"}),Object(s.jsx)("p",{children:"All your basic waveforms included! (Sine, Triangle, Square, Sawtooth, Pulse and Noise)"})]})}),Object(s.jsx)("div",{class:"col-lg-6",children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("img",{src:"img/ADSR.png"}),Object(s.jsx)("h3",{children:"ADSR Envelopes"}),Object(s.jsx)("p",{children:"Control waveform amplitudes with ADSR envelopes!"})]})})]}),Object(s.jsxs)("div",{class:"row",children:[Object(s.jsx)("div",{class:"col-lg-6",children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("img",{src:"img/Polyphony.png"}),Object(s.jsx)("h3",{children:"Polyphony"}),Object(s.jsx)("p",{children:"Play multiple notes, sounds, instruments, etc!"})]})}),Object(s.jsx)("div",{class:"col-lg-6",children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("img",{src:"img/WAV.png"}),Object(s.jsx)("h3",{children:"WAV file output"}),Object(s.jsx)("p",{children:"Save your synthesized audio to .WAV files!"})]})})]})]})})})]})})})}},{key:"dataflow",value:function(){return Object(s.jsx)(n.a.Fragment,{children:Object(s.jsx)("section",{className:"bg-info",children:Object(s.jsxs)(F.a,{fluid:!0,children:[Object(s.jsxs)("div",{class:"section-heading text-center",children:[Object(s.jsx)("h2",{children:"How it works"}),Object(s.jsx)("p",{children:"VSynth is separated into 3 modules:"}),Object(s.jsx)("br",{}),Object(s.jsxs)(p.a,{children:[Object(s.jsx)(f.a,{lg:4,children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("h3",{children:"Middleware"}),Object(s.jsx)("p",{children:"Optional component which processes sound data before it reaches the speakers. Useful for many things such as: outputting to a WAV file, filters, transforms, etc."})]})}),Object(s.jsx)(f.a,{lg:4,children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("h3",{children:"Synthesizer"}),Object(s.jsx)("p",{children:"Main building block of VSynth. Creates a new thread and samples each of its sound generators at the given sampling rate. The sum of the samples are then processed by its middleware prior to reaching the hardware speakers."})]})}),Object(s.jsx)(f.a,{lg:4,children:Object(s.jsxs)("div",{class:"feature-item",children:[Object(s.jsx)("h3",{children:"Sound Generator"}),Object(s.jsx)("p",{children:"Generates sound data. Think of instruments, sequencers, tones, etc."})]})})]}),Object(s.jsx)("hr",{})]}),Object(s.jsx)("img",{src:"img/VSynthDataFlow.svg"})]})})})}},{key:"examples",value:function(){return Object(s.jsx)(n.a.Fragment,{children:Object(s.jsx)("section",{className:"",children:Object(s.jsx)(F.a,{fluid:!0,children:Object(s.jsx)(V,{})})})})}},{key:"render",value:function(){return Object(s.jsxs)(n.a.Fragment,{children:[this.intro(),this.features(),this.dataflow(),this.examples()]})}}]),a}(n.a.Component);var q=function(){return Object(s.jsx)("div",{className:"App",children:Object(s.jsx)(D,{})})},L=function(e){e&&e instanceof Function&&a.e(155).then(a.bind(null,280)).then((function(t){var a=t.getCLS,s=t.getFID,c=t.getFCP,n=t.getLCP,i=t.getTTFB;a(e),s(e),c(e),n(e),i(e)}))};a(85);r.a.render(Object(s.jsx)(n.a.StrictMode,{children:Object(s.jsx)(q,{})}),document.getElementById("root")),L()}},[[86,152,153]]]);
//# sourceMappingURL=main.df3c0362.chunk.js.map