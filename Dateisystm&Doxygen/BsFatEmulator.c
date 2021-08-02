#include"BsFatEmulator.h"
#include"DisckEmu.h"



struct Partitation *Partitionerstellen(char *Pname, unsigned long paritationsize,unsigned int blockSize){
    /**
     * @see Partitionerstellen()
      * @details das Erstellen von Partitation FAT
      * @param  Pname Name der Partitation
      * @param paritationsize grosse des Partitation
      * @param blockSize grosse der Block
      * @return  zeiger auf Partitation FAT
      */
        //Zahl der Block berechnen
     int Blockcount=ceil((paritationsize)/blockSize);
     struct Partitation* PartFat=(struct Partitation*)malloc(sizeof (struct Partitation));
     //Variablen der Funktion ersetzen
     PartFat->blocSize=blockSize;
     PartFat->blockCount=Blockcount;
     PartFat->Pname=Pname;
     PartFat->pblocks=(struct Block**)calloc(Blockcount,sizeof (struct Block*));

    for(int j=0;j<Blockcount;j++){
        //alle Blocks initialisieren
         PartFat->pblocks[j]=(struct Block*)calloc(1,sizeof (struct Block));
     PartFat->pblocks[j]->state=frei;
     PartFat->pblocks[j]->left=malloc(1*sizeof (unsigned int));
     PartFat->pblocks[j]->right=malloc(1*sizeof (unsigned int));
}
    PartFat->FitArray=(struct BsFile**)calloc(10,sizeof(struct BsFile*));
    for (int j=0;j<10;j++) {
        // 10 BsFat Array wurde initialisiert
        PartFat->FitArray[j]=(struct BsFile*)calloc(1,sizeof(struct BsFile));
    }
    printf("es wurde Partitation fuer FAT erstellt .");
    return PartFat;
};


struct  BsFile* createFileFAT(struct Partitation *Part, unsigned long size, unsigned char* name) {

    /**
     * @see createFile()
      * @details BsFile erstellen
      * @param  Part BsFat wo File erstellen
      * @param size grosse des File
      * @return  File in Partitation FAT zurueckgeben
      */

      printf("File creating\n");
        unsigned int block_count = ceil(size / (Part->blocSize));//block-count berchnen
        if (getFreeDiskSpace(Part) < block_count) {
            //wenn gibt es nicht mehr frei Platz  in Partitation  fuer Datei
          printf("Kein freier Speicher für diese Datei\n");
        } else {
            //index  der  platz von Datei
            int indexCurFile = -1;
            //such auf frei platz fuer Detai
            for (int i = 0; i<ARRAY_LENGTH; i++) {
              if (Part->FitArray[i] != NULL) {
                if (Part->FitArray[i]->fileSize == 0) {
                  indexCurFile = i;
                  break;
                }
              }
            }
            if (indexCurFile > -1) {//wenn gibt es platz fuer Datei
            struct Block* firstClusterForFile = (struct Block*) calloc(1, sizeof (struct Block));
            //erst Block fuer Datei erstellen und alle Variable erstzen
            firstClusterForFile->right = NULL;
            firstClusterForFile->left = NULL;
            firstClusterForFile->Datablock = getIndexOfFreeBlock(Part);// Index dafuer geben
            Part->pblocks[firstClusterForFile->Datablock]->state = belegt;
            Part->FitArray[indexCurFile]->fileSize = size;
            strcpy(Part->FitArray[indexCurFile]->name, name);
            Part->FitArray[indexCurFile]->StartBlock = firstClusterForFile;
            struct Block* iteratorC = firstClusterForFile;
            for (unsigned int i = 0; i < (block_count - 1); i++) {//Datei auf mehrer Blocks reinpacken
              struct Block* newCluster = (struct Block*) calloc(1, sizeof (struct Block*));
              if (newCluster != NULL) {
                newCluster->Datablock = getIndexOfFreeBlock(Part);
                newCluster->right = NULL;
                newCluster->left = iteratorC;
                newCluster->left->right = newCluster;
                Part->pblocks[newCluster->Datablock]->state = belegt;
                iteratorC->right = newCluster;
                iteratorC = newCluster;
              } else {//wenn gibt es nicht mehr Speicher fuer den Cluster
                printf("Fehler beim Speichern des Speichers fuer den Cluster [%u] in Datei [%s]\n", i, name);
              }
            }
            printf("Datei  %s wird erfolgreich erstellt - blocks_used= %d\n", name, block_count);
            struct Block* temp = Part->FitArray[indexCurFile]->StartBlock;
            printf(" index of blocks userd: [");//zeigt uns Index ,wo steht Datei
            while (temp != NULL) {
              printf("%u", temp->Datablock);
              temp = temp->right;
              if (temp != NULL) {
                printf("; ");
              }
            }
            printf("]\n");

            return Part->FitArray[indexCurFile];

        }else {//wenn Die maximal zulässige Anzahl von Dateien ist bereits erreicht
            printf("Die maximal zulässige Anzahl von Dateien ist bereits erreicht");
          }
        }
      return NULL;

      }
unsigned  int getIndexOfFreeBlock(struct Partitation *Part){
    /**
     * @see getIndexOfFreeBlock()
      * @details sucht auf Index der Frei Block
      * @param  Part Partitation FAT
      * @return  Index der Frei Block
      */
    unsigned int Index ;
      unsigned int randomBlock = (unsigned int) rand() % Part->blockCount;//gibt zufaellig auf freie Bloecke der Platte.
      if (Part->pblocks[randomBlock] != NULL && Part->pblocks[randomBlock]->state == frei) {//ob ist es freie
         Index=randomBlock;
          return Index;
      } else {
        for (unsigned int j = 0; j < Part->blockCount; j++) {//Ansonsten sucht auf freie Block
          if (Part->pblocks[j]->state == frei) {
              Index=j;
              return Index;
          }
        }
      }
      return 0;}
unsigned int getFreeDiskSpace(struct Partitation *Fatdisck){
    /**
     * @see getFreeDiskSpace()
      * @details freien Speicher auf einer Platte brechnen
      * @param getFreeDiskSpace BsFat*
      * @return  freien Speicher auf einer Platte zurueckgeben
      */
    unsigned int freeDiskSpace=0;
        for(unsigned int j=0;j<Fatdisck->blockCount;j++){//sucht auf alle Bloecke in Partitation
        if(Fatdisck->pblocks[j]->state==frei){//ob Blocke frei ist
            freeDiskSpace ++;
    }

}
 printf("%d",freeDiskSpace);
    return freeDiskSpace;
}

void getFragmentation(struct Partitation* pFat){
    /**
     * @see getFragmentation()
      * @details diese Funktion gibt durchschnittliche Fragmentierung auf Ihrer Festplatte (zwischen 0 und 100 Prozent) zurueck
      * @param  pFat  Partitation der FAT
      */
    int busyBlocks = 0, damagedBlocks = 0, freeBlocks = 0, resavedBlocks = 0, unknownState = 0;

    for (unsigned int i = 0; i < pFat->blockCount; i++) {//alle faelle der State berchnen
      switch (pFat->pblocks[i]->state) {
        case belegt:// ob belegt
          busyBlocks++;
          break;
        case RESERVIERT://ob RESERVIERT
          resavedBlocks++;
          break;
        case defekt://ob defekt
          damagedBlocks++;
          break;
        case frei://frei
          freeBlocks++;
          break;
        default://on unbekannter
          unknownState++;
          printf("getFragmentation:: unbekannter Blockzustand. Blockindex >> %d\n", i);
      }
    }

    printf("\n-- Fragmention --\n");
    printf("Filled Blocks of partitation: %d (%u %%) \n", busyBlocks, (busyBlocks * 100 / pFat->blockCount));
    printf("Damaged Blocks of partitation: %d (%u %%)\n",damagedBlocks, (damagedBlocks * 100 / pFat->blockCount));
    printf("Free Blocks of  partitation: %d (%u %%)\n",freeBlocks, (freeBlocks * 100 / pFat->blockCount));
    printf("Resaved Blocks of  partitation : %d (%u %%)\n",resavedBlocks, (resavedBlocks * 100 / pFat->blockCount));
    if (unknownState > 0) {
      printf("Blocks with undefined state: %d (%u %%)\n", unknownState, (unknownState * 100 / pFat->blockCount));
    }
    printf("------------------------\n");
}
int getFileOwnerOfBlock(struct Partitation* bsFat, int blockIndex) {
    /**
     * @see getFileOwnerOfBlock()
      * @details BsFile erstellen
      * @param  bsFat BsFat
      * @param blockIndex
      * @return  nummer Datei zurueckgeben,die hat erst blocke blockIndex
      */
   for (int i = 0; i < ARRAY_LENGTH; i++) {//alle Datei lesen
     if (bsFat->FitArray[i] != NULL) {
       if (strcmp(bsFat->FitArray[i]->name, "") != 0) {//ob Datei in nicht leer
        struct Block* temp = getClusterByBlockIndex(bsFat->FitArray[i], blockIndex);//test ob blockIndex ist erst block von diesem Datei
         if (temp != NULL) {
           return i;
         }
       }
     }
   }
   return -1;
 }
struct Block *getClusterByBlockIndex(struct BsFile* file,unsigned int index){
    /**
     * @see getClusterByBlockIndex()
      * @details BsFile erstellen
      * @param  file zeiger auf Datei
      * @param index der erst block von Datei
      * @return   erst Block von Datei  zurueckgeben
      */
   if (file != NULL) {//
    struct  Block* temp = file->StartBlock;
     while (temp != NULL) {//such ueber alle erst blcok von Datei
       if (temp->Datablock == index) {
         return temp;
       }
       temp = temp->right;
     }
   } else {//ob hat nicht gefunden
     printf("getClusterByBlockIdnex::file given is not readable\n");
   }
   return NULL;
 }
void defragDisk(struct Partitation * bsFat) {
    /**
     * @see defragDisk()
      * @details es wird die  Bloecke von  jedem einzelnen Datei  gruppiert,dass sie moeglichst zusammenhaengend auf der Platte liegen.
      * @param  bsFat Fat Partitation
      */
  printf("-- Defragmentation --\n");
  printf("\n\n** Versand freie Bloecke zu Ende**\n");
  struct Partitation *Part=malloc(sizeof (struct Partitation));
  Part=bsFat;
  for (unsigned int i = 0; i < Part->blockCount; i++) {//versend freie Bloecke zu Ende
    if (Part->pblocks[i]->state == frei) {
      for (unsigned int j = (i + 1); j < Part->blockCount; j++) {
        if (Part->pblocks[j]->state != frei) {
          if (Part->pblocks[j]->state == belegt) {
            printf("busy block found\n");
            int indexOfFileOwner = getFileOwnerOfBlock(bsFat, j);
            if (indexOfFileOwner > -1) {
             struct  Block* temp = Part->FitArray[indexOfFileOwner]->StartBlock;
              temp = getClusterByBlockIndex(Part->FitArray[indexOfFileOwner], j);
              if (temp == NULL) {
                printf(" Defragmentierung ist  nicht moeglich,weil %s nicht auflöst wurde", Part->FitArray[indexOfFileOwner]->name);
              }
              temp->Datablock = i;
            }
          }
          printf("block mit state (%d) wird aus dem Index verschoben %d nach index %d \n",
                  Part->pblocks[j]->state, j, i);
          struct Block* blockTemp = Part->pblocks[i];
          Part->pblocks[i] = Part->pblocks[j];
          Part->pblocks[j] = blockTemp;
          break;
        }
      }
    }
  }

  printf("\n\n** Sammle Dateibloecke miteinander**\n");
  for (unsigned int i = 0; i < Part->blockCount; i++) {//alle bloecke lesen
    if (Part->pblocks[i]->state != frei) {//ob blocke ist frei
      int indexOfFileOwner = getFileOwnerOfBlock(bsFat, i);//gibt uns File von diesem Index i
      for (unsigned int j = (i + 1); j < Part->blockCount; j++) {//alle Bloecke lesen
        if (Part->pblocks[j]->state == belegt) {//ob state ist belegt
          int indexOfFileOwner2 = getFileOwnerOfBlock(bsFat, j);
          if (indexOfFileOwner != indexOfFileOwner2) {
            for (unsigned int s = (j + 1); s < Part->blockCount; s++) {
              if (Part->pblocks[s]->state == belegt) {
                int indexOfFileOwner3 = getFileOwnerOfBlock(bsFat, s);
                if (indexOfFileOwner == indexOfFileOwner3) {
                  getClusterByBlockIndex(Part->FitArray[indexOfFileOwner2], j)->Datablock = s;
                  getClusterByBlockIndex(Part->FitArray[indexOfFileOwner3], s)->Datablock = j;
                  printf("block moved from index %d to index %d\n\n", s, j);
                  struct Block* tempBlock = Part->pblocks[s];
                  Part->pblocks[s] = Part->pblocks[j];
                  Part->pblocks[j] = tempBlock;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }}
void deleteFileFat(struct Partitation *pFat, char *fileName){
    /**
     * @see deleteFile()
      * @details es wird Datei durch name  loescht
      * @param  pFat BsFat wo File steht
      * @param fileName Name des File , die wollen wir loeschen
      */
    for (int i=0;i<10;i++) {//sucht auf alle Datei in Partitation
        if(strcmp(pFat->FitArray[i]->name,fileName)==0){// Datei loeschen falls es gefunden wurde
            if(pFat->FitArray[i]->StartBlock->right!=NULL){
                pFat->pblocks[pFat->FitArray[i]->StartBlock->Datablock]->state=frei;
                pFat->FitArray[i]->StartBlock=pFat->FitArray[i]->StartBlock->right;
                free(pFat->FitArray[i]->StartBlock->left);
            }
            pFat->pblocks[pFat->FitArray[i]->StartBlock->Datablock]->state=frei;
            pFat->FitArray[i]->StartBlock = pFat->FitArray[i]->StartBlock->left;
            pFat->FitArray[i]->StartBlock->right = NULL;
            free(pFat->FitArray[i]->StartBlock->right);
            for (int j = 0; j < 10; j++) {
              pFat->FitArray[i]->name[j] = '\0';
            }
            printf(" File %s", fileName);
            printf(" wurde geloescht\n");
            return;
        }else if(i==9 && strcmp(pFat->FitArray[i]->name,fileName)!= 0){//ob es keine Datei mit diesem name gefunden wurde
    printf("kein datei mit name %s gefunden .\n", fileName);
    }

    }

}
void sfs_ls(struct Partitation* pFat,unsigned int File_Max_FAT){
    /**
     * @see sfs_ls()
      * @details alle Datei in Partitation FAT anzeigen
      * @param  pFat Fat Partitation
      * @param Zahle der Datei ,der schon erstellt wurde
      */
    printf("\n");
    for(int i=0;i<File_Max_FAT;i++){//alle Datei in Partitation FAT angeben
        if(pFat->FitArray[i]==NULL) break;//falls keine mehr Datei
   printf("%s:\\",pFat->Pname);
   printf("%s \n",pFat->FitArray[i]->name);
    }
}
void CD_FAT(struct Partitation* pFat,struct CD* cd)
{ /**
     * @see CD_FAT()
      * @details es wurde alle Datei von CD nach Partitation FAT koppieren
      * @param  pFat Fat Partitation
      * @param Zahle der Datei ,der schon erstellt wurde
      */
    for(int i=0;i<cd->filesCount;i++){//alle Datei in CDROOM lesen  und wieder in FAT schreiben
    createFileFAT(pFat,cd->files[i]->size,cd->name) ;
    printf("es wurde Datei %s nach FAT partitionen kopiert ",cd->files[i]->name);
    }
}
