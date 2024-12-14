#include "sistema.h"
#include <stdio.h>

void mostrarMenu();

int main()
{
    Materia materias[100];
    Estudiante estudiantes[100];
    Curso cursos[100];
    Profesor profesores[100];
    int numMaterias = 0, numEstudiantes = 0, numCursos = 0, numProfesores = 0;

    leerMaterias(materias, &numMaterias);
    leerEstudiantes(estudiantes, &numEstudiantes);
    leerCursos(cursos, &numCursos);
    leerProfesores(profesores, &numProfesores);

    // Prueba de datos

    // Mostrar las materias leídas
    printf("Materias leidas:\n");
    for (int i = 0; i < numMaterias; i++)
    {
        printf("Materia: %s, Codigo: %s, Estado: %s\n", materias[i].nombre, materias[i].codigo, materias[i].estado);
    }

    // Mostrar los estudiantes leídos
    printf("\nEstudiantes leidos:\n");
    for (int i = 0; i < numEstudiantes; i++)
    {
        printf("Estudiante: %s %s, Matricula: %s, Usuario: %s, Estado: %s\n",
               estudiantes[i].nombres, estudiantes[i].apellidos, estudiantes[i].matricula,
               estudiantes[i].usuario, estudiantes[i].estado);
    }

    printf("\nCursos leidos:\n");
    for (int i = 0; i < numCursos; i++)
    {
        printf("Codigo: %s, CodigoMateria: %s, CedulaProfesor: %s, Fecha de Inicio: %s, Fecha de Fin: %s\n",
               cursos[i].codigoCurso, cursos[i].codigoMateria, cursos[i].ccProfesor,
               cursos[i].fechaInicio, cursos[i].fechaFin);

        // Mostrar las matrículas de los estudiantes
        printf("Matriculas de estudiantes: ");
        for (int j = 0; j < 30; j++)
        { // Limitar a 30 matrículas
            if (cursos[i].matriculasEstudiantes[j][0] != '\0')
            { // Verifica si la matrícula no está vacía
                printf("%s ", cursos[i].matriculasEstudiantes[j]);
            }
        }
        printf("\n");
    }
    printf("\nProfesores leidos:\n");
    for (int i = 0; i < numProfesores; i++)
    {
        printf("Nombre: %s %s , Cedula: %s, Usuario: %s, Estado: %s, Clave %s\n", profesores[i].nombre, profesores[i].apellido, profesores[i].cedula, profesores[i].usuario, profesores[i].estado, profesores[i].clave);
        printf("Areas de Especializacion: ");
        for (int j = 0; j < 2; j++)
        {
            if (profesores[i].materias[j][0] != '\0')
            {
                printf("%s ", profesores[i].materias[j]);
            }
        }
        printf("\n\n");
    }
    // Pruebas
    printf("******** FINALIZACION DE CARGA DE DATOS ********\n");

    printf("******** BIENVENIDO ********\n");

    char opcion;
    do
    {
        mostrarMenu();
        printf("Ingrese la opcion que desee: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'a':
            printf("1. Agregar Materia\n");
            printf("2. Editar Materia\n");
            printf("Ingrese la opcion que desee: ");
            int subopcion;
            scanf("%d", &subopcion);
            if (subopcion == 1)
            {
                agregarMateria(materias, &numMaterias);
            }
            else if (subopcion == 2)
            {
                editarMateria(materias, numMaterias, cursos, numCursos);
            }
            else
            {
                printf("Opción inválida.\n");
            }
            break;
        case 'b':
            // Crear/editar estudiante
            break;
        case 'c':
            // Crear/editar profesor
            break;
        case 'd':
            // Crear/editar curso
            break;
        case 'e':
            printf("Programa finalizado.\n");
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
    } while (opcion != 'e');

    return 0;
}

void mostrarMenu()
{
    printf("a. Materia\n");
    printf("b. Estudiante\n");
    printf("c. Profesor\n");
    printf("d. Curso\n");
    printf("e. Salir\n");
}