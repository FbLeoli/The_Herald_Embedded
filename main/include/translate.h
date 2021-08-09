#ifndef TRANSLATE_H
#define TRANSLATE_H

const char letters[32];
struct Node *createTree();
const char *decodeChar(int position);
const char *alfa2morse(char *phrase);

#endif