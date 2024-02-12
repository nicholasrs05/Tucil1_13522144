#ifndef CYBERPUNKHACK_H
#define CYBERPUNKHACK_H

#include <stdio.h>
#include <string.h>
#include "boolean.h"

/* Definisi tipe data dynamic array of integer */
typedef struct{
    int *buffer;
    int nEff;
    int maxLen;
} intArray;

/* Definisi tipe data dynamic array of string */
typedef struct{
    char **buffer;
    int nEff;
    int maxLen;
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

/* Definisi tipe data point */
typedef struct{
    int X;
    int Y;
} point;

/* Definisi tipe data array of point */
typedef struct{
    point *buffer;
    int nEff;
    int maxLen;
} pointArray;

/* Konstruktor */
void createIntArray(intArray *Arr, int length);
/* I.S. sembarang */
/* F.S. terbentuk dynamic array of integer Arr dengan panjang length */

void createStringArray(strArray *Arr, int length);
/* I.S. sembarang */
/* F.S. terbentuk dynamic array of string Arr dengan panjang length */

void createStringMatrix(strMatrix *Mat, int height, int width);
/* I.S. sembarang */
/* F.S. terbentuk dynamic matrix of string Mat dengan baris height dan kolom width */

void createStack(strStack *Stack, int capacity);
/* I.S. sembarang */
/* F.S. terbentuk stack of string Stack dengan ukuran capacity */

void createPoint(point *P, int X, int Y);
/* I.S. sembarang */
/* F.S. terbentuk point P dengan koordinat (X, Y) */

void createPointArray(pointArray *Arr, int length);
/* I.S. sembarang */
/* F.S. terbentuk dynamic array of point Arr dengan panjang length */

/* Operator array, matrix, dan stack */
void insertLastStrArr(strArray *Arr, char *str);
/* I.S. strArray terdefinisi, mungkin kosong */
/* F.S. str ditambahkan sebagai elemen terakhir strArray */

void insertLastPointArr(pointArray *Arr, int X, int Y);
/* I.S. pointArray Arr terdefinisi, X dan Y integer */
/* F.S. titik (X, Y) ditambahkan sebagai elemen terakhir Arr */

void push(strStack *Stack, char *str);
/* I.S. strStack Stack terdefinisi, mungkin kosong */
/* F.S. menambahkan str sebagai top dari stack of string Stack */

void pop(strStack *Stack, char *str);
/* I.S. strStack Stack terdefinisi, tidak kosong */
/* F.S. string str dihapus dari stack of string Stack*/

void displayArray(strArray Arr);
/* I.S. strArray Arr terdefinisi, mungkin kosong */
/* F.S. tampil pada layar strArray Arr */

void displayMatrix(strMatrix Mat);
/* I.S. strMatrix Mat terdefinisi, mungkin kosong */
/* F.S. tampil pada layar strMatrix Mat */

void displaySeqAndReward(strMatrix Mat, intArray Seq, intArray Reward);
/* I.S. strMatrix Mat, intArray Seq, dan intArray Reward terdefinisi */
/* F.S. tampil pada layar daftar sequence dan rewardnya */

boolean isInStrArray(strArray Arr, char *Str);
/* mengembalikan true jika string Str ada di strArray Arr, false jika tidak */

boolean isSequenceDup(strMatrix Mat, intArray Seq, strArray temp, int tempLen, int curr);
/* mengembalikan true jika strArray temp sudah ada pada strMatrix, false jika tidak */

boolean isInPointArray(pointArray Arr, int X, int Y);
/* mengembalikan true jika koordinat (X, Y) sudah berada pada pointArray Arr, false jika tidak */

#endif