/* 参考网址 https://blog.csdn.net/geek_jerome/article/details/78895289 */

/*
 * B树的定义:
 * B树是一种平衡的多路查找树
 * 一颗m阶B树,或为空树,或为满足下列特性的m叉树:
 *      (1) 树中每个节点最多含有m棵子树
 *      (2) 若根节点不是叶子节点,则至少有两颗子树
 *      (3) 除根之外的所有非终端节点至少有[m/2],向上取整
 *      (4) 每个非终端节点中包含信息: (n, A0, K1, A1, K2, A2, K3, A3, ..., Kn, An)
 *          其中:
 *          1. Ki(1 <= i <= n)为关键字,且关键字按升序排序
 *          2. 指针Ai(0 <= i <= n)指向子树的根节点
 *          3. 关键字的个数n必须满足: [m/2]-1 <= n <= m-1
 *      (5) 所有叶子节点都出现在同一层次上,并且不带信息(可以看作是外部节点或查找失败的节点,
 *      实际上这些节点不存在,指向这些节点的指针为空)
 */

/*
 * B树的抽象数据定义
 * ADT BTree{
 *
 * 数据对象: D是具有相同特性的数据元素的集合
 * 数据关系:
 *      R1 = {<ai-1, ai> | ai-1, ai∈D, i=2, 3, ..., n}
 *      R2 = {<ptr[i-1], ptr[i]> | i = 1..., n}
 *      约定a1|key[1]为关键字数组头,an|key=[p->keynum]为关键字数组尾
 *      约定ptr[i]为节点的第i个子树
 * 基本操作:
 *      InitBTree(t)
 *      初始条件: B树已定义
 *      操作结果: 初始化B树
 *
 *      SearchBTNode(BTNode *p, KeyType k)
 *      初始条件: 节点P已存在
 *      操作结果: 在节点p中查找关键字k的插入位置i
 *
 *      Result SearchBTree(BTree t, KeyType k)
 *      初始条件: B树已存在
 *      操作结果: 在B树查找关键字k的插入位置,返回查找结果
 *
 *      InsertBTNode(BTNode *p, int i, KeyType k, BTNode *q)
 *      初始条件: 节点p和节点q已存在,0<i<p->keynum
 *      操作结果: 将关键字k和节点q分别插入p->key[i+1]和p->ptr[i+1]中
 *
 *      SplitBTNode(BTNode *p,BTNode *q)
 *      初始条件：结点p和结点q已存在
 *      操作结果：将结点p分裂成两个结点,前一半保留,后一半移入结点q
 *
 *      NewRoot(BTNode *t, KeyType k, BTNode *p, BTNode *q)
 *      初始条件：结点t,p,q已存在
 *      操作结果：生成新的根结点t,原p和q为子树指针
 *
 *      InsertBTree(BTree *t,int i,KeyType k,BTNode *p)
 *      初始条件：结点p和结点t已存在，0<i<p->keynum
 *      操作结果：在B树t中插入关键字k
 *
 *      Remove(BTNode *p,int i)
 *      初始条件：结点p已存在，0<i<p->keynum
 *      操作结果：p结点删除key[i]和它的孩子指针ptr[i]
 *
 *      Substitution(BTNode *p,int i)
 *      初始条件：结点p已存在，0<i<p->keynum
 *      操作结果：查找替代值
 *
 *      MoveRight(BTNode *p,int i)
 *      初始条件：结点p已存在，0<i<p->keynum
 *      操作结果：结点调整右移操作
 *
 *      MoveLeft(BTNode *p,int i)
 *      初始条件：结点p已存在，0<i<p->keynum
 *      操作结果：结点调整左移操作
 *
 *      Combine(BTNode *p,int i)
 *      初始条件：结点p已存在，0<i<p->keynum
 *      操作结果：结点调整合并操作
 *
 *      AdjustBTree(BTNode *p,int i)
 *      初始条件：结点p已存在，0<i<p->keynum
 *      操作结果：B树调整操作
 *
 *      BTNodeDelete(BTNode *p,KeyType k)
 *      初始条件：结点p已存在
 *      操作结果：在结点p中删除关键字k
 *
 *      BTreeDelete(BTree &t,KeyType k)
 *      初始条件：B树t已存在
 *      操作结果：在B树t中删除关键字k
 *
 *      DestroyBTree(BTree &t)
 *      初始条件：B树t已存在
 *      操作结果：递归释放B树
 *
 *      PrintBTree(BTree t)
 *      初始条件：B树t已存在
 *      操作结果：遍历打印B树
 * } ADT BTree
 */