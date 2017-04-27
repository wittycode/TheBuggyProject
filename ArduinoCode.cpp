#define DELAY 			0
#define SWEEP_DELAY 		20

#define CALIB_IR 	100
#define RIGHT_IR 	A2
#define LEFT_IR 	A0

int counter=0;

void LeftRotate(){
	digitalWrite(5,LOW);
     	digitalWrite(6,HIGH);
      	digitalWrite(8,HIGH);
    	digitalWrite(7,LOW);
}
void RightRotate(){
	digitalWrite(5,HIGH);
    	digitalWrite(6,LOW);
    	digitalWrite(8,LOW);
    	digitalWrite(7,HIGH);
}
void Forward(){
	digitalWrite(5,HIGH);
    	digitalWrite(6,LOW);
    	digitalWrite(8,HIGH);
   	digitalWrite(7,LOW);
}
void Backward(){
	digitalWrite(5,LOW);
    	digitalWrite(6, HIGH);
    	digitalWrite(8,LOW);
   	digitalWrite(7, HIGH);
}
void StandStill(){
	digitalWrite(5,LOW);
    	digitalWrite(6, LOW);
    	digitalWrite(8, LOW);
   	digitalWrite(7,LOW);

}
void Sweep()
{
	Forward();
	delay(SWEEP_DELAY);
}

void setup() {
  pinMode(RIGHT_IR,INPUT);	//right ir sensor
  pinMode( LEFT_IR,INPUT);	//left ir sensor
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
}


//------------------------------------------------- Entry Point --------------------------------------------------//
void loop() {

int ir1,ir2; 
 ir1 =analogRead(RIGHT_IR);	// right ir sensor
 ir2=analogRead( LEFT_IR);	// left ir sensor
 Serial.println(ir2);

 if(ir1>CALIB_IR&&ir2>CALIB_IR)
  {
    	//Forward();
	Backward();
    	delay(DELAY);        
	//Sweep();    
  }
  else if(ir1<CALIB_IR&&ir2>CALIB_IR)
  {
   	while(ir1<CALIB_IR) 
    	{
    	ir1 =analogRead(RIGHT_IR);	//left Turn
      	LeftRotate();
    	delay(DELAY);        
	Sweep();    
   	 }
  }
  else if(ir1>CALIB_IR&&ir2<CALIB_IR)
  {
    	while(ir2<CALIB_IR)
    	{
     	ir2=analogRead( LEFT_IR); 	//right Turn
    	RightRotate();
   	delay(DELAY);       
 	Sweep();    
    	} 
  }
  else if(ir1<CALIB_IR&&ir2<CALIB_IR)
  {
    	counter++;
    	if(counter==6){
     		while(analogRead( LEFT_IR)<CALIB_IR&&analogRead(RIGHT_IR)>CALIB_IR)
		{
    			LeftRotate();
    		}
   	 }
   	 else if (counter==7){
    		StandStill();
   	 }
   	 else{
      		while(analogRead(LEFT_IR)>CALIB_IR&&analogRead(RIGHT_IR)<CALIB_IR)
		{
    			RightRotate();
    			delay(DELAY);        
			Sweep();    
      		}
    	}
 }



} 	//End LOOP
//------------------------------------------------- END ---------------------------------------------------//

