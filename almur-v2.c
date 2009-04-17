#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>//для isdigit()

int main(int argc, char *argv[])
{
    int fd, file=0;
    int i,j,k;
    int count=0;
    
    //Проверяем количество входных данных. Должно быть ./a.out -f filename
    if (argc >= 2)  {
        for ( i=0; i<argc; i++) {
            if ( argv[i][0] == '-' && argv[i][1] == 'f')    {
                file = i+1;
                printf("Hello\n");
            }
         
            else if ( i==(argc-1) && file == 0) {
                printf("Error: Unknown options\n");
                exit(-1);
            }
        } 
        
        if ( ( fd = open(argv[file], O_RDONLY) ) == -1 )  {
            printf("Error: No such file %s.\n", argv[file]);
            exit(-1);
        }
      
        else    {
            printf("Opened!\n");
            
            k = lseek(fd, 0.0, 2);
            printf("Size of file: %d\n", k);
            //Выделяем память под массив-строку
            char *tmpstr = (char*) malloc(sizeof(char)*k);
            printf("String created!\n");

            lseek(fd, 0.0, 0);

            if ( read(fd, tmpstr, k) != -1 )   {
                printf("file->str\n");

                close(fd);

                for ( i=0; i<k; i++ )   {
                    if ( tmpstr[i] != '\n'&& tmpstr[i] != '\t' && tmpstr[i] != '\0' && isdigit(tmpstr[i])!=0 )    {
                        count++;
                    }
                }

                printf("Numbers in file: %d\n", count);
                
                //Выделяем память под массив float, куда будем записывать файлы.
                float *array =  calloc(count, sizeof(float));
                printf("Float array created!\n");

                j = 0;

                for ( i=0; i<k; i++)    {
                    
                    if ( tmpstr[i] != '\n'&& tmpstr[i] != '\t' && tmpstr[i] != '\0' && j<count)    {
                        printf("NUMBER!!!!\n");
                        array[j] = atof(&tmpstr[i]);
                        j++;
                    }
                }
            }

            else    {
                printf("Error: Couldn't read from file %s\n",argv[file]);
                exit(-1);
            }
        }
    }
    
    else    {
        printf("Error\n");
        exit(-1);
    }

    return 0;
}
