#ifndef __DIRECTLS_H__
#define __DIRECTLS_H__

#include <dirent.h>

typedef struct Directory_
{
    char    name[MAXNAMLEN + 1];
}Directory;

int directory(const char *path, Directory **dir);

#endif
