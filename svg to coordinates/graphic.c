#include <avr/pgmspace.h>
#define ARR_LENGTH 84
const bool pen[] = {0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,};
const uint16_t xval[] PROGMEM = {1852,2436,2335,3013,3721,3557,4095,3315,2940,2622,1852,118,137,192,279,395,535,695,873,1063,1248,1425,1588,1732,1850,1937,1990,2008,1990,1937,1850,1732,1588,1425,1248,1063,878,701,539,395,277,190,136,118,3080,4067,4055,3061,2458,3080,849,692,546,415,301,206,134,87,68,80,126,208,330,493,702,959,1266,1412,1519,1591,1631,1643,1629,1594,1540,1471,1391,1302,1208,1112,1018,929,849,4095,};
const uint16_t yval[] PROGMEM = {1300,777,0,393,57,824,1393,1474,2162,1445,1300,3105,2923,2755,2602,2469,2359,2276,2223,2205,2223,2274,2356,2469,2606,2760,2928,3105,3281,3449,3604,3741,3853,3936,3987,4004,3987,3936,3853,3741,3604,3449,3281,3105,2356,2689,3731,4041,3191,2356,1370,1437,1478,1492,1482,1449,1395,1323,1233,1127,1008,876,733,582,424,261,93,400,674,916,1126,1305,1453,1571,1660,1719,1751,1754,1730,1679,1601,1498,1370,0,};