#include <stdlib.h>
#include <time.h>
#include "cyberpunkhack.h"
#include "boolean.h"

/* --- Realisasi Fungsi dan Prosedur --- */
void createIntArray(intArray *Arr, int length){
    (*Arr).buffer = (int*) malloc (length * sizeof(int));
    (*Arr).nEff = 0;
    (*Arr).maxLen = length;
}

void createStringArray(strArray *Arr, int length){
    (*Arr).buffer = (char**) malloc (length * sizeof(char*));
    (*Arr).nEff = 0;
    (*Arr).maxLen = length;
}

void createStringMatrix(strMatrix *Mat, int height, int width){
    int i;
    (*Mat).buffer = (strArray*) malloc (height * sizeof(strArray));
    for (i = 0; i < height; i++){
        createStringArray(&(*Mat).buffer[i], width);
    }
    (*Mat).row = height;
    (*Mat).col = width;
}

void createStack(strStack *Stack, int capacity){
    (*Stack).buffer = (char**) malloc (capacity * sizeof(char*));
    (*Stack).top = -1;
}

void createPoint(point *P, int X, int Y){
    (*P).X = X;
    (*P).Y = Y;
}

void createPointArray(pointArray *Arr, int length){
    (*Arr).buffer = (point*) malloc (length * sizeof(point));
    (*Arr).nEff = 0;
    (*Arr).maxLen = length;
}

void insertLastStrArr(strArray *Arr, char *str){
    if ((*Arr).nEff == (*Arr).maxLen){
        printf("Array penuh!\n");
    } else {
        (*Arr).buffer[(*Arr).nEff] = (char*) malloc (100 * sizeof(char));
        strcpy((*Arr).buffer[(*Arr).nEff], str);
        (*Arr).nEff++;
    }
}

void push(strStack *Stack, char *str){
    (*Stack).top++;
    (*Stack).buffer[(*Stack).top] = (char*) malloc (100 * sizeof(char));
    strcpy((*Stack).buffer[(*Stack).top], str);
}

void pop(strStack *Stack, char *str){
    (*Stack).top--;
}

void displayArray(strArray Arr){
    int i;
    for (i = 0; i < Arr.nEff; i++){
        printf("%s ", Arr.buffer[i]);
    }
    printf("\n");
}

void displayMatrix(strMatrix Mat){
    int i, j;
    for (i = 0; i < Mat.row; i++){
        for (j = 0; j < Mat.col; j++){
            printf("%s ", Mat.buffer[i].buffer[j]);
        }
        printf("\n");
    }
}

void displaySeqAndReward(strMatrix Mat, intArray Seq, intArray Reward){
    int i, j;
    for (i = 0; i < Mat.row; i++){
        printf("Sequence %d: ", i + 1);
        for (j = 0; j < Seq.buffer[i]; j++){
            printf("%s ", Mat.buffer[i].buffer[j]);
        }
        printf("dengan reward: %d\n", Reward.buffer[i]);
    }
}

/* --- Program Utama --- */
int main(){
    int i, j, k, bufferSize, mtxHeight, mtxWidth, cntSeq, option, cntToken, maxSeqSize, randomInt, reward, tempSeqLength;
    intArray seqSize, seqReward;
    strArray seqArray, tempRow;
    strMatrix sequences, tokenMatrix;
    char Word[100];
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
        // something

    } else { //  Jika input dari CLI (setelah validasi, hanya mungkin option == 2)
        printf("Masukan Anda adalah dari CLI\n");
        printf("Masukkan banyaknya token unik yang ingin dijadikan matrix sequence\n");
        printf(">> "); scanf("%d", &cntToken);
        
        // membuat array untuk menyimpan token unik
        createStringArray(&seqArray, cntToken);

        // menerima input dari user
        printf("Masukkan token unik yang ingin dijadikan matrix sequence\n");
        for (i = 0; i < cntToken; i++){
            scanf("%s", Word);
            insertLastStrArr(&seqArray, Word);
        }

        printf("Masukkan ukuran buffer yang diinginkan\n");
        printf(">> "); scanf("%d", &bufferSize);

        printf("Masukkan ukuran matrix sequence yang diinginkan\n");
        printf(">> "); scanf("%d %d", &mtxHeight, &mtxWidth);

        printf("Masukkan banyaknya sequence yang diinginkan\n");
        printf(">> "); scanf("%d", &cntSeq);

        printf("Masukkan ukuran maksimal sequence yang diinginkan\n");
        printf(">> "); scanf("%d", &maxSeqSize);

        // membuat matrix random
        createStringMatrix(&tokenMatrix, mtxHeight, mtxWidth);
        srand(time(NULL));
        for (i = 0; i < mtxHeight; i++){
            for (j = 0; j < mtxWidth; j++){
                randomInt = rand() % cntToken;
                tokenMatrix.buffer[i].buffer[j] = seqArray.buffer[randomInt];
            }
        }
        displayMatrix(tokenMatrix);

        // membuat random sequence
        createStringMatrix(&sequences, cntSeq, maxSeqSize + 2);
        createIntArray(&seqSize, cntSeq);
        createIntArray(&seqReward, cntSeq);
        for (i = 0; i < cntSeq; i++){
            tempSeqLength = (rand() % maxSeqSize) + 1;
            seqSize.buffer[i] = tempSeqLength;
            for (j = 0; j < tempSeqLength; j++){
                randomInt = rand() % cntToken;
                sequences.buffer[i].buffer[j] = seqArray.buffer[randomInt];
            }
            randomInt = ((rand() % 10) + 1) * 5; // hadiah sequence random berupa integer kelipatan 5 pada range 5 - 50
            reward = randomInt;
            randomInt = rand() % 2;
            if (randomInt == 1){ // jika randomInt == 1, maka reward sequence negatif
                reward = -reward;
            }
            seqReward.buffer[i] = reward;
        }
        displaySeqAndReward(sequences, seqSize, seqReward);
    }

    return 0;
}

/* --- Dummy Driver --- */
// int main(){
//     strArray ArrayString;
//     strMatrix MatrixString;
//     strStack StackString;
//     point P;
//     pointArray ArrayPoint;
//     char word[100];
//     int i, j, arrLen, matRow, matCol, stackCap, random;
//     arrLen = 3;
//     matRow = 2; 
//     matCol = 2;
//     stackCap = 10;
//     createStringArray(&ArrayString, arrLen);
//     createStringMatrix(&MatrixString, matRow, matCol);
//     createStack(&StackString, stackCap);
//     for (i = 0; i < 2; i++){
//         scanf("%s", word);
//         insertLastStrArr(&ArrayString, word);
//     }
//     for (i = 0; i < 2; i++){
//         printf("%s\n", ArrayString.buffer[i]);
//     }
//     MatrixString.buffer[0] = ArrayString;
//     ArrayString.buffer[0] = "A";
//     ArrayString.buffer[1] = "B";
//     MatrixString.buffer[1] = ArrayString;
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

//     srand(time(NULL));
//     random = rand();
//     printf("%d\n", (random % 6) + 1);

//     createStringMatrix(&MatrixString, matRow, matCol);
//     for (i = 0; i < matRow; i++){
//         for (j = 0; j < matCol; j++){
//             scanf("%s", word);
//             insertLastStrArr(&MatrixString.buffer[i], word);
//         }
//     }
//     displayMatrix(MatrixString);

//     createPointArray(&ArrayPoint, arrLen);
//     ArrayPoint.buffer[0].X = 1;
//     ArrayPoint.buffer[0].Y = 2;
//     ArrayPoint.buffer[1].X = 3;
//     ArrayPoint.buffer[1].Y = 4;
//     ArrayPoint.buffer[2].X = 5;
//     ArrayPoint.buffer[2].Y = 6;
//     printf("%d %d\n", ArrayPoint.buffer[0].X, ArrayPoint.buffer[0].Y);
//     printf("%d %d\n", ArrayPoint.buffer[1].X, ArrayPoint.buffer[1].Y);
//     printf("%d %d\n", ArrayPoint.buffer[2].X, ArrayPoint.buffer[2].Y);

//     return 0;
// }