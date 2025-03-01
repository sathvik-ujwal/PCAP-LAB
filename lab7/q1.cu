#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

#define MAX_WORD_LEN 32
#define MAX_SENTENCE_LEN 256

__device__ bool str_cmp(const char *str1, const char *str2, int wordLen) {
    for (int i = 0; i < wordLen; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return (str1[wordLen] == ' ' || str1[wordLen] == '\0' || str1[wordLen] == '.' || str1[wordLen] == ',');
}

__global__ void countWordOccurrences(char *sentence, char *word, int *count, int sentenceLen, int wordLen) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx <= sentenceLen - wordLen) {
        if (str_cmp(&sentence[idx], word, wordLen)) {
            atomicAdd(count, 1);
        }
    }
}

int main() {
    char h_sentence[MAX_SENTENCE_LEN];
    char h_word[MAX_WORD_LEN];
    int h_count = 0;

    printf("Enter a sentence: ");
    fgets(h_sentence, MAX_SENTENCE_LEN, stdin);
    h_sentence[strcspn(h_sentence, "\n")] = 0;

    printf("Enter the word to count: ");
    scanf("%s", h_word);

    char *d_sentence, *d_word;
    int *d_count;
    int sentenceLen = strlen(h_sentence);
    int wordLen = strlen(h_word);

    cudaMalloc((void **)&d_sentence, sentenceLen + 1);
    cudaMalloc((void **)&d_word, wordLen + 1);
    cudaMalloc((void **)&d_count, sizeof(int));

    cudaMemcpy(d_sentence, h_sentence, sentenceLen + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, h_word, wordLen + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &h_count, sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (sentenceLen + blockSize - 1) / blockSize;
    countWordOccurrences<<<gridSize, blockSize>>>(d_sentence, d_word, d_count, sentenceLen, wordLen);
    cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("The word '%s' appears %d times in the sentence.\n", h_word, h_count);

    cudaFree(d_sentence);
    cudaFree(d_word);
    cudaFree(d_count);

    return 0;
}
