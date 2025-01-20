int filter_str(char * str1, char * str2){
    int len1 = 0;
    int len2 = 0;

    /*VERIFICATION TAILLE DES 2 STRING O(m+n)*/
    while(str1[len1] != '\0'){
        len1++;
    }
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

    return 0;

}


int compare_str(const char * str1, const char * str2){
    /*str1 < str2 ===> -1
    str1 = str2 ===> 0
    str1 > str2 ===> 1*/

    int i = 0;
    while(str1[i]>=str2[i]){
        if(str1[i] == str2[i]){
            if(str1[i] == '\0'){
                return 0;
            }
        }else{
            return 1;
        }
        i++;
    }
    return -1;
}
