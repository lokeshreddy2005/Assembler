#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;

// checks I-type or not
bool is_I(string str)
{
    if (str=="addi" || str=="andi" || str=="ori" || str=="xori" || str=="slli" || str=="srli" || str=="srai")
    {
        return true;
    }else if (str=="ld" || str=="lw" || str=="lh" || str=="lb" || str=="lhu" || str=="lbu" || str=="lwu" || str=="jalr")
    {
        return true;
    }else if(str=="jalr"){
        return true;
    }
    return false;
}

//  I-type instruction execution
string I_type(string &instruction,ifstream &read,ll line_number)
{
    string instruction_32="";
    string rd,rs1,imm;
    string imm_rs1;

    if (instruction=="addi" || instruction=="andi" || instruction=="ori" || instruction=="xori" || instruction=="slli" || instruction=="srli" || instruction=="srai")
    {
        // if it is any of the if loop instructions
        string whole;
        streampos pos=read.tellg();
        getline(read,whole);
        istringstream iss(whole);
        
        string extra;
        if (iss>>rd>>rs1>>imm>>extra)
        {
            // Report when more no.of operands
            cout<<"Extra number of operands on line number "<<line_number<<"\n";
            exit(0);
        } else 
        {
            // Report when less no.of operands
            read.seekg(pos);
            string whole1;
            getline(read,whole1);
            read.seekg(pos);
            istringstream iss1(whole1);
            if (iss1>>rd>>rs1>>imm)
            {
                goto OK;
            }
            cout<<"Not enough operands specified on line number "<<line_number<<"\n";
            exit(0);
        }
    } else 
    {
        // if those are remaining operands
        string whole;
        streampos pos=read.tellg();
        getline(read,whole);
        istringstream iss(whole);
        string extra;
        if (iss>>rd>>imm_rs1>>extra)
        {
            // Report when more no.of operands
            cout<<"Extra number of operands on line number "<<line_number<<"\n";
            exit(0);
        } else 
        {
            // Report when less no.of operands
            read.seekg(pos);
            string whole1;
            getline(read,whole1);
            read.seekg(pos);
            istringstream iss1(whole1);
            if (iss1>>rd>>imm_rs1)
            {
                goto OK;
            }
            cout<<"Not enough operands specified on line number "<<line_number<<"\n";
            exit(0);
        }
    }

    OK:
    read>>rd;
    rd.pop_back();

    // rs1 and imm values and different for addi type and ld types
    if (instruction=="addi" || instruction=="andi" || instruction=="ori" || instruction=="xori" || instruction=="slli" || instruction=="srli" || instruction=="srai")
    {
        read>>rs1;
        rs1.pop_back();
        read>>imm;
    }else if (instruction=="ld" || instruction=="lw" || instruction=="lh" || instruction=="lb" || instruction=="lhu" || instruction=="lbu" || instruction=="lwu" || instruction=="jalr")
    {
        string imm_and_rs1;
        read>>imm_and_rs1;
        ll st_in = -1;

        // extraction imm and register from imm(reg) type
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
    }

    // convert ABM values into original
    rd=(convert(rd)=="")?rd:convert(rd);
    rs1=(convert(rs1)=="")?rs1:convert(rs1);

    // Ranges for immediate values
    if(instruction=="slli" || instruction=="srli" || instruction=="srai"){
        if(stoll(imm)>63||stoll(imm)<0){
            cout<<"Immediate value not present in range"<<endl;
            exit(1);
        }
    }
    if(stoll(imm)>=2048||stoll(imm)<-2048){
        cout<<"Immediate value not present in range"<<endl;
        exit(1);
    }
    string imm_value_in_binary = to_binary_12(imm);
    
    // funct7 and imm[11:0] bits
    if(instruction=="slli"||instruction=="slli"){
        instruction_32 += "000000"+imm_value_in_binary.substr(6,6);
    }else if(instruction=="srai"){
        instruction_32 += "010000"+imm_value_in_binary.substr(6,6);
    }else{
        instruction_32 += imm_value_in_binary;
    }

    // extract number from rs1 
    string ll_rs1="";
    for (auto elem:rs1)
    {
        if (isdigit(elem))
        {
            ll_rs1 += elem;
        }
    }
    instruction_32 += to_binary_reg(ll_rs1);

    // funct3 bits...
    if(instruction=="addi"||instruction=="lb"||instruction=="jalr"){
        instruction_32+="000";
    }else if(instruction=="slli"||instruction=="lh"){
        instruction_32+="001";
    }else if(instruction=="slti"||instruction=="lw"){
        instruction_32+="010";
    }else if(instruction=="sltui"||instruction=="ld"){
        instruction_32+="011";
    }else if(instruction=="xori"||instruction=="lbu"){
        instruction_32+="100";
    }else if(instruction=="srli"||instruction=="srai"||instruction=="lhu"){
        instruction_32+="101";
    }else if(instruction=="ori"||instruction=="lwu"){
        instruction_32+="110";
    }else if(instruction=="andi"){
        instruction_32+="111";
    }

    // extract number from rd
    string ll_rd="";
    for (auto elem:rd)
    {
        if (isdigit(elem))
        {
            ll_rd += elem;
        }
    }
    instruction_32 += to_binary_reg(ll_rd);

    // opcode..
    if (instruction == "addi" || instruction == "xori" || instruction == "ori" || instruction == "andi" || instruction == "slli" || instruction == "srli" || instruction == "srai" || instruction == "slti" || instruction == "sltui") {
        instruction_32 += "0010011";
    } else if (instruction == "lb" || instruction == "lh" || instruction == "lw" || instruction == "ld" || instruction == "lbu" || instruction == "lhu" || instruction == "lwu" ) {
        instruction_32 += "0000011";
    }else if(instruction=="jalr"){
        instruction_32+="1100111";
    }

    return instruction_32;
}