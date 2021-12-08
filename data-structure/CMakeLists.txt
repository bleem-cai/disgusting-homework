cmake_minimum_required(VERSION 3.20)
project(data-structure C)

set(CMAKE_C_STANDARD 99)

add_executable(01merge_sort src/01merge_sort/merge_sort.c src/01merge_sort/merge_sort.c src/01merge_sort/merge_sort.c src/01merge_sort/main.c src/01merge_sort/merge_sort.h)
add_executable(02avl_tree src/02avl_tree/02avl_tree.c src/02avl_tree/02avl_tree.h src/02avl_tree/test.c)
add_executable(03topological_sort src/03topological_sort/topological_sort.c)
add_executable(04min_edit_distance src/04min_edit_distance/min_edit_distance.c)
add_executable(05huffman_code src/05huffman_code/huffman_code.c)
add_executable(06dijkstra src/06dijkstra/dijkstra.c src/06dijkstra/dijkstra.c)
add_executable(07quick_sort src/07quick_sort/quick_sort.c)
add_executable(08prim_kruskal src/08prim_kruskal/prim_kruskal.c)