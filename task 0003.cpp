#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000 // Maximum size for input buffer

// Function to compress a text file using Run-Length Encoding
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    
    if (in == NULL || out == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char currentChar, prevChar;
    int count = 1;
    
    // Read the first character
    prevChar = fgetc(in);
    if (prevChar == EOF) {
        printf("Input file is empty!\n");
        fclose(in);
        fclose(out);
        return;
    }

    // Process the file character by character
    while ((currentChar = fgetc(in)) != EOF) {
        if (currentChar == prevChar) {
            // Increment count if the same character is repeated
            count++;
        } else {
            // Write the count and character to the output file
            fprintf(out, "%d%c", count, prevChar);
            prevChar = currentChar;
            count = 1;
        }
    }
    
    // Write the last sequence
    fprintf(out, "%d%c", count, prevChar);

    fclose(in);
    fclose(out);
    printf("File compressed successfully to %s\n", outputFile);
}

// Function to decompress a file compressed with RLE
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    
    if (in == NULL || out == NULL) {
        printf("Error opening files!\n");
        return;
    }

    int count;
    char ch;

    // Read the compressed file
    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        // Write the character 'count' times to the output file
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("File decompressed successfully to %s\n", outputFile);
}

// Main function to handle user input
int main() {
    char inputFile[100], outputFile[100];
    int choice;

    printf("Text File Compression/Decompression Tool\n");
    printf("1. Compress a file\n");
    printf("2. Decompress a file\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // Clear the newline character from input buffer

    if (choice == 1) {
        printf("Enter input file name (e.g., input.txt): ");
        fgets(inputFile, sizeof(inputFile), stdin);
        inputFile[strcspn(inputFile, "\n")] = 0; // Remove newline

        printf("Enter output file name (e.g., compressed.rle): ");
        fgets(outputFile, sizeof(outputFile), stdin);
        outputFile[strcspn(outputFile, "\n")] = 0; // Remove newline

        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        printf("Enter input file name (e.g., compressed.rle): ");
        fgets(inputFile, sizeof(inputFile), stdin);
        inputFile[strcspn(inputFile, "\n")] = 0; // Remove newline

        printf("Enter output file name (e.g., decompressed.txt): ");
        fgets(outputFile, sizeof(outputFile), stdin);
        outputFile[strcspn(outputFile, "\n")] = 0; // Remove newline

        decompressFile(inputFile, outputFile);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
