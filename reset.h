#ifndef reset_h
#define reset_h

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

ssize_t write_string(int fd, const char *str);
void execute_commands(char *commands);
void execute_command(char *comd;
		)
#endif
