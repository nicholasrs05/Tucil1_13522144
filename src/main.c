#include <time.h>
#include <unistd.h>
#include "cyberpunkhack.c"

/* --- Program Utama --- */
int main(){
    /* KAMUS */
    int i, j, k, bufferSize, mtxHeight, mtxWidth, cntSeq, option, cntToken, maxSeqSize, randomInt, reward, tempSeqLength, maxReward, currReward, maxPossible, nlIdx;
    char Word[100], fileName[200], line[100], filePath[200];
    char *token;
    intArray seqSize, seqReward;
    strArray seqArray, bufferSolution;
    strMatrix sequences, tokenMatrix;
    pointArray solutionCoordinate, maxArr;
    boolean valid, fileCheck;
    clock_t start, end;
    double interval;
    FILE *filePointer;

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

        // input nama file
        valid = false;
        while (!valid){
            printf("Silakan masukkan nama file yang ingin Anda buka (maksimal 200 karakter, jangan lupa tambahkan .txt pada akhir nama file)\n");
            printf(">> "); scanf("%199s", fileName);
            
            sprintf(filePath, "../test/%s", fileName);
            filePointer = fopen(filePath, "r");
            if (filePointer == NULL){
                printf("File tidak ditemukan! Silakan masukkan nama file yang benar!\n");
            } else {
                valid = true;
            }
        }

        // membaca input dari file
        fscanf(filePointer, "%d", &bufferSize);
        if (bufferSize <= 0){
            printf("Ukuran buffer tidak valid.\n");
            printf("Program akan dihentikan dalam 5 detik, silakan perbaiki file input.\n");
            sleep(5);
            return 0;
        }

        fscanf(filePointer, "%d %d", &mtxHeight, &mtxWidth);
        if ((mtxHeight <= 0) || (mtxWidth <= 0)){
            printf("Ukuran matrix tidak valid.\n");
            printf("Program akan dihentikan dalam 5 detik, silakan perbaiki file input.\n");
            sleep(5);
            return 0;
        }

        createStringMatrix(&tokenMatrix, mtxHeight, mtxWidth);
        for (i = 0; i < mtxHeight; i++){
            for (j = 0; j < mtxWidth; j++){
                fscanf(filePointer, "%s", Word);
                if (strlen(Word) != 2){
                    printf("Panjang token harus 2.\n");
                    printf("Kesalahan ada pada baris %d kolom %d -> %s\n", i + 1, j + 1, Word);
                    printf("Program akan dihentikan dalam 5 detik, silakan perbaiki file input.\n");
                    sleep(5);
                    return 0;
                }
                tokenMatrix.buffer[i].buffer[j] = strdup(Word);
            }
        }

        fscanf(filePointer, "%d", &cntSeq);
        if (cntSeq <= 0){
            printf("Banyaknya sequence tidak valid.\n");
            printf("Program akan dihentikan dalam 5 detik, silakan perbaiki file input.\n");
            sleep(5);
            return 0;
        }

        createStringMatrix(&sequences, cntSeq, mtxWidth);
        createIntArray(&seqSize, cntSeq);
        createIntArray(&seqReward, cntSeq);
        for (i = 0; i < cntSeq; i++){
            do {
                fgets(line, sizeof(line), filePointer);
            } while (strcmp(line, "\n") == 0);

            token = strtok(line, " ");
            j = 0;
            while (token != NULL) {
                nlIdx = strcspn(token, "\n");
                if (token[nlIdx] == '\n'){
                    token[nlIdx] = '\0';
                }
                if (strlen(token) != 2){
                    printf("Panjang token harus 2.\n");
                    printf("Kesalahan ada pada baris %d -> %s\n", i + 1, token);
                    printf("Program akan dihentikan dalam 5 detik, silakan perbaiki file input.\n");
                    sleep(5);
                    return 0;
                }
                sequences.buffer[i].buffer[j] = strdup(token);
                j++;
                token = strtok(NULL, " ");
            }
            seqSize.buffer[i] = j;
            if (fscanf(filePointer, "%d", &seqReward.buffer[i]) == 1){
                fscanf(filePointer, "%d", &seqReward.buffer[i]);
            } else {
                printf("Reward sequence ke-%d tidak valid.\n", i + 1);
                printf("Program akan dihentikan dalam 5 detik, silakan perbaiki file input.\n");
                sleep(5);
                return 0;
            }
        }

        fclose(filePointer);

        printf("\nBerikut merupakan matrix sequence dari file\n");
        displayMatrix(tokenMatrix);

        printf("\nBerikut merupakan sequence unik dan reward random\n");
        displaySeqAndReward(sequences, seqSize, seqReward);
        printf("\n");

    } else { //  Jika input dari CLI (setelah validasi, hanya mungkin option == 2)
        printf("Masukan Anda adalah dari CLI\n");

        valid = false;
        while (!valid){ // validasi banyaknya token unik (harus lebih dari 0)
            printf("Masukkan banyaknya token unik yang ingin dijadikan matrix sequence\n");
            printf(">> "); scanf("%d", &cntToken);
            if (cntToken > 0){
                valid = true;
            } else {
                printf("Banyaknya token unik harus lebih dari 0!\n");
            }
        }
        
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
            if (strlen(Word) != 2){
                do {
                    printf("Panjang token harus 2! Silakan masukkan ulang token!\n");
                    scanf("%s", Word);
                } while (strlen(Word) != 2);
            }
            insertLastStrArr(&seqArray, Word);
        }

        valid = false;
        while (!valid){
            printf("Masukkan ukuran buffer yang diinginkan\n");
            printf(">> "); scanf("%d", &bufferSize);
            if (bufferSize > 0){
                valid = true;
            } else {
                printf("Ukuran buffer harus lebih dari 0!\n");
            }
        }

        valid = false;
        while (!valid){
            printf("Masukkan ukuran matrix sequence yang diinginkan\n");
            printf(">> "); scanf("%d %d", &mtxHeight, &mtxWidth);
            if ((mtxHeight > 0) && (mtxWidth > 0)){
                valid = true;
            } else {
                printf("Ukuran matrix harus lebih dari 0!\n");
            }
        }

        valid = false;
        while (!valid){
            printf("Masukkan banyaknya sequence yang diinginkan\n");
            printf(">> "); scanf("%d", &cntSeq);
            if (cntSeq > 0){
                valid = true;
            } else {
                printf("Banyaknya sequence harus lebih dari 0!\n");
            }
        }

        valid = false;
        while (!valid){
            printf("Masukkan ukuran maksimal sequence yang diinginkan\n");
            printf(">> "); scanf("%d", &maxSeqSize);
            if (maxSeqSize > 0){
                valid = true;
            } else {
                printf("Ukuran maksimal sequence harus lebih dari 0!\n");
            }
        }

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
        createStringMatrix(&sequences, cntSeq, maxSeqSize);
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

    // time keeper
    start = clock();

    // algoritma brute force untuk mencari solusi optimal
    currReward = 0;
    maxReward = 0;
    createStringArray(&bufferSolution, bufferSize);
    createPointArray(&solutionCoordinate, bufferSize);
    for (i = 0; i < tokenMatrix.col; i++){
        solutionCoordinate.buffer[0].X = 0;
        solutionCoordinate.buffer[0].Y = i;
        solutionCoordinate.nEff = 1;
        currReward = addReward(sequences, seqSize, seqReward, solutionCoordinate, tokenMatrix);
        if (currReward > maxReward){
            createPointArray(&maxArr, bufferSize);
            maxReward = currReward;
            copyPointArray(solutionCoordinate, &maxArr);
        }
        recursiveTraverse(sequences, seqSize, seqReward, &solutionCoordinate, tokenMatrix, &maxReward, &maxArr, 0, i, true);
    }

    // time keeper
    end = clock();
    interval = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    if (maxReward <= 0){
        maxReward = 0;
        printf("Tidak ada solusi!\n");
    } else {
        printf("%d\n", maxReward);
        for (i = 0; i < maxArr.nEff; i++){
            printf("%s ", tokenMatrix.buffer[maxArr.buffer[i].X].buffer[maxArr.buffer[i].Y]);
        }
        printf("\n");
        for (i = 0; i < maxArr.nEff; i++){
            printf("%d, %d\n", maxArr.buffer[i].Y + 1, maxArr.buffer[i].X + 1);
        }
        printf("\n");
    }
    printf("%f ms\n", interval);

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
    if (option == 1){
        printf("Masukkan nama file yang diinginkan (maksimal 200 karakter, jangan lupa tambahkan .txt pada akhir nama file)\n");
        printf(">> "); scanf("%199s", fileName);

        sprintf(filePath, "../test/%s", fileName);
        filePointer = fopen(filePath, "w");
        
        if (maxReward > 0){
            fprintf(filePointer, "%d\n", maxReward);
            for (i = 0; i < maxArr.nEff; i++){
                fprintf(filePointer, "%s ", tokenMatrix.buffer[maxArr.buffer[i].X].buffer[maxArr.buffer[i].Y]);
            }

            fprintf(filePointer, "\n");

            for (i = 0; i < maxArr.nEff; i++){
                fprintf(filePointer, "%d, %d\n", maxArr.buffer[i].Y + 1, maxArr.buffer[i].X + 1);
            }
        } else {
            fprintf(filePointer, "Tidak ada solusi!\n");
        }


        fprintf(filePointer, "\n");
        fprintf(filePointer, "%f ms\n", interval);

        fclose(filePointer);
    }

    return 0;
}