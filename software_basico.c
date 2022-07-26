    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
	#include <time.h>

    int main()
    {
        FILE * File;
        FILE * FBlock;
        int s1,s2;
        int vetor[1000];
        char filename[] = "buffer.txt";
        char filename2[] = "buffer.txt.lock";
        int i = 0;
        int valor;
        int var;
        int pid = fork();

        srand(time(NULL));

        if(pid==0){
            //produtor (filho, pid 0)
            while(1){
                while(FBlock = fopen("buffer.txt.lock","r")){ // verificamos se o arquivo do txt.lock existe, se existir significa que o consumidor esta funcionando no momento.
                	usleep(1000); // e entao esperamos.
                }
                FBlock = fopen ("buffer.txt.lock","w"); // abrimos o arquivo do lock no modo write so para ele existir
                fclose(FBlock); // e ja fechamos, pq nao vamos usa-lo agora.

                File = fopen ("buffer.txt","a"); // abrimos o buffer txt no modo apend para adicionar o valor gerado no final

                var = rand()%99; // geramos um numero aleatorio
                fprintf(File,"%d\n",var); // printamos o numero aleatorio no arquivo ( produzido )
                printf("[Produtor]:%d\n",var);// mostramos o numero produzido

                fclose(File); // fechamos o arquivo
                remove("buffer.txt.lock"); // removemos o lock

                s1 = 1 + rand() % 2; //  geramos um numero aleatorio entre 1 e 3
                sleep(s1);// system dorme esse tempo
            }

        }
        else{
            //consumidor (pai, pid do filho)
            while(1){
                while(FBlock = fopen("buffer.txt.lock","r")){ // verificamos se o lock existe, se existir esperamos.
                	usleep(1000);
                }

                FBlock = fopen ("buffer.txt.lock","w");// geramos o lock, e o fechamos em seguida.
                fclose(FBlock);

                File = fopen ("buffer.txt","r");//abrimos o buffer no modo de leitura
                if(!File){ // se nao conseguir abrir o arquivo e indicado um erro
                    printf("Nao foi possivel abrir o arquivo buffer.txt\n");
                }

               	i=0; // zera o contador para o vetor sempre comecar na posicao 0

                while(fscanf(File, "%d", &valor) != EOF){ // enquanto ele conseguir ler valores
                    vetor[i]=valor; // passa eles para o vetor
                    //printf("vetor[%d]= %d\n",i,vetor[i]);
                    i = i + 1; // incrementa o i
                }

                fclose(File); // fechamos o arquivo

                File = fopen ("buffer.txt","w"); // abrimos ele em modo de escrita

                printf("[Consumidor]:%d\n",vetor[0]); // printamos o primeiro valor do vetor pq ele sera consumido.


                for(int j = 1; j < i; j++){
                    fprintf(File,"%d\n",vetor[j]); // printamos no arquivo os outros valores que nao foram consumidos.
                }

                fclose(File); // fechamos o arquivo

                remove(filename2); // excluimos o lock


                s2 = 1 + rand() % 2; // geramos um numero aleatorio entre 1 e 3
                sleep(s2); // system dorme esse tempo aleatorio gerado.

            }
        }
        return 0;
    }
