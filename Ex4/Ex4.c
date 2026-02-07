#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "Vector.h"

#define MAX_INPUT_LEN 100


void DynamicArrayInsert(void** arr, void* value, int* size);
void* mybsearch(const void* key, const void* base, int arrLen, size_t elementSize, int (*compare)(const void*, const void*));
int compareByBits(const void* e1, const void* e2);
int findByBitSequence(const void* e1, const void* e2);

int main() {
    char input[MAX_INPUT_LEN];
    char temp;
	void** dynArr;
    void* searchResult;
	int dynArrLen = 0;
    int n;
    int searchSequenceLength;
    int i = 0;
    FILE* fptr;
    LIST l1,l2;
    printf("Please enter the string:\n");
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[strlen(input)-1] == '\n') {
        input[strlen(input)-1] = 0;
    }

    if ((fptr = fopen("1.dat", "wb")) == NULL) {
        printf("error opening file");
        return 0;
    }
    fwrite(&input, sizeof(char), strlen(input), fptr);
    fclose(fptr);

    if ((fptr = fopen("1.dat", "rb")) == NULL) {
        printf("error opening file");
        return 0;
    }
	L_init(&l1);
	L_init(&l2);
    while ((n = fread(&temp, sizeof(char), 1, fptr))>0) {
        if (i % 2 == 0)
            L_insert(&l1.head, temp);
        else
            L_insert(&l2.head, temp);
        i++;
	}
    if (l1.head.next != NULL && l2.head.next==NULL)
    {
        /*
        dynArr = (void*)malloc(sizeof(l1.head.next->key));
		dynArrSize = 1;
		dynArr[0] = l1.head.next->key;
		L_delete(&l1.head);
        */
		DynamicArrayInsert(&dynArr, &l1.head.next->key, &dynArrLen);
        
    }
    /*
    while (l1.head.key != NULL && l2.head.key != NULL)
    {
        if (dynArr == NULL)
        {
            dynArr = malloc(2*sizeof(l1.head.key));
            dynArrSize = 2;
        }
        else
        {
            dynArr = realloc(dynArr, (sizeof(l1.head.key) * dynArrSize + 2) * sizeof(char));
			dynArrSize += 2;
        }

    }
    */
    /*
    for (int i = 7; i >= 0; --i)
    {
        putchar((temp & (1 << i)) ? '1' : '0');
    }
    printf("\n");
    */
    qsort(dynArr, dynArrLen, sizeof(dynArr[0]), compareByBits);
    printf("Please enter the sequence length to search for (unsigned number): ");
    scanf("%d", &searchSequenceLength);
    searchResult = mybsearch(3, dynArr, dynArrLen, sizeof(dynArr[0]), findByBitSequence);
    if (searchResult == NULL) {
        printf("no fitting character was found\nGoodbye!");
        return 0;
    }
    printf("character %c has been found!", (char)searchResult);
    fclose(fptr);
    return 0;
}

void DynamicArrayInsert(void** arr, void* value, int* size) {
    if (*arr == NULL) {
        *arr = malloc(sizeof(value));
        (*size) = 1;
    }
    else {
        *arr = realloc(*arr, sizeof(value) * (*size + 1));
        (*size)++;
    }
	memcpy((char*)(*arr) + sizeof(value) * ((*size) - 1), value, sizeof(value));
}

void* mybsearch(const void* key, const void* base, int arrLen, size_t elementSize, int (*compare)(const void*, const void*)) {
    size_t start = 0;
    size_t end = arrLen;

    while (start < end) {
        size_t mid = start + (end - start) / 2;

        const void* element = (const char*)base + mid * elementSize;

        int res = compare(key, element);

        if (res == 0) {
            return (void*)element;
        }
        else if (res < 0) {
            end = mid;
        }
        else {
            start = mid + 1;
        }
    }
    return NULL;
}

int compareByBits(const void* e1, const void* e2) {
    unsigned char b1 = *(const unsigned char*)e1;
    unsigned char b2 = *(const unsigned char*)e2;

	int maxBitsChainE1 = 0, maxBitsChainE2 = 0;
	int bitCounter1 = 0, bitCounter2 = 0;
    for (int i = 7; i >= 0; --i) {
        if(b1 & (1 << i))
        {
            bitCounter1++;
            if (bitCounter1 > maxBitsChainE1)
                maxBitsChainE1 = bitCounter1;
        }
        else
			bitCounter1 = 0;
        if(b2 & (1 << i))
        {
            bitCounter2++;
            if (bitCounter2 > maxBitsChainE2)
                maxBitsChainE2 = bitCounter2;
        }
		else
			bitCounter2 = 0;
    }
	return maxBitsChainE1 - maxBitsChainE2;
}

int findByBitSequence(const void* e1, const void* e2) {
    unsigned int bitSeq = (const unsigned int)e1;
    unsigned char checkElement = *(const unsigned char*)e2;
    int maxBitsChainE1 = 0;
    int bitCounter1 = 0;
    for (int i = 7; i >= 0; --i) {
        if (checkElement & (1 << i))
        {
            bitCounter1++;
            if (bitCounter1 > maxBitsChainE1)
                maxBitsChainE1 = bitCounter1;
        }
        else
            bitCounter1 = 0;
    }
    return bitSeq - maxBitsChainE1;
}