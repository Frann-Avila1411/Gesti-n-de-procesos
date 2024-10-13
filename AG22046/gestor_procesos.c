#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

//AG22046- Franklin Giovanny Avila González
//Función para crear un nuevo proceso
void crear_proceso() {
    pid_t pid = fork();  // Crea un nuevo proceso hijo

    if (pid < 0) {
        perror("Error al crear el proceso"); //Error en la creación del proceso
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // Proceso hijo ejecuta el comando "sleep 10"
        execlp("sleep", "sleep", "10", NULL);
        perror("Error en execlp"); // si execlp falla muestra un error
        exit(EXIT_FAILURE);
    } else {
    //proceso padre que imprime el PID del proceso hijo creado
        printf("Proceso hijo creado con PID: %d\n", pid);
    }
}

// Funcion para eliminar un proceso dado su PID
void eliminar_proceso(pid_t pid) {
//Envia la señal SIGKILL al proceso especificado para terminarlo
    if (kill(pid, SIGKILL) == 0) {
        printf("Proceso con PID %d eliminado\n", pid);
    } else {
    // si falla, muestra un mensaje de error
        perror("Error al eliminar el proceso");
    }
}

//Funcion para monitorear los procesos en ejecucion
void monitorear_procesos() {
    printf("Procesos en ejecución:\n");
    system("ps -e");
}

int main() {
    int opcion; 
    pid_t pid;

    while (1) {
    //menu principal del gestor de procesos
        printf("\nGestor de Procesos:\n");
        printf("1. Crear Proceso\n");
        printf("2. Eliminar Proceso\n");
        printf("3. Monitorear Procesos\n");
        printf("4. Salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
            //llamada a la funcion para crear un nuevo proceso
                crear_proceso();
                break;
            case 2:
                printf("Ingrese el PID del proceso a eliminar: ");
                scanf("%d", &pid);
                //llama a la funcion para eliminar un proceso especificado
                eliminar_proceso(pid);
                break;
            case 3:
            //llamada a la funcion para mostrar los procesos en ejecucion
                monitorear_procesos();
                break;
            case 4:
            //Fin del programa
                printf("Saliendo...\n");
                exit(0);
            default:
            //manejo del caso en el que se introduzca una opción invalida
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }

    return 0;
}
