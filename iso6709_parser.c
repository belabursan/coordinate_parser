#include "iso6709_parser.h"
#include <stdio.h>
#include <string.h>


/* coordinate types */
enum coord_type
{
  coord_type_latitude = 0,
  coord_type_longitude = 1
};


/* represents the iso type of coordinate as in iso 6709 */
enum iso_type
{
  iso_type_dd = 0,
  iso_type_ddmm = 1,
  iso_type_ddmmss = 2
};


static gboolean coordinate_to_double(const gchar *coord, gdouble *result, gint coord_type);
static gboolean validate_coordinate(gdouble d, gint coord_type);
static gboolean get_iso_type(const gchar *coord, gint *iso_type, gint coord_type);
/******************************************************************************/


/**
 * Converts a longitude string from any iso format to decimal degree double
 * @param [in] coord coordinate to convert
 * @param [out] result the converted coordinate
 * @return #TRUE if succeeded, #FALSE otherwise
 */
gboolean
longitude_coord2double(const gchar *coord, gdouble *result)
{
  gdouble d;

  if(result != NULL) {
    if(coord != NULL) {
      if(coordinate_to_double(coord, &d, coord_type_longitude)) {
        if(validate_coordinate(d, coord_type_longitude)) {
          *result = d;
          return TRUE;
        }
      }
    }
    *result = 0;
  }
  return FALSE;
}


/**
 * Converts a latitude string from any iso format to decimal degree double
 * @param [in] coord coordinate to convert
 * @param [out] result the converted coordinate
 * @return #TRUE if succeeded, #FALSE otherwise
 */
gboolean
latitude_coord2double(const gchar *coord, gdouble *result)
{
  gdouble d;

  if(result != NULL) {
    if(coord != NULL) {
      if(coordinate_to_double(coord, &d, coord_type_latitude)) {
        if(validate_coordinate(d, coord_type_latitude)) {
          *result = d;
          return TRUE;
        }
      }
    }
    *result = 0;
  }
  return FALSE;
}
/******************************************************************************/


/**
 * Converts a string coordinate from any iso type to decimal degree type double
 * See iso6709
 * @param [in] coord coordinate to convert
 * @param [out] result the converted coordinate
 * @param [in] coord_type the type of the coordinate(can be longitude or latitude, see coord_type enum)
 * @return #TRUE if succeeded, #FALSE otherwise
 */
static gboolean
coordinate_to_double(const gchar *coord, gdouble *result, gint coord_type)
{
  guint index = 0;
  guint sign_len = 0;
  gint iso_type;
  gint sign = 1;
  gchar deg[5];
  gchar min[128];
  gchar sec[128];
  gdouble d_deg = 0;
  gdouble d_min = 0;
  gdouble d_sec = 0;

  *result = 0;

  if(!get_iso_type(coord, &iso_type, coord_type)) {
    return FALSE;
  }

  /* If type is dd just convert and return */
  if(iso_type == iso_type_dd) {
    return sscanf(coord, "%lg", result) > 0;
  } else {
    if(coord[0] == '+') {
      sign_len = 1;
    } else if(coord[0] == '-') {
      sign_len = 1;
      sign = -1;
    }
    memset(deg, 0, 4);
    memset(min, 0, strlen(coord));
    index = 2 + coord_type + sign_len;

    /* Parse degrees */
    memcpy(deg, coord, index);
    if(sscanf(deg, "%lg", &d_deg) < 1) {
      return FALSE;
    }

    /* parse minutes (ddmm type) */
    if(iso_type == iso_type_ddmm) {
      memcpy(min, &coord[index], (strlen(coord) - index));
      if(sscanf(min, "%lg", &d_min) < 1) {
        return FALSE;
      }
    } else {
      /* parse minutes and seconds (ddmmss type) */
      memset(sec, 0, strlen(coord));
      memcpy(min, &coord[index], 2);
      memcpy(sec, &coord[index + 2], (strlen(coord) - (index - 2)));
      if(sscanf(min, "%lg", &d_min) < 1) {
        return FALSE;
      }
      if(sscanf(sec, "%lg", &d_sec) < 1) {
        return FALSE;
      }
    }
  }

  /* calculate the DecimaDegrees from degrees-minutes-seconds */
  *result = d_deg + (sign * (d_min / 60)) + (sign * (d_sec / 3600));

  return TRUE;
}


/**
 * Validates coordinates according to type
 * @param [in] coord coordinate to validate
 * @param [in] coord_type type of the coordinate, see coord_type enum
 * @return #TRUE if the longitude is between -180 and 180 and
 *                      latitude is between -90 and 90,
 *         #FALSE otherwise
 */
static gboolean
validate_coordinate(gdouble coord, gint coord_type)
{
  if((coord >= (-90 * (1 + coord_type))) && (coord <= (90 * (1 + coord_type)))) {
    return TRUE;
  }
  return FALSE;
}


/**
 * Evaluates the string and determines the iso type
 * @param [in] coord coordinate to validate
 * @param [out] iso_type iso type to set
 * @param [in] coord_type type of the coordinate, see coord_type enum
 * @return #TRUE if string represents a valid coordinate, #FALSE otherwise
 */
static gboolean
get_iso_type(const gchar *coord, gint *iso_type, gint coord_type)
{
  guint index = 0;
  guint len = 0;
  gint ret = -1;
  gboolean integerPart = FALSE;
  gboolean hasDot = FALSE;
  gboolean decimalPart = FALSE;
  gboolean sign = FALSE;
  gboolean badChar = FALSE;
  guint int_count = 0;
  /* https://en.wikipedia.org/wiki/ISO_6709 */

  if(coord) {
    len = strlen(coord);
    while(coord[index] != '\0') {
      if(index == 0) {
        //check first char, it can be +,-,digit
        if(coord[index] == '-' || coord[index] == '+') {
          sign = TRUE;
        } else if(g_ascii_isdigit(coord[index])) {
          sign = TRUE;
          int_count++;
        } else {
          badChar = TRUE;
          break;
        }
        index++;
        continue;
      }
      if(g_ascii_isdigit(coord[index])) {
        if(hasDot == TRUE) {
          decimalPart = TRUE;
        } else {
          int_count++;
        }
      } else if(coord[index] == '.' && hasDot == FALSE) {
        hasDot = TRUE;
      } else {
        badChar = TRUE;
        break;
      }

      index++;
    }

    if(!badChar) {
      if(int_count == (2 + coord_type)) {
        integerPart = TRUE;
        ret = iso_type_dd;
      } else if(int_count == (4 + coord_type)) {
        integerPart = TRUE;
        ret = iso_type_ddmm;
      } else if(int_count == (6 + coord_type)) {
        integerPart = TRUE;
        ret = iso_type_ddmmss;
      }
    }
  }

  if(sign && integerPart && hasDot && decimalPart && !badChar) {
    *iso_type = ret;
    return TRUE;
  }

  return FALSE;
}
