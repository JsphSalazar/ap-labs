def longestString(s):
    chars = []
    longest = 0
    for i in s:
        if i not in chars:
            chars.append(i)
        else:
            chars = []
        if (longest < len(chars)):
            longest = len(chars)
    print(s, longest)

string1 = "abcabcbb"
string2 = "bbbbb"
string3 = "pwwkew"

longestString(string1)
longestString(string2)
longestString(string3)