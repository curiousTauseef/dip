#ifndef __ARG
#define __ARG

bool ArgExists(int argc, char **argv, const char *arg);
char *ArgGetValue(int argc, char **argv, const char *arg);

#endif