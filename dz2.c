#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    int versh;
    int rebro = 0;
    int f = 0;
    int seychas = 1;
    int pustaya = 0;
    bool proydennaya = false;
    bool simple = true ;
    scanf_s("%d", &versh);
    int* arr = (int*)malloc(versh * versh * sizeof(int));

    for (int str = 0; str < versh; str++) {
        printf("%d:", str);

        for (int stolb = 0; stolb < versh; stolb++) {
            scanf_s("%d", (arr + str * versh + stolb));
        }
    }
    printf("\n");

    for (int str = 0; str < versh; str++) {

        for (int stolb = 0; stolb < versh; stolb++) {

            if ((str == stolb) && (arr[str * versh + stolb] != 0)) {    //диагональ
                simple = false ;
            }

            if (arr[str * versh + stolb] != arr[stolb * versh + str]) {     //симметричность отн. диагонали
                simple = false ;
            }

            if ((arr[str * versh + stolb] != 0) && (arr[str * versh + stolb] != 1)) {      //ребра(0 или 1) у каждой вершины
                simple = false ;
            }

            if (arr[str * versh + stolb] == 1) {      //проверка на два ребра у вершины
                rebro++;
            }

            if (rebro > 2) {
                simple = false ;
            }
        }
        rebro = 0;
    }

    for (int str = 0; str < versh; str++) {

        for (int stolb = 0; stolb < versh; stolb++) {

            if ((arr[rebro * versh + stolb] == 1) && (stolb != seychas) && (proydennaya == false)) {     //проверка обходом
                seychas = rebro; //позволяет переходить на следующую непройденную вершину помечая предыдущую как пройденную
                rebro = stolb;
                proydennaya = true;
            }
        }
        proydennaya = false;

        if ((rebro == 0) && (str != versh - 1)) {
            simple = false;
        }

        if ((str == versh - 1) && (rebro != 0)) {
            simple = false;
        }
    }
    if (simple == true) {
        printf("simple cycle");
    }
    else
        printf("not a simple cycle");

    // визуализация //

    FILE* file;

    if ((file = fopen("Dot_file.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(file, "graph G{\n");

    for (int str = 0; str < versh; str++) {

        for (int stolb = 0; stolb <= str; stolb++) {

            if (arr[str * versh + stolb] != 0) {

                for (int graph_line = 0; graph_line < arr[str * versh + stolb]; graph_line++) {
                    fprintf(file, "%d -- %d;\n", str, stolb);
                }
            }
        }
    }
    for (int str = 0; str < versh; str++) {
        for (int stolb = 0; stolb < versh; stolb++) {
            if ((arr[str * versh + stolb]) == 0) {
                pustaya++;
            }
        }
        if (pustaya == versh) {
            fprintf(file, "%d;\n", str);
        }
        pustaya = 0;
    }

    fprintf(file, "}");
    fclose(file);
    system("dot C:\\Users\\stepa\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\Dot_file.txt -Tbmp -o Dot_file.bmp");
    system("rundll32 \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\stepa\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\Dot_file.bmp");
    return (0);
}
