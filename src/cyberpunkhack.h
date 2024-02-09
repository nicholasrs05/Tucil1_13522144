#ifndef CYBERPUNKHACK_H
#define CYBERPUNKHACK_H

#include <stdio.h>
#include <string.h>

/* Definisi tipe data dynamic array of string */
typedef struct{
    char **buffer;
    int nEff;
} strArray;

/* Definisi tipe data dynamic matrix of string */
typedef struct{
    strArray *buffer;
    int row;
    int col;
} strMatrix;

/* Definisi tipe data stack */
typedef struct{
    char **buffer;
    int top;
} strStack;

/* Konstruktor */
void createArray(strArray *Arr, int length);
/* I.S. sembarang */
/* F.S. terbentuk dynamic array of string Arr dengan panjang nEff */

void createMatrix(strMatrix *Mat, int height, int width);
/* I.S. sembarang */
/* F.S. terbentuk dynamic matrix of string Mat dengan baris rowEff dan kolom colEff */

void createStack(strStack *Stack, int capacity);
/* I.S. sembarang */
/* F.S. terbentuk stack of string Stack dengan ukuran capacity */

/* Operator array, matrix, dan stack */
void insertLast(strArray *Arr, char *str);
/* I.S. strArray terdefinisi, mungkin kosong */
/* F.S. str ditambahkan sebagai elemen terakhir strArray */

void push(strStack *Stack, char *str);
/* I.S. strStack Stack terdefinisi, mungkin kosong */
/* F.S. menambahkan str sebagai top dari stack of string Stack */

void pop(strStack *Stack, char *str);
/* I.S. strStack Stack terdefinisi, tidak kosong */
/* F.S. string str dihapus dari stack of string Stack*/

void displayArray(strArray *Arr);
/* I.S. strArray Arr terdefinisi, mungkin kosong */
/* F.S. tampil pada layar strArray Arr */

void displayMatrix(strMatrix *Mat);
/* I.S. strMatrix Mat terdefinisi, mungkin kosong */
/* F.S. tampil pada layar strMatrix Mat */

#endif