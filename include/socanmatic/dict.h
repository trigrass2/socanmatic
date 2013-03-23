/*
 * Copyright (c) 2008-2013, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Neil T. Dantam <ntd@gatech.edu>
 * Georgia Tech Humanoid Robotics Lab
 * Under Direction of Prof. Mike Stilman <mstilman@cc.gatech.edu>
 *
 *
 * This file is provided under the following "BSD-style" License:
 *
 *
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SOCANMATIC_DICT_H
#define SOCANMATIC_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

/// Access type for an object
typedef enum canmat_access_type {
    CANMAT_ACCESS_UNKNOWN,    ///< Unknown access type
    CANMAT_ACCESS_RO,         ///< Read only
    CANMAT_ACCESS_WO,         ///< Write only
    CANMAT_ACCESS_RW,         ///< Read-Write
    CANMAT_ACCESS_RWR,        ///< Read-Write on process input
    CANMAT_ACCESS_RWW,        ///< Read-Write on process output
} canmat_access_type_t;


/** Object Dictionary Object Definition
 *  see CiA 301
 */
typedef enum canmat_object_type {
    CANMAT_OBJ_CODE_NULL       = 0, ///< no data fields
    CANMAT_OBJ_CODE_DOMAIN     = 2, ///< large variable amount of data
    CANMAT_OBJ_CODE_DEFTYPE    = 5, ///< A type definition
    CANMAT_OBJ_CODE_DEFSTRUCT  = 6, ///< A struct definition
    CANMAT_OBJ_CODE_VAR        = 7, ///< A single value
    CANMAT_OBJ_CODE_ARRAY      = 8, ///< An array
    CANMAT_OBJ_CODE_RECORD     = 9  ///< A record type
} canmat_object_type_t;

/** Data type for an object
 *  see CiA 301
 */
typedef enum canmat_data_type {
    CANMAT_DATA_TYPE_BOOLEAN         = 0x0001,
    CANMAT_DATA_TYPE_INTEGER8        = 0x0002,
    CANMAT_DATA_TYPE_INTEGER16       = 0x0003,
    CANMAT_DATA_TYPE_INTEGER32       = 0x0004,
    CANMAT_DATA_TYPE_UNSIGNED8       = 0x0005,
    CANMAT_DATA_TYPE_UNSIGNED16      = 0x0006,
    CANMAT_DATA_TYPE_UNSIGNED32      = 0x0007,
    CANMAT_DATA_TYPE_REAL32          = 0x0008,
    CANMAT_DATA_TYPE_VISIBLE_STRING  = 0x0009,
    CANMAT_DATA_TYPE_OCTET_STRING    = 0x000A,
    CANMAT_DATA_TYPE_UNICODE_STRING  = 0x000B,
    CANMAT_DATA_TYPE_TIME_OF_DAY     = 0x000C,
    CANMAT_DATA_TYPE_TIME_DIFFERENCE = 0x000D,
    /* 0x000E is reserved */
    CANMAT_DATA_TYPE_DOMAIN          = 0x000F,
    CANMAT_DATA_TYPE_INT24           = 0x0010,
    CANMAT_DATA_TYPE_REAL64          = 0x0011,
    CANMAT_DATA_TYPE_INTEGER40       = 0x0012,
    CANMAT_DATA_TYPE_INTEGER48       = 0x0013,
    CANMAT_DATA_TYPE_INTEGER56       = 0x0014,
    CANMAT_DATA_TYPE_INTEGER64       = 0x0015,
    CANMAT_DATA_TYPE_UINT24          = 0x0016,
    /* 0x0017 is reserved */
    CANMAT_DATA_TYPE_UNSIGNED40      = 0x0018,
    CANMAT_DATA_TYPE_UNSIGNED48      = 0x0019,
    CANMAT_DATA_TYPE_UNSIGNED56      = 0x001A,
    CANMAT_DATA_TYPE_UNSIGNED64      = 0x001B,
    /* 0x001C - 0x001F are reserved */
    CANMAT_DATA_TYPE_PDO_COM         = 0x0020,
    CANMAT_DATA_TYPE_PDO_MAP         = 0x0021,
    CANMAT_DATA_TYPE_SDO_PARM        = 0x0022,
    CANMAT_DATA_TYPE_IDENTITY        = 0x0023
    /* 0x0024 - 0x003F are reserved */
} canmat_data_type_t;

/** Description of a CiA Object */
typedef struct canmat_obj {
    /** Index of the object */
    const uint16_t index;

    /** Subindex of the object */
    const uint8_t subindex;

    /* Name of the object */
    const char *parameter_name;

    /** Number of sub-indices for an intex.
     *  May be empty or absent of object has no sub-objects. */
    const uint8_t sub_number;


    /** Access type for object.
     */
    enum canmat_access_type access_type;


    /** The object code
     */
    enum canmat_object_type object_type;

    /** inded of the data type of the object in the object dictionary.
     */
    enum canmat_data_type data_type;

    /** Can object be pammped into a PDO */
    const unsigned pdo_mapping : 1;
} canmat_obj_t;

/** Description of a CiA Dictionary */
typedef struct canmat_dict {
    size_t length;
    struct canmat_obj *obj;
} canmat_dict_t;

typedef union canmat_scalar {
    uint8_t u8;
    int8_t  i8;

    uint16_t u16;
    int16_t  i16;

    uint32_t u32;
    int32_t  i32;

    float r32;
} canmat_scalar_t;


/* Return the index of the item in dict with given name */
canmat_obj_t *canmat_dict_search_name( const struct canmat_dict *dict, const char *name );

canmat_status_t canmat_obj_ul( int fd, uint8_t node, const canmat_obj_t *obj, canmat_scalar_t *val );

canmat_status_t canmat_obj_dl( int fd, uint8_t node, const canmat_obj_t *obj, const canmat_scalar_t *val );

canmat_status_t canmat_obj_dl_str( int fd, uint8_t node, const canmat_obj_t *obj, const char *val );

/* Parse str based on provided type and store in val */
canmat_status_t canmat_typed_parse( canmat_data_type_t type, const char *str, canmat_scalar_t *val );

#ifdef __cplusplus
}
#endif
/* ex: set shiftwidth=4 tabstop=4 expandtab: */
/* Local Variables:                          */
/* mode: c                                   */
/* c-basic-offset: 4                         */
/* indent-tabs-mode:  nil                    */
/* End:                                      */
#endif //SOCANMATIC_DICT_H