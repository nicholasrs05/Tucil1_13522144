#include <stdlib.h>
#include <time.h>
#include "cyberpunkhack.h"

/* --- Realisasi Fungsi dan Prosedur --- */
void createIntArray(intArray *Arr, int length){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*Arr).buffer = (int*) malloc (length * sizeof(int));
    (*Arr).nEff = 0;
    (*Arr).maxLen = length;
}

void createStringArray(strArray *Arr, int length){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*Arr).buffer = (char**) malloc (length * sizeof(char*));
    (*Arr).nEff = 0;
    (*Arr).maxLen = length;
}

void createStringMatrix(strMatrix *Mat, int height, int width){
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    (*Mat).buffer = (strArray*) malloc (height * sizeof(strArray));
    for (i = 0; i < height; i++){
        createStringArray(&(*Mat).buffer[i], width);
    }
    (*Mat).row = height;
    (*Mat).col = width;
}

void createStack(strStack *Stack, int capacity){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*Stack).buffer = (char**) malloc (capacity * sizeof(char*));
    (*Stack).top = -1;
}

void createPoint(point *P, int X, int Y){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*P).X = X;
    (*P).Y = Y;
}

void createPointArray(pointArray *Arr, int length){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*Arr).buffer = (point*) malloc (length * sizeof(point));
    (*Arr).nEff = 0;
    (*Arr).maxLen = length;
}

void insertLastStrArr(strArray *Arr, char *str){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if ((*Arr).nEff == (*Arr).maxLen){
        printf("Array penuh!\n");
    } else {
        (*Arr).buffer[(*Arr).nEff] = (char*) malloc (100 * sizeof(char));
        strcpy((*Arr).buffer[(*Arr).nEff], str);
        (*Arr).nEff++;
    }
}

void insertLastPointArr(pointArray *Arr, int X, int Y){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if ((*Arr).nEff < (*Arr).maxLen){
        (*Arr).buffer[(*Arr).nEff].X = X;
        (*Arr).buffer[(*Arr).nEff].Y = Y;
        (*Arr).nEff++;
    }
}

void push(strStack *Stack, char *str){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*Stack).top++;
    (*Stack).buffer[(*Stack).top] = (char*) malloc (100 * sizeof(char));
    strcpy((*Stack).buffer[(*Stack).top], str);
}

void pop(strStack *Stack, char *str){
    /* KAMUS LOKAL */

    /* ALGORITMA */
    (*Stack).top--;
}

void displayArray(strArray Arr){
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    for (i = 0; i < Arr.nEff; i++){
        printf("%s ", Arr.buffer[i]);
    }
    printf("\n");
}

void displayMatrix(strMatrix Mat){
    /* KAMUS LOKAL */
    int i, j;

    /* ALGORITMA */
    for (i = 0; i < Mat.row; i++){
        for (j = 0; j < Mat.col; j++){
            printf("%s ", Mat.buffer[i].buffer[j]);
        }
        printf("\n");
    }
}

void displaySeqAndReward(strMatrix Mat, intArray Seq, intArray Reward){
    /* KAMUS LOKAL */
    int i, j;

    /* ALGORITMA */
    for (i = 0; i < Mat.row; i++){
        printf("Sequence %d: ", i + 1);
        for (j = 0; j < Seq.buffer[i]; j++){
            printf("%s ", Mat.buffer[i].buffer[j]);
        }
        printf("dengan reward: %d\n", Reward.buffer[i]);
    }
}

boolean isInStrArray(strArray Arr, char *Str){
    /* KAMUS LOKAL */
    int i;
    boolean isIn;

    /* ALGORITMA */
    i = 0;
    isIn = false;
    while ((i < Arr.nEff) && (!isIn)){
        if (strcmp(Arr.buffer[i], Str) == 0){
            isIn = true;
        }
        i++;
    }
    return isIn;
}

boolean isSequenceDup(strMatrix Mat, intArray Seq, strArray temp, int tempLen, int curr){
    /* KAMUS LOKAL */
    int i, j;
    boolean duplicate;

    /* ALGORITMA */
    i = 0;
    duplicate = false;
    while ((i < curr) && (!duplicate)){
        if (Seq.buffer[i] == tempLen){
            j = 0;
            duplicate = true;
            while ((j < tempLen) && (duplicate)){
                if (strcmp(Mat.buffer[i].buffer[j], temp.buffer[j]) == 0){
                    duplicate = true;
                } else {
                    duplicate = false;
                }
                j++;
            }
        }
        i++;
    }
    return duplicate;
}

boolean isInPointArray(pointArray Arr, int X, int Y){
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    if (Arr.nEff == 0){
        return false;
    } else {
        for (i = 0; i < Arr.nEff; i++){
            if ((Arr.buffer[i].X == X) && (Arr.buffer[i].Y) == Y){
                return true;
            }
        }
        return false;
    }
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