#ifndef __GEMS_TRANSMITTER_H_
#define __GEMS_TRANSMITTER_H_

#include "message.h"

#define TRANSMIT_SMTP		1
#define TRANSMIT_SENDMAIL	2

/** send an email */
int transmit_message (message * m, int agent);

#endif
