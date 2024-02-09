#include <stdlib.h>
#include "cyberpunkhack.h"
#include "boolean.h"

/* --- Realisasi Fungsi dan Prosedur --- */
void createArray(strArray *Arr, int length){
    (*Arr).buffer = (char**) malloc (length * sizeof(char*));
    (*Arr).nEff = 0;
}

void createMatrix(strMatrix *Mat, int height, int width){
    (*Mat).buffer = (strArray*) malloc (height * sizeof(strArray));
    (*Mat).row = height;
    (*Mat).col = width;
}

void createStack(strStack *Stack, int capacity){
    (*Stack).buffer = (char**) malloc (capacity * sizeof(char*));
    (*Stack).top = -1;
}

void insertLast(strArray *Arr, char *str){
    (*Arr).buffer[(*Arr).nEff] = (char*) malloc (100 * sizeof(char));
    strcpy((*Arr).buffer[(*Arr).nEff], str);
    (*Arr).nEff++;
}

void push(strStack *Stack, char *str){
    (*Stack).top++;
    (*Stack).buffer[(*Stack).top] = (char*) malloc (100 * sizeof(char));
    strcpy((*Stack).buffer[(*Stack).top], str);
}

void pop(strStack *Stack, char *str){
    (*Stack).top--;
}

void displayArray(strArray *Arr){
    int i;
    for (i = 0; i < (*Arr).nEff; i++){
        printf("%s ", (*Arr).buffer[i]);
    }
    printf("\n");
}

void displayMatrix(strMatrix *Mat){
    int i, j;
    for (i = 0; i < (*Mat).row; i++){
        for (j = 0; j < (*Mat).col; j++){
            printf("%s ", (*Mat).buffer[i].buffer[j]);
        }
        printf("\n");
    }
}

/* --- Program Utama --- */
int main(){
    int i, j, k, bufferSize, mtxHeight, mtxWidth, cntSeq, option, cntToken, maxSeqSize;
    strArray seqArray;
    strMatrix seqReward, tokenMatrix;
    char *Word;
    boolean valid;

    printf("Cyberpunk 2077 Breach Protocol Solver with Brute Force Algorithm\n\n");
    printf("Apakah Anda ingin memasukkan matrix dan sequence dari file atau dari CLI?\n");
    printf("1. File\n");
    printf("2. CLI\n");
    

    // Validasi masukan
    valid = false;
    while (!valid){
        printf("Silakan masukkan nomor pilihan Anda!\n"); 
        printf(">> "); scanf("%d", &option);
        if (option == 1 || option == 2){
            valid = true;
        } else {
            printf("Masukan tidak valid!\n");
        }
    }

    if (option == 1){ //  Jika input dari file
        printf("Masukan Anda adalah dari file\n");
    } else { //  Jika input dari CLI (setelah validasi, hanya mungkin option == 2)
        printf("Masukan Anda adalah dari CLI\n");
        printf("Masukkan banyaknya token unik yang ingin dijadikan matrix sequence\n");
        printf(">> "); scanf("%d", &cntToken);
        
        // membuat array untuk menyimpan token unik
        createArray(&seqArray, cntToken);

        printf("Masukkan token unik yang ingin dijadikan matrix sequence\n");
        for (i = 0; i < cntToken; i++){
            scanf("%s", Word);
            insertLast(&seqArray, Word);
        }

        printf("Masukkan ukuran buffer yang diinginkan\n");
        printf(">> "); scanf("%d", &bufferSize);

        printf("Masukkan ukuran matrix sequence yang diinginkan\n");
        printf(">> "); scanf("%d %d", &mtxHeight, &mtxWidth);

        printf("Masukkan banyaknya sequence yang diinginkan\n");
        printf(">> "); scanf("%d", &cntSeq);

        printf("Masukkan ukuran maksimal sequence yang diinginkan\n");
        printf(">> "); scanf("%d", &maxSeqSize);
    }

    return 0;
}

/* --- Dummy Driver --- */
// int main(){
//     strArray ArrayString;
//     strMatrix MatrixString;
//     strStack StackString;
//     char word[100];
//     int i, j, arrLen, matRow, matCol, stackCap;
//     arrLen = 2;
//     matRow = 2; 
//     matCol = 2;
//     stackCap = 10;
//     createArray(&ArrayString, arrLen);
//     createMatrix(&MatrixString, matRow, matCol);
//     createStack(&StackString, stackCap);
//     for (i = 0; i < 2; i++){
//         scanf("%s", word);
//         insertLast(&ArrayString, word);
//     }
//     for (i = 0; i < 2; i++){
//         printf("%s\n", ArrayString.buffer[i]);
//     }
//     for (i = 0; i < matRow; i++){
//         MatrixString.buffer[i] = ArrayString;
//     }
//     for (i = 0; i < matRow; i++){
//         for (j = 0; j < matCol; j++){
//             printf("%s ", MatrixString.buffer[i].buffer[j]);
//         }
//         printf("\n");
//     }
//     for (i = 0; i < 2; i++){
//         scanf("%s", word);
//         push(&StackString, word);
//     }
//     for (i = 0; i < 2; i++){
//         printf("%s\n", StackString.buffer[i]);
//     }
//     printf("%s\n", StackString.buffer[StackString.top]);
//     pop(&StackString, word);
//     printf("%s\n", StackString.buffer[StackString.top]);

//     return 0;
// }