#include "stdio.h"
#include "02avl_tree.h"

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 15, 16, 14, 13, 12, 11, 9, 8, 10};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main() {
    int i, i_len;
    AVLTree root = NULL;

    printf("== �������: ");
    i_len = TBL_SIZE(arr);
    for (i = 0; i < i_len; i++) {
        printf("%d ", arr[i]);
        //�Բ������ݽ��в���
        root = avltree_insert(root, arr[i]);
    }

    printf("\n== ǰ�����: ");
    preorder_avltree(root);

    printf("\n== �������: ");
    inorder_avltree(root);

    printf("\n== �������: ");
    postorder_avltree(root);
    printf("\n");

    printf("== �߶�: %d\n", avltree_height(root));
    printf("== ��Сֵ: %d\n", avltree_minimum(root)->key);
    printf("== ���ֵ: %d\n", avltree_maximum(root)->key);
    printf("== ������ϸ��Ϣ: \n");
    print_avltree(root, root->key, 0);


    i = 8;
    printf("\n== ɾ�����ڵ�: %d", i);
    root = avltree_delete(root, i);

    printf("\n== �߶�: %d", avltree_height(root));
    printf("\n== �������: ");
    inorder_avltree(root);
    printf("\n== ������ϸ��Ϣ: \n");
    print_avltree(root, root->key, 0);

    destroy_avltree(root);
}