# search for longest compounded word

# assumption for input
# input -> list of strings
# string are in lowercase

# output -> longest compounded word
# if more than one longest compounded word then each one of them will be a appropriate answer
# program will return based on alphabetical order i.e. one that comes first in alphabetical order

# approach
# first sort the list as we want to process list in alphabetical order
# use trie data structure for storing sorted input list as it helps in seraching for a word faster
# searching of a word in trie 'O(s), s - length of string'

# time complexity - O()

import sys

sys.stdin = open('inputFile')
sys.stdout = open('output', 'w')

# list for maintaining word and suffix pair in each index
que = []


class TrieNode:

    def __init__(self, letter=None):
        self.letter = letter
        self.child = {}
        self.isEnd = False


class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):         # O(s), s -> length of word
        curr = self.root
        for i in range(len(word)):
            if curr.isEnd:
                que.append((word, word[i:]))
            if word[i] not in curr.child:
                curr.child[word[i]] = TrieNode(word[i])
            curr = curr.child[word[i]]
        curr.isEnd = True

    def handlePrefix(self, item):       # O(s), s -> length of word
        q = []
        curr = self.root
        word = item[1]
        for i in range(len(word)):
            if curr.isEnd:
                q.append((item[0], word[i:]))
            if word[i] not in curr.child:
                que.extend(q)
                return False
            curr = curr.child[word[i]]
        if not curr.isEnd:
            que.extend(q)
        return curr.isEnd

    def longestCompoundedWord(self):
        longestWord = ''
        secondLongestWord = ''
        for item in que:
            if len(item[0]) <= len(secondLongestWord):
                continue
            if self.handlePrefix(item):
                if len(longestWord) < len(item[0]):
                    secondLongestWord = longestWord
                    longestWord = item[0]
                else:
                    secondLongestWord = item[0]
        return (longestWord, secondLongestWord)


trie = Trie()
with open('inputFile') as fp:
    for line in fp.readlines():
        trie.insert(line.strip())
res = trie.longestCompoundedWord()
print('Longest Compounded Word: ', res[0])
print('Second Longest Compounded Word: ', res[1])
