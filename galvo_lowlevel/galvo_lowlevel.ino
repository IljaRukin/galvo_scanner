/*
 * control galvo mirrors using 2 MCP4725 DACs
 * 
 * MCP4725
 * 5.93Hz sine wave
 * 
 *  VCC   GND  Vout
 *    |    |    |
 * |---------------|
 * |     AJW0      |
 * |---------------|
 *    |    |    |
 *   SDA  CLK   A0
 * 
 * circuit board:
 * smoothing capacitor
 * pullup for SDA/SCL (pads on bottom [connected])
 * pullup/pulldown for A0 (pads on top [disconnected]) => sets Adress
 * A0=GND: Adress=0x60 /// A0=VCC: Adress=0x61
 * 
 */

#include <avr/io.h>
#include <util/delay.h>
#include "TWI.h"

#define F_CPU 16000000
#define LASER 13

uint32_t idx = 0;
uint16_t x = 0;
uint16_t y = 0;


//graphic
#include "graphic.cpp"


/*
//cube
#define ARR_LENGTH 4
const bool pen[ARR_LENGTH] = {1,1,1,1};
const uint16_t xval[ARR_LENGTH] PROGMEM = {0, 4095, 4095, 0};
const uint16_t yval[ARR_LENGTH] PROGMEM = {0, 0, 4095, 4095};
*/

/*
//circle
#include <avr/pgmspace.h>
#define ARR_LENGTH 255
const bool pen[ARR_LENGTH] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};
const uint16_t xval[ARR_LENGTH] PROGMEM = {2048,2098,2148,2199,2249,2299,2349,2399,2448,2498,2547,2596,2644,2692,2740,2787,2834,2880,2926,2971,3016,3060,3104,3147,3189,3230,3271,3311,3351,3389,3427,3464,3500,3535,3569,3602,3635,3666,3697,3726,3754,3782,3808,3833,3857,3880,3902,3923,3943,3961,3979,3995,4010,4024,4036,4048,4058,4067,4074,4081,4086,4090,4093,4095,4095,4094,4092,4088,4084,4078,4071,4062,4053,4042,4030,4017,4002,3987,3970,3952,3933,3913,3891,3869,3845,3821,3795,3768,3740,3711,3681,3651,3619,3586,3552,3517,3482,3445,3408,3370,3331,3291,3251,3210,3168,3125,3082,3038,2994,2949,2903,2857,2811,2764,2716,2668,2620,2571,2522,2473,2424,2374,2324,2274,2224,2174,2123,2073,2022,1972,1921,1871,1821,1771,1721,1671,1622,1573,1524,1475,1427,1379,1331,1284,1238,1192,1146,1101,1057,1013,970,927,885,844,804,764,725,687,650,613,578,543,509,476,444,414,384,355,327,300,274,250,226,204,182,162,143,125,108,93,78,65,53,42,33,24,17,11,7,3,1,0,0,2,5,9,14,21,28,37,47,59,71,85,100,116,134,152,172,193,215,238,262,287,313,341,369,398,429,460,493,526,560,595,631,668,706,744,784,824,865,906,948,991,1035,1079,1124,1169,1215,1261,1308,1355,1403,1451,1499,1548,1597,1647,1696,1746,1796,1846,1896,1947,1997,};
const uint16_t yval[ARR_LENGTH] PROGMEM = {4095,4094,4093,4089,4085,4079,4073,4065,4055,4045,4033,4020,4006,3991,3974,3957,3938,3918,3897,3875,3851,3827,3801,3775,3747,3719,3689,3658,3627,3594,3561,3526,3491,3455,3418,3380,3341,3301,3261,3220,3178,3136,3093,3049,3005,2960,2915,2869,2822,2775,2728,2680,2632,2584,2535,2486,2436,2386,2337,2287,2236,2186,2136,2085,2035,1984,1934,1884,1833,1783,1733,1684,1634,1585,1536,1487,1439,1391,1343,1296,1249,1203,1158,1112,1068,1024,980,938,896,854,814,774,735,696,659,622,586,551,518,484,452,421,391,362,334,307,281,256,232,209,187,167,148,129,112,96,82,68,56,45,35,26,19,13,8,4,1,0,0,1,4,8,13,19,26,35,45,56,68,82,96,112,129,148,167,187,209,232,256,281,307,334,362,391,421,452,484,518,551,586,622,659,696,735,774,814,854,896,938,980,1024,1068,1112,1158,1203,1249,1296,1343,1391,1439,1487,1536,1585,1634,1684,1733,1783,1833,1884,1934,1984,2035,2085,2136,2186,2236,2287,2337,2386,2436,2486,2535,2584,2632,2680,2728,2775,2822,2869,2915,2960,3005,3049,3093,3136,3178,3220,3261,3301,3341,3380,3418,3455,3491,3526,3561,3594,3627,3658,3689,3719,3747,3775,3801,3827,3851,3875,3897,3918,3938,3957,3974,3991,4006,4020,4033,4045,4055,4065,4073,4079,4085,4089,4093,4094,};
*/

void init(void)
{
  TWIInit();
  
  DDRB |= (1<<PB5);
  //PORTB &= ~(1<<PB5);
  PORTB |= (1<<PB5);
  _delay_ms(500);
}

int main(void)
{
  init();
  while(true){
    for(idx=0;idx<ARR_LENGTH;idx++){
      PORTB = (pen[idx]<<PB5);
  
      x = pgm_read_word(xval+idx);
      TWIStart();
      //TWIWrite(0x60);
      TWIWrite(0xC0);
      TWIWrite( x >> 8 );
      TWIWrite( x & B11111111 );
      TWIStop();
  
      y = pgm_read_word(yval+idx);
      TWIStart();
      //TWIWrite(0x61);
      TWIWrite(0xC2);
      TWIWrite( y >> 8 );
      TWIWrite( y & B11111111 );
      TWIStop();
      
      _delay_ms(0.2);
    }
  }
}
