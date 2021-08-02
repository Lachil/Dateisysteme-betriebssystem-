

#include<unistd.h>
#include"dateiSchreiben.h"

void dateiSchreiben(){

    FILE *datei;
    char *ch[30], file_name[10];
    chdir("D:\\");
    system("dir");
    printf("welche Detei  in CD/DVD wollen sie verändern :");
     scanf("%s",file_name);
     datei = fopen(file_name, "w");// read mode
     if (datei == NULL)

      {

        printf("Fehler beim oeffnen der Datei.");

      }

       scanf("%s",ch);
      fprintf (datei, "%s", ch);

      fclose (datei);


}
