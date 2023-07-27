#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN 7

struct tnode {
    struct tnode *left;   /*used when in tree*/
    struct tnode *right;  /*used when in tree*/
    struct tnode *parent; /*used when in tree*/
    struct tnode *next;   /*used when in list*/
    float freq;
    int isleaf;
    char symbol;
};

/*global variables*/
char code[MAX_SYMBOLS][MAX_LEN];
struct tnode *root = NULL;  /*tree of symbols*/
struct tnode *qhead = NULL; /*list of current symbols*/
struct cnode *chead = NULL; /*list of code*/

/*
    @function   talloc
    @desc       allocates new node
*/
struct tnode *talloc(int symbol, float freq)
{
    struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
    if (p != NULL) {
        p->left = p->right = p->parent = p->next = NULL;
        p->symbol = symbol;
        p->freq = freq;
        p->isleaf = 1;
    }
    return p;
}

/*
    @function display_tnode_list
    @desc     displays the list of tnodes during code construction
*/
void pq_display(struct tnode *head)
{
    struct tnode *p = NULL;
    printf("list:");
    for (p = head; p != NULL; p = p->next) {
        printf("(%c,%f) ", p->symbol, p->freq);
    }
    printf("\n");
}

/*
    @function pq_insert
    @desc     inserts an element into the priority queue
    NOTE:     makes use of global variable qhead
*/
void pq_insert(struct tnode *p)
{
    struct tnode *curr = NULL;
    struct tnode *prev = NULL;

    if (qhead == NULL) {
        qhead = p;
        return;
    }

    if (p->freq <= qhead->freq) {
        p->next = qhead;
        qhead = p;
    } else {
        if (qhead->next == NULL) {
            qhead->next = p;
            return;
        }
        curr = qhead->next;
        prev = qhead;

        while (p->freq > curr->freq) {
            if (curr->next == NULL) {
                curr->next = p;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        p->next = curr;
        prev->next = p;
    }
}

/*
    @function   pq_free
    @desc       free resources from the priority queue
*/
void pq_free(struct tnode *p)
{
    struct tnode *curr = p, *next;

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void tree_free(struct tnode *t)
{
    if (t == NULL)
        return;

    if (t->left)
        tree_free(t->left);
    if (t->right)
        tree_free(t->right);

    free(t);
}

/*
    @function pq_pop
    @desc     removes the first element
    NOTE:     makes use of global variable qhead
*/
struct tnode *pq_pop()
{
    if (qhead == NULL)
        return NULL;

    struct tnode *p = qhead;
    qhead = qhead->next;

    printf("popped:%c,%f\n", p->symbol, p->freq);
    return p;
}

/*
        @function build_code
        @desc     generates the string codes given the tree
        NOTE: makes use of the global variable root
*/
void generate_code(struct tnode *root, int depth)
{
    int symbol;
    int len; /*length of code*/
    if (root->isleaf) {
        symbol = root->symbol;
        len = depth - 1;
        /*start backwards*/

        struct tnode *par = root->parent;
        struct tnode *prev = root;
        if (root->symbol == 'b')
            printf("\n");
        do {
            if (par->left->freq == par->right->freq ||
                prev->freq == par->left->freq)
                code[symbol][len] = '0';
            else
                code[symbol][len] = '1';
            len--;
            prev = par;
        } while ((par = par->parent) != NULL);
        printf("built code:%c,%s\n", symbol, code[symbol]);
    } else {
        generate_code(root->left, depth + 1);
        generate_code(root->right, depth + 1);
    }
}

/*
        @func	dump_code
        @desc	output code file
*/
void dump_code(FILE *fp)
{
    int i = 0;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        if (code[i][0]) /*non empty*/
            fprintf(fp, "%c %s\n", i, code[i]);
    }
}

/*
        @func	encode
        @desc	outputs compressed stream
*/
void encode(char *str, FILE *fout)
{
    while (*str) {
        fprintf(fout, "%s", code[*str]);
        str++;
    }
}

/*
    @function main
*/
int main()
{
    /*test pq*/
    struct tnode *p = NULL;
    struct tnode *lc, *rc;
    float freq[] = {0.01, 0.04, 0.05, 0.11, 0.19, 0.20, 0.4};
    int NCHAR = 7; /*number of characters*/
    int i = 0;
    const char *CODE_FILE = "code.txt";
    const char *OUT_FILE = "encoded.txt";

    FILE *fout = NULL;
    /*zero out code*/
    memset(code, 0, sizeof(code));

    qhead = NULL;
    /*initialize with freq*/
    for (i = 0; i < NCHAR; i++) {
        pq_insert(talloc('a' + i, freq[i]));
    }
    /*build tree*/
    for (i = 0; i < NCHAR - 1; i++) {
        lc = pq_pop();
        rc = pq_pop();
        /*create parent*/
        p = talloc(0, lc->freq + rc->freq);
        /*set parent link*/
        lc->parent = rc->parent = p;
        /*set child link*/
        p->right = rc;
        p->left = lc;
        /*make it non-leaf*/
        p->isleaf = 0;
        /*add the new node to the queue*/
        pq_insert(p);
        /* free resources */
    }
    /*get root*/
    root = pq_pop();

    /*build code*/
    generate_code(root, 0);

    /*output code*/
    puts("code:");
    fout = fopen(CODE_FILE, "w");
    dump_code(stdout);
    dump_code(fout);
    fclose(fout);

    /*encode a sample string*/
    puts("orginal: abba cafe bad");
    fout = fopen(OUT_FILE, "w");
    encode("abba cafe bad", stdout);
    encode("abba cafe bad", fout);

    fclose(fout);
    tree_free(root);
}
