#include "header.h"

int main() {//возв массив результ
    finalyAns * answer = Task("a", "test/file1.txt", "test/file3.txt", NULL);
    if (answer == NULL) {
        printf("Memory trouble or zero input files");
        return INVALID_MEMORY;
    }
    for (int i = 0; i < answer[0].count_files; i++) {
        if (answer[i].status == OK) {
            printf("%s %d\n", answer[i].filename, answer[i].ans_for_file_len);
            for (int j = 0; j < answer[i].ans_for_file_len; j++) {
                printf("%d %d\n", answer[i].ans_for_file[j].str_number, answer[i].ans_for_file[j].symbol_number);
            }
            free(answer[i].ans_for_file);
        }
        else {
            if (answer[i].status == OPEN_PROBLEM) {
                printf("%s open problem\n", answer[i].filename);
                free(answer);
                return OPEN_PROBLEM;
            }
            else if (answer[i].status == INVALID_MEMORY) {
                printf("%s memory error\n", answer[i].filename);
                free(answer);
                return INVALID_MEMORY;
            }
        }
    }
    free(answer);
    return OK;
}
