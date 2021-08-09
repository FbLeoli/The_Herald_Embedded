#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Node
{
    char letter;
    int position;
    struct Node *dot;
    struct Node *dash;
};

const char letters[32] = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";

struct Node *
newNode(char data, int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node)); //allocating memory
    node->letter = data;
    node->position = value;
    node->dot = NULL;
    node->dash = NULL;
    return (node);
}

struct Node *createTree()
{
    struct Node *root = newNode('*', 1);
    struct Node **referenceNode = (struct Node **)malloc(sizeof(struct Node));
    int temp = 0;
    int counter = 1;
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

const char *decodeChar(int position)
{
    int temp = position;
    int counter = 1;
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
    static char str[10] = "";
    strcpy(str, "");
    for (int i = 0; i <= (sizeof(lastBranch) / sizeof(lastBranch[0]) - 1); i++)
    {
        if (lastBranch[i] == 0)
        {
            strncat(str, "0", sizeof str - strlen(str) - 1);
        }
        else if (lastBranch[i] == 1)
        {
            strncat(str, "1", sizeof str - strlen(str) - 1);
        }
    }
    strncat(str, "\0", 1);
    return str;
}

const char *alfa2morse(char *phrase)
{
    strupr(phrase);
    int len = 0;
    static char inMorse[500] = "";
    strcpy(inMorse, " ");
    do
    {
        for (int i = 2; i < sizeof(letters); i++)
        {
            if (phrase[len] == ' ')
            {
                strncat(inMorse, " ", sizeof inMorse - strlen(inMorse) - 1);
                break;
            }
            if (phrase[len] == letters[i])
            {
                strncat(inMorse, decodeChar(i), strlen(decodeChar(i)));
                break;
            }
        }
        len++;
        strncat(inMorse, " ", sizeof inMorse - strlen(inMorse) - 1);
    } while (phrase[len] != '\0');
    strncat(inMorse, "\0", sizeof inMorse - strlen(inMorse) - 1);
    return inMorse;
}