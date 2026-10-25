#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ============================================================
   NODE STRUCTURE AND GLOBAL ROOT
   ============================================================ */

// Used to create a normal Binary Tree or Binary Search Tree node
struct Node {
    int data;
    struct Node *left, *right;
};

// Global root of the tree
struct Node *root = NULL;

// Forward declaration required because deleteTwoChildrenNode
// calls deleteNode before its definition
struct Node *deleteNode(struct Node *n, int key);


/* ============================================================
   BASIC BINARY TREE FUNCTIONS
   ============================================================ */

// Q1. Write a function to count the total number of nodes in a Binary Tree
int countNodes(struct Node *n) {
    if (n == NULL)
        return 0;

    return 1 + countNodes(n->left) + countNodes(n->right);
}


// Q2. Write a function to count the leaf nodes in a Binary Tree
int countLeaves(struct Node *n) {
    if (n == NULL)
        return 0;

    if (n->left == NULL && n->right == NULL)
        return 1;

    return countLeaves(n->left) + countLeaves(n->right);
}


// Q3. Write a function to count internal nodes in a Binary Tree
// An internal node is a node having at least one child
int countInternal(struct Node *n) {
    if (n == NULL || (n->left == NULL && n->right == NULL))
        return 0;

    return 1 + countInternal(n->left) + countInternal(n->right);
}


// Q4. Write a function to find the height of a Binary Tree
// Height is measured in number of nodes; empty tree has height 0
int height(struct Node *n) {
    if (n == NULL)
        return 0;

    int l = height(n->left);
    int r = height(n->right);

    return 1 + (l > r ? l : r);
}


// Q5. Write a function to count nodes having exactly one child
int countOneChild(struct Node *n) {
    if (n == NULL)
        return 0;

    int current = ((n->left == NULL) != (n->right == NULL));

    return current + countOneChild(n->left)
                   + countOneChild(n->right);
}


// Q6. Write a function to count nodes having exactly two children
int countTwoChildren(struct Node *n) {
    if (n == NULL)
        return 0;

    int current = (n->left != NULL && n->right != NULL);

    return current + countTwoChildren(n->left)
                   + countTwoChildren(n->right);
}

// Alternative: Return the absolute difference between subtree node counts
int absoluteSubtreeDifference(struct Node *n) {
    if (n == NULL)
        return 0;

    int diff = countNodes(n->left) - countNodes(n->right);

    return diff < 0 ? -diff : diff;
}


// Q7. Write a function to calculate the sum of all nodes
int sumNodes(struct Node *n) {
    if (n == NULL)
        return 0;

    return n->data + sumNodes(n->left) + sumNodes(n->right);
}


// Q8. Write a function to find the minimum element in a Binary Tree
int minimumBT(struct Node *n) {
    if (n == NULL)
        return INT_MAX;

    int a = minimumBT(n->left);
    int b = minimumBT(n->right);
    int m = n->data;

    if (a < m) m = a;
    if (b < m) m = b;

    return m;
}


// Q9. Write a function to find the maximum element in a Binary Tree
int maximumBT(struct Node *n) {
    if (n == NULL)
        return INT_MIN;

    int a = maximumBT(n->left);
    int b = maximumBT(n->right);
    int m = n->data;

    if (a > m) m = a;
    if (b > m) m = b;

    return m;
}

// Q9A. Find the second smallest distinct element in a Binary Tree
void secondSmallestBTUtil(struct Node *n, int *smallest, int *second) {
    if (n == NULL)
        return;

    if (n->data < *smallest) {
        *second = *smallest;
        *smallest = n->data;
    }
    else if (n->data > *smallest && n->data < *second) {
        *second = n->data;
    }

    secondSmallestBTUtil(n->left, smallest, second);
    secondSmallestBTUtil(n->right, smallest, second);
}


// Q9A continued. Returns INT_MAX if no second distinct element exists
int secondSmallestBT(struct Node *n) {
    int smallest = INT_MAX, second = INT_MAX;

    secondSmallestBTUtil(n, &smallest, &second);

    return second;
}


// Q9B. Find the second largest distinct element in a Binary Tree
void secondLargestBTUtil(struct Node *n, int *largest, int *second) {
    if (n == NULL)
        return;

    if (n->data > *largest) {
        *second = *largest;
        *largest = n->data;
    }
    else if (n->data < *largest && n->data > *second) {
        *second = n->data;
    }

    secondLargestBTUtil(n->left, largest, second);
    secondLargestBTUtil(n->right, largest, second);
}


// Q9B continued. Returns INT_MIN if no second distinct element exists
int secondLargestBT(struct Node *n) {
    int largest = INT_MIN, second = INT_MIN;

    secondLargestBTUtil(n, &largest, &second);

    return second;
}


// Q10. Write a function to search for an element in a normal Binary Tree
int searchBT(struct Node *n, int key) {
    if (n == NULL)
        return 0;

    if (n->data == key)
        return 1;

    return searchBT(n->left, key) || searchBT(n->right, key);
}


// Q11. Write a function to copy a Binary Tree
struct Node *copyTree(struct Node *n) {
    if (n == NULL)
        return NULL;

    struct Node *temp = malloc(sizeof(struct Node));

    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    temp->data = n->data;
    temp->left = copyTree(n->left);
    temp->right = copyTree(n->right);

    return temp;
}


// Q12. Write a function to check whether two Binary Trees are identical
int identical(struct Node *a, struct Node *b) {
    if (a == NULL && b == NULL)
        return 1;

    if (a == NULL || b == NULL)
        return 0;

    return a->data == b->data
        && identical(a->left, b->left)
        && identical(a->right, b->right);
}


// Q13. Write a function to mirror a Binary Tree
// This modifies the original tree by swapping left and right subtrees
void mirrorTree(struct Node *n) {
    if (n == NULL)
        return;

    struct Node *temp = n->left;
    n->left = n->right;
    n->right = temp;

    mirrorTree(n->left);
    mirrorTree(n->right);
}


// Q14. Write a function to check whether two Binary Trees are mirrors
int areMirrors(struct Node *a, struct Node *b) {
    if (a == NULL && b == NULL)
        return 1;

    if (a == NULL || b == NULL)
        return 0;

    return a->data == b->data
        && areMirrors(a->left, b->right)
        && areMirrors(a->right, b->left);
}


// Q15. Write a function to check whether a Binary Tree is symmetric
int isSymmetric(struct Node *n) {
    if (n == NULL)
        return 1;

    return areMirrors(n->left, n->right);
}


/* ============================================================
   TREE TRAVERSALS
   ============================================================ */

// Q16. Write a recursive function for Preorder Traversal (Root, Left, Right)
void preorder(struct Node *n) {
    if (n == NULL)
        return;

    printf("%d ", n->data);
    preorder(n->left);
    preorder(n->right);
}


// Q17. Write a recursive function for Inorder Traversal (Left, Root, Right)
void inorder(struct Node *n) {
    if (n == NULL)
        return;

    inorder(n->left);
    printf("%d ", n->data);
    inorder(n->right);
}


// Q18. Write a recursive function for Postorder Traversal (Left, Right, Root)
void postorder(struct Node *n) {
    if (n == NULL)
        return;

    postorder(n->left);
    postorder(n->right);
    printf("%d ", n->data);
}


// Q19. Write an iterative function for Preorder Traversal
void iterativePreorder(struct Node *n) {
    if (n == NULL)
        return;

    struct Node *stack[1000];
    int top = -1;

    stack[++top] = n;

    while (top != -1) {
        n = stack[top--];
        printf("%d ", n->data);

        if (n->right != NULL)
            stack[++top] = n->right;

        if (n->left != NULL)
            stack[++top] = n->left;
    }
}


// Q20. Write an iterative function for Inorder Traversal
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


// Q21. Write an iterative function for Postorder Traversal using two stacks
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


// Q22. Write a function for Level Order Traversal using a queue
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


// Q23. Write a function to count nodes at a given level
// Root is considered level 1
int countAtLevel(struct Node *n, int level) {
    if (n == NULL || level < 1)
        return 0;

    if (level == 1)
        return 1;

    return countAtLevel(n->left, level - 1)
         + countAtLevel(n->right, level - 1);
}


// Q24. Write a function to find the sum of nodes at a given level
// Root is considered level 1
int sumAtLevel(struct Node *n, int level) {
    if (n == NULL || level < 1)
        return 0;

    if (level == 1)
        return n->data;

    return sumAtLevel(n->left, level - 1)
         + sumAtLevel(n->right, level - 1);
}


/* ============================================================
   ADVANCED BINARY TREE QUESTIONS
   ============================================================ */

// Q25. Write a function to find the diameter of a Binary Tree
// Diameter is the number of nodes on the longest path between two nodes
int diameterHeight(struct Node *n, int *diameter) {
    if (n == NULL)
        return 0;

    int l = diameterHeight(n->left, diameter);
    int r = diameterHeight(n->right, diameter);

    if (l + r + 1 > *diameter)
        *diameter = l + r + 1;

    return 1 + (l > r ? l : r);
}


// Q25 continued. Function to call to obtain the diameter
int diameter(struct Node *n) {
    int d = 0;
    diameterHeight(n, &d);
    return d;
}


// Q26. Write a function to check whether a Binary Tree is height-balanced
// Returns -1 internally if a subtree is unbalanced
int balancedHeight(struct Node *n) {
    if (n == NULL)
        return 0;

    int l = balancedHeight(n->left);

    if (l == -1)
        return -1;

    int r = balancedHeight(n->right);

    if (r == -1)
        return -1;

    if (abs(l - r) > 1)
        return -1;

    return 1 + (l > r ? l : r);
}


// Q26 continued. Returns 1 if balanced, otherwise 0
int isBalanced(struct Node *n) {
    return balancedHeight(n) != -1;
}


// Q27. Write a function to print all Root-to-Leaf paths
void printPathsUtil(struct Node *n, int path[], int len) {
    if (n == NULL)
        return;

    path[len++] = n->data;

    if (n->left == NULL && n->right == NULL) {
        for (int i = 0; i < len; i++)
            printf("%d ", path[i]);

        printf("\n");
        return;
    }

    printPathsUtil(n->left, path, len);
    printPathsUtil(n->right, path, len);
}


// Q27 continued. Function to call for printing Root-to-Leaf paths
void printRootToLeafPaths(struct Node *n) {
    int path[1000];
    printPathsUtil(n, path, 0);
}


// Q28. Write a function to check whether a Root-to-Leaf path has a given sum
int hasPathSum(struct Node *n, int target) {
    if (n == NULL)
        return 0;

    if (n->left == NULL && n->right == NULL)
        return n->data == target;

    return hasPathSum(n->left, target - n->data)
        || hasPathSum(n->right, target - n->data);
}


/* ============================================================
   BINARY SEARCH TREE INSERTION AND SEARCH
   ============================================================ */

// Q29. Write a recursive function to insert a node into a BST
struct Node *insertRecursive(struct Node *n, int key) {
    if (n == NULL) {
        struct Node *temp = malloc(sizeof(struct Node));

        if (temp == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }

        temp->data = key;
        temp->left = temp->right = NULL;

        return temp;
    }

    if (key < n->data)
        n->left = insertRecursive(n->left, key);
    else if (key > n->data)
        n->right = insertRecursive(n->right, key);

    return n;
}


// Q30. Write an iterative function to insert a node into a BST
// Uses the global root
void insertIterative(int key) {
    struct Node *temp = malloc(sizeof(struct Node));

    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    temp->data = key;
    temp->left = temp->right = NULL;

    if (root == NULL) {
        root = temp;
        return;
    }

    struct Node *n = root;
    struct Node *parent = NULL;

    while (n != NULL) {
        parent = n;

        if (key < n->data)
            n = n->left;
        else if (key > n->data)
            n = n->right;
        else {
            free(temp);
            return;
        }
    }

    if (key < parent->data)
        parent->left = temp;
    else
        parent->right = temp;
}


// Q31. Write a recursive function to search for a value in a BST
struct Node *searchRecursive(struct Node *n, int key) {
    if (n == NULL || n->data == key)
        return n;

    if (key < n->data)
        return searchRecursive(n->left, key);

    return searchRecursive(n->right, key);
}


// Q32. Write an iterative function to search for a value in a BST
struct Node *searchIterative(struct Node *n, int key) {
    while (n != NULL && n->data != key) {
        if (key < n->data)
            n = n->left;
        else
            n = n->right;
    }

    return n;
}


// Q33. Write a function to find the minimum element in a BST
// The minimum element is the leftmost node
struct Node *minimumBST(struct Node *n) {
    if (n == NULL)
        return NULL;

    while (n->left != NULL)
        n = n->left;

    return n;
}


// Q34. Write a function to find the maximum element in a BST
// The maximum element is the rightmost node
struct Node *maximumBST(struct Node *n) {
    if (n == NULL)
        return NULL;

    while (n->right != NULL)
        n = n->right;

    return n;
}


/* ============================================================
   BINARY SEARCH TREE DELETION
   ============================================================ */

// Q35. Write a function to delete a node from a BST
// Handles all three cases:
// 1. Leaf node
// 2. Node with one child
// 3. Node with two children
struct Node *deleteNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data) {
        n->left = deleteNode(n->left, key);
    }
    else if (key > n->data) {
        n->right = deleteNode(n->right, key);
    }
    else {
        // Case 1 and Case 2: zero or one child
        if (n->left == NULL) {
            struct Node *temp = n->right;
            free(n);
            return temp;
        }

        if (n->right == NULL) {
            struct Node *temp = n->left;
            free(n);
            return temp;
        }

        // Case 3: two children
        // Replace with inorder successor (smallest in right subtree)
        struct Node *temp = minimumBST(n->right);

        n->data = temp->data;

        n->right = deleteNode(n->right, temp->data);
    }

    return n;
}


// Q36. Write a function to delete a leaf node from a BST
// This only deletes the node if it is a leaf
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


// Q37. Write a function to delete a node having exactly one child
// This only deletes the target if it has exactly one child
struct Node *deleteOneChildNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteOneChildNode(n->left, key);
    else if (key > n->data)
        n->right = deleteOneChildNode(n->right, key);
    else if (n->left == NULL && n->right != NULL) {
        struct Node *temp = n->right;
        free(n);
        return temp;
    }
    else if (n->left != NULL && n->right == NULL) {
        struct Node *temp = n->left;
        free(n);
        return temp;
    }

    return n;
}

// Q37A. Delete a node having a left child but no right child
struct Node *deleteLeftOnlyNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteLeftOnlyNode(n->left, key);
    else if (key > n->data)
        n->right = deleteLeftOnlyNode(n->right, key);
    else if (n->left != NULL && n->right == NULL) {
        struct Node *temp = n->left;
        free(n);
        return temp;
    }

    return n;
}

// Q37B. Delete a node having a right child but no left child
struct Node *deleteRightOnlyNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteRightOnlyNode(n->left, key);
    else if (key > n->data)
        n->right = deleteRightOnlyNode(n->right, key);
    else if (n->left == NULL && n->right != NULL) {
        struct Node *temp = n->right;
        free(n);
        return temp;
    }

    return n;
}

// Q38. Write a function to delete a node having exactly two children
// This only deletes the target if it has two children
struct Node *deleteTwoChildrenNode(struct Node *n, int key) {
    if (n == NULL)
        return NULL;

    if (key < n->data)
        n->left = deleteTwoChildrenNode(n->left, key);
    else if (key > n->data)
        n->right = deleteTwoChildrenNode(n->right, key);
    else if (n->left != NULL && n->right != NULL) {
        struct Node *temp = minimumBST(n->right);

        n->data = temp->data;
        n->right = deleteNode(n->right, temp->data);
    }

    return n;
}


/* ============================================================
   MORE BST QUESTIONS
   ============================================================ */

// Q39. Write a function to find the inorder predecessor of a key in a BST
// Returns the largest value smaller than key
struct Node *predecessor(struct Node *n, int key) {
    struct Node *ans = NULL;

    while (n != NULL) {
        if (key > n->data) {
            ans = n;
            n = n->right;
        }
        else {
            n = n->left;
        }
    }

    return ans;
}


// Q40. Write a function to find the inorder successor of a key in a BST
// Returns the smallest value greater than key
struct Node *successor(struct Node *n, int key) {
    struct Node *ans = NULL;

    while (n != NULL) {
        if (key < n->data) {
            ans = n;
            n = n->left;
        }
        else {
            n = n->right;
        }
    }

    return ans;
}


// Q41. Write a function to check whether a Binary Tree is a valid BST
int isBSTUtil(struct Node *n, long long min, long long max) {
    if (n == NULL)
        return 1;

    if (n->data <= min || n->data >= max)
        return 0;

    return isBSTUtil(n->left, min, n->data)
        && isBSTUtil(n->right, n->data, max);
}


// Q41 continued. Function to call for checking a BST
int isBST(struct Node *n) {
    return isBSTUtil(n, LLONG_MIN, LLONG_MAX);
}


// Q42. Write a function to find the kth smallest element in a BST
// Inorder traversal of a BST gives values in sorted order
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


// Q42 continued. Returns -1 if k is invalid or the element doesn't exist
int kthSmallest(struct Node *n, int k) {
    int count = 0;
    int answer = -1;

    if (k <= 0)
        return -1;

    kthSmallestUtil(n, k, &count, &answer);

    return answer;
}


// Q43. Write a function to print all BST values within a given range
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


// Q44. Write a function to find the Lowest Common Ancestor of two keys in a BST
struct Node *lcaBST(struct Node *n, int a, int b) {
    while (n != NULL) {
        if (a < n->data && b < n->data)
            n = n->left;
        else if (a > n->data && b > n->data)
            n = n->right;
        else
            return n;
    }

    return NULL;
}


/* ============================================================
   EXPRESSION TREE QUESTIONS
   ============================================================ */

// Helper function for creating an expression tree node
struct Node *newNode(int value) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    n->data = value;
    n->left = n->right = NULL;

    return n;
}


// Q45. Write a function to build an Expression Tree from a postfix expression
// Assumes single-digit operands and operators +, -, *, /
struct Node *buildExpressionTree(char postfix[]) {
    struct Node *stack[1000];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (c == ' ')
            continue;

        if (c >= '0' && c <= '9') {
            stack[++top] = newNode(c - '0');
        }
        else {
            struct Node *n = newNode(c);

            if (top < 1) {
                printf("Invalid postfix expression\n");
                return NULL;
            }

            n->right = stack[top--];
            n->left = stack[top--];

            stack[++top] = n;
        }
    }

    if (top != 0) {
        printf("Invalid postfix expression\n");
        return NULL;
    }

    return stack[top];
}


// Q46. Write a function to evaluate an Expression Tree
// Assumes leaf nodes are single-digit operands
int evaluateExpressionTree(struct Node *n) {
    if (n == NULL)
        return 0;

    // Leaf node is an operand
    if (n->left == NULL && n->right == NULL)
        return n->data;

    int l = evaluateExpressionTree(n->left);
    int r = evaluateExpressionTree(n->right);

    switch (n->data) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/':
            if (r == 0) {
                printf("Division by zero\n");
                exit(1);
            }
            return l / r;
        default:
            return 0;
    }
}


// Q47. Write a function to print an Expression Tree in prefix form
// Operator is printed before left and right operands
void expressionPrefix(struct Node *n) {
    if (n == NULL)
        return;

    if (n->data >= 0 && n->data <= 9)
        printf("%d ", n->data);
    else
        printf("%c ", (char)n->data);

    expressionPrefix(n->left);
    expressionPrefix(n->right);
}


// Q48. Write a function to print an Expression Tree in postfix form
void expressionPostfix(struct Node *n) {
    if (n == NULL)
        return;

    expressionPostfix(n->left);
    expressionPostfix(n->right);

    if (n->data >= 0 && n->data <= 9)
        printf("%d ", n->data);
    else
        printf("%c ", (char)n->data);
}


/* ============================================================
   THREADED BINARY TREE BONUS
   ============================================================ */

// Bonus Q49. Structure for a simple inorder-threaded Binary Tree
// lthread = 1 means left points to inorder predecessor
// rthread = 1 means right points to inorder successor
struct ThreadNode {
    int data;
    struct ThreadNode *left, *right;
    int lthread, rthread;
};


// Bonus Q49. Find the leftmost node in a threaded Binary Tree
struct ThreadNode *threadLeftmost(struct ThreadNode *n) {
    if (n == NULL)
        return NULL;

    while (n->lthread == 0 && n->left != NULL)
        n = n->left;

    return n;
}


// Bonus Q49. Perform inorder traversal of a threaded Binary Tree
void threadedInorder(struct ThreadNode *n) {
    n = threadLeftmost(n);

    while (n != NULL) {
        printf("%d ", n->data);

        if (n->rthread == 1)
            n = n->right;
        else
            n = threadLeftmost(n->right);
    }
}


/* ============================================================
   MAIN FUNCTION
   ============================================================ */

// Demonstration of BST insertion, traversal, searching and deletion
// Change the values here to test different functions
int main(void) {
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

    printf("\nLevel Order: ");
    levelOrder(root);

    printf("\n\nTotal nodes: %d", countNodes(root));
    printf("\nLeaf nodes: %d", countLeaves(root));
    printf("\nInternal nodes: %d", countInternal(root));
    printf("\nHeight: %d", height(root));
    printf("\nSum: %d", sumNodes(root));
    printf("\nDiameter: %d", diameter(root));
    printf("\nBalanced: %s", isBalanced(root) ? "Yes" : "No");
    printf("\nIs BST: %s", isBST(root) ? "Yes" : "No");

    struct Node *min = minimumBST(root);
    struct Node *max = maximumBST(root);

    if (min != NULL)
        printf("\nMinimum BST value: %d", min->data);

    if (max != NULL)
        printf("\nMaximum BST value: %d", max->data);

    printf("\nSearch 40: %s",
           searchRecursive(root, 40) != NULL ? "Found" : "Not found");

    printf("\n3rd smallest: %d", kthSmallest(root, 3));

    printf("\nValues between 30 and 70: ");
    printRange(root, 30, 70);

    printf("\n\nRoot-to-leaf paths:\n");
    printRootToLeafPaths(root);

    printf("\nHas root-to-leaf path sum 100: %s",
           hasPathSum(root, 100) ? "Yes" : "No");

    struct Node *pred = predecessor(root, 50);
    struct Node *succ = successor(root, 50);

    if (pred != NULL)
        printf("\nPredecessor of 50: %d", pred->data);

    if (succ != NULL)
        printf("\nSuccessor of 50: %d", succ->data);

    struct Node *lca = lcaBST(root, 20, 40);

    if (lca != NULL)
        printf("\nLCA of 20 and 40: %d", lca->data);

    printf("\n\nDeleting node 30...\n");
    root = deleteNode(root, 30);

    printf("Inorder after deletion: ");
    inorder(root);

    printf("\n");

    // Test Q9A: Second smallest distinct element
printf("\nSecond smallest: ");
int secondSmall = secondSmallestBT(root);
if (secondSmall == INT_MAX)
    printf("Does not exist");
else
    printf("%d", secondSmall);

// Test Q9B: Second largest distinct element
printf("\nSecond largest: ");
int secondLarge = secondLargestBT(root);
if (secondLarge == INT_MIN)
    printf("Does not exist");
else
    printf("%d", secondLarge);

// Test Q6A: Difference between left and right subtree node counts
printf("\nSubtree node difference: %d",
       subtreeNodeDifference(root));

// Delete node 30 only if it has a left child and no right child
root = deleteLeftOnlyNode(root, 30);

// Delete node 70 only if it has a right child and no left child
root = deleteRightOnlyNode(root, 70);

    return 0;
}