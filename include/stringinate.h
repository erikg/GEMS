#ifndef __STRINGINATE_H
#define __STRINGINATE_H

/** convert a linked list into a single character array (string) */
extern char *stringinate (void *list);

/** read a file into a linked list. */
void *read_file_to_list (char *filename);


#endif
