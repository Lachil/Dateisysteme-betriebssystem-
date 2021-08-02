#ifndef BSINODES_H
#define BSINODES_H
#include"DisckEmu.h"
#include"BsFatEmulator.h"
static  const unsigned int INODES_PER_BLOCK   = 128;//globale Variable fur INODE Blocks
static const unsigned int POINTERS_PER_INODE = 12;//globale Variable fuer INODE
/**
* @brief BsInodes
* @details BsInodes ist  für Partitation INODE Funktionen dafür ,zu erstellen
* @author Lhabib Lachil
* @version 1.0
* @date 28.08.2020
*/


typedef enum StateInode{
    FREE,BELEGT
}StateInode;
struct InodeBlock{
    /**
     * @struct InodeBlock
     * @brief die struct ,die die Verwaltung  einer  Festplatte   ueber  InodeBloecke ermoeglich
     * @brief  Variable Index zeiger auf block
     * @brief Variable Data Info der Datei
     * @brief Variable State faelle der Block
     */
    StateInode state;
    unsigned int index;
     double Data;
    }InodeBlock;
 struct InodeFile{
     /**
      * @struct InodeFile
      * @brief die struct ,die die Verwaltung  einer  Festplatte   ueber  Bloecke ermoeglich
      * @brief  Variable Index zeiger auf block
      * @brief Variable Data Info der Datei
      * @brief Variable State faelle der Block
      */
    char* name;
    int size;
    struct InodeBlock* direct[12];
    struct indirectBlock* indirect;
    struct InodeFile* nextFile;
} ;
 struct indirectBlock{
     /**
      * @struct indirectBlock
      * @brief indirect Zeiger auf 128 Blocks
        */
     struct InodeBlock* indirect[128];
 };
 struct IPartition{
     /**
      * @struct IPartition
      * @brief die struct ,die die Verwaltung  einer  Partition   ueber  InodeBloecke ermoeglich
      * @brief  Variable disckSize grosse der PArtitation
      * @brief Variable blockSize grosse der Block
      * @brief Variable BlockCount Zahle der Blocks
      * @brief Variable blocks zeiger auf Tabelle von blocks
      *
      * @brief Variable Files zeiger  auf Datei
      */
     int disckSize;
     int blockSize;
     int BlockCount;
     char *NameIPart;
     struct InodeBlock** blocks;
      struct InodeFile* Files;
 } ;


struct IPartition* createINODEpartition(char *NameIPart,int Partsize, unsigned int sizeBlock);
void addINODEfile(struct IPartition* pInode, struct InodeFile* file);
float fragmentationINODE(struct IPartition* pInode);
void createINODEfile(struct IPartition* pinode, int Filesize, char* name);
int freediskspaceInode(struct IPartition* pInode);
void fileINODE(struct IPartition* pinode);
void defragIpartition(struct IPartition* pInode);
#endif // BSINODES_H

