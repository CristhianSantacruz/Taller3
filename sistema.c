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


// Guardar profesores en el archivo correspondiente
void guardarProfesores(Profesor *profesores, int numProfesores) {
    FILE *archivo = fopen("data/profesores.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los profesores.\n");
        return;
    }

    for (int i = 0; i < numProfesores; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s", profesores[i].nombre, profesores[i].apellido, profesores[i].cedula, profesores[i].usuario, profesores[i].clave, profesores[i].estado);
        for (int j = 0; j < 10; j++) {
            if (profesores[i].materias[j][0] != '\0') {
                fprintf(archivo, "/%s", profesores[i].materias[j]);
            }
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);
    printf("Profesores guardados exitosamente en el archivo.\n");
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

void agregarProfesor(Profesor *profesores, int *numProfesores) {
    if (*numProfesores >= 100) {
        printf("No se pueden agregar más profesores.\n");
        return;
    }

    Profesor nuevoProfesor;
    printf("Ingrese el nombre del profesor: ");
    scanf(" %[^\n]", nuevoProfesor.nombre);
    printf("Ingrese el apellido del profesor: ");
    scanf(" %[^\n]", nuevoProfesor.apellido);
    printf("Ingrese la cédula del profesor: ");
    scanf(" %s", nuevoProfesor.cedula);
    printf("Ingrese el usuario del profesor: ");
    scanf(" %s", nuevoProfesor.usuario);
    printf("Ingrese la clave del profesor: ");
    scanf(" %s", nuevoProfesor.clave);
    strcpy(nuevoProfesor.estado, "Activo");

    printf("Ingrese los códigos de las materias que puede dictar (máximo 10, separados por espacio, termine con -1):\n");
    for (int i = 0; i < 10; i++) {
        char codigo[20];
        scanf(" %s", codigo);
        if (strcmp(codigo, "-1") == 0) {
            for (int j = i; j < 10; j++) { // Limpiar posiciones restantes
                nuevoProfesor.materias[j][0] = '\0';
            }
            break;
        }
        strcpy(nuevoProfesor.materias[i], codigo);
    }


    // Validación de unicidad de cédula y usuario
    for (int i = 0; i < *numProfesores; i++) {
        if (strcmp(profesores[i].cedula, nuevoProfesor.cedula) == 0 || strcmp(profesores[i].usuario, nuevoProfesor.usuario) == 0) {
            printf("Error: Cédula o usuario ya existen.\n");
            return;
        }
    }

    profesores[*numProfesores] = nuevoProfesor;
    (*numProfesores)++;

    guardarProfesores(profesores, *numProfesores);
    printf("Profesor agregado y guardado exitosamente.\n");
}

// Editar un profesor
void editarProfesor(Profesor *profesores, int numProfesores, Curso *cursos, int numCursos) {
    char cedula[20];
    printf("Ingrese la cédula del profesor a editar: ");
    scanf(" %s", cedula);

    for (int i = 0; i < numProfesores; i++) {
        if (strcmp(profesores[i].cedula, cedula) == 0) {
            printf("Profesor encontrado: %s %s (Estado: %s)\n", profesores[i].nombre, profesores[i].apellido, profesores[i].estado);

            char opcionClave;
            printf("¿Desea cambiar la clave del profesor? (S/N): ");
            scanf(" %c", &opcionClave);

            if (opcionClave == 'S' || opcionClave == 's') {
                printf("Ingrese la nueva clave del profesor: ");
                char nuevaClave[50];
                scanf(" %s", nuevaClave);

                // Limpiar el campo clave y asignar la nueva clave
                memset(profesores[i].clave, '\0', sizeof(profesores[i].clave));
                strncpy(profesores[i].clave, nuevaClave, sizeof(profesores[i].clave) - 1);

                printf("Clave actualizada exitosamente.\n");
            }

            char opcionEstado;
            printf("¿Desea cambiar el estado del profesor? (S/N): ");
            scanf(" %c", &opcionEstado);

            if (opcionEstado == 'S' || opcionEstado == 's') {
                char nuevoEstado[10];
                printf("Ingrese el nuevo estado (Activo/Inactivo): ");
                scanf(" %s", nuevoEstado);

                if (strcmp(nuevoEstado, "Inactivo") == 0 && tieneCursosActivosProfesor(cedula, cursos, numCursos)) {
                    printf("No se puede inactivar el profesor porque tiene cursos activos.\n");
                } else {
                    strncpy(profesores[i].estado, nuevoEstado, sizeof(profesores[i].estado) - 1);
                    printf("Estado actualizado exitosamente.\n");
                }
            }

            guardarProfesores(profesores, numProfesores); // Guardar los cambios
            return;
        }
    }

    printf("Profesor con cédula %s no encontrado.\n", cedula);
}


// Verificar si un profesor tiene cursos activos
bool tieneCursosActivosProfesor(const char *cedula, Curso *cursos, int numCursos) {
    for (int i = 0; i < numCursos; i++) {
        if (strcmp(cursos[i].ccProfesor, cedula) == 0) {
            return true;
        }
    }
    return false;
}

void agregarCurso(Curso *cursos, int *numCursos, Materia *materias, int numMaterias,
                  Profesor *profesores, int numProfesores, Estudiante *estudiantes, int numEstudiantes) {
    if (*numCursos >= 100) {
        printf("No se pueden agregar más cursos.\n");
        return;
    }

    Curso nuevoCurso;
    printf("Ingrese el código del curso: ");
    scanf(" %s", nuevoCurso.codigoCurso);
    printf("Ingrese el código de la materia: ");
    scanf(" %s", nuevoCurso.codigoMateria);
    printf("Ingrese la cédula del profesor: ");
    scanf(" %s", nuevoCurso.ccProfesor);
    printf("Ingrese la fecha de inicio (DD/MM/AAAA): ");
    scanf(" %s", nuevoCurso.fechaInicio);
    printf("Ingrese la fecha de fin (DD/MM/AAAA): ");
    scanf(" %s", nuevoCurso.fechaFin);

    printf("Ingrese las matrículas de los estudiantes (máximo 30, separados por espacio, termine con -1):\n");
    for (int i = 0; i < 30; i++) {
        char matricula[10];
        scanf(" %s", matricula);
        if (strcmp(matricula, "-1") == 0) {
            nuevoCurso.matriculasEstudiantes[i][0] = '\0';
            break;
        }
        strcpy(nuevoCurso.matriculasEstudiantes[i], matricula);
    }

    // Validaciones omitidas aquí por brevedad...

    cursos[*numCursos] = nuevoCurso;
    (*numCursos)++;

    guardarCursos(cursos, *numCursos); // Guardar los cambios en el archivo
    printf("Curso agregado exitosamente y guardado en el archivo.\n");
}


void editarCurso(Curso *cursos, int numCursos) {
    char codigo[20];
    printf("Ingrese el código del curso a editar: ");
    scanf(" %s", codigo);

    for (int i = 0; i < numCursos; i++) {
        if (strcmp(cursos[i].codigoCurso, codigo) == 0) {
            printf("Curso encontrado: %s\n", cursos[i].codigoCurso);

            char opcion;
            printf("¿Desea editar la materia (M), profesor (P), fechas (F), o estudiantes (E)? Ingrese su opción: ");
            scanf(" %c", &opcion);

            if (opcion == 'M' || opcion == 'm') {
                printf("Ingrese el nuevo código de materia: ");
                scanf(" %s", cursos[i].codigoMateria);
            } else if (opcion == 'P' || opcion == 'p') {
                printf("Ingrese la nueva cédula del profesor: ");
                scanf(" %s", cursos[i].ccProfesor);
            } else if (opcion == 'F' || opcion == 'f') {
                printf("Ingrese la nueva fecha de inicio (DD/MM/AAAA): ");
                scanf(" %s", cursos[i].fechaInicio);
                printf("Ingrese la nueva fecha de fin (DD/MM/AAAA): ");
                scanf(" %s", cursos[i].fechaFin);
            } else if (opcion == 'E' || opcion == 'e') {
                printf("Ingrese las nuevas matrículas de estudiantes (máximo 30, termine con -1):\n");
                for (int j = 0; j < 30; j++) {
                    char matricula[10];
                    scanf(" %s", matricula);
                    if (strcmp(matricula, "-1") == 0) {
                        cursos[i].matriculasEstudiantes[j][0] = '\0';
                        break;
                    }
                    strcpy(cursos[i].matriculasEstudiantes[j], matricula);
                }
            } else {
                printf("Opción inválida.\n");
                return;
            }

            guardarCursos(cursos, numCursos); // Guardar los cambios en el archivo
            printf("Curso actualizado exitosamente y guardado en el archivo.\n");
            return;
        }
    }

    printf("Curso con código %s no encontrado.\n", codigo);
}


void guardarCursos(Curso *cursos, int numCursos) {
    FILE *archivo = fopen("data/cursos.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los cursos.\n");
        return;
    }

    for (int i = 0; i < numCursos; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s", cursos[i].codigoCurso, cursos[i].codigoMateria,
                cursos[i].ccProfesor, cursos[i].fechaInicio, cursos[i].fechaFin);
        for (int j = 0; j < 30; j++) {
            if (cursos[i].matriculasEstudiantes[j][0] != '\0') {
                fprintf(archivo, "/%s", cursos[i].matriculasEstudiantes[j]);
            }
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);
    printf("Cursos guardados exitosamente en el archivo.\n");
}
