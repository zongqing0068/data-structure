/*----------------------------------------------------------------------------
文件名: experiment3
创建人: 宗晴
学号：200110513
日 期: 2021.4.15.
描述：树型结构及其应用
主要功能：按层次遍历建立二叉树，并输出该二叉树的前序遍历、 中序遍历和后序遍历的序列；
          求取二叉树的最大路径和；求取二叉树的所有左子叶权重之和；翻转二叉树
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode {
    int id;
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef struct ListNode {
    struct TreeNode *node; // 队列的值的类型是树节点指针
    struct ListNode *next;
} ListNode, *ListNodePtr;

typedef struct Queue {
    ListNodePtr dummyHead;
    ListNodePtr tail;
    int size;
} *QueuePtr;

// 创建链表的节点
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next) {
    ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
    curr->node = node;
    curr->next = next;
    return curr;
}

// 创建树的节点
int TreeId = 0;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right) {
    TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    curr->id = TreeId++;
    curr->val = val;
    curr->left = left;
    curr->right = right;
    return curr;
}

// 单链表队列初始化
QueuePtr InitQueue() {
    QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
    TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
    queue->size = 0;
    queue->dummyHead = createListNode(dummyTreeNode, NULL);
    queue->tail = queue->dummyHead;
    return queue;
}

// 在 queue 的尾部添加一个元素的副本
void EnQueue(QueuePtr queue, TreeNodePtr node) {
    ListNodePtr curr = createListNode(node, NULL);
    queue->tail->next = curr;
    queue->tail = queue->tail->next;
    queue->size++;
}

// 删除 queue 中的第一个元素
void DeQueue(QueuePtr queue) {
    if (queue->size == 0) {
        perror("error! the size of queue is zero when call DeQueue().");
        return;
    }
    ListNodePtr head = queue->dummyHead->next;
    queue->dummyHead->next = head->next;
    queue->size--;
    if (queue->size == 0) queue->tail = queue->dummyHead;
    free(head);
}

// 如果 queue 中没有元素, 返回 true
bool QueueEmpty(QueuePtr queue) {
    return queue->size == 0;
}

// 返回 queue 中第一个元素的引用
TreeNodePtr GetHead(QueuePtr queue) {
    if (QueueEmpty(queue)) {
        perror("error! the size of queue is zero when call front().");
        return NULL;
    } else {
        return queue->dummyHead->next->node;
    }
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

// 将输入转换为数组
void getDigits(char *buff, int *data) {
    int len = strlen(buff);
    int index = 0;
    for (int i = 0; i < len; i++) {
        int num = 0;
        if (buff[i] == '#') {
            num = -1;
            i++;
        } else {
            while (buff[i] != ' ' && buff[i] != '\0') {
                num = num * 10 + (buff[i++] - '0');
            }
        }
        data[index++] = num;
    }
}

// 创建 dot 可视化文件，感兴趣的同学可以学习
void createDotFile(const char *filename, TreeNodePtr root, int MaxSize) {
    FILE *fp = fopen(filename, "w");    // 文件指针
    if (fp == NULL) {   // 为NULL则返回
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // 开头
    // 利用层次遍历构造
    QueuePtr queue = InitQueue();
    EnQueue(queue, root);
    int id = 1;
    while (!QueueEmpty(queue)) { // 若队列不空，继续遍历。否则，遍历结束
        TreeNodePtr curr = GetHead(queue);
        DeQueue(queue);
        if (curr == NULL) continue;
        fprintf(fp, "%d [shape=circle, label=\"%d\"];\n", curr->id, curr->val);
        if (curr->left != NULL) { // 如果有左孩子，左孩子入队
            EnQueue(queue, curr->left);
            fprintf(fp, "%d->%d;\n", curr->id, curr->left->id);
        }
        id++;
        // 中间虚拟节点，补充空的左孩子或左孩子节点
        fprintf(fp, "_n%d [shape=circle, label=\"#\", style=invis];\n", id);
        fprintf(fp, "%d->_n%d [style=invis, weight=10];\n", curr->id, id);
        if (curr->right != NULL) { // 如果有右孩子，右孩子入队
            EnQueue(queue, curr->right);
            fprintf(fp, "%d->%d;\n", curr->id, curr->right->id);
        }
        id++;
    }
    fprintf(fp, "}\n"); // 结尾
    fclose(fp); // 关闭IO
}


// 绘制二叉树图片,调用 createDotFile 并使用 system 执行命令
void plot(TreeNodePtr tree_root, int i, int size, char *name) {
    char tree_filename[50], paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, size);
    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);
}


// 删除二叉树
void destoryTree(TreeNodePtr root) {
    if (!root) return;
    if (root->left) {
        destoryTree(root->left);
        root->left = NULL;
    }
    if (root->right) {
        destoryTree(root->right);
        root->right = NULL;
    }
    free(root);
}

/** TODO:  任务一：请你通过队列来实现层次遍历构建二叉树，并返回二叉树的头结点 */
TreeNodePtr createTreeWithLevelOrder(int *data, int size) {
    if(data[0] == -1) return NULL;//只输入一个#时，返回空树
    QueuePtr Q = InitQueue();
    int i = 0;
    TreeNodePtr root = createTreeNode(data[0], NULL, NULL);
    EnQueue(Q, root);//否则创建根结点并将其入队
    TreeNodePtr TNode, TNodep;//TNode用来指向有效结点，TNodep用来指向无效结点
    while(i < (size-1)){//数组中还有剩余元素
        TNode = GetHead(Q);
        DeQueue(Q);//获取队头元素并将其从队列中删去
        if(data[++i] == -1){
            TNode->left = NULL;
            TNodep = createTreeNode(data[i], NULL, NULL);
            EnQueue(Q, TNodep);
        }//值为-1表示空结点，将左指针置空，但仍需建立该结点并将其入队
        else{
            TNode->left = createTreeNode(data[i], NULL, NULL);
            EnQueue(Q, TNode->left);//否则建立有效值结点，左指针指向该结点，并将该结点入队
        }
        if(i < (size-1)){//数组中还有剩余元素
            if(data[++i] == -1){
                TNode->right = NULL;
                TNodep = createTreeNode(data[i], NULL, NULL);
                EnQueue(Q, TNodep);
            }
            else{
                TNode->right = createTreeNode(data[i], NULL, NULL);
                EnQueue(Q, TNode->right);
            }
        }//右指针操作同左指针
        else TNode->right = NULL;//数组中没有右孩子的值，也说明是空指针
        if(TNode->val == -1) free(TNode);//释放无效结点
    }
    while(!QueueEmpty(Q)){
        TNode = GetHead(Q);
        DeQueue(Q);
        if(TNode->val == -1) free(TNode);
        else TNode->left = TNode->right = NULL;
    }//将最底层元素的左右指针置空，并释放无效结点
    return root;
}

/**
 * ================================================
 * ||                  前序遍历                   ||
 * ================================================
 */
void preOrderTraverse(TreeNodePtr root) {
    if(root){
        printf("%d ", root->val);//输出当前结点值
        preOrderTraverse(root->left);//前序遍历左子树
        preOrderTraverse(root->right);//前序遍历右子树
    }
}

/**
 * ================================================
 * ||                  中序遍历                   ||
 * ================================================
 */
void inOrderTraverse(TreeNodePtr root) {
    if(root){
        inOrderTraverse(root->left);//中序遍历左子树
        printf("%d ", root->val);//输出当前结点值
        inOrderTraverse(root->right);//中序遍历右子树
    }
}

/**
 * ================================================
 * ||                  后序遍历                   ||
 * ================================================
 */
void postOrderTraverse(TreeNodePtr root) {
    if(root){
        postOrderTraverse(root->left);//后序遍历左子树
        postOrderTraverse(root->right);//后序遍历右子树
        printf("%d ", root->val);//输出当前结点值
    }
}

/** TODO: 任务二：请你通过深度优先遍历来求取该二叉树的最大路径和 */
int maxPathSum(TreeNodePtr root) {
    if(!root) return 0;//空结点，返回0
    else{
        int l, r;
        l = maxPathSum(root->left);
        r = maxPathSum(root->right);//分别递归求取其左右子树的最大路径和
        return max(l, r) + root->val;//返回较大值和当前结点的权重之和
    }
}

/** ToDO: 任务三：请你通过递归求取该二叉树的所有左子叶权重之和 */
int sumOfLeftLeaves(TreeNodePtr root) {
    if(!root) return 0;//空结点，返回0
    if(root->left && !root->left->left && !root->left->right) return root->left->val;//如果当前结点的左指针非空，且其左孩子的左右指针均为空，表示其左孩子为左子叶，返回其左孩子的权重
    else return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);//否则递归求取其左右子树的所有左子叶权重之和
}

/** TODO: 任务四：请你通过递归求取该树的镜像，即翻转该二叉树 */
TreeNodePtr invertTree(TreeNodePtr root) {
    if(!root) return root;//如果传入的是空指针，则直接返回
    TreeNodePtr p;
    p = invertTree(root->left);
    root->left = invertTree(root->right);
    root->right = p;//递归翻转其左右子树并将两子树位置交换
    return root;//返回翻转后的根结点
}


int main() {

    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    char num[MAX_NUM];
    bool use_graphviz = true;
    /**
     * ===============================================================
     * ||                   End Configuration                       ||
     * ===============================================================
     */

    // printf("Read data...\n");
    FILE *fp = fopen("./test.txt", "r");
    if (!fp) {
        perror("打开文件时发生错误");
        return -1;
    } else {
        int i = 0;
        // printf("success!\n");
        /**
         * ===============================================================
         * ||                   Read data here                          ||
         * ===============================================================
         */
        while (fgets(num, MAX_NUM, fp) && fgets(buff, SIZE, fp)) {
            char *nextline = strchr(buff, '\n');          //查找换行符
            if (nextline)                            //如果find不为空指针
                *nextline = '\0';                    //就把一个空字符放在这里
            printf("Case %d, data: %s, nodes number: %s", i, buff, num);
            int size = atoi(num);
            int data[size];
            getDigits(buff, data);

            /**
             * ===============================================================
             * ||       你的任务在这里，当然你也可以以任意方式修改函数的原型          ||
             * ===============================================================
             */

            /** 任务一 */
            TreeNodePtr tree_root = createTreeWithLevelOrder(data, size);
            printf("Answer for task 1 is: \n");
            printf("preOrderTraverse is:");
            preOrderTraverse(tree_root);
            printf("\n");
            printf("inOrderTraverse is:");
            inOrderTraverse(tree_root);
            printf("\n");
            printf("postOrderTraverse is:");
            postOrderTraverse(tree_root);
            printf("\n");

            /** 通过 graphviz 可视化，勿删，助教测试使用 */
            if (use_graphviz) {
                plot(tree_root, i, size, "tree");
            }

            /** 任务二 */
            int max_path_sum = maxPathSum(tree_root);
            printf("Answer for task 2 is : %d \n", max_path_sum);

            /** 任务三 */
            int weight_sum = sumOfLeftLeaves(tree_root);
            printf("Answer for task 3 is : %d \n", weight_sum);

            /** 任务四 */
            TreeNodePtr invert_tree_root = invertTree(tree_root);
            printf("inOrderTraverse for task 4 is:");
            inOrderTraverse(invert_tree_root);
            printf("\n\n");

            /** 通过 graphviz 可视化，勿删，助教测试使用 */
            if (use_graphviz) {
                plot(invert_tree_root, i, size, "invert_tree");
            }

            destoryTree(invert_tree_root);
            tree_root = invert_tree_root = NULL;
            i++;

        }

        /**
         * ===============================================================
         * ||                       End read                            ||
         * ===============================================================
         */
    }

    fclose(fp);

}
