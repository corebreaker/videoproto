/* 
 * File:   flasher.h
 * Author: frederic
 *
 * Created on 29 novembre 2022, 05:40
 */

#ifndef APP_FLASHER_H
#define	APP_FLASHER_H

#include <stdbool.h>
#include "./app_data.h"

#ifdef	__cplusplus
extern "C" {
#endif

bool flasher_cmd_header(t_ep_data *);
bool flasher_cmd_record(t_ep_data *);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_FLASHER_H */
