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

struct BTBEntry {
    vector<int> branchAddress;
    vector<int> targetAddress;
    vector<bool> validAlways_taken;
    vector<bool> validAlways_not_taken;
    vector<bool> validone_bit;
    vector<bool> validtwo_bit;
};

struct HistoryTableEntry {
    vector<int> branchAddress;
    vector<bool> taken;
};

BTBEntry BTB;

HistoryTableEntry History;


int number_of_branches = 0;
int one_state = 0;
int two_state[2] = {0,0};

void predict_next(int current_address, string predictor_method, int next_address, int label)
{number_of_branches++;
 History.branchAddress.push_back(current_address);
 BTB.branchAddress.push_back(current_address);
 BTB.targetAddress.push_back(current_address + label);


   
        if(next_address==current_address + label) //Always taken
        {
            BTB.validAlways_taken.push_back(true);
            History.taken.push_back(true);
        }
        else
        {
            BTB.validAlways_taken.push_back(false);
            History.taken.push_back(false);
        }
    
    
                if(next_address!=current_address + label) //Always not taken
                {
                    BTB.validAlways_not_taken.push_back(true);
                }
                else
                {
                    BTB.validAlways_not_taken.push_back(false);
                }
            
           
                        if(one_state==1) //One bit
                        {
                             if(next_address==current_address + label)
                             {
                                BTB.validone_bit.push_back(true);
                             }
                             else
                                {
                                  BTB.validone_bit.push_back(false);
                                  one_state = 0;
                                }
                        }
                        else if(one_state==0)
                            {
                                if(next_address!=current_address + label)
                                {
                                    BTB.validone_bit.push_back(true);
                                }
                                else
                                {
                                    BTB.validone_bit.push_back(false);
                                    one_state = 1;
                                }
                            }
                    
                    
                                if( two_state[0]==0 && two_state[1]==0) //Two bit
                                {
                                     if(next_address==current_address + label)
                                        {
                                            BTB.validtwo_bit.push_back(false);
                                            two_state[1] = 1;
                                        }
                                    else
                                        {
                                              BTB.validtwo_bit.push_back(true);
                                        }
                                }
                                else if(two_state[0]==0 && two_state[1]==1)
                                        {
                                            if(next_address==current_address + label)
                                             {
                                                    BTB.validtwo_bit.push_back(false);
                                                    two_state[1] = 0;
                                                    two_state[0] = 1;
                                            }
                                            else
                                            {
                                              BTB.validtwo_bit.push_back(true);
                                              two_state[1] = 0;
                                            }
                                        }
                                        else if(two_state[0]==1 && two_state[1]==0)
                                                {
                                                    if(next_address==current_address + label)
                                                   {
                                                        BTB.validtwo_bit.push_back(true);
                                                         two_state[1] = 1;
                                                    }
                                                    else
                                                    {
                                                        BTB.validtwo_bit.push_back(false);
                                                           two_state[0] = 0;
                                                           two_state[1] = 1;
                                                    }
                                                }
                                                else
                                                {
                                                     if(next_address==current_address + label)
                                                     {
                                                        BTB.validtwo_bit.push_back(true);
                                                        
                                                    }
                                                    else
                                                    {
                                                        BTB.validtwo_bit.push_back(false);
                                                           two_state[1] = 0;
                                                    }
                                                }
                            




}


void Accuracy()
{int i = 0 ;
float aAlways_taken=0, aAlways_not_taken=0, aOne_bit=0, aTwo_bit=0 ;
    while(i<number_of_branches)
    {
        if(BTB.validAlways_taken[i]==true)
        {
            aAlways_taken += 1;
        }
        if(BTB.validAlways_not_taken[i]==true)
        {
            aAlways_not_taken += 1;
        }
        if(BTB.validone_bit[i]==true)
        {
            aOne_bit += 1;
        }
        if(BTB.validtwo_bit[i]==true)
        {
            aTwo_bit += 1;
        }
     i++;
    }
    
    cout<<"Acuracy of Always Taken - ";
    cout<<(aAlways_taken)/number_of_branches*100<<endl;
    cout<<"Acuracy of Always not Taken - ";
    cout<<(aAlways_not_taken)/number_of_branches*100<<endl;
    cout<<"Acuracy of One bit - ";
    cout<<(aOne_bit)/number_of_branches*100<<endl;
    cout<<"Acuracy of Two bit - ";
    cout<<(aTwo_bit)/number_of_branches*100<<endl;
}


void printBTB()
{int i;
    for(i=0;i<number_of_branches;i++)
    {
        cout<<BTB.branchAddress[i]<<" "<<BTB.targetAddress[i]<<" "<<BTB.validAlways_taken[i]<<" "<<BTB.validAlways_not_taken[i]<<" "<<BTB.validone_bit[i]<<" "<<BTB.validtwo_bit[i]<<endl;
    }
}

int main(){
    return 0;
}
