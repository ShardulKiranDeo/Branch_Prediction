#include<bits/stdc++.h>
using namespace std;

int br_check(string &h, int length)
{
    string a, b;
    int i = 0;
    if(h[0] == '0' && h[1] == 'x'){
        h.erase(0,2);
    }
    while (i < 8)
    {
        switch (h[i])
        {
        case '0':
            a = "0000";
            break;
        case '1':
            a = "0001";
            break;
        case '2':
            a = "0010";
            break;
        case '3':
            a = "0011";
            break;
        case '4':
            a = "0100";
            break;
        case '5':
            a = "0101";
            break;
        case '6':
            a = "0110";
            break;
        case '7':
            a = "0111";
            break;
        case '8':
            a = "1000";
            break;
        case '9':
            a = "1001";
            break;
        case 'a':
        case 'A':
            a = "1010";
            break;
        case 'b':
        case 'B':
            a = "1011";
            break;
        case 'c':
        case 'C':
            a = "1100";
            break;
        case 'd':
        case 'D':
            a = "1101";
            break;
        case 'e':
        case 'E':
            a = "1110";
            break;
        case 'f':
        case 'F':
            a = "1111";
            break;
        }
        b += a;
        a.clear();
        i++;
    }
    while (b.size() < 32)
    {
        b = "0" + b;
    }
 string c = b.substr(25,7);
 if(c == "1100011"){
    string d = b.substr(16,3);
    if(d == "000" || d=="001" || d== "101"|| d== "100"){
        return 1;
    }
 }
    return 0;
}


int main(){
    return 0;
}
