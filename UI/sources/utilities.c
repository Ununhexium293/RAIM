#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../header/struct_passage.h"
#include "../../Data_gestion/header/struct.h"

int log_10(int n){
    int count = 0;

    while (n != 0){
        n /= 10;
        count++;
    }

    count--;

    return count;
}

void lib_str(gpointer data){
    char *str = data;

    free(str);
}


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

int filter_str(char * str1, const char * str2){
    int len1 = 0;
    int len2 = 0;

    /*VERIFICATION TAILLE DES 2 STRING O(m+n)*/
    while(str1[len1] != '\0'){
        len1++;
    }

    if (len1 == 0){
        return 1;
    }else{
        while(str2[len2] != '\0'){
            len2++;
        }

        printf("%d:%d\n",len1,len2);
        printf("%c%c%c",str1[0],str1[1],str1[2]);
        if(len1>len2){
            return 0;
        }

        /*FENETRE GLISSANTE O(n*m)*/
        int i,j;
        for(i = 0;i<len2-len1+1;i++){
            for(j = 0; j<len1 ; j++){
                printf("val : %c:%c\n",str1[j],str2[j+i]);
                if(str1[j]!=str2[j+i]){
                    break;
                }
                if(j == len1-1){
                    return 1;
                }
            }
        }
    }

    return 0;

}