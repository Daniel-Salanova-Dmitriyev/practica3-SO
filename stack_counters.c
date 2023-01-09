//Creadores
//Arkadiy Kosyuk
//Alexander Cordero Gómez
//Daniel Salanova Dmitriyev

#include "my_lib.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#define NUM_THREADS 10
#define NUM_ITER 1000000

pthread_t arrayHilos[NUM_THREADS];
struct my_stack *stack;
pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER;
void *z;
void *worker(void *ptr);
void inicializar_pila(char *nombre);
void imprimir_datos_stack(struct my_stack *stack);


/**
 * Función que sumará 1 sobre la pila 
*/

struct my_data {
    int val;
};

/**
    Función que ejecutará cada uno de los hilos, recoge un dato de la pila, le suma 1, y lo inserta dentro 
    de nuevo.
*/
void *worker(void *ptr){
    for(int i = 0; i<NUM_ITER;i++){

        //Recogida del dato
        pthread_mutex_lock(&semaforo);
        int *dato = my_stack_pop(stack);
        pthread_mutex_unlock(&semaforo);
        
        (*dato) += 1; // Incrementamos

        //Incorporacion
        pthread_mutex_lock(&semaforo);
        my_stack_push(stack,dato);
        pthread_mutex_unlock(&semaforo);
       
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){
    if(argv[1]){ //SI existe nombre de pila   
        inicializar_pila(argv[1]);
        

        //En este punto tenemos ya la pila o creada o con datos añadidos 
        
        //Creamos los hilos
        for(int i = 0; i<NUM_THREADS;i++){
            pthread_create(&arrayHilos[i], NULL, worker, NULL);
            printf("%i) Thread %li created \n",i,arrayHilos[i]);
        }

        //void **estatus;//Estado del hilo
        
        //Esperamos a que acaben
        for(int i = 0; i<NUM_THREADS;i++){
            pthread_join(arrayHilos[i],NULL);
        }
        
        //Imprimos todos los datos del stack
        printf("stack content after threads iterations \n");
        imprimir_datos_stack(stack);
        printf("stack length: %i \n", my_stack_len(stack));


        //Escribimos la pila en otro fichero
        my_stack_write(stack,argv[1]);
        printf("Written elements from stack to file: %i \n", my_stack_len(stack));
        
        int data_free = my_stack_purge(stack); //Liberamos todo el espacio reservado de la pila
        printf("Released bytes: %i \n", data_free);
        printf("Bye from main \n");
        pthread_exit(0);        
    }else{ //No hay argumentos
        perror("USAGE: ./stack_counters stack_file \n");
        return EXIT_FAILURE;
    }

}



void inicializar_pila(char *nombre){
    printf("Threads: %i, Iterations: %i \n", NUM_THREADS, NUM_ITER);
    stack = my_stack_read(nombre); //Leemos el fichero
    if(stack){ //En caso de encontrar un fichero
        int longitud = my_stack_len(stack);
        printf("initial stack content: \n");
        imprimir_datos_stack(stack); //Imprimimos los datos actuales del stack
        if(longitud<NUM_THREADS){ //Añadimos datos dentro del stack
            int dif = NUM_THREADS - longitud;
            int *data;
            for(int i = dif; i>0;i--){ //Añadimos datos dentro de la pila
                data = malloc(sizeof(int));
                if(!data){ //Si no hay memoria
                    perror("No hay espacio de memoria! \n");
                }
                *data = 0;
                my_stack_push(stack, data);
            }
            printf("original stack length: %i \n", longitud);
            printf("Number of elements added to initial stack : %i\n", dif);
            printf("stack content for treatment: \n");
            imprimir_datos_stack(stack);
            printf("stack length: %i \n",NUM_THREADS);


        }else{
            printf("stack length: %i \n", longitud);
        }

    }else{ //Pila vacía
        printf("initial stack content: \n");
        stack = my_stack_init(sizeof(int)); //Inicializamos una pila de int
        int *data;
        for(int i = 0; i<NUM_THREADS;i++){//Añadimos datos al stack
            data = malloc(sizeof(int));
                if(!data){ //Si no hay memoria
                    perror("No hay espacio de memoria! \n");
                }
                *data = 0;
                my_stack_push(stack, data);
                printf("0 \n");
        }
        printf("new stack length: %i \n", NUM_THREADS);
    }
}

/**
    Función que imprime todos los datos que contiene la pila pasada por parámetro
*/
void imprimir_datos_stack(struct my_stack *stack){
    struct my_stack_node *nodo = stack->top; //Primer dato
    while(nodo != NULL){
        printf("%d\n", *((int *)nodo->data));    
        nodo = nodo->next; //Pasamos al siguiente nodo
    }

}

