/*
 * Cable Tester
 * James Hogg
 * 
 * This program is used to test continuity in an ethernet cable.
 * The arduino is connected at 1 end of the cable. At the opposite
 * end of the cable another board is connected with 8 LEDs.
 * The arduino sends 5vdc down each core 1 at a time, which lights up
 * the corresponding LED.
 * The switch is used to select straight through or cross over cable.
 * 
 * If the LEDs light up in order the cable is OK.
 * A fault has occured if: 
 *                        The LEDs light up in the wrong order
 *                        Fail to light up
 *                        More than 1 LED lights up at a time
 * 
 */

const int DELAY = 1000;//Time between LEDs activated
int straight_through[8] = {9,8,7,6,5,4,3,2};//Type A order
int cross_over[8] = {9,8,3,6,5,2,7,4};//Type B order
int cable_types[2][8] = {{9,8,7,6,5,4,3,2}, {9,8,3,6,5,2,7,4}};
int switch_pin = 10; //Switch to change cable type
int current_state = 0; //Detect changes to switch

void setup() {
  for(int pin: straight_through){
    pinMode(pin, OUTPUT);
  }
  pinMode(switch_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
    //Serial.print(digitalRead(switch_pin));
    //delay(500);
    check_cable();
    reset_LEDs();
}

//Check switch for cable type
bool check_input_change(){
  if(current_state != digitalRead(switch_pin)){
    current_state = digitalRead(switch_pin);
    return true;
  }
  return false;
}

//Cycle through cores
void check_cable(){
  for(int pin: cable_types[current_state]){
    check_core(pin);
    if(check_input_change()){
      return;
    }
  }
}

//Send 5vdc down core, light LED
void check_core(int pin){
    digitalWrite(pin, HIGH);
    delay(DELAY);
    digitalWrite(pin, LOW);
    delay(DELAY);
}

//Set all pins to LOW
void reset_LEDs(){
  for(int pin: cable_types[current_state]){
    digitalWrite(pin, LOW); 
  }
}
