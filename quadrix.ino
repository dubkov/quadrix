#define CLK 13
#define STB 12
#define OE 11
#define C 10
#define B 9
#define A 8
#define TD 7
#define BD 6

#define SHOWTIME 500
#define CLKTIME 10

uint16_t theBigXtop[8]={
0b0000000000000000,
0b1111000000001111,
0b0110000000000110,
0b0011000000001100,
0b0001100000011000,
0b0000110000110000,
0b0000011001100000,
0b0000001111000000},

theBigXbottom[8]={
0b0000001111000000,
0b0000011001100000,
0b0000110000110000,
0b0001100000011000,
0b0011000000001100,
0b0110000000000110,
0b1111000000001111,
0b0000000000000000};

void setup()
 { 
   pinMode(CLK,OUTPUT);
   pinMode(STB,OUTPUT);
   pinMode(OE,OUTPUT);
   pinMode(C,OUTPUT);
   pinMode(B,OUTPUT);
   pinMode(A,OUTPUT);
   pinMode(TD,OUTPUT);
   pinMode(BD,OUTPUT);
 }

void loop()
 {
   for(int bigXrowNumber=0; bigXrowNumber<16;bigXrowNumber++)   show(theBigXtop,theBigXbottom);
 }
 
 void transferBits(boolean bitToSendTop, boolean bitToSendBottom){
   digitalWrite(TD,bitToSendTop);
   digitalWrite(BD,bitToSendBottom);
   digitalWrite(CLK,HIGH);
   delayMicroseconds(CLKTIME);
   digitalWrite(CLK,LOW); 
   delayMicroseconds(CLKTIME); 
 }

 void transferLines(uint16_t lineToSendTop, uint16_t lineToSendBottom){
   digitalWrite(STB,LOW);
   for(int i=0; i<8; i++) transferBits(lineToSendTop&(1<<i),lineToSendBottom&(1<<i));
   for(int i=0; i<8; i++) transferBits(lineToSendTop>>8&(1<<i),lineToSendBottom>>8&(1<<i));
   digitalWrite(STB,HIGH);
 }

 void selectRow(uint8_t rowNumber){
   digitalWrite(A,rowNumber&1);
   digitalWrite(B,rowNumber&2);
   digitalWrite(C,rowNumber&4);
 }
 
 void showLine(){
   digitalWrite(OE,LOW);
   delayMicroseconds(SHOWTIME);
   digitalWrite(OE,HIGH);
 }
 
 void show(uint16_t topLine[8], uint16_t bottomLine[8]){
    for (int j=0;j<8;j++){
      selectRow(j);
      transferLines(topLine[j],bottomLine[j]);
      showLine();
   }
 }
