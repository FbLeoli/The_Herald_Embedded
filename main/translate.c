#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char letter;
    int position;
    struct Node *dot;
    struct Node *dash;
};

static int counter = 1;
const char letters[32] = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";

struct Node *
newNode(char data, int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node)); //allocating memory
    node->letter = data;
    node->position = value;
    node->dot = NULL;
    node->dash = NULL;
    counter++;
    return (node);
}

struct Node *createTree()
{
    struct Node *root = newNode('*', 1);
    struct Node **referenceNode = (struct Node **)malloc(sizeof(struct Node));
    int temp = 0;
    for (int i = 2; i < sizeof(letters); i++)
    {
        referenceNode = &root;
        counter = 1;
        temp = i;
        int lastBranch[4] = {2, 2, 2, 2};
        while (temp != 1)
        {
            if (temp % 2 == 0)
            {
                lastBranch[sizeof(lastBranch) / sizeof(lastBranch[0]) - counter] = 0;
            }
            else
            {
                lastBranch[sizeof(lastBranch) / sizeof(lastBranch[0]) - counter] = 1;
            }
            counter++;
            temp = temp / 2;
        }
        for (int j = 0; j < (sizeof(lastBranch) / sizeof(lastBranch[0])); j++)
        {
            if (lastBranch[j] == 0)
            {
                referenceNode = &((*referenceNode)->dot);
            }
            else if (lastBranch[j] == 1)
            {
                referenceNode = &((*referenceNode)->dash);
            }
            if (j == 3)
            {
                (*referenceNode) = newNode(letters[i], i);
            }
        }
    }
    return root;
}

int main()
{
    char letra = createTree()->dash->dash->dash->dash->letter;
    printf("%s", &letra);
    return 0;
}