// C++ code

#define prd 10                           //two variables should be same as transmitter so that two system can be synchronised
#define del 10
volatile byte count;

ISR(TIMER2_COMPA_vect)                 //Timer interrupt which counts up by 1 
{
  count++;
  OCR2A = prd;
}


ISR(INT0_vect){                         //Interrupt activated when pin 2 (input) is low
  
   sei();                                         //All global interrupts turned on to allow timer to continue running
   EIMSK = (0 << INT0);                          //This specific interrupt is turned off
  
  char symbol[2];                                  //Code to print symbols to serial port
  sprintf(symbol,"%c",int(symb()));
  Serial.print(" = ");
  Serial.println(symbol);
  
  
  EIMSK = (1 << INT0);
  }


  
void setup()
{
  Serial.begin(115200);                                  //data rate of 115200 bits per second 
  pinMode(A0, INPUT);
  pinMode(6,OUTPUT);
  

  DDRD &= B00000100;                                    //Sets pin 2 as an input pin

  PORTD = 0b00000100;
  
  EIMSK = (1 << INT0);

  TCCR0B = 0;  
  OCR2A = prd;                                             //Value timer were compare to
  TCCR2A = 1<<WGM21;                                      //CTC mode
  TCCR2B = (0<<CS22) | (1<<CS21) | (1<<CS20);             //defining prescaler
  TIMSK2 = (1<<OCIE2A);

  sei();
}

byte msg_byte = 0;
int pos=0;
char msg[16];
bool prev_st;
bool curr_st;
  
int sensor ()
{                                                                 //function to read value at input
  int sens;
  sens = (PIND >> 2 & B0000100 >> 2) ;
  
  
  return sens;
}

char symb ()                                                 //Function to work out what symbol has been sent 
{
  
  char msg_byte=0 ;
  count=0;                                          //precise delay executed to start reading from pin at correct time
  do{}
  while(count <= 1.5*del);
  
  bool curr_st;
  for(int i=7; i>-1; i--)
  {
    
    Serial.print(sensor());                                 //reads value then stores in correct order into variable
    msg_byte = msg_byte | sensor() << i;
    count=0;                                                //waits for correct interval
    do{}
    while(count <= del);
    
     
     }
      
  
  return msg_byte;
  
}



void loop()
{

    count=0;
    do{}
    while(count <= 11*del);
   
  }

   
    
  
 
  
  
  
