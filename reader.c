//Creadores
//Arkadiy Kosyuk
//Alexander Cordero Gómez
//Daniel Salanova Dmitriyev

#include "my_lib.c"
#include <limits.h>

#define NUM_THREADS 10
struct my_stack *stack;
struct my_data {
    int val;
};

int main(int argc, char *argv[]){    
    if(argv[1]){ //Le pasamos 1 argumento
        int fd = open(argv[1], O_RDONLY); //Fichero a abrir
        if(fd == -1){ //Fichero no existe
            close(fd); //Cerramos el fichero
            perror("Couldn't open stack file \n");
            return EXIT_FAILURE;
        }else{ //Fichero existe
            close(fd);
            stack = my_stack_read(argv[1]);            
            int size = my_stack_len(stack);//Vemos el tamoño del fichero            
            printf("Stack length: %i\n", size);
            struct my_data *data = malloc(sizeof(struct my_data));                       
            int max = INT_MIN;//Inicializamos el máximo
            int min = INT_MAX;//Inicializamos el mínimo
            int sum = 0;
            if(size>NUM_THREADS){
                size = NUM_THREADS;
            }
            for(int i = 0;i<size;i++ ){
                data = my_stack_pop(stack);
                printf("%i\n", data->val); 
                if (max<data->val){//Tomamos el máximo
                    max=data->val;
                }
                if (min>data->val){//Tomamos el mínimo
                    min=data->val;
                }
                sum += data->val;//Sumamos todos los elementos 
            }          
            printf("Items: %i Sum: %i Min: %i Max: %i Average: %i\n", size, sum, min, max, sum/size);  
        } 
    }else{ //No hay argumentos
        perror("USAGE ./reader stack_file\n");
        return EXIT_FAILURE;
    }
}
