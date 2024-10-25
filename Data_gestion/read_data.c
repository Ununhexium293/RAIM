void read_database(){
    FILE * fread;
    fread = fopen("./Data/database.txt","r");
    if(fread==NULL){
        printf("Faut remplir\n");
        return;
    }

    /*Je declare les valeur importante a fscanf*/
    int id;
    int ing;
    int quant;
    char virg;
    char pointvirgule;
    int i;

    for(i=0;i<MAX_RECETTES;i++){
    

        /*Recupere l'ID de recette et le stock dans le tableau pour que ça soit plus rapide par la suite (btw jsp pk mais il est rapid a l'execution le code ajd)*/
        fscanf(fread,"id=%d",&id);
        ListeRec[id-1].id = id;
        printf("\n%d\n",id);

        /*Je scanne " / ing=[" pour m'en debarassey*/
        fscanf(fread," / ing=[");


        /*Boucle pour recuperer les couple ingredient*/
        int j = 0;
        while(j<MAX_INGREDIENTS){

            /* Je fscanf les valeur du couple dans les parenthese et ce qui suit la parenthese*/
            fscanf(fread,"(%d:%d)%c",&ing,&quant,&virg);
            printf("(%d : %d) %c|",ing,quant,virg);
            /*J'assigne a la liste d'Ingredient de ma struc recette les valeurs*/
            ListeRec[id-1].liste[j] = (Ingredient){
                ing,
                quant
            };

            /*Fin du tableau entre crocher => break*/
            if(virg == ']'){
                ListeRec[id-1].nb_ing = j+1;
                break;
            }
            j++;
        }

        fscanf(fread,"%c\n",&pointvirgule);

        /*Je break si la derniere ligne n'est pas un ; c'est temporaire je sais pas reconnaitre une fin de fichier en C dcp je vais le faire
        automatiquement a l'ecriture etc*/
        if(feof(fread)!=0){
            break;
        }
        printf("[[[[%d--%d]]]]",NOMBRE_RECETTE,i);
    }
    fclose(fread);
    NOMBRE_RECETTE = i+1;
}

