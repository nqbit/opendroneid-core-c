/*
Copyright (C) 2019 Intel Corporation

SPDX-License-Identifier: Apache-2.0

Mavlink to Open Drone ID C Library

Maintainer:
Soren Friis
soren.friis@intel.com
*/

#ifndef _MAV2ODID_H_
#define _MAV2ODID_H_

#include <opendroneid.h>

/*
// Mavlink internally allocates two global buffers. If this is unacceptable from
// a system perspective, these can be allocated either globally here by
// uncommenting the below code or the below definitions can be changed to
// pointers and the memory allocated somewhere else and the pointers initialized
// before calling any functions in mav2odid.
// If Mavlink's virtual channel functionality is not used, some memory can be
// saved by defining MAVLINK_COMM_NUM_BUFFERS to be equal to 1, before including
// mavlink_types.h

#include "../mavlink_c_library_v2/mavlink_types.h"

#define MAVLINK_EXTERNAL_RX_BUFFER
mavlink_message_t m_mavlink_buffer[MAVLINK_COMM_NUM_BUFFERS];

#define MAVLINK_EXTERNAL_RX_STATUS
mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS];
*/

#include <common/mavlink.h>

#define DRONEID_SCHEDULER_SIZE 8

typedef struct {
    uint8_t droneidSchedule[DRONEID_SCHEDULER_SIZE];
    uint8_t scheduleIdx;

    ODID_BasicID_data basicId;
    ODID_BasicID_encoded basicIdEnc;
    ODID_Location_data location;
    ODID_Location_encoded locationEnc;
    ODID_Auth_data authentication;
    ODID_Auth_encoded authenticationEnc;
    ODID_SelfID_data selfId;
    ODID_SelfID_encoded selfIdEnc;
    ODID_System_data system;
    ODID_System_encoded systemEnc;
} mav2odid_t;

int m2o_init(mav2odid_t *m2o);
int m2o_cycleMessages(mav2odid_t *m2o, uint8_t *data);
ODID_messagetype_t m2o_parseMavlink(mav2odid_t *m2o, uint8_t data);

void m2o_basicId2Mavlink(mavlink_open_drone_id_basic_id_t *mavBasicId,
                         ODID_BasicID_data *basicId);
void m2o_location2Mavlink(mavlink_open_drone_id_location_t *mavLocation,
                          ODID_Location_data *location);
void m2o_authentication2Mavlink(mavlink_open_drone_id_authentication_t *mavAuth,
                                ODID_Auth_data *Auth);
void m2o_selfId2Mavlink(mavlink_open_drone_id_self_id_t *mavSelfID,
                        ODID_SelfID_data *selfID);
void m2o_system2Mavlink(mavlink_open_drone_id_system_t *mavSystem,
                        ODID_System_data *system);

#endif /* _MAV2ODID_H_ */
