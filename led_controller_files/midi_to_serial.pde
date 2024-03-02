import themidibus.*;
import javax.sound.midi.MidiMessage;
import processing.serial.*;

MidiBus midi;
IntList activeNotes = new IntList();
Serial arduino;
String valToSend;

//*** TODO: put name of virtual midi port in variable 'PORT_NAME' ****
// REFER TO VIDEO: https://youtu.be/3bhiUGFt6as 
String PORT_NAME = "Bus 1";
// *************


// run when your sketch runs
void setup(){
  midi = new MidiBus(this, PORT_NAME, -1);
  
  // NOTE: Depending on your computer configuration, you may need to change 
  // the '[1]' below to a different number, most likely '[0]' or '[2]'
  String port = Serial.list()[1];
  arduino = new Serial(this, port, 9600);
}


// run repeatedly every frame
void draw(){
  if(activeNotes.size() > 0){
    for(int n = 0; n < activeNotes.size(); n++){
      arduino.write(activeNotes.get(n));
    }
  } else {
    arduino.write(0);
  }
  // DEBUGGING: uncomment line below to see which notes are active
  println(activeNotes);
}

// called whenever we receive a midi message
void midiMessage(MidiMessage m){
  
  // DEBUGGING: uncomment line below to read midi note message
  //println(m.getMessage()[1]);
  
  // the message type (eg note on/off)
  int status = m.getStatus();
  
  // data like which note (c# vs c etc)
  int msgData = m.getMessage()[1];
  
  if(status == 144) noteOn(msgData);
  if(status == 128) noteOff(msgData);
}

void noteOn(int noteNumber){
  if(!activeNotes.hasValue(noteNumber)){
    activeNotes.push(noteNumber);
  }
}

void noteOff(int noteNumber){
  if(activeNotes.hasValue(noteNumber)){
    int noteIndex = indexOf(noteNumber, activeNotes);
    activeNotes.remove(noteIndex);
  } 
}

// Return int representing the index of target data in a list
// or -1 if not found
int indexOf(int target, IntList source){
  for(int i = 0; i < source.size(); i++){
    if(source.get(i) == target) return i;
  }
  return -1;
}
