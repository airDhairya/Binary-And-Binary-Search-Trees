#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* =========================================================
   COMMON STRUCTURE FOR BINARY TREE AND BINARY SEARCH TREE
   ========================================================= */

struct Node {
    int data;
    struct Node *left, *right;
};

/* GLOBAL ROOT */
struct Node *root = NULL;

/* COMMON FUNCTION: CREATE A NEW NODE */
struct Node *createNode(int x) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL)
        return NULL;

    n->data = x;
    n->left = n->right = NULL;

    return n;
}

/* =========================================================
   Q1. COUNT TOTAL NODES IN A BINARY TREE
   ========================================================= */

int countNodes(struct Node *n) {
    if (n == NULL)
        return 0;

    return 1 + countNodes(n->left) + countNodes(n->right);
}

/* =========================================================
   Q2. COUNT LEAF NODES IN A BINARY TREE
   Leaf node = node having no children
   ========================================================= */

int countLeaves(struct Node *n) {
    if (n == NULL)
        return 0;

    if (n->left == NULL && n->right == NULL)
        return 1;

    return countLeaves(n->left) + countLeaves(n->right);
}

/* =========================================================
   Q3. COUNT INTERNAL NODES IN A BINARY TREE
   Internal node = node having at least one child
   ========================================================= */

int countInternal(struct Node *n) {
    if (n == NULL ||
       (n->left == NULL && n->right == NULL))
        return 0;

    return 1 + countInternal(n->left)
             + countInternal(n->right);
}

/* =========================================================
   Q4. FIND HEIGHT OF A BINARY TREE
   Height measured in number of nodes
   Empty tree = 0; single node = 1
   ========================================================= */

int height(struct Node *n) {
    if (n == NULL)
        return 0;

    int l = height(n->left);
    int r = height(n->right);

    return 1 + (l > r ? l : r);
}

/* =========================================================
   Q5. COUNT NODES HAVING EXACTLY ONE CHILD
   ========================================================= */

int countOneChild(struct Node *n) {
    if (n == NULL)
        return 0;

    int current = (n->left == NULL) != (n->right == NULL);

    return current + countOneChild(n->left)
                   + countOneChild(n->right);
}

/* =========================================================
   Q6. COUNT NODES HAVING TWO CHILDREN
   ========================================================= */

int countTwoChildren(struct Node *n) {
    if (n == NULL)
        return 0;

    int current = n->left != NULL && n->right != NULL;

    return current + countTwoChildren(n->left)
                   + countTwoChildren(n->right);
}

/* =========================================================
   Q7. FIND SUM OF ALL NODES
   ========================================================= */

int sumNodes(struct Node *n) {
    if (n == NULL)
        return 0;

    return n->data + sumNodes(n->left) + sumNodes(n->right);
}

/* =========================================================
   Q8. FIND MINIMUM IN A GENERAL BINARY TREE
   ========================================================= */

int minimumBT(struct Node *n) {
    if (n == NULL)
        return INT_MAX;

    int l = minimumBT(n->left);
    int r = minimumBT(n->right);
    int m = n->data;

    if (l < m) m = l;
    if (r < m) m = r;

    return m;
}

/* =========================================================
   Q9. FIND MAXIMUM IN A GENERAL BINARY TREE
   ========================================================= */

int maximumBT(struct Node *n) {
    if (n == NULL)
        return INT_MIN;

    int l = maximumBT(n->left);
    int r = maximumBT(n->right);
    int m = n->data;

    if (l > m) m = l;
    if (r > m) m = r;

    return m;
}

/* =========================================================
   Q10. SEARCH FOR AN ELEMENT IN A GENERAL BINARY TREE
   ========================================================= */

struct Node *searchBT(struct Node *n, int key) {
    if (n == NULL || n->data == key)
        return n;

    struct Node *found = searchBT(n->left, key);

    if (found != NULL)
        return found;

    return searchBT(n->right, key);
}

/* =========================================================
   Q11. COPY A BINARY TREE
   ========================================================= */

struct Node *copyTree(struct Node *n) {
    if (n == NULL)
        return NULL;

    struct Node *copy = createNode(n->data);

    if (copy == NULL)
        return NULL;

    copy->left = copyTree(n->left);
    copy->right = copyTree(n->right);

    return copy;
}

/* =========================================================
   Q12. CHECK WHETHER TWO BINARY TREES ARE IDENTICAL
   ========================================================= */

int identical(struct Node *a, struct Node *b) {
    if (a == NULL && b == NULL)
        return 1;

    if (a == NULL || b == NULL)
        return 0;

    return a->data == b->data
        && identical(a->left, b->left)
        && identical(a->right, b->right);
}

/* =========================================================
   Q13. RECURSIVE PREORDER TRAVERSAL
   Order: ROOT LEFT RIGHT
   ========================================================= */

void preorder(struct Node *n) {
    if (n == NULL)
        return;

    printf("%d ", n->data);
    preorder(n->left);
    preorder(n->right);
}

/* =========================================================
   Q14. RECURSIVE INORDER TRAVERSAL
   Order: LEFT ROOT RIGHT
   ========================================================= */

void inorder(struct Node *n) {
    if (n == NULL)
        return;

    inorder(n->left);
    printf("%d ", n->data);
    inorder(n->right);
}

/* =========================================================
   Q15. RECURSIVE POSTORDER TRAVERSAL
   Order: LEFT RIGHT ROOT
   ========================================================= */

void postorder(struct Node *n) {
    if (n == NULL)
        return;

    postorder(n->left);
    postorder(n->right);
    printf("%d ", n->data);
}

/* =========================================================
   Q16. ITERATIVE PREORDER TRAVERSAL
   Uses a stack
   ========================================================= */

void iterativePreorder(struct Node *n) {
    if (n == NULL)
        return;

    struct Node *stack[1000];
    int top = -1;

    stack[++top] = n;

    while (top != -1) {
        n = stack[top--];
        printf("%d ", n->data);

        /* Push right first so left is processed first */
        if (n->right != NULL)
            stack[++top] = n->right;

        if (n->left != NULL)
            stack[++top] = n->left;
    }
}

/* =========================================================
   Q17. ITERATIVE INORDER TRAVERSAL
   Uses a stack
   ========================================================= */

void iterativeInorder(struct Node *n) {
    struct Node *stack[1000];
    int top = -1;

    while (n != NULL || top != -1) {
        while (n != NULL) {
            stack[++top] = n;
            n = n->left;
        }

        n = stack[top--];
        printf("%d ", n->data);

        n = n->right;
    }
}

/* =========================================================
   Q18. ITERATIVE POSTORDER TRAVERSAL
   Uses two stacks
   ========================================================= */

void iterativePostorder(struct Node *n) {
    if (n == NULL)
        return;

    struct Node *s1[1000], *s2[1000];
    int t1 = -1, t2 = -1;

    s1[++t1] = n;

    while (t1 != -1) {
        n = s1[t1--];
        s2[++t2] = n;

        if (n->left != NULL)
            s1[++t1] = n->left;

        if (n->right != NULL)
            s1[++t1] = n->right;
    }

    while (t2 != -1)
        printf("%d ", s2[t2--]->data);
}

/* =========================================================
   Q19. LEVEL-ORDER TRAVERSAL
   Uses a queue
   ========================================================= */

void levelOrder(struct Node *n) {
    if (n == NULL)
        return;

    struct Node *queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = n;

    while (front < rear) {
        n = queue[front++];
        printf("%d ", n->data);

        if (n->left != NULL)
            queue[rear++] = n->left;

        if (n->right != NULL)
            queue[rear++] = n->right;
    }
}

/* =========================================================
   Q20. BST INSERTION USING RECURSION
   ========================================================= */

struct Node *insertRecursive(struct Node *n, int key) {
    if (n == NULL)
        return createNode(key);

    if (key < n->data)
        n->left = insertRecursive(n->left, key);
    else if (key > n->data)
        n->right = insertRecursive(n->right, key);

    return n;
}

/* =========================================================
   Q21. BST INSERTION ITERATIVELY
   Uses the GLOBAL root
   ========================================================= */

void insertIterative(int key) {
    struct Node *newNode = createNode(key);

    if (newNode == NULL)
        return;

    if (root == NULL) {
        root = newNode;
        return;
    }

    struct Node *n = root, *parent = NULL;

    while (n != NULL) {
        parent = n;

        if (key < n->data)
            n = n->left;
        else if (key > n->data)
            n = n->right;
        else {
            free(newNode);
            return;
        }
    }

    if (key < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
}

/* =========================================================
   Q22. BST SEARCH USING RECURSION
   ========================================================= */

struct Node *searchRecursive(struct Node *n, int key) {
    if (n == NULL || n->data == key)
        return n;

    if (key < n->data)
        return searchRecursive(n->left, key);

    return searchRecursive(n->right, key);
}

/* =========================================================
   Q23. BST SEARCH ITERATIVELY
   ========================================================= */

struct Node *searchIterative(struct Node *n, int key) {
    while (n != NULL && n->data != key) {
        if (key < n->data)
            n = n->left;
        else
            n = n->right;
    }

    return n;
}

/* =========================================================
   Q24. FIND MINIMUM NODE IN A BST
   Minimum = leftmost node
   ========================================================= */

struct Node *minimumBST(struct Node *n) {
    if (n == NULL)
        return NULL;

    while (n->left != NULL)
        n = n->left;

    return n;
}

/* =========================================================
   Q25. FIND MAXIMUM NODE IN A BST
   Maximum = rightmost node
   ========================================================= */

struct Node *maximumBST(struct Node *n) {
    if (n == NULL)
        return NULL;

    while (n->right != NULL)
        n = n->right;

    return n;
}

/* =========================================================
   Q26. DELETE A LEAF NODE FROM A BST
   Deletes only if the node has NO children
   ========================================================= */

struct Node *deleteLeafNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteLeafNode(n->left, key);
    else if (key > n->data)
        n->right = deleteLeafNode(n->right, key);
    else if (n->left == NULL && n->right == NULL) {
        free(n);
        return NULL;
    }

    return n;
}

/* =========================================================
   Q27. DELETE A NODE HAVING EXACTLY ONE CHILD
   ========================================================= */

struct Node *deleteOneChildNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteOneChildNode(n->left, key);
    else if (key > n->data)
        n->right = deleteOneChildNode(n->right, key);
    else {
        if ((n->left == NULL) != (n->right == NULL)) {
            struct Node *child =
                (n->left != NULL) ? n->left : n->right;

            free(n);
            return child;
        }
    }

    return n;
}

/* =========================================================
   Q28. DELETE A NODE HAVING TWO CHILDREN
   Replace it with its inorder successor
   ========================================================= */

struct Node *deleteTwoChildrenNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteTwoChildrenNode(n->left, key);
    else if (key > n->data)
        n->right = deleteTwoChildrenNode(n->right, key);
    else if (n->left != NULL && n->right != NULL) {
        struct Node *successor = minimumBST(n->right);

        n->data = successor->data;
        n->right = deleteNode(n->right, successor->data);
    }

    return n;
}

/* =========================================================
   GENERAL BST DELETION HELPER
   Used by Q28 and Q29
   ========================================================= */

struct Node *deleteNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteNode(n->left, key);
    else if (key > n->data)
        n->right = deleteNode(n->right, key);
    else {
        /* Case 1: No children */
        if (n->left == NULL && n->right == NULL) {
            free(n);
            return NULL;
        }

        /* Case 2: Only right child */
        if (n->left == NULL) {
            struct Node *temp = n->right;
            free(n);
            return temp;
        }

        /* Case 3: Only left child */
        if (n->right == NULL) {
            struct Node *temp = n->left;
            free(n);
            return temp;
        }

        /* Case 4: Two children */
        struct Node *temp = minimumBST(n->right);

        n->data = temp->data;
        n->right = deleteNode(n->right, temp->data);
    }

    return n;
}

/* =========================================================
   Q29. DELETE A NODE FROM A BST
   Handles leaf, one-child and two-child cases
   ========================================================= */

/* Use:
   root = deleteNode(root, key);
*/

/* =========================================================
   Q30. DELETE THE ROOT NODE OF A BST
   ========================================================= */

/* Use:
   if (root != NULL)
       root = deleteNode(root, root->data);
*/

/* =========================================================
   Q31. FIND INORDER PREDECESSOR IN A BST
   Predecessor = largest value smaller than the key
   ========================================================= */

struct Node *predecessor(struct Node *n, int key) {
    struct Node *pred = NULL;

    while (n != NULL) {
        if (key > n->data) {
            pred = n;
            n = n->right;
        } else {
            n = n->left;
        }
    }

    return pred;
}

/* =========================================================
   Q32. FIND INORDER SUCCESSOR IN A BST
   Successor = smallest value larger than the key
   ========================================================= */

struct Node *successor(struct Node *n, int key) {
    struct Node *succ = NULL;

    while (n != NULL) {
        if (key < n->data) {
            succ = n;
            n = n->left;
        } else {
            n = n->right;
        }
    }

    return succ;
}

/* =========================================================
   Q33. COUNT NODES IN A BST
   Same recursive logic as a general binary tree
   ========================================================= */

/* Use:
   countNodes(root);
*/

/* =========================================================
   Q34. COUNT LEAF NODES IN A BST
   Same recursive logic as a general binary tree
   ========================================================= */

/* Use:
   countLeaves(root);
*/

/* =========================================================
   Q35. FIND HEIGHT OF A BST
   Same recursive logic as a general binary tree
   ========================================================= */

/* Use:
   height(root);
*/

/* =========================================================
   Q36. CHECK WHETHER A BINARY TREE IS A VALID BST
   Every value must lie within its allowed range
   ========================================================= */

int isBSTUtil(struct Node *n, long long min, long long max) {
    if (n == NULL)
        return 1;

    if (n->data <= min || n->data >= max)
        return 0;

    return isBSTUtil(n->left, min, n->data)
        && isBSTUtil(n->right, n->data, max);
}

int isBST(struct Node *n) {
    return isBSTUtil(n, LLONG_MIN, LLONG_MAX);
}

/* =========================================================
   Q37. FIND KTH SMALLEST ELEMENT IN A BST
   Inorder traversal visits values in sorted order
   ========================================================= */

void kthSmallestUtil(struct Node *n, int k, int *count, int *answer) {
    if (n == NULL || *count >= k)
        return;

    kthSmallestUtil(n->left, k, count, answer);

    (*count)++;

    if (*count == k) {
        *answer = n->data;
        return;
    }

    kthSmallestUtil(n->right, k, count, answer);
}

int kthSmallest(struct Node *n, int k) {
    int count = 0, answer = -1;

    if (k <= 0 || k > countNodes(n))
        return -1;

    kthSmallestUtil(n, k, &count, &answer);

    return answer;
}

/* =========================================================
   Q38. PRINT BST VALUES WITHIN A GIVEN RANGE
   Prints values between low and high, inclusive
   ========================================================= */

void printRange(struct Node *n, int low, int high) {
    if (n == NULL)
        return;

    if (n->data > low)
        printRange(n->left, low, high);

    if (n->data >= low && n->data <= high)
        printf("%d ", n->data);

    if (n->data < high)
        printRange(n->right, low, high);
}

/* =========================================================
   Q39. EXPRESSION TREE FROM POSTFIX + EVALUATION
   Example postfix: 23+4*
   Represents (2 + 3) * 4 = 20
   Assumes single-digit operands and binary operators
   ========================================================= */

struct ExprNode {
    char data;
    struct ExprNode *left, *right;
};

struct ExprNode *createExprNode(char x) {
    struct ExprNode *n = malloc(sizeof(struct ExprNode));

    if (n == NULL)
        return NULL;

    n->data = x;
    n->left = n->right = NULL;

    return n;
}

struct ExprNode *buildExpressionTree(char postfix[]) {
    struct ExprNode *stack[1000];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        struct ExprNode *n = createExprNode(postfix[i]);

        if (n == NULL)
            return NULL;

        if (postfix[i] == '+' || postfix[i] == '-' ||
            postfix[i] == '*' || postfix[i] == '/') {
            if (top < 1) {
                free(n);
                return NULL;
            }

            n->right = stack[top--];
            n->left = stack[top--];
        }

        stack[++top] = n;
    }

    if (top != 0)
        return NULL;

    return stack[top];
}

int evaluateExpression(struct ExprNode *n) {
    if (n == NULL)
        return 0;

    /* Operand */
    if (n->left == NULL && n->right == NULL)
        return n->data - '0';

    int l = evaluateExpression(n->left);
    int r = evaluateExpression(n->right);

    switch (n->data) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/':
            if (r == 0) {
                printf("Division by zero!\n");
                return 0;
            }
            return l / r;
    }

    return 0;
}

/* =========================================================
   EXTRA: THREADED BINARY TREE STRUCTURE AND INORDER TRAVERSAL
   Right thread points to the inorder successor
   ========================================================= */

struct ThreadNode {
    int data;
    struct ThreadNode *left, *right;
    int rightThread;
};

void threadedInorder(struct ThreadNode *n) {
    if (n == NULL)
        return;

    /* Go to the leftmost node */
    while (n->left != NULL)
        n = n->left;

    while (n != NULL) {
        printf("%d ", n->data);

        /* Follow the thread to the successor */
        if (n->rightThread)
            n = n->right;
        else {
            n = n->right;

            while (n != NULL && n->left != NULL)
                n = n->left;
        }
    }
}

/* =========================================================
   MAIN FUNCTION: DEMONSTRATION
   Delete this main if your lab asks for individual programs
   ========================================================= */

int main() {
    /* Build a BST using recursive insertion */
    root = insertRecursive(root, 50);
    root = insertRecursive(root, 30);
    root = insertRecursive(root, 70);
    root = insertRecursive(root, 20);
    root = insertRecursive(root, 40);
    root = insertRecursive(root, 60);
    root = insertRecursive(root, 80);

    printf("Inorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nPostorder: ");
    postorder(root);

    printf("\nLevel order: ");
    levelOrder(root);

    printf("\nTotal nodes: %d", countNodes(root));
    printf("\nLeaf nodes: %d", countLeaves(root));
    printf("\nInternal nodes: %d", countInternal(root));
    printf("\nHeight: %d", height(root));
    printf("\nSum: %d", sumNodes(root));

    struct Node *minNode = minimumBST(root);
    struct Node *maxNode = maximumBST(root);

    if (minNode != NULL)
        printf("\nBST minimum: %d", minNode->data);

    if (maxNode != NULL)
        printf("\nBST maximum: %d", maxNode->data);

    printf("\nSearch 40: %s",
           searchRecursive(root, 40) ? "Found" : "Not found");

    printf("\nValid BST: %s", isBST(root) ? "Yes" : "No");

    printf("\n3rd smallest: %d", kthSmallest(root, 3));

    printf("\nRange 30 to 70: ");
    printRange(root, 30, 70);

    printf("\n");

    /* Delete a node using general BST deletion */
    root = deleteNode(root, 30);

    printf("After deleting 30: ");
    inorder(root);

    /* Expression tree example */
    char postfix[] = "23+4*";
    struct ExprNode *expr = buildExpressionTree(postfix);

    if (expr != NULL)
        printf("\nExpression result: %d", evaluateExpression(expr));

    printf("\n");

    return 0;
}