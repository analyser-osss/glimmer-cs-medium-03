#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        perror("stat failed");
        exit(EXIT_FAILURE);
    }
    return statbuf.st_ino;
}

void print_path(ino_t cur_ino) 
{
    ino_t parent_ino = get_inode("..");//查上一级inode
    if (cur_ino == parent_ino) //判断是否到根目录
    {
        return; 
    }
    if (chdir("..") == -1) //判断是否正常
    {
        perror("chdir ..");//打印
        exit(EXIT_FAILURE);
    }
    DIR *dir = opendir(".");//打开并存储当前文件夹
    if (!dir) //判断是否打开
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;//暂存
    char name[256];
    int found = 0;

    while ((entry = readdir(dir)) != NULL) 
    {
        // 跳过 "." 和 ".."，防死循环
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }


        if (get_inode(entry->d_name) == cur_ino) 
        {
            strncpy(name, entry->d_name, sizeof(name) - 1); //记录名字
            name[sizeof(name) - 1] = '\0';//
            found = 1;
            break;
        }
        if(found==0)
        {
            return;
        }
        closedir(dir);
        print_path(parent_ino);
        printf("/%s",name);//到根目录开始逐级打印
    }
}

int main() 
{
    ino_t cur_ino = get_inode(".");     // 获取当前目录的 inode
    ino_t parent_ino = get_inode(".."); // 获取父目录的 inode

    if (cur_ino == parent_ino) 
    {
        printf("/\n"); // 如果一开始就在根目录，打印/
    } 
    else 
    {
        print_path(cur_ino); // 开始往上倒推
        printf("\n");
    }

    return 0;
}


