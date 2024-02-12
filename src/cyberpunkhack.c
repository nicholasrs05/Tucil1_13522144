#include <stdlib.h>
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

void displayPointArray(pointArray Arr){
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    for (i = 0; i < Arr.nEff; i++){
        printf("(%d, %d) ", Arr.buffer[i].X, Arr.buffer[i].Y);
    }
    printf("\n");
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
        printf("dengan reward %d dan panjang %d\n", Reward.buffer[i], Seq.buffer[i]);
    }
}

void copyPointArray(pointArray Arr1, pointArray *Arr2){
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    createPointArray(Arr2, Arr1.maxLen);
    for (i = 0; i < Arr1.nEff; i++){
        (*Arr2).buffer[i] = Arr1.buffer[i];
    }
    (*Arr2).nEff = Arr1.nEff;
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

int addReward(strMatrix Mat, intArray Seq, intArray Reward, pointArray Arr, strMatrix tokenMat){
    /* KAMUS LOKAL */
    int i, j, k, reward;
    boolean equal, used;

    /* ALGORITMA */
    reward = 0;
    for (i = 0; i < Mat.row; i++){ // loop setiap sequence
        used = false;
        if (Seq.buffer[i] <= Arr.nEff){ // jika panjang jalur saat ini lebih besar atau sama dengan dibanding sequence saat ini, akan dicek kesamaan
            for (j = 0; j < (Arr.nEff - Seq.buffer[i]) + 1; j++){ // loop sequence untuk menemukan kesamaan
                equal = false;
                for (k = 0; k < Seq.buffer[i]; k++){ // menyamakan tiap elemen
                    if (tokenMat.buffer[Arr.buffer[j + k].X].buffer[Arr.buffer[j + k].Y] == Mat.buffer[i].buffer[k]){
                        equal = true;
                    } else {
                        equal = false;
                        break;
                    }
                }
                if ((equal) && (!used)){ // jika ada sequence yang sama dan belum terpakai, tambahkan reward
                    reward += Reward.buffer[i];
                    used = true;
                }
            }
        }
    }
    return reward;
}

void recursiveTraverse(strMatrix seqMat, intArray Seq, intArray Reward, pointArray *Arr, strMatrix tokenMat, int *maxReward, pointArray *maxArr, int currX, int currY, boolean vertical){
    /* KAMUS LOKAL */
    int currReward, i;

    /* ALGORITMA */
    if ((*Arr).nEff == (*Arr).maxLen){ // Basis
        currReward = addReward(seqMat, Seq, Reward, *Arr, tokenMat);
        if (currReward > *maxReward){
            // printf("Rute saat ini: "); displayPointArray(*Arr);
            // printf("Solusi baru dengan reward %d\n", currReward);
            *maxReward = currReward;
            copyPointArray(*Arr, maxArr);
        }
    } else { // Rekurens
        if (vertical){
            for (i = 0; i < tokenMat.row; i++){
                if (!isInPointArray(*Arr, i, currY)){
                    insertLastPointArr(Arr, i, currY);
                    if (addReward(seqMat, Seq, Reward, *Arr, tokenMat) > *maxReward){
                        // printf("Rute saat ini: "); displayPointArray(*Arr);
                        // printf("Rute ini rewardnya %d\n", addReward(seqMat, Seq, Reward, *Arr, tokenMat));
                        *maxReward = addReward(seqMat, Seq, Reward, *Arr, tokenMat);
                        copyPointArray(*Arr, maxArr);
                    }
                    recursiveTraverse(seqMat, Seq, Reward, Arr, tokenMat, maxReward, maxArr, i, currY, !vertical);
                    (*Arr).nEff--;
                }
            }
        } else {
            for (i = 0; i < tokenMat.col; i++){
                if (!isInPointArray(*Arr, currX, i)){
                    insertLastPointArr(Arr, currX, i);
                    if (addReward(seqMat, Seq, Reward, *Arr, tokenMat) > *maxReward){
                        // printf("Rute saat ini: "); displayPointArray(*Arr);
                        // printf("Rute ini rewardnya %d\n", addReward(seqMat, Seq, Reward, *Arr, tokenMat));
                        *maxReward = addReward(seqMat, Seq, Reward, *Arr, tokenMat);
                        copyPointArray(*Arr, maxArr);
                    }
                    recursiveTraverse(seqMat, Seq, Reward, Arr, tokenMat, maxReward, maxArr, currX, i, !vertical);
                    (*Arr).nEff--;
                }
            }
        }
    }
}