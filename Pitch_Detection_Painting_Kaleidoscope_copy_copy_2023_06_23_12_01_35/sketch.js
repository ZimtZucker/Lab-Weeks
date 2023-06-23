/*
Pitch Painting Kaleidoscope

The example detects the current pitch and volume from the microphone allowing people to paint on the canvas. The note detected controls the color and the volume controls a noise function, that updates the position of the current line being drawn. The outputs are mirrored by a kaledioscope because it looks nice🎨

Built with pitchDetection model fromw

Created by Andreas Refsgaard 2020

Kaleidoscope adopted from https://p5js.org/examples/interaction-kaleidoscope.html
*/

// Symmetry corresponding to the number of reflections
let symmetry = 6;

let angle = 360 / symmetry;
let clearButton;
let sizeSlider;

let xOff;
let yOff;

let inc = 0.01;

let vol = 0.0;
let mic;
let pitch;
let audioContext;
let model_url = 'https://cdn.jsdelivr.net/gh/ml5js/ml5-data-and-models/models/pitch-detection/crepe/';

let keyRatio = 0.58;
let noteScale = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B'];
let currentNote = '';

let colors = [];

function setup() {
  createCanvas(710, 710);
  audioContext = getAudioContext();
  mic = new p5.AudioIn();
  mic.start(startPitch);

  //Change the colorMode to HSB
  colorMode(HSB); //360,100,100,1.0

  //Define the color pallet
  for (let i = 0; i < noteScale.length; i++) {
    let newColor = color(i * 360 / noteScale.length, 50, 100, 0.8);
    colors.push(newColor);
  }

  angleMode(DEGREES);

  xOff = random(10);
  yOff = random(10);

  createDiv();

  // Creating the clear screen button
  clearButton = createButton('clear');
  clearButton.mousePressed(clearScreen);

  // Setting up the slider for the thickness of the brush
  sizeSlider = createSlider(1, 10, 2, 0.1);

  background(0);
  
  textAlign(CENTER);
  let squareWidth = width/colors.length
  
  for (let i = 0; i < colors.length; i++) {
    fill(colors[i]);
    rect(i*squareWidth, 0, squareWidth, 25);
    fill(360,0,100,1);
    text(noteScale[i], i*squareWidth + squareWidth/2, 15);
  }
}

function startPitch() {
  pitch = ml5.pitchDetection(model_url, audioContext, mic.stream, modelLoaded);
}

//Load the model and get the pitch
function modelLoaded() {
  select('#status').html('Model Loaded');
  getPitch();
}

//Draw on the canvas
function draw() {
  //Use the volume from the microphone to control the size
  vol = mic.getLevel();
  //ellipse(mouseX, mouseY, vol*500);
  translate(width / 2, height / 2);


  let mx = noise(xOff) * width - width / 2;
  let my = noise(yOff) * height - height / 2;

  let pmx = noise(xOff - inc) * width - width / 2;
  let pmy = noise(yOff - inc) * height - height / 2;

  //Only start drawing if there is a bit of noise
  if (vol > 0.01) {
    for (let i = 0; i < symmetry; i++) {
      rotate(angle);
      strokeWeight(sizeSlider.value());
      line(mx, my, pmx, pmy);
      push();
      scale(1, -1);
      line(mx, my, pmx, pmy);
      pop();
    }
  }
  xOff += constrain(vol / 5,0,0.01);
  yOff += constrain(vol / 5,0,0.01);
}

//Get the pitch, find the closest note and set the fill color
function getPitch() {
  pitch.getPitch(function(err, frequency) {
    if (frequency) {
      let midiNum = freqToMidi(frequency);
      currentNote = noteScale[midiNum % 12];
      stroke(colors[midiNum % 12]);
      select('#noteAndVolume').html('Note: ' + currentNote + " - volume " + nf(vol, 1, 2));
    }
    getPitch();
  })
}

// Clear Screen function
function clearScreen() {
  background(0);
}