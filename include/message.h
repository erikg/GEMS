#ifndef _MESSAGE_H
#define _MESSAGE_H

/** An email message */
typedef struct {
    char **attachments;
    char *body;
    char *header;
    char *id;
    char *mbox;
    char *recipt;
    char *recvdate;
    char *references;
    char *replyto;
    char *senddate;
    char *sender;
    char *status;
    char *subject;
} message;

/** the info useful for displaying lists of emails */
typedef struct _synopsis {
    int id;
    char *sender;
    char *date;
    char *subject;
} synopsis;

/** info pertaining to a mail box */
typedef struct {
    int id;
    char *name;
    int sub;
    int hasunread;
} mboxs;

/** convert a linked list to a message struct */
extern message *message_build_from_list (void *list);

/** convert a text buffer to a message struct */
extern message *message_build_from_buffer (char *buf);

/** purge a message from memory */
extern int message_destroy (message * mess);

#endif
