def lps(pattern: str) -> list:
    m = len(pattern)
    l = [0]*m
    j = 0

    for i in range(1, m):
        while j > 0 and pattern[i] != pattern[j]:
            j = l[j-1]
        if pattern[i] == pattern[j]:
            j += 1
        l[i] = j

    return l


def kmp(text: str, pattern: str) -> list:
    l = lps(pattern)
    m = len(pattern)
    n = len(text)
    j = 0
    match = []

    for i in range(n):
        while j > 0 and text[i] != pattern[j]:
            j = l[j-1]
        if text[i] == pattern[j]:
            j += 1
        if j == m:
            match.append(i-j+1)
            j = l[j-1]

    return match


text = "abababacababcababac"
pattern = "ababac"
match = kmp(text, pattern)
print("Found pattern at index: ", match)
