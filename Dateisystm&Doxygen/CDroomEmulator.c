#include"CDroomEmulator.h"

struct CD* createCD(char *name, int size, int blockSize, struct  CDFile** Files, int filescount)
{
    /**
     * @see createCD()
      * @details das Erstellen von Partitation FAT
      * @param  name Name der CDROOM
      * @param size grosse des CDROOM
      * @param blockSize grosse der Block
      * @param Files Zeiger auf Tabelle der Datei
      * @param filescount Zahle der Datei in CDROOM
      * @return  zeiger auf CDROOM
      */
    struct CD* cd = (struct CD*) malloc(sizeof(struct  CD));

    cd->cdSize = size;
    cd->name=name;
    cd->blockSize = blockSize;
    cd->blocksCount = size/blockSize;
    cd->filesCount = filescount;



    time_t t = time(NULL);
    struct tm *ptm = gmtime(&t);
    char buf[50];
    strftime(buf, sizeof buf, "%c", ptm);
    cd->zeitErstellt = strdup(buf);
    int neededBlocks = 0;
    for(int i = 0; i < cd->filesCount; i++)
    {
        neededBlocks += ceil((Files[i]->size)/(blockSize));
    }

    if(neededBlocks > cd->blocksCount)
    {
        printf("Nicht genüg Platz mehr vorhanden!");
        return NULL;
    }

    cd->blocks = (struct CDBlock**) malloc(sizeof(struct CDBlock*) * cd->blocksCount);
    cd->files = Files;

    for(int i = 0; i < cd->blocksCount; i++)
    {
        cd->blocks[i] = (struct CDBlock*) malloc(sizeof(struct CDBlock));
        cd->blocks[i]->index = -1;
        cd->blocks[i]->boot = 0;
        cd->blocks[i]->frei = 1;
        cd->blocks[i]->meta = 0;
    }
    for(int i = 0; i < 16; i++)
    {
        cd->blocks[i]->frei = 0;
        cd->blocks[i]->meta = 0;
        cd->blocks[i]->boot = 1;
    }

    cd->blocks[16]->frei = 0;
    cd->blocks[16]->meta = 1;
    cd->blocks[16]->boot = 0;

    int index = 0;
    int a = ceil((Files[0]->size)/(blockSize));
    for(int i = 17; i < neededBlocks+17; i++)
    {
        if(i-17 == a)
        {
            index++;
            if(index > cd->filesCount-1) break;
            a += ceil((Files[index]->size*1.0)/(blockSize*1.0));
        }
        cd->blocks[i]->index = index;
        cd->blocks[i]->frei = 0;
    }
    printf("es wurde ein CD %s in Zeit %s ",cd->name,cd->zeitErstellt);
    return cd;
}

struct CDFile* CDFileerstellt(char* name, int fileSize)
{
    /**
     * @see CDFileerstellt()
      * @details BsFile erstellen
      * @param Filesize grosse des File
      * @param name der File
      * @return  File fuer CDROOM erstellen
      */
    struct CDFile* file = (struct CDFile*) malloc(sizeof(struct CDFile));
    file->name = name;
    file->size = fileSize;
    time_t t = time(NULL);
    struct tm *ptm = gmtime(&t);
    char buf[50];
    strftime(buf, sizeof buf, "%c", ptm);
    file->zeitErstellt = strdup(buf);
    printf("es wurde eine CdDatei %s : in Zeit : %s erstellt:  .",name,file->zeitErstellt);
    return file;
}
void ls_cd(struct CD *cd){
    /**
     * @see ls_cd()
      * @details alle Datei in CDROOM anzeigen
      * @param  cd Zeiger auf CDROOM
      */
    for(int i = 0; i < cd->filesCount; i++){//lesen alle Datei in CDROOM
        printf("%s://",cd->name);
        printf("%s\n",cd->files[i]->name);

    }
}
