#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    if(QueueLength(Q)) return 0;
    else return 1;
    //TODO
}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    if(QueueLength(*Q) == MaxSize) return 0;
    Push(&Q->stack1, e);//������δ������ֱ�ӽ�Ԫ��ѹ��ջ1��
    return 1;
    /*ջ1������ջ��ջ2������ջ��
    ��ջ1����Ԫ�أ���ջ1��ջ��Ԫ���ܴ����βԪ�أ�����ջ2��ջ��Ԫ�ش����βԪ�ء�
    ��ջ2����Ԫ�أ���ջ2��ջ��Ԫ�ش����ͷԪ�أ�����ջ1��ջ��Ԫ�ش����ͷԪ�ء�
    */
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    DataType i;//i����ת��ջ�е�Ԫ��
    if(QueueEmpty(*Q)) return 0;
    if(StackEmpty(Q->stack2)) {
        while(!StackEmpty(Q->stack1)){
            Pop(&Q->stack1, &i);
            Push(&Q->stack2, i);
        }
    }//ջ2��û��Ԫ��ʱ����ζ��ջ1��ջ��Ԫ���Ƕ�ͷԪ�أ�Ӧ�ý�ջ1�е�Ԫ��ת�Ƶ�ջ2��
    Pop(&Q->stack2, e);//��ʱջ2��ջ��Ԫ���Ƕ�ͷԪ�أ�Ӧ�ý�ջ2��ջ��Ԫ�س���
    return 1;
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
 */
int GetHead(Queue Q, DataType *e)
{
    DataType i;//i����ת��ջ�е�Ԫ��
    if(QueueEmpty(Q)) return 0;
    if(StackEmpty(Q.stack2)) {
        while(!StackEmpty(Q.stack1)){
            Pop(&Q.stack1, &i);
            Push(&Q.stack2, i);
        }
    }//ջ2��û��Ԫ��ʱ����ζ��ջ1��ջ��Ԫ���Ƕ�ͷԪ�أ�Ӧ�ý�ջ1�е�Ԫ��ת�Ƶ�ջ2��
    GetTop(Q.stack2, e);//��ʱջ2��ջ��Ԫ���Ƕ�ͷԪ�أ�Ӧ�ö�ȡջ2��ջ��Ԫ��
    return 1;

    //TODO
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    DataType i;//i����ת��ջ�е�Ԫ��
    int j = 0;
    while(!StackEmpty(Q.stack2))
    {
        Pop(&Q.stack2, &i);
        seq[j++] = i;
    }//��ջ2����Ԫ�أ����ջ����ջ�����ο�����������
    StackToArray(Q.stack1, seq + j);//��ջ1�е�Ԫ�ؽ���ȥ������������

    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    //TODO
}
