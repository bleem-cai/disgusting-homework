#include "stdio.h"
#include "02avl_tree.h"

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 15, 16, 14, 13, 12, 11, 9, 8, 10};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main() {
    int i, i_len;
    AVLTree root = NULL;

    printf("== 依次添加: ");
    i_len = TBL_SIZE(arr);
    for (i = 0; i < i_len; i++) {
        printf("%d ", arr[i]);
        //对测试数据进行插入
        root = avltree_insert(root, arr[i]);
    }

    printf("\n== 前序遍历: ");
    preorder_avltree(root);

    printf("\n== 中序遍历: ");
    inorder_avltree(root);

    printf("\n== 后序遍历: ");
    postorder_avltree(root);
    printf("\n");

    printf("== 高度: %d\n", avltree_height(root));
    printf("== 最小值: %d\n", avltree_minimum(root)->key);
    printf("== 最大值: %d\n", avltree_maximum(root)->key);
    printf("== 树的详细信息: \n");
    print_avltree(root, root->key, 0);


    i = 8;
    printf("\n== 删除根节点: %d", i);
    root = avltree_delete(root, i);

    printf("\n== 高度: %d", avltree_height(root));
    printf("\n== 中序遍历: ");
    inorder_avltree(root);
    printf("\n== 树的详细信息: \n");
    print_avltree(root, root->key, 0);

    destroy_avltree(root);
}