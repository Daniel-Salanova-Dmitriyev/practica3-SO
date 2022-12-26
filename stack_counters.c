//Creadores
//Arkadiy Kosyuk
//Alexander Cordero Gómez
//Daniel Salanova Dmitriyev

#include "my_lib.h"
#include <pthread.h>
#define NUM_THREADS 10
#define NUM_ITER 1000000

pthread_t arrayHilos[10];
struct my_stack *stack;
pthread_mutex_t semaforo;

/**
 * Función que sumará 1 sobre la pila 
*/

struct my_data {
    int val;
};

void *worker(void *ptr){
    for(int i = 0; i<NUM_ITER;i++){
        
        pthread_mutex_lock(ptr);
        struct my_data *dato = my_stack_pop(stack);
        pthread_mutex_unlock(ptr);
        
        dato->val += 1; // Incrementamos

        pthread_mutex_lock(ptr);
        my_stack_push(stack,dato);
        pthread_mutex_unlock(ptr);
        

        printf("Valor de n: %i\n", dato->val);
        pthread_exit(NULL);
    }
}


int main(int argc, char *argv[]){

    
    if(argv[1]){ //Le pasamos 1 argumento
        int fd = open(argv[1], O_RDONLY); //Fichero a abrir
        if(fd == -1){ //Fichero no existe
            close(fd); //Cerramos el fichero
            struct my_stack *stack = my_stack_init(sizeof(struct my_data)); //Inicializamos el stack
            for(int i = 0; i<NUM_THREADS;i++){
                struct my_data *data = malloc(sizeof(struct my_data));
                data->val = 0;
                my_stack_push(stack,data);
            }

        }else{ //Fichero existe
            close(fd);
            stack = my_stack_read(argv[1]);
            int size = my_stack_len(stack);
            if(size < 10){ //En el caso de que se pongan menos elementos que hilos, añadimos datos 
                int add = 10 -size;
                for(int i = add;add<NUM_THREADS;i++ ){
                   struct my_data *data = malloc(sizeof(struct my_data));
                    data->val = 0;
                    my_stack_push(stack, data);
                    add++;
                }
            }
        }

        //En este punto tenemos ya la pila o creada o con datos añadidos

        //Creamos los hilos
        for(int i = 0; i<10;i++){
            pthread_t thread_id;
            arrayHilos[i] = thread_id;
            pthread_create(thread_id,NULL, worker, NULL);
        }

        //MAL!!!! CAMBIAR!!
        pthread_mutex_init(&semaforo,NULL); 




    }else{ //No hay argumentos
        perror("No existe fichero con pila!!\n");
        return EXIT_FAILURE;
    }

}


