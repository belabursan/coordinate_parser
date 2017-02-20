/*
 * File:   iso6709_parser.h
 * Author: buri
 *
 * Created on February 18, 2017, 9:59 AM
 */
#ifndef ISO6709_PARSER_H
#define ISO6709_PARSER_H

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Converts a longitude string from any iso format to decimal degree double
     * @param [in] coord coordinate to convert
     * @param [out] result the converted coordinate
     * @return #TRUE if succeeded, #FALSE otherwise
     */
    gboolean longitude_coord2double(const gchar *coord, gdouble *result);


    /**
     * Converts a latitude string from any iso format to decimal degree double
     * @param [in] coord coordinate to convert
     * @param [out] result the converted coordinate
     * @return #TRUE if succeeded, #FALSE otherwise
     */
    gboolean latitude_coord2double(const gchar *coord, gdouble *result);

#ifdef __cplusplus
}
#endif

#endif /* ISO6709_PARSER_H */
