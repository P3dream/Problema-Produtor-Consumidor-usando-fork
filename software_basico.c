    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>

    int main()
    {
        FILE * File;
        FILE * FBlock;
        int s1,s2;
        int num;
        int vetor[101];
        char filename[] = "buffer.txt";
        char filename2[] = "buffer.txt.lock";
        int i = 0;
        int valor;
        int retorno;
        int retorno2;
        int pid = fork();

        if(pid==0){
            //produtor (filho, pid 0)
            while(1){
                while(FBlock){

                    s1 = 1 + rand() % 2;
                    sleep(s1);

                }

                FBlock = fopen ("buffer.txt.lock","w");
                fclose(FBlock);

                File = fopen ("buffer.txt","a");

                fprintf(File,"%d\n",rand()%99);
                fprintf(File,"%d\n",rand()%99);
                fprintf(File,"%d\n",rand()%99);

                fclose(File);

                int retorno = remove(filename2);

                if(retorno==-1){
                    printf("Problema de permissao");
                }// se for 0 o retorno, conseguiu deletar o arquivo Fblock.
            }

        }
        else{
            //consumidor (pai, pid do filho)
            while(1){
                while(FBlock){

                    s2 = 1 + rand() % 2;
                    sleep(s2);

                }
                FBlock = fopen ("buffer.txt.lock","w");
                fclose(FBlock);

                File = fopen ("buffer.txt","r");
                if(!File){
                    printf("Nao foi possivel abrir o arquivo buffer.txt\n");
                }
                if(fscanf(File, "%d", &valor) == 0){

                    retorno2 = remove(filename2);
                    s2 = 1 + rand() % 2;
                    sleep(s2);
                    while(FBlock){
                        s2 = 1 + rand() % 2;
                        sleep(s2);
                    }
                }
                while(fscanf(File, "%d", &valor) == 1){
                    vetor[i]=valor;
                    i=(i%99)+1;
                }
                fclose(File);

                File = fopen ("buffer.txt","w");
                printf("%d",vetor[i-1]);
                printf("\n");

                for(int j = 0; j < i-1; j++){
                    fprintf(File,"%d\n",vetor[j]);
                    printf("vetor na posicao j:%d  = %d valor de i %d\n",j,vetor[j],i);
                }

                fclose(File);

                retorno2 = remove(filename2);

                if(retorno==-1){
                    printf("Problema de permissao");
                }// se for 0 o retorno, conseguiu deletar o arquivo Fblock.
            }
        }
        return 0;
    }
