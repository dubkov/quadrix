// Quadrix project is 16x16 monocolored display for cellular automaton visualization
// Current file is sample code for displaying big letter X
// created 06.12.2014 by Ilya Dubkov during Hackember event in NSTU
// http://developer-x.ru dubkov@skbrii.ru


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

#define COLSNUM 16
#define ROWSNUM 16
#define HALFCOLSNUM 8
#define HALFROWSNUM 8

uint16_t theBigX[ROWSNUM]={
0b0000000000000000,
0b1111000000001111,
0b0110000000000110,
0b0011000000001100,
0b0001100000011000,
0b0000110000110000,
0b0000011001100000,
0b0000001111000000,
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
   show(theBigX);
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
   for(int i=0; i<HALFROWSNUM; i++) transferBits(lineToSendTop&(1<<i),lineToSendBottom&(1<<i));
   for(int i=0; i<HALFROWSNUM; i++) transferBits(lineToSendTop>>HALFCOLSNUM&(1<<i),lineToSendBottom>>HALFCOLSNUM&(1<<i));
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
 
 void show(uint16_t picture[16]){
    for (int j=0;j<HALFROWSNUM;j++){
      selectRow(j);
      transferLines(picture[j],picture[j+HALFROWSNUM]);
      showLine();
   }
 }
