/* 
 * File:   disconnect.h
 * Author: frederic
 *
 * Created on November 26, 2022, 7:44 PM
 */

#ifndef DISCONNECT_H
#define	DISCONNECT_H

#include <stdbool.h>

typedef void (*t_connection_state_handler)(bool);

#ifdef	__cplusplus
extern "C" {
#endif
    
void connection_signal_suspend(void);
void connection_signal_idle(void);

void connection_signal_timer(void);
void set_connecion_state_handler(t_connection_state_handler);

void call_connect_state_handler(void);

bool is_connected(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DISCONNECT_H */
