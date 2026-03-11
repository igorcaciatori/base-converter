#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hexCharToVal(char c);

char* decToBin(int n);
char* decToHex(int n);
int binToDec(char* n);
char* binToHex(char* n);
int hexToDec(char* n);
char* hexToBin(char* n);

int main() {
    int origin, destiny;
    char number[64];

    printf("Origin system (2=Binary, 10=Decimal, 16=Hexadecimal): ");
    scanf("%i", &origin);

    if (origin != 2 && origin != 10 && origin != 16) {
        printf("Invalid base.\n");
        return 1;
    }

    printf("Destiny system (2=Binary, 10=Decimal, 16=Hexadecimal): ");
    scanf("%i", &destiny);

    if (destiny != 2 && destiny != 10 && destiny != 16) {
        printf("Invalid base.\n");
        return 1;
    }

    if (origin == destiny) {
        printf("Origin and destiny cannot be equal.\n");
        return 1;
    }

    printf("Number: ");
    scanf("%63s", number);
    int len = strlen(number);

    for (int i = 0; i < len; i++)
        if (number[i] >= 'a' && number[i] <= 'f')
            number[i] -= 32;

    for (int i = 0; i < len; i++) {
        int ok = 0;
        if (origin == 2)  
            ok = (number[i] == '0' || number[i] == '1');
        if (origin == 10) 
            ok = (number[i] >= '0' && number[i] <= '9');
        if (origin == 16) 
            ok = (number[i] >= '0' && number[i] <= '9') || (number[i] >= 'A' && number[i] <= 'F');
        if (!ok) {
            printf("Invalid number for base %i.\n", origin);
            return 1;
        }
    }

    char* res = NULL;
    if (origin == 2  && destiny == 10) { 
        printf("%s to decimal: %i\n", number, binToDec(number));
        return 0;
    }
    else if (origin == 2  && destiny == 16) 
        res = binToHex(number);
    else if (origin == 10 && destiny == 2)
        res = decToBin(atoi(number));
    else if (origin == 10 && destiny == 16)
        res = decToHex(atoi(number));
    else if (origin == 16 && destiny == 2)
        res = hexToBin(number);
    else if (origin == 16 && destiny == 10) { 
        printf("%s to decimal: %i\n", number, hexToDec(number)); 
        return 0; 
    }

    printf("Result: %s\n", res);
    free(res);
    return 0;
}

char* decToBin(int n) {
    char* res = malloc(33);
    char bin[32];
    int tam = 0;

    while (n > 0) {
        bin[tam++] = (n % 2) + '0';
        n = n / 2;
    }

    int i = 0;
    for (int j = tam - 1; j >= 0; j--) {
        res[i] = bin[j];
        i++;
    }

    res[i] = '\0';
    return res;
}


char* decToHex(int n) {
    char* res = malloc(33);
    char hex[32];
    int i = 0;

    while (n > 0) {
        int num = n % 16;
        if (num >= 0 && num <= 9) hex[i] = num + '0';
        if (num >= 10 && num <= 15) hex[i] = num - 10 + 'A';
        i++;
        n /= 16;
    }

    int k = 0;
    for (int j = i - 1; j >= 0; j--) {
        res[k] = hex[j];
        k++;
    }
    res[k] = '\0';
    return res;
}

int binToDec(char* n) {
    int res = 0;
    int len = strlen(n);
    for (int i = 0; i < len; i++)
        res = res * 2 + (n[i] - '0');
    return res;
}

char* binToHex(char* n) {
    int dec = binToDec(n);
    char* res = decToHex(dec);
    return res;
}

int hexToDec(char* n) {
    int res = 0;
    int len = strlen(n);
    for (int i = 0; i < len; i++) {
        int val = hexCharToVal(n[i]);
        res = res * 16 + val;
    }
    return res;
}

char* hexToBin(char* n) {
    char* res = calloc(128, 1);
    int len = strlen(n);

    for (int i = 0; i < len; i++) {
        int val = hexCharToVal(n[i]);
        char* tmp = decToBin(val);
        strcat(res, tmp);
        free(tmp);
    }
    return res;
}

int hexCharToVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}