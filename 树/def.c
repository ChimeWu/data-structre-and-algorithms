//各种树的定义

#define MAXSIZE 100

//定义一棵二叉树
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//定义一棵二叉排序树
typedef struct BSTNode
{
    int data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

//定义一棵平衡二叉树
typedef struct AVLNode
{
    int data;
    int bf; //平衡因子
    struct AVLNode *lchild, *rchild;
} AVLNode, *AVLTree;

//定义一棵红黑树
typedef struct RBNode
{
    int data;
    int color; //0表示红色，1表示黑色
    struct RBNode *lchild, *rchild, *parent;
} RBNode, *RBTree;

//定义一棵哈夫曼树
typedef struct HuffmanNode
{
    int data;
    struct HuffmanNode *lchild, *rchild;
} HuffmanNode, *HuffmanTree;

//定义一棵B树
typedef struct BNode
{
    int keynum; //结点中关键字的个数，即结点的大小
    struct BNode *parent;
    int key[MAXSIZE]; //关键字数组，长度为m-1
    struct BNode *ptr[MAXSIZE]; //子树指针数组，长度为m
} BNode, *BTree;

//定义一棵B+树
typedef struct BPlusNode
{
    int keynum; //结点中关键字的个数，即结点的大小
    struct BPlusNode *parent;
    int key[MAXSIZE]; //关键字数组，长度为m-1
    struct BPlusNode *ptr[MAXSIZE]; //子树指针数组，长度为m
    struct BPlusNode *next; //叶子结点的指针域
} BPlusNode, *BPlusTree;

//定义一棵B*树
typedef struct BStarNode
{
    int keynum; //结点中关键字的个数，即结点的大小
    struct BStarNode *parent;
    int key[MAXSIZE]; //关键字数组，长度为m-1
    struct BStarNode *ptr[MAXSIZE]; //子树指针数组，长度为m
    struct BStarNode *next; //叶子结点的指针域
} BStarNode, *BStarTree;

