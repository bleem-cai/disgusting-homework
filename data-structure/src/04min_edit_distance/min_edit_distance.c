#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minDistance(char *word1, char *word2) {
    if (word1 == NULL && word2 == NULL) {
        return 0;
    }
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    if (word1 == NULL) {
        return len2;
    } else if (word2 == NULL) {
        return len1;
    }
    int **dp = (int **) malloc(sizeof(int *) * (len1 + 1));
    if (dp == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < len1 + 1; i++) {
        dp[i] = (int *) malloc(sizeof(int) * (len2 + 1));
        if (dp[i] == NULL) {
            return 0;
        }
    }
    dp[0][0] = 0;
    for (i = 1; i < len1 + 1; i++) {
        dp[i][0] = dp[i - 1][0] + 1;    // 初始化第一列的情况
    }
    for (i = 1; i < len2 + 1; i++) {
        dp[0][i] = dp[0][i - 1] + 1;   // 初始化第一行的情况
    }
    int j;
    for (i = 1; i < len1 + 1; i++) {
        for (j = 1; j < len2 + 1; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
    }

    return dp[len1][len2];
}

int main() {
    char s1[100];
    char s2[100];
    scanf("%s", s1);
    scanf("%s", s2);
    printf("%d", minDistance(s1, s2));
}
