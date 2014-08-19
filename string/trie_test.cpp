#include "gtest/gtest.h"
#include "./trie.cpp"

TEST(Trie, Small){
    Node* root = new Node();
    for(int i = 0; i < 128; i++) {
        Node* p = find(root, string(2, (char)i));
        p->value = i;
    }
    for(int i = 0; i < 128; i++) {
        ASSERT_EQ(i, root->next[i]->next[i]->value);
    }
}
