#include "arg.h"

#include <string.h>

bool ArgExists(int argc, char **argv, const char *arg)
{
	for(int i = 0; i<argc; ++i){
		if(!strcmp(argv[i],arg)){
			return true;
		}
	}
	return false;
}

char *ArgGetValue(int argc, char **argv, const char *arg)
{
	for(int i = 0; i<argc; ++i){
		if(!strcmp(argv[i],arg)){
			if((i+1)<argc){
				return argv[i+1];
			}else return 0;
		}
	}
	return 0;
}
