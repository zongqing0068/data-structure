#include "stack.h"

/**
 * ��ʼ��һ��ջ
 * @param S
 */
void InitStack(Stack *s)
{
    s->top = -1;
}

/**
 * ����ջ��ʹ�ó���
 * @param S ����ջ
 * @return ����ջ�ĳ���
 */
int StackLength(Stack S)
{
    return S.top + 1;
}

/**
 * ��ȡջ��һ�����鿽����˳��Ϊ��ջ�׵�ջ��
 * @param S ����ջ
 * @param seq ջ��Ԫ�ص�һ������
 */
void StackToArray(Stack S, DataType *seq)
{
    int i = 0;
    for (; i <= S.top; i++)
    {
        seq[i] = S.data[i];
    }
}

/**
 * �ж�ջ�Ƿ�գ�Ϊ�շ���1�����򷵻�0
 * @param S
 * @return
 */
int StackEmpty(Stack S)
{
    if(S.top == -1) return 1;
    else return 0;
    //TODO
}

/**
 * ��ջ����һ��Ԫ��
 * @param S ����ջ
 * @param e ������
 * @return �ɹ�����1�����򷵻�0
 */
int Push(Stack *s, DataType e)
{
    if(s->top == MaxSize - 1) return 0;
    else {
        s->top++;
        s->data[s->top] = e;
        return 1;
    }
    //TODO
}

/**
 * ��ջ�е���һ��Ԫ��
 * @param S ����ջ
 * @param e ����ջ������ֵ
 * @return �ɹ�����1�����򷵻�0
 */
int Pop(Stack *S, DataType *e)
{
    if(StackEmpty(*S)) return 0;
    else {
        *e = S->data[S->top];
        S->top--;
        return 1;
    }
    //TODO
}

/**
 * ��ȡջ��Ԫ�أ���ɾ����Ԫ��
 * @param S ����ջ
 * @param e ����ջ��Ԫ��
 * @return �ɹ�����1�����򷵻�0
 */
int GetTop(Stack S, DataType *e)
{
    if(StackEmpty(S)) return 0;
    else {
        *e = S.data[S.top];
        return 1;
    }
    //TODO
}

