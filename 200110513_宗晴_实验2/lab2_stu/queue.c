#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    if(QueueLength(Q)) return 0;
    else return 1;
    //TODO
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    if(QueueLength(*Q) == MaxSize) return 0;
    Push(&Q->stack1, e);//若队列未满，则直接将元素压入栈1中
    return 1;
    /*栈1用来入栈，栈2用来出栈。
    若栈1中有元素，则栈1的栈顶元素总代表队尾元素，否则栈2的栈底元素代表队尾元素。
    若栈2中有元素，则栈2的栈顶元素代表队头元素，否则栈1的栈底元素代表队头元素。
    */
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //TODO
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    DataType i;//i用来转移栈中的元素
    if(QueueEmpty(*Q)) return 0;
    if(StackEmpty(Q->stack2)) {
        while(!StackEmpty(Q->stack1)){
            Pop(&Q->stack1, &i);
            Push(&Q->stack2, i);
        }
    }//栈2中没有元素时，意味着栈1的栈底元素是队头元素，应该将栈1中的元素转移到栈2中
    Pop(&Q->stack2, e);//此时栈2的栈顶元素是队头元素，应该将栈2的栈顶元素出队
    return 1;
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //TODO
}

/**
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    DataType i;//i用来转移栈中的元素
    if(QueueEmpty(Q)) return 0;
    if(StackEmpty(Q.stack2)) {
        while(!StackEmpty(Q.stack1)){
            Pop(&Q.stack1, &i);
            Push(&Q.stack2, i);
        }
    }//栈2中没有元素时，意味着栈1的栈底元素是队头元素，应该将栈1中的元素转移到栈2中
    GetTop(Q.stack2, e);//此时栈2的栈顶元素是队头元素，应该读取栈2的栈顶元素
    return 1;

    //TODO
}

/**
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    DataType i;//i用来转移栈中的元素
    int j = 0;
    while(!StackEmpty(Q.stack2))
    {
        Pop(&Q.stack2, &i);
        seq[j++] = i;
    }//若栈2中有元素，则从栈顶到栈底依次拷贝到数组中
    StackToArray(Q.stack1, seq + j);//将栈1中的元素接下去拷贝到数组中

    /*
        取决于你的栈如何设计，元素存在哪个队列里。
    */
    //TODO
}
