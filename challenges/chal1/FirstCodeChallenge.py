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

longestString('The answer is "abc", with the length of ' + string1)
longestString('The answer is "b", with the length of ' + string2)
longestString('The answer is "wke", with the length of ' + string3)