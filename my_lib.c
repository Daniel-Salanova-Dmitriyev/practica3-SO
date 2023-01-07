#include "my_lib.h"
#include <assert.h>
//Creadores
//Arkadiy Kosyuk
//Alexander Cordero Gómez
//Daniel Salanova Dmitriyev

/**
 * Función que cuenta cuanta longitud tiene una cadena
 * INPUT -> cadena de caracteres
 * OUTPUT -> longitud de la cadena
*/
size_t my_strlen(const char *str) {
   size_t len = 0;
   int i = 0;
 
   while (str[i]) { // o while (str[i]!='\0')
           i++;
           len++;
   }
   return len;
}

/**
 * FUnción que compara 2 cadenas y en caso de encontrar un caracter diferente devuelve
 * la diferencia entre los 2
 * INPUT -> 2 cadenas de texto
 * OUTPUT -> 0 (si son iguales) o la diferencia entre las 2 letras
*/
int my_strcmp(const char *str1, const char *str2){
    int cont = 0; //Contabiliza cuantas coinciden
    int i = 0; //Utilizado para recorrer a la vez str1 y str2
    for(; str1[i] && str2[i]; i++){
        if(str1[i] - str2[i] == 0){
            cont++;
        }else{
            return str1[i] - str2[i];
        }
    }
    //Si salimos puede ser porque en uno no hay datos o porque son iguales
    if(str1[i] && !str2[i]){ //En el caso de que str1 tenga los primeros caracteres iguales y sea mas grande 
        return str1[i];
    }else if (!str1[i] && str2[i]){ //En el caso de que str2 tenga los primeros caracteres iguales y sea mas grande 
        return str2[i];
    }
    
    // En el caso de que sean iguales
    return 0;

}


/**
 * Función que se encarga de copiar el contenido de una cadena en otra
 * INPUT -> 1 posición de memoria y 1 cadena de texto
 * OUTPUT -> puntero a la posicion de memoria (dest)
*/
char *my_strcpy(char *dest, const char *src){
	char* str = dest;
	while ((*dest++ = *src++)!= '\0');
	return str;
}


/**
 * Función que copia de n caracteres dentro de dest
 * INPUT -> posicion de memoria, cadena de caracteres y número que indica cuantos son
 * OUTPUT -> puntero a la posición de memoria
*/
char *my_strncpy(char *dest, const char *src, size_t n){
    char *cp = dest;
	while (n && (*dest++ = *src++))	{
		n--;
	}
	if (n>0){
		while (--n)	{
			*dest++ = '\0';
		}
	}
	return cp;
}

/**
 * Función que añade una cadena al final de otra
 * INPUT -> 2 cadenas de texto
 * OUTPUT -> devuelve el puntero de la cadena dest 
*/
char *my_strcat(char *dest, const char *src){
    int posNull = 0;
    while(dest[posNull]){ //Hayamos el caracter \0
        posNull++;
    }
    //Ahora sabemos donde esta la posNull, procedemos ha añadir caracteres
    int i = 0;
    for(; src[i];i++ ){
        dest[posNull++] = src[i];
   
    }
    //Colocamos el final de cadena
    dest[posNull] = '\0';
    return dest;
}

/**
 * Función que busca una letra dentro de la cadena
 * INPUT -> cadena y letra a buscar
 * OUTPUT -> puntero donde se encuentra la ocurrecia o -1 en caso de no hayarse
*/
char *my_strchr(const char *str, int c){
	assert(str != NULL);//comprobamos que no este vacio
	while (*str)// mientras *str sea distinto de \0 seguira buscando
	{
		if (*str == c) //si la letra de la dirección es igual a la que buscamos
			return (char *)str;//se devuelve la dirección de la letra
		else
			str++;//si no es la letra que buscamos pasamos a la siguiente
	}
	return NULL;//en caso de que no haya la letra devolvemos un valor nulo
}

/**
 * Inicializamos la pila
 * INPUT -> tamaño de los datos
 * OUTPUT -> puntero a la pila
*/
struct my_stack *my_stack_init(int size) {
    struct my_stack *pila=malloc(sizeof(struct my_stack)); //Guardamos espacio en memoria para la pila
    if(!pila){
        perror("Error: ");
        return NULL;
    }
    
    pila->size=size;    //Esto indicará el tamaño de los datos a colocar
    pila->top=NULL;     //Como no hay nada apunta a NULL
    return pila;
}

/**
 * Función con la que podremos añadir datos a la pila
 * INPUT -> puntero a la pila y dato a añadir
 * OUTPUT -> -1 si hay error o 0 si se hizo bien la operacion
*/
int my_stack_push(struct my_stack *stack,void *data) {
    if(stack == NULL){ //Si el stack no ha sido inicializado
        perror("Stack no inicializado");
        return -1;
    }

    if(stack->size <= 0){
        perror("Stack no inicializado o tamaño de datos incorrectos");
        return -1;
    }

    //Creamos el elemento a añadir
    struct my_stack_node *nuevo;
    nuevo = malloc(sizeof(struct my_stack_node)); //Guardamos espacio en memoria para el elemento

    if(!nuevo){ //Si no se le ha podido asignar memoria o ha fallado la asignacion
        perror("Error: ");
        return -1;
    }

    struct my_stack_node *antiguoTop = stack->top;
    
    //Asignamos el dato y el siguiente nodo    
    nuevo->data = data;
    nuevo->next = antiguoTop;

    //Actualizamos el top
    stack->top = nuevo;
    return 0;
    
}

/**
 * Función con el que eliminamos el nodo señalado por el top de la pila
 * INPUT -> puntero a la pila
 * OUTPUT -> puntero al dato eliminado
*/
void *my_stack_pop (struct my_stack *stack) {
    if(stack->top == NULL){ //En el caso de que este vacio
        return NULL;
    }else{
        //Nodo a eliminar
        struct my_stack_node *nodo = stack->top;

        //Recogemos el dato
        void *dato = nodo->data;

        //Actualizamos el puntero de top
        stack->top = nodo->next;

        //Liberamos la memoria del top anterior
        free(nodo);

        return dato;
    }
    
}


/**
 * Función que recorre la pila y cuenta los elementos que contiene.
 * INPUT -> pila
 * OUTPUT -> longitud de la pila
*/
int my_stack_len(struct my_stack *stack) {
    int contador = 0; //Contador

    struct my_stack_node *nodo = stack->top; //Primer dato
    while(nodo != NULL){
        //Actualizamos el contador y el siguiente nodo
        contador++;
        nodo = nodo->next;
    }

    return contador;
    
}

/**
 * Devolvemos la cantidad de memoria liberada
 * INPUT -> pila
 * OUTPUT -> cantidad de memoria liberada
*/
int my_stack_purge (struct my_stack *stack) {
    int liberado = stack->size; //Memoria liberada
    int numero = 0; //Cuenta los nodos que hay
    struct my_stack_node *aux; //Nuestro indice

    while(stack->top){ //Mientras no este vacío
        aux = stack->top;
        stack->top = stack->top->next;
        free(aux->data); //Liberamos los daots
        free(aux); //Liberamos el nodo
        numero++;        
    }
    liberado *= numero; //Cuanto han ocupado los datos
    liberado += numero * sizeof(struct my_stack_node) + sizeof(struct my_stack);
    free(stack); //Liberamos la pila
    return liberado;
}



/**
 * Función que se encarga de escribir el contenido de la pila dentro de un fichero dado
 * INPUT -> pila y nombre del fichero
 * OUTPUT -> -1 si hay error, y sino la cantidad de datos escritos
*/
int my_stack_write (struct my_stack *stack, char *filename){
    
    struct my_stack *aux_stack;   //Nuestra pila auxiliar
    aux_stack = my_stack_init(stack->size); //Inicializamos la pila
    struct my_stack_node *aux_node = stack->top;

    //Colocamos datos dentro de la pila auxiliar
    while(aux_node){
        my_stack_push(aux_stack, aux_node->data);
        aux_node = aux_node->next;
    }

    //Abrimo el fichero si existe, o lo creamos en cualquier caso
    int fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    if(fd == -1){ //En caso de que haya ocurrido un error a la hora de abrir el fichero, soltamos un error
        perror("Error: ");
        return -1;
    }

    //Escribimos la cantidad de bytes que ocupan nuestros datos
    int fichero = write(fd, &(aux_stack->size), sizeof(int));
    if(fichero == -1){
        perror("Error: ");
        close(fd);
        return -1;
    }

    //Acumulador que indicará cuantos elementos hemosa almacenado
    int contador = 0;
    aux_node = aux_stack->top;
    while(aux_node){
        fichero = write(fd, aux_node->data,aux_stack->size );
    
        //En caso de error de escritura devolvemos -1
        if(fichero == -1){
            perror("Error: ");
            close(fd);
            return -1;
        }

        aux_node = aux_node->next;
        contador++;
    }

    //Cerramos fichero
    fichero = close(fd);
    if(fichero == -1){
        perror("Error: ");
        return -1;
    }

    return contador;
}


/**
 * Función que lee un stack del fichero filename y lo devuelve
 * INPUT -> fichero
 * OUTPUT -> puntero a la pila leida
 * */ 
struct my_stack *my_stack_read(char *filename) {
    struct my_stack *stack; //Nuestra pila
    int pila_size = 0;  //Tamaño de la pila
    int fd = open(filename, O_RDONLY); //Abrimos el fichero
    if(fd == -1){ //En caso de error
        //perror("Error: ");
        return NULL;
    }

    int fichero = read(fd, &(pila_size), sizeof(int)); //Guardamos el tamaño de los datos

    if(fichero == -1){ //En caso de error
        perror("Error: ");
        close(fd);
        return NULL;
    }

    stack = my_stack_init(pila_size); //Inicializamos la pila

    void *data;
    data = malloc(stack->size);
    if(!data){
        perror("Error: ");
        return NULL;
    }

    //Leemos el primer dato
    fichero = read(fd, data, stack->size);

    //En caso de error, deshacemos todo y devolvemos NULL
    if(fichero == -1){
            close(fd);
            free(data);
            my_stack_purge(stack);
            perror("Error: ");
            return NULL;
    }

    //Mientras no hayamos llegado al final del fichero
    while(fichero >0){
        my_stack_push(stack,data);

        data = malloc(stack->size);

        fichero = read(fd, data, stack->size);
        if(fichero == -1 || !data){
            close(fd);
            free(data);
            my_stack_purge(stack);
            perror("Error: ");
            return NULL;
        }
    }

    free(data);
  
    fichero = close(fd); //Cerramos el fichero

    if(fichero == -1){ //En caso de error
        perror("Error: ");
        my_stack_purge(stack);
        return NULL;
    }
    return stack;

}