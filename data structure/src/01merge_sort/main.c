#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"


static void esort(void) {
    int num_ways = 3;//使用辅助文件数量

    int run_size = 5;//每个辅助排序文件所包含的数量

    int num_size = num_ways * run_size;//总需排序数量

    char input_file[] = "C:\\sources\\ClionProjects\\data structure\\src\\01merge_sort\\sort\\input.txt";
    char output_file[] = "C:\\sources\\ClionProjects\\data structure\\src\\01merge_sort\\sort\\output.txt";

    FILE *in = openFile(input_file, "w");

    srand(time(NULL));

    for (int i = 0; i < num_size; i++)
        fprintf(in, "%d ", rand() % 10000);//防止数字过大

    fclose(in);

    external_sort(input_file, output_file, num_ways, run_size);
}

int main(void) {
    esort();
    return 0;
}
