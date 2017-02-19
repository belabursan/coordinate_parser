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
main (int argc, char** argv)
{
  double d;
  gboolean b;

  /* Just testing */
  b = longitude_coord2double ("-0780433.555", &d);
  printf ("b:%d, d:%.9f\n", b, d);
  b = latitude_coord2double ("-074433.555", &d);
  printf ("b:%d, d:%.9f\n", b, d);

  return (EXIT_SUCCESS);
}
