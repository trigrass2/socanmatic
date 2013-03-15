/* Copyright (c) 2008-2013, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Neil T. Dantam <ntd@gatech.edu>
 *            Can Erdogan <cerdogan@gatech.edu>
 *
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

#ifndef SOCIA_NMT_H
#define SOCIA_NMT_H

/**
 * \file socia_canopen.h
 *
 * \brief CANopen implementation using SocketCAN and esd's NTCAN
 * API. See the website
 * http://en.wikipedia.org/wiki/Canopen#Service_Data_Object_.28SDO.29_protocol
 * for details of service data object (SDO) protocol.
 *
 * \author Neil Dantam
 * \author Can Erdogan (bug fixes)
 *
 * \bug Deferring implementation of segmented messages
 *
 * \bug esd's driver will non-deterministically order loopback and
 * off-the-wire CAN messages.
 */


/// Produce COB-ID for response from node


#ifdef __cplusplus
extern "C" {
#endif


/*********************/
/* NMT Communication */
/*********************/

typedef enum socia_nmt_msg {
    SOCIA_NMT_INVAL = -1,
    SOCIA_NMT_START_REMOTE = 0x1,
    SOCIA_NMT_STOP_REMOTE = 0x2,
    SOCIA_NMT_PRE_OP = 0x80,
    SOCIA_NMT_RESET_NODE = 0x81,
    SOCIA_NMT_RESET_COM = 0x82
} socia_nmt_msg_t;

/* ID for all nodes */
#define SOCIA_NODE_ALL 0x00

/**  Send an NMT Message.
 */
int socia_send_nmt( int fd, uint8_t node,
                    socia_nmt_msg_t nmt_msg );






#ifdef __cplusplus
}
#endif

/* ex: set shiftwidth=4 tabstop=4 expandtab: */
/* Local Variables:                          */
/* mode: c                                   */
/* c-basic-offset: 4                         */
/* indent-tabs-mode:  nil                    */
/* End:                                      */

#endif //SOCIA_NMT_H
