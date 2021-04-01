/*
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I
am a student. "，则输出"student. a am I"。

输入: "  hello    world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

考虑空字符串 ""

*/
class Solution {
public:
  string reverseWords(string s) {

    int len = s.size();
    string retstr = "";

    int i = s.size() - 1; // start

    while (i >= 0) {
      while (i >= 0 && s[i] == ' ') {
        i--;
      }

      //抵达字符串
      while (i >= 0 && s[i] != ' ') {
        i--;
      }

      //保存字符串开头
      int pos = i + 1;

      //添加字符串
      while (pos < len && s[pos] != ' ') {
        retstr += s[pos];
        pos++;
      }
      //追加空格
      retstr += ' ';
    }

    //循环删除末尾多余append的空格，处理空字符串形式
    while (retstr != "" && retstr[retstr.size() - 1] == ' ')
      retstr.erase(retstr.size() - 1, 1);

    return retstr;
  }
};