#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// J-type or not
bool is_J(string str)
{
    if(str=="jal"){
        return true;
    }
    return false;
}

// J-type function
string J_type(string &instruction,ifstream &read,ll line_number,map <string,ll> store_LN,map <string,ll> count){
    string instruction_32="";
    
    string whole;
    streampos posi=read.tellg();
    getline(read,whole);
    istringstream iss(whole);
    string rd,imm;
    string extra;
    if (iss>>rd>>imm>>extra)
    {
        // Report when more no.of operands
        cout<<"Extra number of operands on line number "<<line_number<<"\n";
        exit(0);
    } else 
    {
        // Report when less no.of operands
        read.seekg(posi);
        string whole1;
        getline(read,whole1);
        read.seekg(posi);
        istringstream iss1(whole1);
        if(iss1>>rd>>imm)
        {
            goto OK;
        }
        cout<<"Not enough operands specified on line number "<<line_number<<"\n";
        exit(0);
    }

    OK:
    
    read>>rd;
    rd.pop_back();
    string label;
    read>>label;

    // convert ABM values into original
    rd=(convert(rd)=="")?rd:convert(rd);

    bool is_number=true;
    // checks number or label
    for (auto elem:label)
    {
        if (!isdigit(elem))
        {
            is_number=false;
            break;
        }
    }
    // if it is number
    if (is_number == true)
    {
        if(stoll(label)>1048575&&stoll(label)<-1048576){
            cout << "Error OOB(Out of bounds) encountered on the line number "<<line_number<<"\n";
            exit(0);
        }

        string imm=to_binary_20(label);
        // imm[20]
        instruction_32 += imm[0];

        //imm[10:1]
        for (ll i=9;i<19;i++)
        {
            instruction_32 += imm[i];
        }

        // imm[11]
        instruction_32 += imm[8];

        //imm[19:12]
        for (ll i=0;i<=7;i++)
        {
            instruction_32 += imm[i];
        }

        // extract number from rd
        string ll_imm="";
        for (auto elem:rd)
        {
            if (isdigit(elem))
            {
                ll_imm+=elem;
            }
        }
        instruction_32 += to_binary_reg(ll_imm);

    } else
    {
        // if it is a label
        string read_whole;
        bool label_exists = false;
        ll temp_line_number=line_number;
        if(count[label]==1){
            // if label already encountered in above instructions
            temp_line_number=store_LN[label];
            label_exists = true;
        }else{
            // checks below this instruction for label
            read.ignore();
            streampos pos1=read.tellg();
            while (getline(read,read_whole))
            {
                temp_line_number++;

                if (read_whole.find(label + ":") != string::npos)
                {
                    label_exists = true;
                    break;
                } 
            }
            read.seekg(pos1);
        }

        // if we don't find label anywhere then exit
        if (label_exists == false)
        {
            cout<<"Label present on line number "<<line_number<<" does not exist in the input file...";
            exit(0);
        } else 
        {
            // label exists
            ll imm=((temp_line_number)-(line_number))*4;    // To calculate the immediate value as one instruction is 32 bits...
            if(imm>1048575&&imm<-1048576){
                cout<<"This instruction immediate doesn't fit in the range !";
                exit(0);
            }

            string str_imm = to_string(imm);

            string bin_imm=to_binary_20(str_imm);

            // imm[20]
            instruction_32 += bin_imm[0];

            // imm[10:1]
            for (ll i=9;i<19;i++)
            {
                instruction_32 += bin_imm[i];
            }

            // imm[11]
            instruction_32 += bin_imm[8];

            //imm[19:12]
            for (ll i=0;i<=7;i++)
            {
                instruction_32 += bin_imm[i];
            }

            // extract number from rd
            string ll_imm="";
            for (auto elem:rd)
            {
                if (isdigit(elem))
                {
                    ll_imm+=elem;
                }
            }
            instruction_32 += to_binary_reg(ll_imm);

        }


    }
    // opcode
    instruction_32 += "1101111";

    return instruction_32;
}