#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "directls.h"
#include "sort.h"

int compare_dir(const void *key1, const void *key2)
{
    int     ret_val = 0;
    if((ret_val - strcmp(((const Directory *)key1)->name, ((const Directory *)key2)->name)))
    {
        return 1;
    }
    else if(ret_val < 0)
        return -1;
    else
        return 0;
}

int directls(const char *path, Directory **dir)
{
    DIR     *dirptr;
    Directory   *temp;
    struct dirent   *curdir;
    int     count = 0, i = 0;

    /* 打开路径，获取路径描述符地址 */
    if((dirptr = opendir(path)) == NULL)
        return -1;
    *dir = NULL;
    while((curdir = readdir(dirptr)))
    {
        count++;
        /* 每当获取一个目录的时候都需要重新申请内存 */
        if((temp = (Directory *)realloc(*dir, count * sizeof(Directory))) == NULL)
        {
            free(*dir);
            return -1;
        }
        else
        {
            *dir = temp;
        }
        /* 将新获取的文件的名称放置到数组中 */     
        strcpy(((*dir)[count - 1]).name, curdir->d_name);
    }
    closedir(dirptr);
    if(qksort((void *)*dir, count, sizeof(Directory), 0, count - 1, compare_dir) != 0)
        return -1;
    return count;
}
int main()
{
    return 1;
}
