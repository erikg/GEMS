#include "message.h"
#include "transmitter.h"

int transmit_sendmail (message *);

int transmit_message (message * m, int agent)
{
	return transmit_sendmail (m);
}
