#include <stdlib.h>
#include "stdio.h"

const int BUFFER_SIZE = 16;
const int linePerPage = 20;

int compare(char *str1, char *str2) {
    if (str1 == NULL || str2 == NULL)
        if (str1 == NULL && str2 == NULL)
            return 0;
        else if (str1 == NULL)
            return -1;
        else return 1;
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    }
    return 0;
}

typedef struct Word {
    char *key;
    int lineNumber;
    int pageNumber;
} Word;

Word nextWord(FILE *file, int *lineNumber, int *page);

typedef struct Node {
    Word key;
    unsigned char height;
    struct Node *left;
    struct Node *right;
} Node;

unsigned char height(Node *p) {
    return p ? p->height : (unsigned char) 0;
}

int bfactor(Node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(Node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (unsigned char) ((hl > hr ? hl : hr) + 1);
}

Node *rotateright(Node *p) // правый поворот вокруг p
{
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Node *initNode(Word word) {
    Node *node = malloc(sizeof(Node));
    node->key = word;
    node->right = NULL;
    node->left = NULL;
    node->height = 0;
    return node;
}

Node *rotateleft(Node *q) // левый поворот вокруг q
{
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

Node *balance(Node *p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

Node *insert(Node *p, Word k) // вставка ключа k в дерево с корнем p
{
    if (!p) {
        return initNode(k);
    };
    if (compare(k.key, p->key.key) < 0)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void freeNode(Node *p) {
    if (p != NULL) {
        freeNode(p->left);
        freeNode(p->right);
        free(p->key.key);
        free(p);
    }
}

void printNode(Node *node) {
    if (node == NULL)
        return;
    printNode(node->left);
    printf("%s: %d %d\n", node->key.key, node->key.lineNumber, node->key.pageNumber);
    printNode(node->right);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Необходимо указать название файла");
        return 0;
    }
    Node *rootNode;
    FILE *file = fopen(argv[1], "r");
    int page = 1;
    int line = 1;

    if (file == NULL) {
        printf("Невозможно открыть файл");
        return 0;
    }
    Word word = nextWord(file, &line, &page);
    rootNode = initNode(word);
    while ((word = nextWord(file, &line, &page)).key != NULL) {
        insert(rootNode, word);
    }

    printNode(rootNode);
    freeNode(rootNode);
    fclose(file);
    return 0;
}

Word nextWord(FILE *file, int *lineNumber, int *page) {
    int bufferSize = BUFFER_SIZE;
    int count = 0;
    char *word = (char *) calloc((size_t) bufferSize, sizeof(char));
    int tmpChar = 0;
    Word toOut;
    toOut.lineNumber = *lineNumber;
    toOut.pageNumber = *page;
    while ((tmpChar = fgetc(file)) != EOF && tmpChar != ' ' && tmpChar != ',') {
        if (tmpChar == '\n') {
            (*lineNumber)++;
            break;
        }
        word[count++] = (char) tmpChar;
        if (count == bufferSize) {
            bufferSize *= 1.5;
            word = (char *) realloc(word, bufferSize * sizeof(char));
        }
    }
    word[count] = 0;
    if (count == 0) {
        free(word);
        word = NULL;
    }
    toOut.key = word;
    if (*lineNumber > linePerPage) {
        *lineNumber = 1;
        (*page)++;
    }
    return toOut;
}
