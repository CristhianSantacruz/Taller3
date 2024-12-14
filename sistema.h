#ifndef SISTEMA_H
#define SISTEMA_H

#include <string.h>
#include <stdlib.h>

// Estructuras para almacenar los datos
typedef struct {
    char nombre[100];
    char codigo[20];
    char estado[10]; // "Activo" o "Inactivo"
} Materia;

typedef struct {
    char nombres[100];
    char apellidos[100];
    char matricula[20];
    char usuario[50];
    char clave[50];
    char estado[10]; // "Activo" o "Inactivo"
} Estudiante;

typedef struct {
    char nombre[100];
    char apellido[100];
    char cedula[20]; // Cédula de ciudadanía
    char usuario[50];
    char clave[50];
    char estado[10]; // "Activo" o "Inactivo"
    char materias[10][20]; // Códigos de las materias que puede dictar
} Profesor;

typedef struct {
    char codigoCurso[20];
    char codigoMateria[20];
    char ccProfesor[20];
    char fechaInicio[11]; // DD/MM/AAAA
    char fechaFin[11];    // DD/MM/AAAA
    char matriculasEstudiantes[30][10]; // Matrículas de estudiantes
} Curso;

// Funciones para leer archivos
void leerMaterias(Materia *materias, int *numMaterias);
void leerEstudiantes(Estudiante *estudiantes, int *numEstudiantes);
void leerCursos(Curso *cursos, int *numCursos);
void leerProfesores(Profesor *profesor, int *numProfesor);
#endif // SISTEMA_H
