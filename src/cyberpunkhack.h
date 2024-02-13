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

/* Definisi tipe data point */
typedef struct{
    int X;
    int Y;
} point;

/* Definisi tipe data dynamic array of point */
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

void displayArray(strArray Arr);
/* I.S. strArray Arr terdefinisi, mungkin kosong */
/* F.S. tampil pada layar strArray Arr */

void displayMatrix(strMatrix Mat);
/* I.S. strMatrix Mat terdefinisi, mungkin kosong */
/* F.S. tampil pada layar strMatrix Mat */

void displayPointArray(pointArray Arr);
/* I.S. pointArray Arr terdefinisi, mungkin kosong */
/* F.S. tampil pada layar pointArray Arr */

void displaySeqAndReward(strMatrix Mat, intArray Seq, intArray Reward);
/* I.S. strMatrix Mat, intArray Seq, dan intArray Reward terdefinisi */
/* F.S. tampil pada layar daftar sequence dan rewardnya */

void copyPointArray(pointArray Arr1, pointArray *Arr2);
/* I.S. pointArray Arr1 terdefinisi */
/* F.S. pointArray Arr1 di-copy ke pointArray Arr2 */

boolean isInStrArray(strArray Arr, char *Str);
/* mengembalikan true jika string Str ada di strArray Arr, false jika tidak */

boolean isSequenceDup(strMatrix Mat, intArray Seq, strArray temp, int tempLen, int curr);
/* mengembalikan true jika strArray temp sudah ada pada strMatrix, false jika tidak */

boolean isInPointArray(pointArray Arr, int X, int Y);
/* mengembalikan true jika koordinat (X, Y) sudah berada pada pointArray Arr, false jika tidak */

int addReward(strMatrix Mat, intArray Seq, intArray Reward, pointArray Arr, strMatrix tokenMat);
/* mengembalikan reward yang bersesuaian jika terdapat sequence strMatrix Mat pada jalur yang disimpan di pointArray Arr*/

void recursiveTraverse(strMatrix seqMat, intArray Seq, intArray Reward, pointArray *Arr, strMatrix tokenMat, int *maxReward, pointArray *maxArr, int currX, int currY, boolean vertical);
/* I.S. strMatrix seqMat, intArray Seq, intArray Reward, pointArray Arr, strMatrix tokenMat, int maxReward, pointArray maxArr, int currX, int currY, boolean vertical terdefinisi */
/* F.S. int maxReward menyimpan reward maksimal dan pointArray maxArr menyimpan rutenya */

#endif