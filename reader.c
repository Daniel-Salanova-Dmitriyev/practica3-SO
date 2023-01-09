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

int main(int argc, char *argv[]){    
    struct my_stack *stack;
    if(argv[1]){ //Si se ha escrito un nombre de fichero
        stack = my_stack_read(argv[1]);
        if(stack){ //Si la pila no esta vacía
            if(my_stack_len(stack) >= NUM_THREADS){ //Si el tamaño es igual o superior al de hilos
                int size = my_stack_len(stack);//Vemos el tamaño del fichero            
                printf("Stack length: %i\n", size);
                int *data;                       
                int max = INT_MIN;//Inicializamos el máximo
                int min = INT_MAX;//Inicializamos el mínimo
                int sum = 0;
                for(int i = 0; i<NUM_THREADS;i++){
                    data = my_stack_pop(stack);
                    printf("%i\n", *data);
                    if(*data < min){
                        min = *data;
                    }
                    if(*data > max){
                        max = *data;
                    }
                    sum += *data;

                }
                printf("Items: %i Sum: %i Min: %i Max: %i Average: %i\n", size, sum, min, max, sum/NUM_THREADS);  
                
            }else{
                printf("No exists enough elements, stack_length < number of threads \n");
                return EXIT_FAILURE;
            }
        }else{ //Si no existe pila
            printf("Couldn't open stack file \n");
            return EXIT_FAILURE;
        }

        my_stack_purge(stack); //Eliminamos la pila
        return EXIT_SUCCESS;
    }else{
        perror("USAGE ./reader stack_file \n");
        return EXIT_FAILURE;
    }

}



