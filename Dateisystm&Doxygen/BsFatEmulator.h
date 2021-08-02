#ifndef BSFAT_H
#define BSFAT_H

#define ARRAY_LENGTH 10
#define MAX_FILE_NAME_LENGTH 10
#include"CDroomEmulator.h"
/**
* @brief BsFatEmulator
* @details BsFatEmulator ist  für Partitation FAT Funktionen dafür ,zu erstellen
* @author Lhabib Lachil
* @version 1.0
* @date 28.08.2020
*/




struct Partitation{
    /**
     * @struct BsCluster
     * @brief die struct ,die die Verwaltung  einer  Festplatte   ueber  Bloecke ermoeglich
     * @brief  Variable PSize grosse der Partitation
     * @brief Variable blocSize grosse der Block
     * @brief Variable blockCount Zahle der Block in Partitation
     * @brief Variable pblocks tabelle von zeiger auf Blocks,die wurde es erstellt
     * @brief Variable FitArray tabelle von zeiger auf alle Array in diese Partitation
     */
    char *Pname;
    unsigned long PSize;
    unsigned int blocSize;
    unsigned int blockCount;
   struct  Block** pblocks;
   struct BsFile** FitArray;
};

typedef enum State {
    frei, /**< enum Frei Platz  */
    RESERVIERT, /**< enum Frei  */
    belegt, /**< enum belegt  */
    defekt /**< enum defekt  */
} State;
struct Block{
    /**
     * @struct Block
     * @brief die struct ,die die Verwaltung  einer  Festplatte   ueber  Bloecke ermoeglich
     * @brief Variable index Block index
     * @brief Variable left Vorgänger Element
     * @brief Variable right nächste Element
     */
    unsigned int Datablock;
    struct Block* left;
    struct Block* right;
    State state;
};

struct BsFile{
    /**
     * @struct BsFile
     * @brief die struct ,die eine Datei Festplatte erstellt
     * @param neame[10] Datei Name
     * @param fileSize Datei Größe
     * @param Id Besetzer ID
     * @param clusterBlock eine Veketette Liste
     */
    char name[10];
    unsigned int fileSize;
    unsigned int Id;
    struct Block* StartBlock;
};
//struct disck *disckerstellen(char *disck_name, unsigned long diskSize,unsigned int zahl_partitation);
struct Partitation *Partitionerstellen(char *Pname, unsigned long paritationsize, unsigned int blockSize);
struct  BsFile* createFileFAT(struct Partitation *Fatdisck, unsigned long size,unsigned char* name) ;
unsigned int getFreeDiskSpace(struct Partitation *Fatdisck);
unsigned  int getIndexOfFreeBlock(struct Partitation *Part);
void getFragmentation(struct Partitation* pFat);
int getFileOwnerOfBlock(struct Partitation* bsFat, int blockIndex);
struct Block *getClusterByBlockIndex(struct BsFile* file, unsigned int index);
void defragDisk(struct Partitation * bsFat);
void deleteFileFat(struct Partitation *pFat,char *fileName);
void sfs_ls(struct Partitation* pFat, unsigned int File_Max_FAT);
void CD_FAT(struct Partitation* pFat,struct CD* cd);




#endif // BSFAT_H
