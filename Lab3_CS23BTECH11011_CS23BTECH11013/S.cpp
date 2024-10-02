#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;

// checks S-type or not
bool is_S(string str)
{
    if(str=="sb"||str=="sh"||str=="sw"||str=="sd"){
        return true;
    }
    return false;
}

// S-type instruction function
string S_type(string &instruction,ifstream &read,ll line_number)
{
    string instruction_32="";
    string whole;
    streampos pos=read.tellg();
    getline(read,whole);
    istringstream iss(whole);
    string rs2,imm_and_rs1;
    string extra;
    if (iss>>rs2>>imm_and_rs1>>extra)
    {
        // Report when more no.of operands
        cout<<"Extra number of operands on line number "<<line_number<<", or there is an extra space in existing operands"<<"\n";
        exit(0);
    } else 
    {
        // Report when less no.of operands
        read.seekg(pos);
        string whole1;
        getline(read,whole1);
        read.seekg(pos);
        istringstream iss1(whole1);
        if (iss1>>rs2>>imm_and_rs1)
        {
            goto OK;
        }
        cout<<"Not enough operands specified on line number "<<line_number<<"\n";
            exit(0);
    }
    OK:
    read>>rs2;
    rs2.pop_back();
    read>>imm_and_rs1;
    
    // extraction imm and register from imm(reg) type
    string imm="";
    ll st_in = -1;
    for (ll i=0;i<imm_and_rs1.size();i++)
    {
        if (imm_and_rs1[i]=='(')
        {
            st_in = i;
            break;
        } else
        {
            imm+=imm_and_rs1[i];
        }
    }
    
    string rs1="";
    for (ll i=st_in+1;i<imm_and_rs1.size();i++)
    {
        if (imm_and_rs1[i]==')')
        {
            break;
        } else 
        {
            rs1+=imm_and_rs1[i];
        }
    }

    // convert ABM values into original
    rs1=(convert(rs1)=="")?rs1:convert(rs1);
    rs2=(convert(rs2)=="")?rs2:convert(rs2);

    // Ranges for immediate values
    if(stoll(imm)>=2048||stoll(imm)<-2048){
        cout<<"Immediate value not present in range"<<endl;
        exit(0);
    }

    string imm_in_binary=to_binary_12(imm);

    // imm[11:5]
    for (ll i=0;i<7;i++)
    {
        instruction_32+=imm_in_binary[i];
    }

    // extract number from rs2 
    string ll_rs2="";
    for (auto elem:rs2)
    {
        if (isdigit(elem))
        {
            ll_rs2+=elem;
        }
    }            
    instruction_32 += to_binary_reg(ll_rs2);

    // extract number from rs1 
    string ll_rs1="";
    for (auto elem:rs1)
    {
        if (isdigit(elem))
        {
            ll_rs1+=elem;
        }
    }
    instruction_32 += to_binary_reg(ll_rs1);
    
    // funct3 bits
    if(instruction=="sb"){
        instruction_32+="000";
    }else if(instruction=="sh"){
        instruction_32+="001";
    }else if(instruction=="sw"){
        instruction_32+="010";
    }else if(instruction=="sd"){
        instruction_32+="011";
    }
    
    // imm[4:0] bits
    for (ll i=7;i<12;i++)
    {
        instruction_32 += imm_in_binary[i];
    }

    // opcode
    instruction_32+="0100011";

    return instruction_32;
}