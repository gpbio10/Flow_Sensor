int flowPin = 2;                  //Input pin on the Arduino
double totalVolume;               //This is the value we intend to calculate.
double flowRate;
volatile int count = 0;           //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.
volatile int countInitial = 0;
volatile int timeChange;
volatile int timeInitial = 0;
volatile int timeFinal;
double tankVolume = 2630.0;       //Total volume of tank used (Test tank is 2630 mL
 
void setup() {

  pinMode(flowPin, INPUT);              //Input
  attachInterrupt(0, Flow, RISING);     //Run flow when digital pin gets pulse  
  Serial.begin(9600);                   //Serial Begin
}
void loop() { 
  
  interrupts();
  delay (5000);                          //1s delay 
  noInterrupts();
   
  totalVolume = count * 0.75;                               //Converts number of revolutions to mL
  totalVolume = 100 - ((totalVolume / tankVolume) * 100);   // Converts mL to percent of tank.
 
  Serial.print(totalVolume);              //Print the variable flowRate to Serial
  Serial.print(" %\n");                  //Prints percent sign to Serial

  flowRate = (count - countInitial) * 0.75 / 5;      //Change in mL/s 
  flowRate = flowRate/1000*60;                     //Change in L/min

  countInitial = count;                           //Resets initial count
  
  Serial.print(flowRate);
  Serial.print(" L/min\n");                       //Prints Flow Rate
  
}


void Flow()
{
   count++; //Increments count by 1 for every revolution

}
