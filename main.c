#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "documento.h"


double progDinamica(int numeroLlaves, double *probabilidades, double **tablaA, int ** tablaR){
    for(int i = 0; i <= numeroLlaves; i++){
        tablaA[i][i] = 0;
        tablaR[i][i] = 0;
        if(i < numeroLlaves){
            tablaA[i][i+1] = probabilidades[i];
            tablaR[i][i+1] = i+1;
        }
    }
    int j;
    double sumaProb;
    double suma;
    double minSuma;
    int minK;
    for(int d = 1; d < numeroLlaves; d++){
        for(int i = 1; i + d <= numeroLlaves; i++){
            j = i + d;
            sumaProb = 0;
            for(int l = i - 1; l < j; l++){
                sumaProb += probabilidades[l];
            }
            minSuma = -1;
            minK = i;
            for(int k = i; k <= j; k++){
                suma = tablaA[i-1][k-1] + tablaA[k][j] + sumaProb;
                if(suma < minSuma || minSuma==-1){
                    minSuma = suma;
                    minK = k;
                }
            }
            tablaA[i-1][j] = minSuma;
            tablaR[i-1][j] = minK;
        }
    }
    return tablaA[0][numeroLlaves];
}

double calcularGreedy(int posInicio, int posFinal, double *probabilidades, int nivel, int **solucion){
    if(posInicio==posFinal){
        solucion[posInicio][posFinal+1] = posInicio+1;
        return nivel * probabilidades[posInicio];
    }
    else if(posInicio + 1 == posFinal){
        if(probabilidades[posInicio] > probabilidades[posFinal]){
            solucion[posInicio][posFinal+1] = posInicio+1;
            return (nivel * probabilidades[posInicio]) + ((nivel + 1) * probabilidades[posFinal]);
        }
        else{
            solucion[posInicio][posFinal+1] = posFinal+1;
            return (nivel * probabilidades[posFinal]) + ((nivel + 1) * probabilidades[posInicio]);
        }
    }
    else if(posInicio>posFinal){
        solucion[posInicio][posFinal+1] = 0;
        return 0;
    }
    double probMayor = probabilidades[posInicio];
    int posMayor = posInicio;
    for(int i = posInicio + 1; i<=posFinal; i++){
        if(probabilidades[i]>probMayor){
            probMayor = probabilidades[i];
            posMayor = i;
        }
    }
    solucion[posInicio][posFinal+1] = posMayor+1;
    return (probMayor * nivel) + calcularGreedy(posInicio, posMayor-1, probabilidades, nivel+1, solucion) + calcularGreedy(posMayor+1, posFinal, probabilidades, nivel+1, solucion);
}

double greedy(int numeroLlaves, double *probabilidades, int **solucion){
    for(int i = 0; i<numeroLlaves; i++){
        solucion[i][i+1] = i+1;
    }
    double result = calcularGreedy(0, numeroLlaves-1, probabilidades, 1, solucion);
    return result;
}

void modoEjemplo(){
    double probabilidades[6];
    double sumaProbabilidades = 0;
    int valores[6];
    char valoresASCII[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int sumaValor = 0;
    double resultadoPD;
    double resultadoGreedy;
    for(int i = 0; i < 6; i++){
        valores[i] = (rand() % 1000) + 1;
        sumaValor += valores[i];
    }
    for(int i = 0; i < 5; i++){
        probabilidades[i] = (double)valores[i]/sumaValor;
        sumaProbabilidades += probabilidades[i];
    }
    probabilidades[5] = 1 - sumaProbabilidades;
    double **tablaA;
    int **tablaR;
    tablaA = (double **) malloc(7 * sizeof(double*));
    for (int i = 0; i<7; i++) {
        tablaA[i] = (double *) malloc(7 * sizeof(double));
    }
    tablaR = (int **) malloc(7 * sizeof(int*));
    for (int i = 0; i<7; i++) {
        tablaR[i] = (int *) malloc(7 * sizeof(int));
    }
    clock_t begin = clock();
    resultadoPD = progDinamica(6, probabilidades, tablaA, tablaR);
    clock_t end = clock();
    double tiempo_prog_dinamica = (double)(end - begin) / CLOCKS_PER_SEC;
    int **tablaRGreedy;
    tablaRGreedy = (int **) malloc(7 * sizeof(int*));
    for (int i = 0; i<7; i++) {
        tablaRGreedy[i] = (int *) malloc(7 * sizeof(int));
    }
    begin = clock();
    resultadoGreedy = greedy(6, probabilidades, tablaRGreedy);
    end = clock();
    double tiempo_greedy = (double)(end - begin) / CLOCKS_PER_SEC;
    crearPdf();
    crearTituloEjemploProb("Probabilidades", probabilidades);
    crearTituloEjemplo("Programación dinámica", resultadoPD, tiempo_prog_dinamica);
    crearTablaEjemploD(tablaA, "Tabla A usando programación dinámica.");
    crearTablaEjemplo(tablaR, "Tabla R usando programación dinámica.");
    crearArbolEjemplo(tablaR);
    crearTituloEjemplo("Greedy", resultadoGreedy, tiempo_greedy);
    crearTablaEjemplo(tablaRGreedy, "Tabla R usando greedy.");
    crearArbolEjemplo(tablaRGreedy);
    terminaPdf();
    printf("Probabilidades:\n");
    for(int i = 0; i<6; i++){
        printf("%f", probabilidades[i]);
        if(i < 5){
            printf(", ");
        }
    }
    printf("\n");
    printf("Tabla A:\n");
    for(int i =0; i<6; i++){
        for(int j = 0; j<=6; j++){
            printf("%f", tablaA[i][j]);
            if(j < 6){
                printf(", ");
            }
        }
        printf("\n");
    }
    printf("Tabla R:\n");
    for(int i =0; i<6; i++){
        for(int j = 0; j<=6; j++){
            printf("%d", tablaR[i][j]);
            if(j < 6){
                printf(", ");
            }
        }
        printf("\n");
    }
    printf("Tiempo Progra Dinamica: %f\n", tiempo_prog_dinamica);
    printf("Resultado Progra Dinamica: %f\n", resultadoPD);
    printf("Tabla R Greedy:\n");
    for(int i =0; i<6; i++){
        for(int j = 0; j<=6; j++){
            printf("%d", tablaRGreedy[i][j]);
            if(j < 6){
                printf(", ");
            }
        }
        printf("\n");
    }
    printf("Tiempo Greedy: %f\n", tiempo_greedy);
    printf("Resultado Greedy: %f\n", resultadoGreedy);
    free(tablaA);
    free(tablaR);
    free(tablaRGreedy);
}

void modoExperimento(int n){
    int sumaValor;
    double sumaProbabilidades;
    double resultadoPD;
    double resultadoGreedy;
    int correctasGreedy;
    double sumaDinamica;
    double sumaGreedy;
    double promedioTiemposDinamica[10];
    double promedioTiemposGreedy[10];
    double porcentajeAciertosGreedy[10];
    int valores[100];
    double probabilidades[100];
    clock_t begin;
    clock_t end;
    double **tablaA;
    int **tablaR;
    tablaA = (double **) malloc(101 * sizeof(double*));
    for (int i = 0; i<101; i++) {
        tablaA[i] = (double *) malloc(101 * sizeof(double));
    }
    tablaR = (int **) malloc(101 * sizeof(int*));
    for (int i = 0; i<101; i++) {
        tablaR[i] = (int *) malloc(101 * sizeof(int));
    }
    for(int i = 10; i <= 100; i+=10){
        sumaDinamica = 0;
        sumaGreedy = 0;
        correctasGreedy = 0;
        for(int j = 0; j < n; j++){
            sumaValor = 0;
            for(int k = 0; k < i; k++){
                valores[k] = (rand() % 1000) + 1;
                sumaValor += valores[k];
            }
            sumaProbabilidades = 0;
            for(int k = 0; k < i-1; k++){
                probabilidades[k] = (double)valores[k]/sumaValor;
                sumaProbabilidades += probabilidades[k];
            }
            probabilidades[i-1] = 1 - sumaProbabilidades;
            begin = clock();
            resultadoPD = progDinamica(i, probabilidades, tablaA, tablaR);
            end = clock();
            sumaDinamica += (double)(end - begin) / CLOCKS_PER_SEC;
            begin = clock();
            resultadoGreedy = greedy(i, probabilidades, tablaR);
            end = clock();
            sumaGreedy += (double)(end - begin) / CLOCKS_PER_SEC;
            if(resultadoPD == resultadoGreedy)
                correctasGreedy++;
        }
        promedioTiemposDinamica[i/10 - 1] = sumaDinamica/n;
        promedioTiemposGreedy[i/10-1] = sumaGreedy/n;
        porcentajeAciertosGreedy[i/10-1] = (double)correctasGreedy * 100 / n;
    }
    crearPdf();
    crearTablaExperimento(promedioTiemposDinamica, "Promedios de tiempo en milisegundos", "programación dinámica", 0);
    crearTablaExperimento(promedioTiemposGreedy, "Promedios de tiempo en milisegundos", "greedy", 0);
    crearTablaExperimento(porcentajeAciertosGreedy, "Porcentaje de aciertos", "greedy", 1);
    terminaPdf();
    printf("El promedio de tiempo que dura la programacion dinamica en milisegundos:\n");
    for(int i = 0; i < 10; i++){
        printf("%f", promedioTiemposDinamica[i]);
        if(i < 9){
            printf(", ");
        }
    }
    printf("\nEl promedio de tiempo que dura el algoritmo greedy en milisegundos:\n");
    for(int i = 0; i < 10; i++){
        printf("%f", promedioTiemposGreedy[i]);
        if(i < 9){
            printf(", ");
        }
    }
    printf("\nEl porcentaje de veces que el greedy acierta:\n");
    for(int i = 0; i < 10; i++){
        printf("%f", porcentajeAciertosGreedy[i]);
        if(i < 9){
            printf(", ");
        }
    }
    printf("\n");
    free(tablaA);
    free(tablaR);
}


void mostrarAyuda(){
    printf("Parece que necesitas ayuda.\n\n");
    printf("Comando\tExplicación");
    printf("\n\n-X\tEl programa resolverá un solo caso aleatorio del problema de los Árboles\n\tBinarios de Búsqueda Óptimos con un algoritmo de programación dinámica y\n\tun algoritmo greedy. El árbol tiene 6 llaves. Cada llave tendrá sus\n\tprobabilidades aleatorias y tendrá un valor ASCII asignado que va de\n\tforma ascendente. Se despliega un pdf hecho en Latex con los resultados.");
    printf("\n\n-E=n\tEl programa resolverá 10n casos diferentes del problema de los Árboles\n\tBinarios de Búsqueda Óptimos con un algoritmo de programación dinámica y\n\tun algoritmo greedy. Las llaves del árbol van de 10 hasta 100. Para cada\n\tuno de los n casos en la cantidad de llaves, se generarán aleatoriamente\n\tlas probabilidades de cada llave, y la suma de estas probabilidades debe\n\tser 1. Se muestran los resultados de ejecución de los dos algoritmos con\n\ttablas de promedios de tiempo de ejecución y para el greedy se coloca\n\ttambién una tabla con los porcentajes de éxito.\n");
}

int main(int argc, char *argv[]){
    srand(time(0));
    if(argc != 2){
        mostrarAyuda();
        return -1;
    }
    if(strcmp(argv[1],"-X") == 0){
        modoEjemplo();
    }
    else{
        int n;
        if(argv[1][0] == '-' && argv[1][1] == 'E' && argv[1][2] == '=' && isdigit(argv[1][3])){
            sscanf(argv[1], "-E=%d", &n);
            if(n > 0){
                modoExperimento(n);
            } else {
                mostrarAyuda();
            }
        }
        else{
            mostrarAyuda();
        }
    }
    return 0;
}
