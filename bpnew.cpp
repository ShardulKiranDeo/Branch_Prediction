#include <bits/stdc++.h>
using namespace std;

long long bitset_to_signed_long_long(const bitset<32> &bits)
{
    // Convert the bitset to a 32-bit integer
    unsigned long long value = bits.to_ulong();

    // If the most significant bit (bit 31) is set, it represents a negative number
    if (bits[31])
    {
        // Convert the 32-bit number into a signed long long by sign-extending
        // and clearing the upper 32 bits.
        return static_cast<long long>(value) - (1LL << 32);
    }
    else
    {
        // If the most significant bit is not set, it's a positive number
        return static_cast<long long>(value);
    }
}

int br_check(string h, int length)
{
    string a, b;
    int i = 0;

    h = h.substr(3);
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

    string c = b.substr(25, 7);
    if (c == "1100011")
    {
        string d = b.substr(17, 3);

        if (d == "000" || d == "001" || d == "101" || d == "100" || d == "110" || d == "111")
        {
            return 1;
        }
    }
    return 0;
}

string hex2bin(string &h, int length)
{
    string a, b;

    int i = 0;
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
    while (b.size() < length)
    {
        b = b + "0";
    }
    return b;
}

int pow2(int k)
{
    return (1 << k); // Compute 2 raised to the power of k
}

// int bin2dec(string &c)
// { // c has to be 13 bit..
//     int flag5 = 0;
//     if (c[0] == '1')
//     {
//         flag5++;
//         int i = 12;
//         while (c[i] != '1')
//         {
//             c[i] = '1';
//             i--;
//         }
//         c[i] = '0';
//         for (int j = 0; j < 13; j++)
//         {
//             if (c[j] == '0')
//             {
//                 c[j] = '1';
//             }
//             else
//                 c[j] = '0';
//         }
//     }
//     int sum = 0;
//     for (int i = 12; i >= 0; i--)
//     {
//         int k = c[i] - '0';
//         sum += k * pow2(12 - i);
//     }
//     if (flag5 == 0)
//         return sum;
//     else
//         return -1 * sum;
// }

long long bin2dec(string &p)
{
    bitset<32> tr(p);
    long long vres = bitset_to_signed_long_long(tr);
    return vres;
}

long long sboffset(string &a)
{
    string b;
    b += a[0];
    b += a[24];
    b += a.substr(1, 6);
    b += a.substr(20, 4);
    b += '0';
    int madhu = 13;
    char shardul = b[0];
    while (madhu < 32)
    {
        madhu++;
        b = shardul + b;
    }
    
    return bin2dec(b);
}

unordered_map<long long, int> one_state
{

};

unordered_map<long long, string> two_state
{

};

struct BTBEntry
{
    vector<long long> branchAddress;
    vector<long long> targetAddress;
    vector<bool> validAlways_taken;
    vector<bool> validAlways_not_taken;
    vector<bool> validone_bit;
    vector<bool> validtwo_bit;
};

struct HistoryTableEntry
{
    vector<long long> branchAddress;
    vector<bool> taken;
};

BTBEntry BTB;

HistoryTableEntry History;

int number_of_branches = 0;


void predict_next(long long current_address, long long next_address, long long label)
{
   auto it = one_state.find(current_address);
    if (it == one_state.end())
    {
         one_state.insert({current_address, 0});
         two_state.insert({current_address, "00"});
    }
    number_of_branches++;
    History.branchAddress.push_back(current_address);
    BTB.branchAddress.push_back(current_address);
    BTB.targetAddress.push_back(current_address + label);

    if (next_address == current_address + label) // Always taken
    {
        BTB.validAlways_taken.push_back(true);
        History.taken.push_back(true);
    }
    else
    {
        BTB.validAlways_taken.push_back(false);
        History.taken.push_back(false);
    }

    if (next_address != current_address + label) // Always not taken
    {
        BTB.validAlways_not_taken.push_back(true);
    }
    else
    {
        BTB.validAlways_not_taken.push_back(false);
    }

    if (one_state[current_address] == 1) // One bit
    {
        if (next_address == current_address + label)
        {
            BTB.validone_bit.push_back(true);
        }
        else
        {
            BTB.validone_bit.push_back(false);
            one_state[current_address] = 0;
        }
    }
    else if (one_state[current_address] == 0)
    {
        if (next_address != current_address + label)
        {
            BTB.validone_bit.push_back(true);
        }
        else
        {
            BTB.validone_bit.push_back(false);
            one_state[current_address] = 1;
        }
    }

    if (two_state[current_address] == "00") // Two bit
    {
        if (next_address == current_address + label)
        {
            BTB.validtwo_bit.push_back(false);
            two_state[current_address] = "01";
        }
        else
        {
            BTB.validtwo_bit.push_back(true);
        }
    }
    else if (two_state[current_address] == "01")
    {
        if (next_address == current_address + label)
        {
            BTB.validtwo_bit.push_back(false);
            two_state[current_address] = "10";
        }
        else
        {
            BTB.validtwo_bit.push_back(true);
            two_state[current_address] = "00";
        }
    }
    else if (two_state[current_address] == "10")
    {
        if (next_address == current_address + label)
        {
            BTB.validtwo_bit.push_back(true);
           two_state[current_address] = "11";
        }
        else
        {
            BTB.validtwo_bit.push_back(false);
           two_state[current_address] = "01";
        }
    }
    else
    {
        if (next_address == current_address + label)
        {
            BTB.validtwo_bit.push_back(true);
        }
        else
        {
            BTB.validtwo_bit.push_back(false);
            two_state[current_address] = "10";
        }
    }
}

void Accuracy()
{
    int i = 0;
    float aAlways_taken = 0, aAlways_not_taken = 0, aOne_bit = 0, aTwo_bit = 0;
    while (i < number_of_branches)
    {
        if (BTB.validAlways_taken[i] == true)
        {
            aAlways_taken += 1;
        }
        if (BTB.validAlways_not_taken[i] == true)
        {
            aAlways_not_taken += 1;
        }
        if (BTB.validone_bit[i] == true)
        {
            aOne_bit += 1;
        }
        if (BTB.validtwo_bit[i] == true)
        {
            aTwo_bit += 1;
        }
        i++;
    }

    cout << "Acuracy of Always Taken = ";
    cout << (aAlways_taken) / number_of_branches * 100 << "%" << endl;
    cout << "Acuracy of Always not Taken = ";
    cout << (aAlways_not_taken) / number_of_branches * 100 << "%" << endl;
    cout << "Acuracy of One bit = ";
    cout << (aOne_bit) / number_of_branches * 100 << "%" << endl;
    cout << "Acuracy of Two bit = ";
    cout << (aTwo_bit) / number_of_branches * 100 << "%" << endl;
}

void printBTB()
{
    cout << "Branch Target Buffer - " << endl;
    cout << "Branch_Address "
         << "Target_Address "
         << "Always_Taken "
         << "Always_Not_Taken "
         << "1-bit "
         << "2-bit" << endl;
    int i;
    for (i = 0; i < number_of_branches; i++)
    {
        cout << hex << "   " << BTB.branchAddress[i] << "       " << BTB.targetAddress[i] << "         " << BTB.validAlways_taken[i] << "              " << BTB.validAlways_not_taken[i] << "           " << BTB.validone_bit[i] << "     " << BTB.validtwo_bit[i] << endl;
    }
}

void printVectorSizes()
{
    cout << "Size of branchAddress vector: " << BTB.branchAddress.size() << endl;
    cout << "Size of targetAddress vector: " << BTB.targetAddress.size() << endl;
    cout << "Size of validAlways_taken vector: " << BTB.validAlways_taken.size() << endl;
    cout << "Size of validAlways_not_taken vector: " << BTB.validAlways_not_taken.size() << endl;
    cout << "Size of validone_bit vector: " << BTB.validone_bit.size() << endl;
    cout << "Size of validtwo_bit vector: " << BTB.validtwo_bit.size() << endl;
}

int main()
{

    cout << "Enter file name with extension" << endl;
    string inputf;
    cin >> inputf;
    cout << inputf << endl;
    ifstream infile(inputf);

    if (!infile.is_open())
    {
        cout << "Error opening files" << endl;
        return -1;
    }

    vector<string> lines_vector;
    string t_line;

    // Read all lines into vector
    while (getline(infile, t_line))
    {
        if (t_line.empty())
        {
            continue;
        }
        lines_vector.push_back(t_line);
    }

    string line;

    for (long long i = 0; i < lines_vector.size(); i++)
    {
        istringstream iss(lines_vector[i]);
        vector<string> tokens;
        for (string token; iss >> token;)
        {
            tokens.push_back(token);
        }

        long long gft = 0;
        for (long long xc = 0; xc < tokens.size(); xc++)
        {
            if (tokens[xc] != "core")
            {
                gft++;
            }
            else
            {
                break;
            }
        }

        if (gft != 0)
        {
            tokens.erase(tokens.begin(), tokens.begin() + gft - 1);
        }

        if (tokens[0] != "core")
        {
            continue;
        }

        string pc_hex = tokens[2];
        string mc_hex = tokens[3];
       

        pc_hex = pc_hex.substr(2);
        string te_pc = hex2bin(pc_hex, 32);

        int res = br_check(mc_hex, 8);
        if (res == 1)
        {
            string temp = mc_hex.substr(2);
            temp = temp.substr(0, temp.size() - 1);
            string gh = hex2bin(temp, 32);
            long long temp_label_offset = sboffset(gh);

            if (i < lines_vector.size() - 1)
            {
                istringstream iss2(lines_vector[i + 1]);
                vector<string> tokens_2;
                for (string token_2; iss2 >> token_2;)
                {
                    tokens_2.push_back(token_2);
                }

                long long gft_2 = 0;
                for (long long xc_2 = 0; xc_2 < tokens_2.size(); xc_2++)
                {
                    if (tokens_2[xc_2] != "core")
                    {
                        gft_2++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (gft_2 != 0)
                {
                    tokens_2.erase(tokens_2.begin(), tokens_2.begin() + gft_2 - 1);
                }

                if (tokens_2[0] != "core")
                {
                    continue;
                }

                string pc_hex_2 = tokens_2[2];
                string mc_hex_2 = tokens_2[3];

                pc_hex_2 = pc_hex_2.substr(2);

                string te_pc_2 = hex2bin(pc_hex_2, 32);

                bitset<32> curr_val(te_pc);
                bitset<32> next_val(te_pc_2);

                long long curr_val_i = bitset_to_signed_long_long(curr_val);
                long long next_val_i = bitset_to_signed_long_long(next_val);

                predict_next(curr_val_i, next_val_i, temp_label_offset);
            }
        }
    }

    // printBTB();
    Accuracy();
   
    return 0;
}
