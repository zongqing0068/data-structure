/*----------------------------------------------------------------------------
�ļ���: experiment1
������: ����
ѧ�ţ�200110513
�� ��: 2021.4.1.
������ѧ���ɼ�¼��ͳ�Ƴ���
��Ҫ���ܣ�������������ڵ㡢��������������ת���������ཻ�ڵ㡢��������
------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
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

/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}

/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
    StudentLinkedListNode *p = head;
    if(!p){
        printf("��Ϊ�գ�");
        exit(1);
    }
    while(p){
        printLinkedListNode(p);//����������ӡ�ýڵ���Ϣ
        p = p->next;
    }
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
    StudentLinkedListNode *p;
    p = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
    if(!p)//�������ڴ��Ƿ�ɹ�
    {
        printf("overflow");
        exit(1);
    }
    strcpy(p->StuID, student_id);
    p->Grade = grade;
    p->next = NULL;//����Ϣ����ýڵ��У�������ָ�����ÿ�
    return p;
}


/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    if(!head){
        head = node;//����Ϊ�գ���ֱ�ӽ�ͷ���ָ��ýڵ�
    }
    else{
        if(node->Grade > head->Grade){//��������Ƿ�����������
            node->next = head;
            head = node;//ͷ�巨����ýڵ�
        }
        else{
            printf("����δ����������");
            exit(1);
        }
    }
    return head;
}


/** ��ת���� */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
    StudentLinkedListNode *p, *q;
    p = head;
    if(!p){
        printf("��Ϊ��!");
        exit(1);
    }
    p = p->next;
    if(!p) return head;//��ʱ����ֻ��һ���ڵ�
    head->next = NULL;
    while(p->next){
        q = p->next;
        p->next = head;
        head = p;//����ǰ�ڵ�������
        p = q;
    }
    p->next = head;
    head = p;//����β���
    return head;
}

/** �ҵ��ཻ�ĵ�һ����� */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
    int len1, len2, i, l;
    len1 = len2 = 1;
    StudentLinkedListNode *p, *q;
    p = class1;
    q = class2;
    if(!p || !q){
        printf("��Ϊ��!");
        exit(1);
    }//�жϱ��Ƿ�Ϊ��
    while(p->next){
        len1++;
        p = p->next;
    }
    while(q->next){
        len2++;
        q = q->next;
    }//�ֱ������������
    if(p != q){
        printf("�������ཻ�ڵ�");
        exit(0);
    }//�ж��������һ���ڵ�ĵ�ַ�Ƿ���ͬ�����ж������Ƿ����ཻ�ڵ�
    p = class1;
    q = class2;
    if(len1 > len2){//�ҵ�����϶̵�һ��ı�
        l = len1 - len2;
        for(i = 0;i < l;i++) p = p->next;//������ָ���Ƶ����β���̱����λ��
        while(p != q){
            p = p->next;
            q = q->next;
        }//��ָ��ͬʱ���ƣ��ҵ���ַ��ͬ�Ľڵ�
        return p;
    }
    else{//ͬ��
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
        // �洢���ݵ�����
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

        // ��ת����
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // �����ཻ����
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // ��ӡ�ཻ���
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //�����ཻ����
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
