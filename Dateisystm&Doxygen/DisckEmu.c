#include"DisckEmu.h"

struct HDD* createHDD(unsigned int size)
{
    /**
     * @see createHDD()
      * @details das Erstellen von HDD-DISCK
      * @param size grosse der Festplatt
      * @return  zeiger auf HDD,der wurde erstellt
      */
    struct HDD* hdd = (struct HDD*) malloc(sizeof(HDD));

    hdd->mbr = (struct MBR*) malloc(sizeof(struct MBR));
    hdd->mbr->partitionTable[FAT] =  malloc(sizeof(struct Partitation));
    hdd->mbr->partitionTable[INODE] =  malloc(sizeof(struct IPartition));

    hdd->mbr->partitionTable[FAT]->fat = NULL;
    hdd->mbr->partitionTable[FAT]->inode = NULL;
    hdd->mbr->partitionTable[INODE]->inode = NULL;
    hdd->mbr->partitionTable[INODE]->fat = NULL;

    hdd->size = size;
    printf("es wurde HDD mit grosse %d  erstellt .",size);
    return hdd;
}
void createPartition(struct HDD* hdd,char *nameParti,unsigned int Art ,int size, int blockSize){
    /**
     * @see createPartition()
      * @details das Erstellen von Partitation fuer HDD
      * @param  hdd zeiger auf HDD-DISCK,der wurde schon erstellt
      * @param nameParti Name der Partition
      * @param blockSize grosse der Block
      * @param Art ob ist INODE oder FAT
      */
    struct Partitiondisck* partition = (struct Partitiondisck*) malloc(sizeof(struct Partitiondisck));

    if(Art == 0)
    {
        if(hdd->mbr->partitionTable[FAT]->fat == NULL)
        {
            partition->fat = Partitionerstellen(nameParti,size,blockSize);
            hdd->mbr->partitionTable[FAT]->superblock = (struct Superblock*) malloc(sizeof(struct Superblock));
            hdd->mbr->partitionTable[FAT]->superblock->magicNumber = 0;
            hdd->mbr->partitionTable[FAT]->superblock->numberOfBlocks = partition->fat->blockCount;
            hdd->mbr->partitionTable[FAT]->fat = partition->fat;
        }
        else
        {
           printf("Partition bereits belegt!");
        }
    }
    else if(Art == 1)
    {
        if(hdd->mbr->partitionTable[INODE]->inode == NULL)
        {
            partition->inode = createINODEpartition(nameParti,size,blockSize);
            hdd->mbr->partitionTable[INODE]->superblock = (struct Superblock*) malloc(sizeof(struct Superblock));
            hdd->mbr->partitionTable[INODE]->superblock->magicNumber = 1;
            hdd->mbr->partitionTable[INODE]->superblock->numberOfBlocks = partition->inode[1].BlockCount;
            hdd->mbr->partitionTable[INODE]->inode = partition->inode;
        }
        else
        {
            printf("Partition bereits belegt!");
        }
    }
    free(partition);//frei fuer speicherplz partition
}
