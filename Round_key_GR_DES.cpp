#include <iostream>

using namespace std;

// Function prototypes
void permute(int inSize, int outSize, int inKey[], int outKey[], int permutationTable[]);
void split(int inSize, int halfSize, int inKey[], int leftKey[], int rightKey[]);
void shiftLeft(int block[], int numOfShifts);
void combine(int inSize1, int inSize2, int leftKey[], int rightKey[], int preRoundKey[]);

void Key_Generator(int keyWithParities[], int RoundKeys[][48], int ShiftTable[], int ParityDropTable[], int KeyCompressionTable[]) {
    int cipherKey[56];
    int leftKey[28];
    int rightKey[28];
    int preRoundKey[56];

    permute(64, 56, keyWithParities, cipherKey, ParityDropTable);
    split(56, 28, cipherKey, leftKey, rightKey);

    for (int round = 0; round < 16; round++) {
        shiftLeft(leftKey, ShiftTable[round]);
        shiftLeft(rightKey, ShiftTable[round]);
        combine(28, 56, leftKey, rightKey, preRoundKey);
        permute(56, 48, preRoundKey, RoundKeys[round], KeyCompressionTable);
    }
}

void permute(int inSize, int outSize, int inKey[], int outKey[], int permutationTable[]) {
    for (int i = 0; i < outSize; i++) {
        outKey[i] = inKey[permutationTable[i] - 1];
    }
}

void split(int inSize, int halfSize, int inKey[], int leftKey[], int rightKey[]) {
    for (int i = 0; i < halfSize; i++) {
        leftKey[i] = inKey[i];
        rightKey[i] = inKey[i + halfSize];
    }
}

void shiftLeft(int block[], int numOfShifts) {
    for (int shift = 0; shift < numOfShifts; shift++) {
        int temp = block[0];
        for (int j = 1; j < 28; j++) {
            block[j - 1] = block[j];
        }
        block[27] = temp;
    }
}

void combine(int inSize1, int inSize2, int leftKey[], int rightKey[], int preRoundKey[]) {
    for (int i = 0; i < inSize1; i++) {
        preRoundKey[i] = leftKey[i];
        preRoundKey[i + inSize1] = rightKey[i];
    }
}

int main() {
    // Define necessary data structures and tables
    int keyWithParities[64] = {
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0
};
 int RoundKeys[16][48];
int ShiftTable[16] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16
};

int ParityDropTable[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int KeyCompressionTable[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};


    // Call Key_Generator function
    Key_Generator(keyWithParities, RoundKeys, ShiftTable, ParityDropTable, KeyCompressionTable);

       for (int i = 0; i < 16; i++) {
        cout << "Round " << i+1 << " Key: ";
        for (int j = 0; j < 48; j++) {
            cout << RoundKeys[i][j];
        }
        cout << endl;
    }
    // Output or further processing
    return 0;
}
