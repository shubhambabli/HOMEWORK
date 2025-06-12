void displayScrambledKeywordBinary() {
    char reversed[8], scrambled[8];
    int len = strlen(arthur.keyword);

    // Step 1: Reverse the keyword
    for (int i = 0; i < len; ++i) {
        reversed[i] = arthur.keyword[len - 1 - i];
    }
    reversed[len] = '\0';

    // Step 2: Rearrange - collect odd-indexed letters first, then even-indexed
    int k = 0;
    for (int i = 1; i < len; i += 2) {
        scrambled[k++] = reversed[i];
    }
    for (int i = 0; i < len; i += 2) {
        scrambled[k++] = reversed[i];
    }
    scrambled[len] = '\0';

    // Step 3: Convert to binary and display
    printf("\n[Bonus] Scrambled keyword binary:\n");
    for (int i = 0; i < len; ++i) {
        char bin[9];
        toBinary(scrambled[i], bin);
        printf("%s ", bin);
    }
    printf("\n");
}
