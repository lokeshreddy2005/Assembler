#include"Assembler.hh"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main()
{
    // map to store line number and label
    map <string,ll> store_LN;          // LN stands for Line Number...
    // map to store label and its count
    map <string,ll> count;             // Map to store the count of the labels encountered...
    
    ofstream write("output.hex");
    
    ifstream read("input.s");
    ll line_number=1;
    string instruction;
    again:
    while(read>>instruction)
    {
        // if R-type
        if (is_R(instruction))
        {
            string instruction_32=R_type(instruction,read,line_number);
            if (instruction_32.size()<32)
            {
                cout<<"Commas are missing in the input.s file"<<"\n";
                return 0;
            }
            write<<to_hexadecimal(instruction_32)<<"\n";
        } 
        else if (is_I(instruction))   // if I-type
        {
            string instruction_32=I_type(instruction,read,line_number);
            if (instruction_32.size()<32)
            {
                cout<<"Commas are missing in the input.s file"<<"\n";
                return 0;
            }
            write<<to_hexadecimal(instruction_32)<<"\n";
        } 
        else if (is_J(instruction))     // if J-type
        {
            string instruction_32=J_type(instruction,read,line_number,store_LN,count);
            if (instruction_32.size()<32)
            {
                cout<<"Commas are missing in the input.s file"<<"\n";
                return 0;
            }
            write<<to_hexadecimal(instruction_32)<<"\n";
        } 
        else if (is_B(instruction))     // if B-type
        {
            string instruction_32=B_type(instruction,read,line_number,store_LN,count);
            if (instruction_32.size()<32)
            {
                cout<<"Commas are missing in the input.s file"<<"\n";
                return 0;
            }
            write<<to_hexadecimal(instruction_32)<<"\n";
        }
         else if (is_S(instruction))    // if S-type
        {
            string instruction_32=S_type(instruction,read,line_number);
            if (instruction_32.size()<32)
            {
                cout<<"Commas are missing in the input.s file"<<"\n";
                return 0;
            }
            write<<to_hexadecimal(instruction_32)<<"\n";
        }
         else if (is_U(instruction))    // if U-type
        {
            string instruction_32=U_type(instruction,read,line_number);
            if (instruction_32.size()<32)
            {
                cout<<"Commas are missing in the input.s file"<<"\n";
                return 0;
            }
            write<<to_hexadecimal(instruction_32)<<"\n";
        }
         else if (instruction[instruction.size()-1]==':')   // if it has label at start
        {
            // if it has only colon then report error and exit
            if (instruction.size()==1)
            {
                cout<<"Label not present, only colon present"<<"\n";
                return 0;
            }
            instruction.pop_back();

            // if encountered label was already encountered then report and exit
            if (count[instruction]>0)
            {
                cout<<"Hey, This label was encountered before in the file as well, maybe try renaming it"<<"\n";
                return 0;
            }
            store_LN[instruction]=line_number;
            count[instruction]++;
            goto again;
        } else
        {
            // if it is not any type or label , then report and exit
            cout<<"Encountered syntax error on line number "<<line_number<<"\n";
            cout<< "If the starting word was supposed to be the label, then either you missed the colon, or wrote it after some spaces"<<"\n";
            return 0;
        }

        // Increasing line number and go to next instruction 
        line_number++;
    }
    return 0;
}
