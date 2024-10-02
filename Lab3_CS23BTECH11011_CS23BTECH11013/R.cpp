#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;

// checks str is R-type or not
bool is_R(string str)
{   
    if (str=="add" || str=="sub" || str=="and" || str=="or" || str=="xor" || str=="sll" || str=="srl" || str=="sra" || str=="slt" || str=="sltu" )
    {
        return true;
    }
    return false;
}


// Execute R-type instruction
string R_type(string &instruction,ifstream &read,ll line_number)
{
    string instruction_32="";
    string whole;
    streampos pos=read.tellg();
    getline(read,whole);
    istringstream iss(whole);
    string rd,rs1,rs2;
    string extra;

    // Checks if it has less or more less no.of operands
    if (iss>>rd>>rs1>>rs2>>extra)
    {
        // if has more no.of operands then reporting error and exit
        cout<<"Extra number of operands on line number "<<line_number<<"\n";
        exit(0);
    } else 
    {
        // if has less no.of operands then report error and exit
        read.seekg(pos);
        string whole1;
        getline(read,whole1);
        read.seekg(pos);
        istringstream iss1(whole1);
        if (iss1>>rd>>rs1>>rs2)
        {
            goto OK;
        }
        cout<<"Not enough operands specified on line number "<<line_number<<"\n";
        exit(0);
    }

    // if has correct no.of operands then execute
    OK:
    read>>rd;
    rd.pop_back();
    read>>rs1;
    rs1.pop_back();
    read>>rs2;

    // if rd,rs1,rs2 has ABM names then change it to original
    rd=(convert(rd)=="")?rd:convert(rd);
    rs1=(convert(rs1)=="")?rs1:convert(rs1);
    rs2=(convert(rs2)=="")?rs2:convert(rs2);

    // funct7 bits
    if(instruction=="sub"||instruction=="sra"){
        instruction_32+="0100000";
    }else{
        instruction_32+="0000000";
    }

    // extract number from register
    string ll_rs2="";
    for (auto elem:rs2)
    {
        if (isdigit(elem))
        {
            ll_rs2 += elem;
        }
    }
    // extract number from register
    instruction_32 += to_binary_reg(ll_rs2);
    string ll_rs1;
    for (auto elem:rs1)
    {
        if (isdigit(elem))
        {
            ll_rs1 += elem;
        }
    }
    instruction_32 += to_binary_reg(ll_rs1);

    // funct3 bits...
    if(instruction=="add"||instruction=="sub"){
        instruction_32+="000";
    }else if(instruction=="sll"){
        instruction_32+="001";
    }else if(instruction=="slt"){
        instruction_32+="010";
    }else if(instruction=="sltu"){
        instruction_32+="011";
    }else if(instruction=="xor"){
        instruction_32+="100";
    }else if(instruction=="srl"||instruction=="sra"){
        instruction_32+="101";
    }else if(instruction=="or"){
        instruction_32+="110";
    }else if(instruction=="and"){
        instruction_32+="111";
    }

    // extract number from register
    string ll_rd="";
    for (auto elem:rd)
    {
        if (isdigit(elem))
        {
            ll_rd += elem;
        }
    }
    instruction_32 += to_binary_reg(ll_rd);
    
    // opcode....
    instruction_32 += "0110011";
    
    return instruction_32;
}