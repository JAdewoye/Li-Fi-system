// C++ code
//
#define prd 10
#define del 10                                      //two variables should be same as receiver so that two system can be synchronised
int lgth;
int z;
const char *test = "Test Message";
volatile byte count;

ISR(TIMER2_COMPA_vect)                                  //Timer Interrupt which counts up by 1 
{
  count++;
  OCR2A = prd;
}


void setup()
{
  Serial.begin(115200);                                 //Sets serial rate to 115200
  
  DDRD=B00001100;                                        //Sets pin 2 as an output pin


  TCCR0B = 0; 
  OCR2A = prd;                                             //value timer will compare to
  TCCR2A = 1<<WGM21;                                      //CTC mode
  TCCR2B = (0<<CS22) | (1<<CS21) | (1<<CS20);             //defining prescaler
  TIMSK2 = (1<<OCIE2A);
  
}


 void trans_byte (char *msg)                             //Function to tranfer a byte
{
 
  for (int i=0; i<strlen(msg); i++){                      //works out how long the message is
    PORTD &= B11110011;                                  //change in signal 'high to low' to signify start bit for receiver to read
     count=0;                                            //precise delay
     do{}
     while(count <= del);

    
                                                   
    char symb = msg[i];                               //gets specific character in string and stores in symb
    Serial.println("");
    Serial.print(symb);                                 //Prints character 
    Serial.print(" = ");                            
                                       
    for (int symb_bit=0; symb_bit <8; symb_bit++){               
      bool msg_bit = symb & (0x80 >> symb_bit);               //compares each bit to 1 to find out what the bit is in the byte
      
      Serial.print(msg_bit);                                   //print specific bit
      
      
      if (msg_bit == 1){

      PORTD = B00001100;                                        //Set pin 2 to high or low depending on the specific bit
      count=0;
      do{}
      while(count <= del);

   
      }
      else if(msg_bit == 0){
     
      PORTD &= B11110011;
      count=0;
      do{}
      while(count <= del);
      
      ;}
    }

    PORTD = B00001100;                           //sets pin 2 to high again so that receiver no bits are being sent 
    count=0;
    do{}
    while(count <= del);

    }
} 

void loop()
{

    
    Serial.print("\nyour message was ");                          //sending the message in a loop and displaying it in the serial port
    Serial.print(test);
    trans_byte(test);
    for(int the_delay=0; the_delay <5000; the_delay++){
    count=0;
    do{}
    while(count <= del);}
      
  
  }




 
    
    
  
   
  
