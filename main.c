/*
 * File:   main.c
 * Author: buri
 *
 * Created on February 14, 2017, 9:23 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iso6709_parser.h"


/*
 * Main
 */
int
main(int argc, char** argv)
{
  double d;
  gboolean b;

  /* Just testing */

  //test dd
  printf("[DD]\n");
  b = longitude_coord2double("-133.555", &d);
  printf("LON-: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("-03.555", &d);
  printf("LAT-: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("+013.1487", &d);
  printf("LON+: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("+55.555", &d);
  printf("LAT+: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("133.555", &d);
  printf("LON:  b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("13.555", &d);
  printf("LAT:  b:%d, d:%.9f\n", b, d);


  printf("\n[DDMM]\n");
  b = longitude_coord2double("-13355.678", &d);
  printf("LON-: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("-1357.326", &d);
  printf("LAT-: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("+01312.1487", &d);
  printf("LON+: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("+5512.555", &d);
  printf("LAT+: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("13345.555", &d);
  printf("LON:  b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("1334.555", &d);
  printf("LAT:  b:%d, d:%.9f\n", b, d);

   printf("\n[DDMMSS]\n");
  b = longitude_coord2double("-1335511.678", &d);
  printf("LON-: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("-135712.326", &d);
  printf("LAT-: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("+0131243.1487", &d);
  printf("LON+: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("+551234.555", &d);
  printf("LAT+: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("0334532.555", &d);
  printf("LON:  b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("133432.555", &d);
  printf("LAT:  b:%d, d:%.9f\n", b, d);
  
  printf("\nNegative test\n");
  b = longitude_coord2double("-1335.678", &d); //should be xxxxx.xx... and not xxxx.xx..
  printf("LON-: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("-135.326", &d); //should be xxxx.x and not xxx.xx
  printf("LAT-: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("+03.1487", &d); //should be xxx.xx
  printf("LON+: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("+2.555", &d); //should be xx.xx
  printf("LAT+: b:%d, d:%.9f\n", b, d);

  b = longitude_coord2double("133456.555", &d);//should be xxxx.xx and not xxxxxx.xx
  printf("LON:  b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("1334636.555", &d); //should be xxx
  printf("LAT:  b:%d, d:%.9f\n", b, d);
  
   printf("\nStr test\n");
  b = longitude_coord2double("", &d); //empty str
  printf("LON: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double(NULL, &d); //null
  printf("LAT: b:%d, d:%.9f\n", b, d);
  
  b = longitude_coord2double("123.123", NULL); //null 
  printf("LON: b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double("+1A.098", &d); //bad str
  printf("LAT: b:%d, d:%.9f\n", b, d);

  return (EXIT_SUCCESS);
}
