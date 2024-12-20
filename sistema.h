#ifndef SISTEMA_H
#define SISTEMA_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

//Nos servira para cargar los datos y manejarlos de mejor manera
void leerMaterias(Materia *materias, int *numMaterias);
void leerEstudiantes(Estudiante *estudiantes, int *numEstudiantes);
void leerCursos(Curso *cursos, int *numCursos);
void leerProfesores(Profesor *profesor, int *numProfesor);


// guardar los nuevos datos
void guardarMateria(Materia *materias, int numMaterias);

// estos nos permitiran manera la logica de materias
void agregarMateria(Materia *materias, int *numMaterias);
void editarMateria(Materia *materias, int numMaterias, Curso *cursos, int numCursos);
bool tieneCursosActivosMateria(const char *codigoMateria, Curso *cursos, int numCursos);
void editarEstudiante(Estudiante *estudiantes, int numEstudiantes, Curso *cursos, int numCursos);
bool tieneCursosActivosEstudiante(const char *matricula, Curso *cursos, int numCursos);
void agregarEstudiante(Estudiante *estudiantes, int *numEstudiantes);
void guardarEstudiantes(Estudiante *estudiantes, int numEstudiantes);
#endif // SISTEMA_H
