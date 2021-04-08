/* 
给你一个字符串 s，由若干单词组成，单词之间用空格隔开。返回字符串中最后一个单词的长度。如果不存在最后一个单词，请返回 0 。

单词 是指仅由字母组成、不包含任何空格字符的最大子字符串。

示例 1：

输入：s = "Hello World"
输出：5
示例 2：

输入：s = " "
输出：0

*/

class Solution {
public:
    int lengthOfLastWord(string s) {
        // if(s.size() == 0)//不用考虑空串,题目要求为不为空串
        //     return 0;

        int first = s.size()-1;//倒序双指针求解
        int last;

        //定位到末尾首个单词
        while(s[first] == ' '){
            if(first == 0)//无字母
                return 0;
            first--;

            if(s[first] != ' '){
                last = first;
                break;
            }
        }

        while(s[first] != ' '){
            first--;
            if(first == 0){ //左边界first不为空格,即仅一个单词
                first--;
                break;
            }
        }
        
        return last -first;
    }
};