#ifndef __get_next_line_h__
#define __get_next_line_h__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int get_next_line(int fd, char **line);

#endif