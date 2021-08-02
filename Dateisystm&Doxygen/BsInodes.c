#include"BsInodes.h"


struct IPartition* createINODEpartition(char *NameIPart, int Partsize, unsigned int sizeBlock){
    /**
     * @see createINODEpartition()
      * @details das Erstellen von Partitation INODE
      * @param  NameIPart Name der Partitation
      * @param Partsize grosse des Partitation
      * @param sizeBlock grosse der Block
      * @return  zeiger auf Partitation INODE
      */
   struct  IPartition* Pinode = (struct  IPartition*) malloc(sizeof(struct IPartition));

    Pinode->disckSize=Partsize;
    Pinode->blockSize = sizeBlock;
    Pinode->NameIPart=NameIPart;
    Pinode->BlockCount = Partsize/sizeBlock;

    Pinode->blocks = (struct  InodeBlock**) malloc(sizeof(struct InodeBlock*) * Pinode->BlockCount);

    for(int i = 0; i < Pinode->BlockCount; i++)
    {
        Pinode->blocks[i] = (struct InodeBlock*) malloc(sizeof(struct InodeBlock));
        Pinode->blocks[i]->state = FREE;
        Pinode->blocks[i]->index = i;
        Pinode->blocks[i]->Data = -1;
    }


    Pinode->Files = NULL;

    printf("es wurde 1 Partitation fuer Inode erstellt");

    return Pinode;
}
void addINODEfile(struct IPartition* pinode,struct InodeFile* file)
{

    /**
     * @see addINODEfile()
      * @details BsFile hinzufuegen
      * @param  pinode IPartition wo File hinzufuegen
      * @param file datei ,der hinzufuegen wird
      * @return  File in Partitation INODE hinzufuegen
      */
   struct  InodeFile* e = pinode->Files;

    if(e == NULL)
    {
        file->nextFile = NULL;
        pinode->Files = file;
        return;
    }

    while(e->nextFile != NULL)
    {
        e = e->nextFile;

    }

    file->nextFile = NULL;
    e->nextFile = file;
    printf("es wurde %s File in Inode Part erstellt .\n",file->name);
}
void createINODEfile(struct IPartition* pinode, int Filesize, char* name){

    /**
     * @see createINODEfile()
      * @details BsFile erstellen
      * @param  pinode  wo in  IPartition File erstellen
      * @param Filesize grosse des File
      * @param name der File
      * @return  File in Partitation FAT erstellen
      */
    unsigned int Data = 0;

    int neededBlocks = ceil((Filesize)/(pinode->blockSize));
    if(neededBlocks > pinode->blockSize)
    {
        printf("Nicht genügend Speicher vorhanden!");
        return ;
    }

    int freiBlocks =0;

    for(int i = 0; i < pinode->BlockCount; i++)
    {
        if(pinode->blocks[i]->state == FREE)
        {
            freiBlocks++;
        }
    }

    if(neededBlocks > freiBlocks){
        printf("Nicht genaügend Speicher vorhanden!");
        return;
    }

     struct InodeFile* file=(struct InodeFile*)malloc(sizeof(struct InodeFile));

    file->name = (name);
    file->size=Filesize;

    for(unsigned int i = 0; i < POINTERS_PER_INODE; i++)
    {
        file->direct[i] = NULL;
    }

    int foo = 0;
    int choosenBlock = rand()%pinode->BlockCount;
    while(foo < 12 && foo < neededBlocks)
    {
        if(pinode->blocks[choosenBlock]->state == FREE)
        {
            pinode->blocks[choosenBlock]->state = FREE;
            pinode->blocks[choosenBlock]->Data = Data;
            file->direct[foo] = pinode->blocks[choosenBlock];
            foo++;
        }
        choosenBlock = rand()%pinode->BlockCount;
    }

    struct indirectBlock* indirectFile=NULL;

    if(neededBlocks > 12)
    {
        indirectFile = (struct indirectBlock*) malloc(sizeof(struct indirectBlock));
        for(unsigned int i = 0; i < INODES_PER_BLOCK; i++)
        {
            indirectFile->indirect[i] = NULL;
        }

        file->indirect = indirectFile;

        int bar = 0;
        choosenBlock = rand()%pinode->BlockCount;
        while(bar < neededBlocks-10)
        {
            if(pinode->blocks[choosenBlock]->state == FREE)
            {
                pinode->blocks[choosenBlock]->state = BELEGT;
                pinode->blocks[choosenBlock]->Data = Data;
                file->indirect->indirect[bar] = pinode->blocks[choosenBlock];
                bar++;
            }
            choosenBlock = rand()%pinode->BlockCount;
        }
    }

    file->indirect = indirectFile;
    addINODEfile(pinode, file);}

int freediskspaceInode(struct IPartition* pInode)
{
    /**
     * @see freediskspaceInode()
      * @details freien Speicher auf  IPartition brechnen
      * @param pInode IPartition*
      * @return  freien Speicher auf einer Platte zurueckgeben
      */
    if(pInode!=NULL)
    {
        int freeSpace = 0;
        for(int i = 0; i < pInode->BlockCount; i++)
        {
             if(pInode->blocks[i]->state == FREE )
             {
                 freeSpace += pInode->blockSize;
             }
        }
        return freeSpace;
    }
    return 0;
}
float fragmentationINODE(struct IPartition* pInode){
    /**
     * @see fragmentationINODE()
      * @details diese Funktion gibt durchschnittliche Fragmentierung auf Ihrer Festplatte (zwischen 0 und 100 Prozent) zurueck
      * @param  pInode  IPartition der INODE
      */
    if(freediskspaceInode(pInode)<pInode->disckSize)
    {
        float verbblock = 0, belegtebloecke=0;
        for(int i =0;i<pInode->BlockCount;i++)
        {
            struct InodeBlock* Inode =pInode->blocks[i];
            if(Inode->Data!=-1)
                belegtebloecke++;
        }
         float freiBlock=0;
        for(int i =0;i<pInode->BlockCount;i++)
        {
            if(pInode->blocks[i]->state==FREE)
                freiBlock++;
        }
        for(int i =0;i<pInode->BlockCount;i++)
        {
            struct InodeBlock* node =pInode->blocks[i];
            unsigned int clusterBlock = node->Data;
            node=pInode->blocks[i];
            if (node->Data== clusterBlock && node->Data!=-1)
                verbblock++;
            clusterBlock = node->Data;
        }
        struct InodeFile* element=pInode->Files;
        float numberoffiles = 0;
        while(element!=NULL)
        {
            numberoffiles++;
            element=element->nextFile;
        }
        float fragmentierung = (unsigned int)(1.0-(verbblock) / (belegtebloecke-numberoffiles))* 100.0f;
        printf("\n-- Fragmention --\n");
        printf("belegt Blocks of partitation: %.2f (%.2f %%) \n", belegtebloecke, (belegtebloecke * 100 / pInode->BlockCount));
        printf("frei Blocks of partitation: %.2f (%.2f %%)\n",verbblock, (verbblock  /( pInode->BlockCount))* 100);

         printf("fragmentierung : %.2f %%",fragmentierung);
        if(fragmentierung>=0)
            return fragmentierung;
        return 0;
    }
    return 0;
}
void fileINODE(struct IPartition* pinode){
    /**
     * @see fileINODE()
      * @details alle Datei in Partitation INODE anzeigen
      * @param  pinode Zeiger auf INODE Partitation
      */
    printf("\n");
    struct InodeFile* element=pinode->Files;
    while(element!=NULL)
    {
        printf("%s:\\",pinode->NameIPart);
        printf("%s \n",element->name);
        element=element->nextFile;
    }

}
void defragIpartition(struct IPartition* pInode)
{
    /**
     * @see defragIpartition()
      * @details es wird die  Bloecke von  jedem einzelnen Datei  gruppiert,dass sie moeglichst zusammenhaengend auf der Platte liegen.
      * @param  pInode INODE Partition
      */
    for( int i = 0; i < pInode->BlockCount-1; i++)
    {
        for(int j = 0; j < pInode->BlockCount-i-1; j++)
        {
            if(pInode->blocks[j]->Data < pInode->blocks[j+1]->Data)
            {
               struct  InodeBlock* node = pInode->blocks[j];
                pInode->blocks[j] = pInode->blocks[j+1];
                pInode->blocks[j+1] = node;
            }
        }
    }

    for(int i = 0;i < pInode->BlockCount;i++)
    {
        if(pInode->blocks[i] == NULL) break;
        pInode->blocks[i]->index = i;
    }

  printf("Erfolgreich Defragmentiert!");

}

