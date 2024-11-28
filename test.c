#include <stdlib.h>
#include <stdio.h>


void strlower(char * str){
    int nb_lettre =0;
    int i = 0;
    while(str[i] != '\0'){
        
        if(str[i]!= (-61)){
            nb_lettre++;
        }
        i++;
        
    }
    
    
    int decalage = 0;
    i=0;
    for(i = 0; i<nb_lettre;i++){
        if((str[i+decalage]>='A') && (str[i+decalage]<='Z')){
            str[i] = str[i+decalage] + 'a' - 'A';
            continue;
        }else
        if(str[i+decalage]==-61){
            
            decalage++;
            if(((str[i+decalage] >= -96) && (str[i+decalage]<=-90)) || ((str[i+decalage] >= -128) && (str[i+decalage]<=-123))){
                str[i] = 'a';
                continue;
            }
            if(((str[i+decalage] >= -88) && (str[i+decalage]<=-85)) || ((str[i+decalage] >= -120) && (str[i+decalage]<= -117))){
                str[i] = 'e';
                continue;
            }
            if(((str[i+decalage] >= -84) && (str[i+decalage]<=-81)) || ((str[i+decalage] >= -116) && (str[i+decalage]<= -113))){
                str[i] = 'i';
                continue;
            }
            if(((str[i+decalage] >= -71) && (str[i+decalage]<=-68)) || ((str[i+decalage] >= -103) && (str[i+decalage]<= -100))){
                str[i] = 'u';
                continue;
            }
            if(((str[i+decalage] >= -78) && (str[i+decalage]<=-74)) || ((str[i+decalage] >= -110) && (str[i+decalage]<= -106)) || str[i+decalage] == -72 || str[i+decalage] == -104){
                str[i] = 'o';
                continue;
            }
            if(((str[i+decalage] == -67) || (str[i+decalage]==-65) || (str[i+decalage] == -99) || (str[i+decalage]== -59))){
                str[i] = 'y';
                continue;
            }
            if((str[i+decalage] == -89) || (str[i+decalage] == -121)){
                str[i] = 'c';
                continue;
            }
            if((str[i+decalage]==-79) || (str[i+decalage] ==-111)){
                str[i] = 'n';
                continue;
            }
            if((str[i+decalage]==-80) || (str[i+decalage] ==-121)){
                str[i] = 'd';
                continue;
            }
        }
        str[i] = str[i+decalage];
        
    }
    str[nb_lettre] = '\0';

    return;
}



int main() {
    char * printstr = "àèìòùÀÈÌÒÙ áéíóú    ýÁÉÍÓÚ    Ý âêîôûÂÊÎÔÛ ãñõÃÑÕ äëïöü    ÿÄËÏÖÜ     åÅ çÇ ð øØ ";
    char * changement = (char*)malloc(146*sizeof(char));

    int i = 0;
    while(printstr[i]!='\0'){
        changement[i] = printstr[i];
        if(printstr[i] == -61){
            i++;
            continue;
        }if(printstr[i] == ' '){
            printf(" ");
            i++;
            continue;
        }
        printf("%d",printstr[i]);
        i++;
    }
    printf("  \n");
    printf("%c,%c",-73,-105);
    i=0;
    printf("\n%s\n",changement);
    strlower(changement);
    while(changement[i]!=0){
        printf("%c",changement[i]);
        i++;
    }
    return 0;
}