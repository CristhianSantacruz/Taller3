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

            char opcion;
            printf("¿Desea cambiar el estado de la materia? (s/n): ");
            scanf(" %c", &opcion);

            if (opcion == 's' || opcion == 'S') {
                char nuevoEstado[20];
                printf("Ingrese el nuevo estado (Activo/Inactivo): ");
                scanf(" %s", nuevoEstado);

                if (strcmp(nuevoEstado, "Inactivo") == 0 && tieneCursosActivosMateria(codigo, cursos, numCursos)) {
                    printf("No se puede inactivar la materia porque tiene cursos activos.\n");
                    printf("*************************************************************\n");
                } else {
                    strcpy(materias[i].estado, nuevoEstado);
                    printf("Estado actualizado exitosamente.\n");
                    printf("********************************\n");

                    guardarMateria(materias, numMaterias); // Guardar cambios en el archivo
                }
            } else {
                printf("No se realizó ningún cambio en el estado de la materia.\n");
            }
            return; // Salir de la función una vez que se encuentra la materia
        }
    }

    printf("Materia con código %s no encontrada.\n", codigo);
}

bool tieneCursosActivosMateria(const char *codigoMateria, Curso *cursos, int numCursos) {
    for (int i = 0; i < numCursos; i++) {
        if (strcmp(cursos[i].codigoMateria, codigoMateria) == 0) {
            return true;
        }
    }
    return false;
}



void guardarEstudiantes(Estudiante *estudiantes, int numEstudiantes) {
    FILE *archivo = fopen("data/estudiantes.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los estudiantes.\n");
        return;
    }

    for (int i = 0; i < numEstudiantes; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s\n",
                estudiantes[i].nombres, estudiantes[i].apellidos,
                estudiantes[i].matricula, estudiantes[i].usuario,
                estudiantes[i].clave, estudiantes[i].estado);
    }

    fclose(archivo);
    printf("Estudiantes guardados exitosamente en el archivo.\n");
}

void agregarEstudiante(Estudiante *estudiantes, int *numEstudiantes) {
    if (*numEstudiantes >= 100) {
        printf("No se pueden agregar más estudiantes.\n");
        return;
    }

    Estudiante nuevoEstudiante;
    printf("Ingrese los nombres del estudiante: ");
    scanf(" %[^\n]", nuevoEstudiante.nombres);
    printf("Ingrese los apellidos del estudiante: ");
    scanf(" %[^\n]", nuevoEstudiante.apellidos);
    printf("Ingrese la matrícula del estudiante: ");
    scanf(" %s", nuevoEstudiante.matricula);
    printf("Ingrese el usuario del estudiante: ");
    scanf(" %s", nuevoEstudiante.usuario);
    printf("Ingrese la clave del estudiante: ");
    scanf(" %s", nuevoEstudiante.clave);
    strcpy(nuevoEstudiante.estado, "Activo");

    // Validación de unicidad
    for (int i = 0; i < *numEstudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, nuevoEstudiante.matricula) == 0 ||
            strcmp(estudiantes[i].usuario, nuevoEstudiante.usuario) == 0) {
            printf("Error: Matrícula o usuario ya existen.\n");
            return;
        }
    }

    estudiantes[*numEstudiantes] = nuevoEstudiante;
    (*numEstudiantes)++;

    guardarEstudiantes(estudiantes, *numEstudiantes); // Guardar cambios
    printf("Estudiante agregado y guardado exitosamente.\n");
}

void editarEstudiante(Estudiante *estudiantes, int numEstudiantes, Curso *cursos, int numCursos) {
    char matricula[20];
    printf("Ingrese la matrícula del estudiante a editar: ");
    scanf(" %s", matricula);

    for (int i = 0; i < numEstudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            printf("Estudiante encontrado: %s %s (Estado: %s)\n", estudiantes[i].nombres, estudiantes[i].apellidos, estudiantes[i].estado);

            int cambiosRealizados = 0;  // Variable para verificar si hubo cambios

            // Preguntar si desea cambiar la clave
            char opcionClave;
            printf("¿Desea cambiar la clave del estudiante? (S/N): ");
            scanf(" %c", &opcionClave);

            if (opcionClave == 'S' || opcionClave == 's') {
                printf("Ingrese la nueva clave del estudiante: ");
                scanf(" %s", estudiantes[i].clave);
                cambiosRealizados = 1;  // Se realizó un cambio
                printf("Clave actualizada exitosamente.\n");
            }

            // Preguntar si desea cambiar el estado
            char opcionEstado;
            printf("¿Desea cambiar el estado del estudiante? (S/N): ");
            scanf(" %c", &opcionEstado);

            if (opcionEstado == 'S' || opcionEstado == 's') {
                char nuevoEstado[20];
                printf("Ingrese el nuevo estado (Activo/Inactivo): ");
                scanf(" %s", nuevoEstado);

                if (strcmp(nuevoEstado, "Inactivo") == 0) {
                    if (tieneCursosActivosEstudiante(matricula, cursos, numCursos)) {
                        printf("No se puede inactivar el estudiante porque está inscrito en cursos activos.\n");
                    } else {
                        strcpy(estudiantes[i].estado, nuevoEstado);
                        cambiosRealizados = 1;  // Se realizó un cambio
                        printf("Estado actualizado exitosamente.\n");
                    }
                } else {
                    strcpy(estudiantes[i].estado, nuevoEstado);
                    cambiosRealizados = 1;  // Se realizó un cambio
                    printf("Estado actualizado exitosamente.\n");
                }
            }

            // Guardar solo si se realizaron cambios
            if (cambiosRealizados) {
                guardarEstudiantes(estudiantes, numEstudiantes);
                printf("Cambios guardados exitosamente.\n");
            } else {
                printf("No se realizaron cambios.\n");
            }

            return;  // Salir después de editar
        }
    }

    printf("Estudiante con matrícula %s no encontrado.\n", matricula);
}


bool tieneCursosActivosEstudiante(const char *matricula, Curso *cursos, int numCursos) {
    bool encontrado = false;

    for (int i = 0; i < numCursos; i++) {
        for (int j = 0; j < 30; j++) {
            if (strcmp(cursos[i].matriculasEstudiantes[j], matricula) == 0) {
                printf("El estudiante está inscrito en el curso: %s (Código: %s)\n", 
                       cursos[i].codigoCurso, cursos[i].codigoMateria);
                encontrado = true;
            }
        }
    }
    return encontrado;
}


