/**
  * @brief Projekt 3, Dateisysteme
  * @details Innerhalb dieses Projekts soll ein Framework zur Manipulation von Dateisys-tems implementiert werden
  * @author Lhabib Lachil
  * @version 1.0
  * @date 31.08.2020  */

#include"file-ls.h"
#include"DisckEmu.h"
#include"CDroomEmulator.h"
unsigned int File_MAX_CD=0;
unsigned int File_Max_FAT=0;




int main()
{/**
    * @brief Hauptfunktion fuer projekt  Dateisystem   zur Manipulation
    */
    unsigned int a,b=0,discksize=8192,Partsize;
    unsigned long filesizeFat,blockSize,filesizeCd;
      char nameFileFat[10],fileloschen[10], nameFileCd[10];
    struct HDD* hdd=(struct HDD*)malloc(sizeof (struct HDD));//wir erstellen hier ein hdd
    struct CDFile **filesCd=(struct CDFile**)malloc(sizeof (struct CDFile*));//wir erstellen hier Zeiger auf Tabelle
    struct CD* cd=(struct CD*)malloc(sizeof (struct CD));//wir erstellen hier CD struct
                system("color 6");
                printf("            Projekt 3 : Dateisytem. \n");
                printf("\n====================================================");

          do{//kann man ein nummer von 1 bis 18 angebn ,jede nummer mach Operation in DISCK

                   printf("\n====================================================\n");
                   printf("1) eine neue HDD  erstellen.\n");
                   printf("2) Partitatiun fuer  das Erstellen  von Fat   .\n");
                   printf("3) Partitatiun fuer das  erstellen von INODE .\n");
                   printf("4) eine FileFat  erstellen.\n");
                   printf("5) eine FileInode  erstellen\n");
                   printf("6) den frei Speicher auf einer PartitatiunFAT zurueckgeben\n");
                   printf("7) Fragmentation von Datei FAT .\n");
                   printf("8) Defragmentation von Datei FAT \n");
                   printf("9) DateiFat loeschen \n");
                   printf("10) den frei Speicher auf einer  PartitatiunInode zurueckgeben\n");
                   printf("11) Fragmentation von Datei INODE .\n");
                   printf("12) Defragmentation von Datei INODE \n");
                   printf("13) Inhalt der FATPartitation anzeigen\n");
                   printf("14)Inhalt der INODEPartitation anzeigen \n");
                   printf("15)ein FileCD erstellen\n ");
                   printf("16)ein CDROOM erstellen\n");
                   printf("17) Inhalt der CDROOM anzeigen \n");
                   printf("18) Dateivon CD nach FAT partitionen kopieren");
                   printf("exit");
                   printf("\n====================================================\n");
                   printf("Nummer angeben :");
                        scanf("%d",&a);
                        switch(a){
                        case 1:
                            printf("Groesse der Festplatte angeben :");
                            scanf("%d",&discksize);
                            hdd=createHDD(discksize);
                            break;
                        case 2:
                            do{printf("grosses der FestPalt angeben :");
                            scanf("%d",&Partsize);
                            if(Partsize>=discksize)printf(" der Partitation ist zu grosse .\n");
                            }while(Partsize>=discksize);
                            printf("grosse der Block angeben :");
                            scanf("%ld",&blockSize);
                          createPartition(hdd, "FAT",0, Partsize, blockSize);
                            break;
                        case 3:
                            do{printf("grosses der FestPalt angeben :");
                            scanf("%d",&Partsize);
                            if(Partsize>=discksize)printf(" der Partitation ist zu grosse .\n");
                            }while(Partsize>=discksize);
                            printf("grosse der Block angeben :");
                            scanf("%ld",&blockSize);
                        createPartition(hdd, "INODE",1, Partsize, blockSize);
                            break;
                        case 4:
                            printf("Name der File angeben :");
                            scanf("%s",&nameFileFat);
                            printf("Datei groesse angeben :");
                             scanf("%ld",&filesizeFat);
                           createFileFAT(hdd->mbr->partitionTable[0]->fat, filesizeFat,nameFileFat) ;
                            File_Max_FAT++;
                            break;
                        case 5:
                            printf("Name der File angeben :");
                            scanf("%s",&nameFileFat);
                            printf("Datei groesse angeben :");
                             scanf("%ld",&filesizeFat);
                            createINODEfile(hdd->mbr->partitionTable[1]->inode,filesizeFat,nameFileFat);
                            break;
                        case 6:
                            printf("es gibt noch %d frei Blocks :",getFreeDiskSpace(hdd->mbr->partitionTable[0]->fat));
                            break;
                        case 7:
                            getFragmentation(hdd->mbr->partitionTable[0]->fat);
                            break;
                        case 8:
                            defragDisk(hdd->mbr->partitionTable[0]->fat);
                            break;
                        case 9:
                            printf("Name der Datei löschen :");
                            scanf("%s",&fileloschen);
                            deleteFileFat(hdd->mbr->partitionTable[0]->fat,fileloschen);
                            File_Max_FAT--;
                            break;
                        case 10:
                            printf("%d",freediskspaceInode(hdd->mbr->partitionTable[1]->inode));
                            break;
                        case 11:
                            fragmentationINODE(hdd->mbr->partitionTable[1]->inode);
                            break;
                        case 12 :
                            defragIpartition(hdd->mbr->partitionTable[1]->inode);
                        case 13:

                            sfs_ls(hdd->mbr->partitionTable[0]->fat,File_Max_FAT);
                            ;
                            break;
                        case 14:
                            fileINODE(hdd->mbr->partitionTable[1]->inode);
                            break ;
                        case 15:

                            printf("Name der File angeben :");
                            scanf("%s",&nameFileCd);
                            printf("Datei groesse angeben :");
                             scanf("%ld",&filesizeCd);
                            filesCd[File_MAX_CD]=CDFileerstellt(nameFileCd, filesizeCd);
                            File_MAX_CD++;
                            break ;
                        case 16:
                            cd=createCD("CD",17408, 512, filesCd,File_MAX_CD);
                            break;
                        case 17:
                            ls_cd(cd);
                            break;
                        case 18:
                            CD_FAT(hdd->mbr->partitionTable[0]->fat,cd);
                        case 19:
                            return 0;
                            break;

                        }}while(1);}


