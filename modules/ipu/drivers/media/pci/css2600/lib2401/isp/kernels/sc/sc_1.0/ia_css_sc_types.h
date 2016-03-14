/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef __IA_CSS_SC_TYPES_H
#define __IA_CSS_SC_TYPES_H

/** Number of color planes in the shading table. */
#define IA_CSS_SC_NUM_COLORS           4

/** The 4 colors that a shading table consists of.
 *  For each color we store a grid of values.
 */
enum ia_css_sc_color {
	IA_CSS_SC_COLOR_GR, /**< Green on a green-red line */
	IA_CSS_SC_COLOR_R,  /**< Red */
	IA_CSS_SC_COLOR_B,  /**< Blue */
	IA_CSS_SC_COLOR_GB  /**< Green on a green-blue line */
};

/** Lens Shading Correction table.
 *
 *  This describes the color shading artefacts
 *  introduced by lens imperfections. To correct artefacts,
 *  bayer values should be multiplied by gains in this table.
 *
 *------------ deprecated(bz675) : from ---------------------------
 *  When shading_settings.enable_shading_table_conversion is set as 0,
 *  this shading table is directly sent to the isp. This table should contain
 *  the data based on the ia_css_shading_info information filled in the css.
 *  So, the driver needs to get the ia_css_shading_info information
 *  from the css, prior to generating the shading table.
 *
 *  When shading_settings.enable_shading_table_conversion is set as 1,
 *  this shading table is converted in the legacy way in the css
 *  before it is sent to the isp.
 *  The driver does not need to get the ia_css_shading_info information.
 *
 *  NOTE:
 *  The shading table conversion will be removed from the css in the near future,
 *  because it does not support the bayer scaling by sensor.
 *  Also, we had better generate the shading table only in one place(AIC).
 *  At the moment, to support the old driver which assumes the conversion is done in the css,
 *  shading_settings.enable_shading_table_conversion is set as 1 by default.
 *------------ deprecated(bz675) : to ---------------------------
 *
 *  ISP block: SC1
 *  ISP1: SC1 is used.
 *  ISP2: SC1 is used.
 */
struct ia_css_shading_table {
	uint32_t enable; /**< Set to false for no shading correction.
		          The data field can be NULL when enable == true */
/* ------ deprecated(bz675) : from ------ */
	uint32_t sensor_width;  /**< Native sensor width in pixels. */
	uint32_t sensor_height; /**< Native sensor height in lines.
		When shading_settings.enable_shading_table_conversion is set
		as 0, sensor_width and sensor_height are NOT used.
		These are used only in the legacy shading table conversion
		in the css, when shading_settings.
		enable_shading_table_conversion is set as 1. */
/* ------ deprecated(bz675) : to ------ */
	uint32_t width;  /**< Number of data points per line per color.
				u8.0, [0,81] */
	uint32_t height; /**< Number of lines of data points per color.
				u8.0, [0,61] */
	uint32_t fraction_bits; /**< Bits of fractional part in the data
				points.
				u8.0, [0,13] */
	uint16_t *data[IA_CSS_SC_NUM_COLORS];
	/**< Table data, one array for each color.
	     Use ia_css_sc_color to index this array.
	     u[13-fraction_bits].[fraction_bits], [0,8191] */
};

/* ------ deprecated(bz675) : from ------ */
/** Shading Correction settings.
 *
 *  NOTE:
 *  This structure should be removed when the shading table conversion is
 *  removed from the css.
 */
struct ia_css_shading_settings {
	uint32_t enable_shading_table_conversion; /**< Set to 0,
		if the conversion of the shading table should be disabled
		in the css. (default 1)
		  0: The shading table is directly sent to the isp.
		     The shading table should contain the data based on the
		     ia_css_shading_info information filled in the css.
		  1: The shading table is converted in the css, to be fitted
		     to the shading table definition required in the isp.
		NOTE:
		Previously, the shading table was always converted in the css
		before it was sent to the isp, and this config was not defined.
		Currently, the driver is supposed to pass the shading table
		which should be directly sent to the isp.
		However, some drivers may still pass the shading table which
		needs the conversion without setting this config as 1.
		To support such an unexpected case for the time being,
		enable_shading_table_conversion is set as 1 by default
		in the css. */
};
/* ------ deprecated(bz675) : to ------ */

#endif /* __IA_CSS_SC_TYPES_H */

