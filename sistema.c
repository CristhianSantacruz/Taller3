#include "sistema.h"
#include <stdio.h>

// carga las materias en el main
void leerMaterias(Materia *materias, int *numMaterias) {
    FILE *file = fopen("data/materias.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de materias.\n");
        return;
    }

    while (fscanf(file, "%[^-]-%[^-]-%s\n", materias[*numMaterias].nombre, 
                   materias[*numMaterias].codigo, materias[*numMaterias].estado) != EOF) {
        (*numMaterias)++;
    }

    fclose(file);
}

// carga los estudiantes en el main
void leerEstudiantes(Estudiante *estudiantes, int *numEstudiantes) {
    FILE *file = fopen("data/estudiantes.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de estudiantes.\n");
        return;
    }

    while (fscanf(file, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%s\n", estudiantes[*numEstudiantes].nombres,
                   estudiantes[*numEstudiantes].apellidos, estudiantes[*numEstudiantes].matricula,
                   estudiantes[*numEstudiantes].usuario, estudiantes[*numEstudiantes].clave, estudiantes[*numEstudiantes].estado) != EOF) {
        (*numEstudiantes)++;
    }

    fclose(file);
}
// carga los cursos en ell main
void leerCursos(Curso *cursos, int *numCursos) {
    FILE *file = fopen("data/cursos.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de cursos.\n");
        return;
    }

    char line[256];  // Para almacenar cada línea del archivo
    while (fgets(line, sizeof(line), file) != NULL) {
        // Eliminar el salto de línea al final de la línea leída
        line[strcspn(line, "\n")] = 0;

        // Variables para almacenar los campos extraídos
        char matriculasCopy[100];  // Copia de las matrículas para procesarlas
        char *token;
        
        // Usamos strtok para separar la línea por '-'
        token = strtok(line, "-");
        if (token != NULL) {
            // Almacenamos los datos en los campos correspondientes
            strcpy(cursos[*numCursos].codigoCurso, token);  // CURS01
            token = strtok(NULL, "-");
            strcpy(cursos[*numCursos].codigoMateria, token);  // EST101
            token = strtok(NULL, "-");
            strcpy(cursos[*numCursos].ccProfesor, token);  // 12345678
            token = strtok(NULL, "-");
            strcpy(cursos[*numCursos].fechaInicio, token);  // 2024/01/10
            token = strtok(NULL, "-");
            strcpy(cursos[*numCursos].fechaFin, token);  // 2024/06/10
            token = strtok(NULL, "-");

            // Almacenamos las matrículas
            if (token != NULL) {
                strcpy(matriculasCopy, token);  // Copia de las matrículas
                int index = 0;

                // Separamos las matrículas usando '/' como delimitador
                char *matricula = strtok(matriculasCopy, "/");
                while (matricula != NULL && index < 30) {
                    strcpy(cursos[*numCursos].matriculasEstudiantes[index], matricula);
                    index++;
                    matricula = strtok(NULL, "/");
                }
            }
        }

        // Incrementar el contador de cursos
        (*numCursos)++;
    }

    fclose(file);
}

// carga los profesores en el main
void leerProfesores(Profesor *profesores, int *numProfesor) {
    FILE *file = fopen("data/profesores.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de profesores.\n");
        return;
    }

    char line[256];  // Para almacenar cada línea del archivo
    while (fgets(line, sizeof(line), file) != NULL) {
        // Eliminar el salto de línea al final de la línea leída
        line[strcspn(line, "\n")] = 0;

        // Variables para almacenar los campos extraídos
        char *token;

        // Usamos strtok para separar la línea por '-'
        token = strtok(line, "-");
        if (token != NULL) {
            // Almacenamos los datos en los campos correspondientes
            strcpy(profesores[*numProfesor].nombre, token);  // Ejemplo: "María"
            token = strtok(NULL, "-");
            strcpy(profesores[*numProfesor].apellido, token);  // Ejemplo: "Díaz"
            token = strtok(NULL, "-");
            strcpy(profesores[*numProfesor].cedula, token);  // Ejemplo: "45678901"
            token = strtok(NULL, "-");
            strcpy(profesores[*numProfesor].usuario, token);  // Ejemplo: "mdiaz1234"
            token = strtok(NULL, "-");
            strcpy(profesores[*numProfesor].clave, token);  // Ejemplo: "Clave"
             token = strtok(NULL, "-");
            strcpy(profesores[*numProfesor].estado, token);  // Ejemplo: "Activo"
            token = strtok(NULL, "-");

            // Almacenamos las áreas, separando por '/'
            if (token != NULL) {
                int index = 0;
                char *materia = strtok(token, "/");
                while (materia != NULL && index < 10) {  // Limitar a 2 áreas
                    strcpy(profesores[*numProfesor].materias[index], materia);
                    index++;
                    materia = strtok(NULL, "/");
                }
            }
        }

        // Incrementar el contador de profesores
        (*numProfesor)++;
    }

    fclose(file);
}

void guardarMateria(Materia *materias, int numMaterias) {
    FILE *archivo = fopen("data/materias.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las materias.\n");
        return;
    }

    for (int i = 0; i < numMaterias; i++) {
        fprintf(archivo, "%s-%s-%s\n", materias[i].nombre, materias[i].codigo, materias[i].estado);
    }

    fclose(archivo);
    printf("Materias guardadas exitosamente en el archivo.\n");
}
void agregarMateria(Materia *materias, int *numMaterias) {
    if (*numMaterias >= 100) {
        printf("No se pueden agregar más materias.\n");
        return;
    }
    Materia nuevaMateria;
    printf("Ingrese el nombre de la materia: ");
    scanf(" %[^\n]", nuevaMateria.nombre);
    printf("Ingrese el codigo de la materia: ");
    scanf(" %s", nuevaMateria.codigo);
    strcpy(nuevaMateria.estado, "Activo");

    materias[*numMaterias] = nuevaMateria;
    (*numMaterias)++;

    guardarMateria(materias, *numMaterias); // Guardar cambios en el archivo
    printf("Materia agregada y guardada exitosamente.\n");
}
void editarMateria(Materia *materias, int numMaterias, Curso *cursos, int numCursos) {
    char codigo[20];
    printf("Ingrese el codigo de la materia a editar: ");
    scanf(" %s", codigo);

    for (int i = 0; i < numMaterias; i++) {
        if (strcmp(materias[i].codigo, codigo) == 0) {
            printf("Materia encontrada: %s (%s)\n", materias[i].nombre, materias[i].estado);

            if (tieneCursosActivos(codigo, cursos, numCursos)) {
                printf("No se puede inactivar la materia porque tiene cursos activos.\n");
                printf("*************************************************************\n");
            } else {
                printf("Ingrese el nuevo estado (Activo/Inactivo): ");
                scanf(" %s", materias[i].estado);
                printf("Estado actualizado exitosamente.\n");
                printf("********************************\n");

                guardarMateria(materias, numMaterias); // Guardar cambios en el archivo
            }

            return; // Salir de la función una vez que se edita el estado
        }
    }

    printf("Materia con código %s no encontrada.\n", codigo);
}

bool tieneCursosActivos(const char *codigoMateria, Curso *cursos, int numCursos) {
    for (int i = 0; i < numCursos; i++) {
        if (strcmp(cursos[i].codigoMateria, codigoMateria) == 0) {
            return true;
        }
    }
    return false;
}


