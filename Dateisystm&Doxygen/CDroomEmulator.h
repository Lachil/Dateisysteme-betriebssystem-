#ifndef CDROOMEMULATOR_H
#define CDROOMEMULATOR_H
#include <math.h>
#include <time.h>
#include"DisckEmu.h"
/**
* @brief CDroomEmulator
* @details CDroomEmulator ist  CDROOM und Funktionen dafür ,zu erstellen
* @author Lhabib Lachil
* @version 1.0
* @date 28.08.2020
*/
 struct CDFile{
     /**
      * @struct CDFile
      * @brief CDFile Name der Datei
      * @brief size grosse der Datei
      * @brief zeitErstellt zeit der Erstellt
        */
     unsigned char* name;
    int size;
    char *zeitErstellt;
} CDFile;

 struct CDBlock{
     /**
      * @struct CDBlock
      * @brief frei ob block ist frei
      * @brief meta der Datei
      * @brief Index  auf DAtei
        */
    int frei;
    int boot;
    int meta;
    int index;
} CDBlock;

 struct CD{
     /**
      * @struct CD
      * @brief cdSize grosse der CDROOM
      * @brief blocksCount zahl der Blcok in CDROOM
      * @brief blockSize  grosse der Block
      * @brief filesCount zahl der Blcok von Datei
      * @brief zeitErstellt Zeit der Ertellst
      * @brief blocks Tabelle von Zeiger auf alle blocks
      * @brief files Tabelle von Zeiger auf alle Datei in CD
        */
    int cdSize;
    char *name;
    int blocksCount;
    int blockSize;
    int filesCount;
    char* zeitErstellt;
   struct  CDBlock** blocks;
    struct CDFile** files;
};
struct CDFile* CDFileerstellt(char* name, int fileSize);
struct CD* createCD(char *name,int size, int blockSize, struct CDFile** Files, int amountfiles);
void ls_cd(struct CD *cd);





#endif // CDROOMEMULATOR_H
