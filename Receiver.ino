// C++ code

#define prd 6
#define del 5
volatile byte count;

ISR(TIMER2_COMPA_vect)                 //Timer interrupt which counts up by 1 
{
  count++;
  OCR2A = prd;
}


ISR(INT0_vect){                         //Interrupt activated when pin 2 is low
   sei();                                //
   EIMSK = (0 << INT0);
  
  char symbol[2];
  sprintf(symbol,"%c",int(symb()));
  Serial.print(" = ");
  Serial.println(symbol);
  
  
  EIMSK = (1 << INT0);
  }


  
void setup()
{
  Serial.begin(115200);//data rate of 9600 bits per second
  pinMode(A0, INPUT);
  pinMode(6,OUTPUT);
  //pinMode(2,INPUT);

  DDRD &= B00000100;

  PORTD = 0b00000100;
  //PCICR = 0b00000100;
  //PCMSK2 = 0b01100000;

  //EICRA = 0b00000000;
  EIMSK = (1 << INT0);

  TCCR0B = 0; 
  OCR2A = prd;
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
{
  int sens;
  sens = (PIND >> 2 & B0000100 >> 2) ;
  
  
  return sens;
}

char symb ()
{
  //TIMSK2 = (1<<OCIE2A);
  char msg_byte=0 ;
  count=0;
  do{}
  while(count <= 1.5*del);
  //delayMicroseconds(prd*1.4);
  bool curr_st;
  for(int i=7; i>-1; i--)
  {
    
    Serial.print(sensor());
    msg_byte = msg_byte | sensor() << i;
    count=0;
    do{}
    while(count <= del);
    
    //delayMicroseconds(prd);   
     }
      
  //Serial.println(msg_byte);
  return msg_byte;
  
}



void loop()
{

    count=0;
    do{}
    while(count <= 11*del);
   
  }

   
    
  
 
  
  
  
