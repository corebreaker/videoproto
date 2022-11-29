/* 
 * File:   flasher.h
 * Author: frederic
 *
 * Created on 29 novembre 2022, 05:40
 */

#ifndef FLASHER_H
#define	FLASHER_H

#include <stdbool.h>
#include "./data.h"

#ifdef	__cplusplus
extern "C" {
#endif

bool flasher_cmd_header(t_endpoint_data *);
bool flasher_cmd_record(t_endpoint_data *);

#ifdef	__cplusplus
}
#endif

#endif	/* FLASHER_H */
