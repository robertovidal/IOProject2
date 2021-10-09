#include "documento.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *archivo;

void terminaPdf(){
    fputs("\\end{document}", archivo);
    fclose(archivo);
    system("cd Latex && lualatex main.tex && mv ./main.pdf ../resultado.pdf && cd .. && evince resultado.pdf");
}

void crearPdf(){
    archivo = fopen("Latex/main.tex", "w");
    if(archivo == NULL){
        printf("No se pudo abrir Latex/main.tex");
        exit(0);
    }
    char inicio[] = "\\documentclass[a4paper]{article}\n\\input{head}\n\\begin{document}\n\n%-------------------------------\n%	TITLE SECTION\n%-------------------------------\n\n\\fancyhead[C]{}\n\\hrule \\medskip % Upper rule\n\\begin{minipage}{0.295\\textwidth} % Left side of title section\n\\raggedright\nIO\\\\ % Your lecture or course\n\\footnotesize % Authors text size\n\\hfill\\\\\nJose Pablo Fernández Cubillo, 2019047740 \\\\% Your name, your matriculation number\nRoberto Vidal Patiño, 2019065537% Your name, your matriculation number\n\\end{minipage}\n\\begin{minipage}{0.4\\textwidth} % Center of title section\n\\centering \n\\large % Title text size\nProyecto 2\\\\ % Assignment title and number\n\\normalsize % Subtitle text size\nA.B.B Dinámico vs A.B.B Greedy\\\\ % Assignment subtitle\n\\end{minipage}\n\\begin{minipage}{0.295\\textwidth} % Right side of title section\n\\raggedleft\n\\today\\\\ % Date\n\\footnotesize % Email text size\n\\hfill\\\\\npablof5181@estudiantec.cr\\\\\nrobertovidal@estudiantec.cr% Your email\n\\end{minipage}\n\\medskip\\hrule % Lower rule\n\\bigskip\n\n%-------------------------------\n%	CONTENTS\n%-------------------------------\n";
    fputs(inicio, archivo);
}

void quita0sDerecha(char numero[17], int ponePorcentaje){
    int i = 14;
    for(; i >= 1; i--){
        if(numero[i] == '\0'){
            continue;
        }
        if(numero[i] == '0'){
            numero[i] = '\0';
        } else if(numero[i] == '.'){
            numero[i] = '\0';
            i--;
            break;
        } else {
            break;
        }
    }
    if(ponePorcentaje){
        numero[i+1] = '\\';
        numero[i+2] = '%';
    }
    printf("%s\n",numero);
}

void crearTablaExperimento(double lista[10], char tipoTabla[], char nombre[], int ponePorcentaje){
    char numeroInt[4];
    char numeroDouble[17] = {'\0'};
    fputs("\\section{", archivo);
    fputs(tipoTabla, archivo);
    fputs(" usando ", archivo);
    fputs(nombre, archivo);
    fputs("}\n\n\\begin{table}[H]\n\\centering\n\\relax\n\\resizebox{\\textwidth}{!} {%\n\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}\n\\hline\n \\multicolumn{10}{|c|}{\\textbf{Cantidad de llaves}} \\\\\n \\hline \n", archivo);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 10; j++){
            if(i == 0){
                sprintf(numeroInt, "%d", j*10);
                fputs(numeroInt, archivo);
            } else {
                sprintf(numeroDouble, "%f", lista[j]);
                quita0sDerecha(numeroDouble, ponePorcentaje);
                fputs(numeroDouble, archivo);
            }
            if(j == 9){
                fputs(" \\\\\n", archivo);
            } else {
                fputs(" & ", archivo);
            }
        }
        fputs("\\hline\n", archivo);
    }
    fputs("\\end{tabular}%\n}\n\\caption{", archivo);
    fputs(tipoTabla, archivo);
    fputs(" usando ", archivo);
    fputs(nombre, archivo);
    fputs(".}\n\\end{table}\n", archivo);
}

void crearTituloEjemploProb(char titulo[], double probabilidades[6]){
    char numeroDouble[17] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    fputs("\\section{", archivo);
    fputs(titulo, archivo);
    fputs("}\n$$", archivo);
    for(int i = 0; i<6; i++){
        fputc('A'+i, archivo);
        fputs(" = ", archivo);
        sprintf(numeroDouble, "%f", probabilidades[i]);
        quita0sDerecha(numeroDouble, 0);
        fputs(numeroDouble, archivo);
        if(i < 5)
            fputs(",\\;", archivo);
    }
    fputs("$$\n", archivo);
}

void crearTituloEjemplo(char titulo[], double resultado, double tiempo){
    char numeroDouble[17] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    fputs("\\section{", archivo);
    fputs(titulo, archivo);
    fputs("}\n", archivo);
    fputs("\\textbf{Resultado:} ", archivo);
    sprintf(numeroDouble, "%f", resultado);
    quita0sDerecha(numeroDouble, 0);
    fputs(numeroDouble, archivo);
    fputs("\n\n\\textbf{Tiempo:} ", archivo);
    sprintf(numeroDouble, "%f", tiempo);
    quita0sDerecha(numeroDouble, 0);
    fputs(numeroDouble, archivo);
}

void crearTablaEjemplo(int **tabla, char nombre[]){
    char numeroInt[4]= {'\0', '\0', '\0', '\0'};
    fputs("\n\n\\begin{table}[H]\n\\centering\n\\relax\n\\begin{tabular}{|c|c|c|c|c|c|c|c|}\n", archivo);
    for(int i =0; i<7; i++){
        fputs("\\hline\n", archivo);
        for(int j = 0; j<=7; j++){
            if(i == 0){
                if(j != 0){
                    sprintf(numeroInt, "%d", j-1);
                    fputs(numeroInt, archivo);
                    fputs("\\cellcolor{blue!20}", archivo);
                }
            } else if(j == 0){
                sprintf(numeroInt, "%d", i);
                fputs(numeroInt, archivo);
                fputs("\\cellcolor{blue!20}", archivo);
            } else {
                if(i <= j || tabla[i-1][j-1] != 0){
                    sprintf(numeroInt, "%d", tabla[i-1][j-1]);
                    fputs(numeroInt, archivo);
                }
            }
            if(j == 7){
                fputs(" \\\\\n", archivo);
            } else {
                fputs(" & ", archivo);
            }
        }
        if(i == 6){
            fputs("\\hline\n", archivo);
        }
    }
    fputs("\\end{tabular}\n\\caption{", archivo);
    fputs(nombre, archivo);
    fputs("}\n\\end{table}\n", archivo);
}

void crearTablaEjemploD(double **tabla, char nombre[]){
    char numeroInt[4]= {'\0', '\0', '\0', '\0'};
    char numeroDouble[17] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    fputs("\n\n\\begin{table}[H]\n\\centering\n\\relax\n\\begin{tabular}{|c|c|c|c|c|c|c|c|}\n", archivo);
    for(int i = 0; i < 7; i++){
        fputs("\\hline\n", archivo);
        for(int j = 0; j <= 7; j++){
            if(i == 0){
                if(j != 0){
                    sprintf(numeroInt, "%d", j-1);
                    fputs(numeroInt, archivo);
                    fputs("\\cellcolor{blue!20}", archivo);
                }
            } else if(j == 0){
                sprintf(numeroInt, "%d", i);
                fputs(numeroInt, archivo);
                fputs("\\cellcolor{blue!20}", archivo);
            } else {
                if(i <= j || tabla[i-1][j-1] != 0){
                    sprintf(numeroDouble, "%f", tabla[i-1][j-1]);
                    quita0sDerecha(numeroDouble, 0);
                    fputs(numeroDouble, archivo);
                }
            }
            if(j == 7){
                fputs(" \\\\\n", archivo);
            } else {
                fputs(" & ", archivo);
            }
        }
        if(i == 6){
            fputs("\\hline\n", archivo);
        }
    }
    fputs("\\end{tabular}\n\\caption{", archivo);
    fputs(nombre, archivo);
    fputs("}\n\\end{table}\n", archivo);
}

void crearArbolEjemplo(int **tabla){
    char arbol[110] = {'\0'};
    fputs("\\begin{center}\n\\begin{tikzpicture}[>=Stealth]\n\\graph[binary tree layout]", archivo);
    for(int i = 0; i < 6; i++){
        for(int j = 6; j >= 0; j--){
            if(tabla[i][j] != 0){
                insertar(tabla[i][j]);
            }
        }
    }
    arbolLatex(arbol);
    fputs(arbol, archivo);
    fputs(";\n\\end{tikzpicture}\n\\end{center}\n", archivo);
    borrarArbol();
}
