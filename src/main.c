#include "cyberpunkhack.c"

/* --- Program Utama --- */
int main(){
    /* KAMUS */
    int i, j, k, bufferSize, mtxHeight, mtxWidth, cntSeq, option, cntToken, maxSeqSize, randomInt, reward, tempSeqLength, maxReward, currReward;
    char Word[100];
    intArray seqSize, seqReward;
    strArray seqArray, bufferSolution;
    strMatrix sequences, tokenMatrix;
    pointArray solutionCoordinate;
    boolean valid, vertical, horizontal;

    /* ALGORITMA PROGRAM UTAMA */
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
            if (isInStrArray(seqArray, Word)){
                do {
                    printf("Token harus unik! Silakan masukkan ulang token!\n");
                    scanf("%s", Word);
                } while (isInStrArray(seqArray, Word));
            }
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
        printf("\nBerikut merupakan matrix sequence random\n");
        displayMatrix(tokenMatrix);

        // membuat random sequence
        createStringMatrix(&sequences, cntSeq, maxSeqSize + 2);
        createIntArray(&seqSize, cntSeq);
        createIntArray(&seqReward, cntSeq);
        for (i = 0; i < cntSeq; i++){
            // panjang sequence random
            tempSeqLength = (rand() % maxSeqSize) + 1;
            seqSize.buffer[i] = tempSeqLength;

            // sequence random
            for (j = 0; j < tempSeqLength; j++){
                randomInt = rand() % cntToken;
                sequences.buffer[i].buffer[j] = seqArray.buffer[randomInt];
            }
            while (isSequenceDup(sequences, seqSize, sequences.buffer[i], tempSeqLength, i)){ // loop untuk memeriksa sequence duplikat
                for (j = 0; j < tempSeqLength; j++){
                    randomInt = rand() % cntToken;
                    sequences.buffer[i].buffer[j] = seqArray.buffer[randomInt];
                }
            }

            // hadiah sequence random berupa integer kelipatan 5 pada range -50 sampai 50
            randomInt = ((rand() % 10) + 1) * 5;
            reward = randomInt;
            randomInt = rand() % 5;
            if (randomInt == 1){ // jika randomInt == 1, maka reward sequence negatif (peluang 1/5 untuk mendapatkan reward negatif)
                reward = -reward;
            }
            seqReward.buffer[i] = reward;
        }
        printf("\nBerikut merupakan sequence unik dan reward random\n");
        displaySeqAndReward(sequences, seqSize, seqReward);
        printf("\n");
    }

    // algoritma brute force untuk mencari solusi optimal
    vertical = true;
    horizontal = false;
    createStringArray(&bufferSolution, bufferSize);
    createPointArray(&solutionCoordinate, bufferSize);
    for (i = 0; i < tokenMatrix.col; i++){
        insertLastPointArr(&solutionCoordinate, 0, i);
        // [PENTING] cek ada di sequences atau engga [PENTING]

        while (solutionCoordinate.nEff <= solutionCoordinate.maxLen){
            if (vertical){
                for (j = 0; j < tokenMatrix.row; j++){
                    
                }
            } else {
                // something
            }

            // [PENTING] cek ada di sequences atau engga [PENTING]
        }
    }

    // menyimpan hasil ke dalam file
    printf("Apakah Anda ingin menyimpan solusi ke dalam file .txt?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
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

    return 0;
}