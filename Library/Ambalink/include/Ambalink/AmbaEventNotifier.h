/**
 * Copyright (C) 2015 Ambarella Corporation. All rights reserved.
 *
 * No part of this file may be reproduced, stored in a retrieval
 * system, or transmitted, in any form, or by any means,
 * electronic, mechanical, photocopying, recording, or otherwise,
 * without the prior consent of Ambarella Corporation.
 */
#ifndef __AMBAEVENTNOTIFIER_H__
#define __AMBAEVENTNOTIFIER_H__

#ifdef  __cplusplus
extern "C" {
#endif

/***************************************************************************/
/* This is the header file for Ambarella's Event Notifier API.             */
/* User's implementation may also include the AmbaEventDef.h               */
/* for the Event definition.                                               */
/***************************************************************************/

/**********
 * type definition for event callback, it will get four parameters:
 * event - the type of event.
 * param - the extra data for the event. For example, it will contents
 *                 [DRIVE] for card instered event,
 *                 [DRIVE] for card removed event,
 *                 [FULL PATH FILENAME] for new file created event,
 *                 [FULL PATH FILENAME] for file deleted event.
 * param_len - vaild lenth of the content in param.
 * userdata - user sepacified data.
 *
 * !!Please Note!! The param will be free automatically after callback return.
 *                 User has to backup the content if he still needd this content after
 *                 callback returns.
 *
 * !!Please Note!! The DRIVE/PATH for event will be based on definition of RTOS.
 *                 For Linux user, he needs to convert DRIVE/PATH based on Virtual FileSystem's
 *                 settings. For example, DRIVE "D" has to convert as "/tmp/fus_d", and
 *                 "A:\DCIM\100MEDIA\AMBA0001.MP4" has to convert as
 *                 "/tmp/fuse_a/DCIM/100MEDIA/AMBA0001.MP4".
 **********/
typedef void (*amba_eventnotify_eventcb)(unsigned int event, char *param, unsigned int param_len, void *userdata);

/**
 * init function for event notifier api
 *
 * @return >0 - success (version number)
 *          0 - fail
 *         <0 - fail
 **/
int AmbaEventNotify_Init(void);

/**
 * release function for event notifier api
 *
 * @return  0 - success
 *         <0 - fail
 **/
int AmbaEventNotify_Release(void);

/**
 * release function for event notifier api
 *
 * [in] event, the type of event to send to RTOS.
 * [in] param, the extra data for the event.
 * [in] param_len, vaild lenth of the content in param.
 *
 * @return <0 - fail
 *         others - send out length.
 **/
int AmbaEventNotify_Send(unsigned int event, char *param, unsigned int param_len);

/**
 * register callback function for event handling
 *
 * [in] cb_func, callback function that will be called while
 *               got event from RTOS.
 *
 * @return  0 - success
 *         <0 - fail
 **/
int AmbaEventNotifier_Reg_cbEvent(amba_eventnotify_eventcb cb_func, void *userdata);

/**
 * Execute Event Process flow.
 * This function will run forever except there is any fatal error occurs or user calls AmbaEventNotifier_StopEventProcess().
 * If program's flow does not want be blocked, it need to run this function in a separated thread.
 *
 * @return  0 - success
 *         <0 - fail
 */
int AmbaEventNotifier_ExecEventProcess(void);

/**
 * Stop Event Process flow.
 *
 * @return  0 - success
 *         <0 - fail
 */
int AmbaEventNotifier_StopEventProcess(void);


#ifdef  __cplusplus
}
#endif
#endif /* __AMBAEVENTNOTIFIER_H__ */

