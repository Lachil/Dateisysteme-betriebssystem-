#ifndef INODECREAT_H
#define INODECREAT_H
#include<stdint.h>
const static int POINTERS_PER_INODE = 10;
struct Inode;
struct Inode* createInod(long sizenode,int valid);
struct Inode* InodeBlock(unsigned long size,unsigned long disksize,unsigned int blocSize);

#endif // INODECREAT_H
