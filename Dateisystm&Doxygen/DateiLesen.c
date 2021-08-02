
#include<unistd.h>
#include"DateiLesen.h"




void lesenvoncdrom(){

    FILE *fp;
    char ch, file_name[10];
    chdir("D:\\");
    system("dir");
    printf("welche Detei oder vorzeichen in CD/DVD wollen sie öffnen :");
    //gets(file_name);
    scanf("%s",file_name);
     fp = fopen(file_name, "r");// read mode
     if (fp == NULL)
       {
          perror("Error while opening the file.\n");
          //exit(EXIT_FAILURE);
       }

       printf("The contents of %s file are:\n", file_name);

       while((ch = fgetc(fp)) != EOF)
          printf("%c", ch);

       fclose(fp);


       fclose(fp);
}
