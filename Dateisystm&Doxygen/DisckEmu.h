
#ifndef DISCK_H
#define DISCK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include"BsInodes.h"
/**
* @brief DisckEmu
* @details DisckEmu ist  Festplatt und Funktionen dafür ,zu erstellen
* @author Lhabib Lachil
* @version 1.0
* @date 28.08.2020
*/




typedef enum StateDisck{
    /**
     * @enum StateDisck
     * @brief gibt uns ob FAT oder INODE ist ein Partition
     */
    FAT,INODE
}StateDisck;

struct Superblock {
    /**
     * @struct Superblock
     * @brief die struct erstellt die magicNumber und numberOfBlocks usf disck
     * @brief  Variable magicNumber der Festplatt
     * @brief Variable numberOfBlocks nummer der Blocks
     */
    int magicNumber;
    int numberOfBlocks;
} Superblock;

struct Partitiondisck {
    /**
     * @struct Partitiondisck
     * @brief die struct ,die die Verwaltung  einer  Partition von Disck
     * @brief  Variable superblock der Disck
     * @brief Variable fat wenn Partitation ist FAT
     * @brief Variable inode wenn Partitation ist INODE
     */
    struct Superblock* superblock;
    struct Partitation* fat;//BsFat
    struct IPartition* inode;//Inode
} Partition;


struct MBR {
    /**
     * @struct MBR
     * @brief die struct ,die die Verwaltung  einer  tabelle von Festplatt
     * @brief  Variable partitionTable Tabelle der Festplatt
     */
    struct Partitiondisck* partitionTable[2];
} MBR;

struct HDD {
    /**
     * @struct HDD
     * @brief die struct ,die die Verwaltung  einer  HDDdisck mit grosse size
     * @brief  Variable mbr zeiger auf struct MBR
     * @brief Variable size grosse der der Festplatt
     */
    struct MBR* mbr;
    unsigned int size;
} HDD;

struct HDD* createHDD(unsigned int size);
void createPartition(struct HDD* hdd,char *disck_name,unsigned int Art ,int size, int blockSize);
void deletePartition(struct HDD* hdd, int typ);
void deleteHDD(struct HDD* hdd);

struct HDD* createHDD(unsigned int size);
#endif // DISCK_H
