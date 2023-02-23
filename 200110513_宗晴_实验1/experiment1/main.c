/*----------------------------------------------------------------------------
文件名: experiment1
创建人: 宗晴
学号：200110513
日 期: 2021.4.1.
描述：学生成绩录入统计程序
主要功能：创建链表、插入节点、遍历访问链表、反转链表、查找相交节点、销毁链表
------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* 创建相交链表 */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a和b后面若干结点值相同
    // beforeCross1为跳过的a中的个数，从第beforeCross1 + 1个结点开始相交
    // beforeCross2为跳过的b中的个数，从第beforeCross2 + 1个结点开始相交
    // 相交方法是将b中的前一结点指向a中的首个相交结点
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //销毁野指针结点
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
}

void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode){
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode){
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode){
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}

/** 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode* head){
    StudentLinkedListNode *p = head;
    if(!p){
        printf("表为空！");
        exit(1);
    }
    while(p){
        printLinkedListNode(p);//遍历链表并打印该节点信息
        p = p->next;
    }
}


/** 新建一个链表node并返回 */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
    StudentLinkedListNode *p;
    p = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
    if(!p)//检查分配内存是否成功
    {
        printf("overflow");
        exit(1);
    }
    strcpy(p->StuID, student_id);
    p->Grade = grade;
    p->next = NULL;//将信息输入该节点中，并将其指针域置空
    return p;
}


/** 按照降序插入学生的成绩情况,并返回链表头指针 */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    if(!head){
        head = node;//若表为空，则直接将头结点指向该节点
    }
    else{
        if(node->Grade > head->Grade){//检查输入是否按照升序排列
            node->next = head;
            head = node;//头插法插入该节点
        }
        else{
            printf("输入未按升序排列");
            exit(1);
        }
    }
    return head;
}


/** 反转链表 */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
    StudentLinkedListNode *p, *q;
    p = head;
    if(!p){
        printf("表为空!");
        exit(1);
    }
    p = p->next;
    if(!p) return head;//此时表中只有一个节点
    head->next = NULL;
    while(p->next){
        q = p->next;
        p->next = head;
        head = p;//将当前节点插入表首
        p = q;
    }
    p->next = head;
    head = p;//处理尾结点
    return head;
}

/** 找到相交的第一个结点 */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
    int len1, len2, i, l;
    len1 = len2 = 1;
    StudentLinkedListNode *p, *q;
    p = class1;
    q = class2;
    if(!p || !q){
        printf("表为空!");
        exit(1);
    }//判断表是否为空
    while(p->next){
        len1++;
        p = p->next;
    }
    while(q->next){
        len2++;
        q = q->next;
    }//分别求出两链表长度
    if(p != q){
        printf("两表无相交节点");
        exit(0);
    }//判断两表最后一个节点的地址是否相同，即判断两表是否有相交节点
    p = class1;
    q = class2;
    if(len1 > len2){//找到两表较短的一表的表长
        l = len1 - len2;
        for(i = 0;i < l;i++) p = p->next;//将长表指针移到与表尾相距短表表长的位置
        while(p != q){
            p = p->next;
            q = q->next;
        }//两指针同时后移，找到地址相同的节点
        return p;
    }
    else{//同理
        l = len2 - len1;
        for(i = 0;i < l;i++) q = q->next;
        while(p != q){
            p = p->next;
            q = q->next;
        }
        return p;
    }
}

int main(){
    freopen("./gradeImport.in","r",stdin);

    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    while(~scanf("%d%d", &num1, &num2)){
        class1 = class2 = NULL;
        // 存储数据到链表
        for(i = 0;i < num1;i++){
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class1 = studentLinkedListAdd(class1, node);
        }
        for(i = 0;i < num2;i++){
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class2 = studentLinkedListAdd(class2, node);
        }
        printf("* part1:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // 反转链表
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // 生成相交链表
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // 打印相交结点
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //销毁相交链表
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
