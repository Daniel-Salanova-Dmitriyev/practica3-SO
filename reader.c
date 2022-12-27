//Creadores
//Arkadiy Kosyuk
//Alexander Cordero Gómez
//Daniel Salanova Dmitriyev

#include "my_lib.h"
#include <limits.h>

#define NUM_THREADS 10
struct my_stack *stack;
struct my_data {
    int val;
};

int main(char *argv[]){    
    if(argv[1]){ //Le pasamos 1 argumento
        int fd = open(argv[1], O_RDONLY); //Fichero a abrir
        if(fd == -1){ //Fichero no existe
            close(fd); //Cerramos el fichero
            perror("No existe el fichero!!\n");
            return EXIT_FAILURE;
        }else{ //Fichero existe
            close(fd);
            stack = my_stack_read(argv[1]);            
            int size = my_stack_len(stack);//Vemos el tamoño del fichero            
            printf("Stack length: %i\n", size);
            struct my_data *data;
            int max = INT_MIN;//Inicializamos el máximo
            int min = INT_MAX;//Inicializamos el mínimo
            int sum = 0;

            for(int i = 0;i<NUM_THREADS && i<size;i++ ){
                data = malloc(sizeof(struct my_data));
                data->val = argv[i];
                printf("%i\n", data->val); 
                if (max<data->val){//Tomamos el máximo
                    max=data->val;
                }
                if (min>data->val){//Tomamos el mínimo
                    min=data->val;
                }
                sum = sum + data->val;//Sumamos todos los elementos
            }          
            printf("Items: %a Sum: %e Min: %i Max: %o Average: %u\n", data->val, sum, min, max, sum/size);  
        } 
    }else{ //No hay argumentos
        perror("No existe fichero con pila!!\n");
        return EXIT_FAILURE;
    }
}
