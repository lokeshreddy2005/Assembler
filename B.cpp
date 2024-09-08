#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;

// B-type or not
bool is_B(string str)
{
    if(str=="beq"||str=="bne"||str=="blt"||str=="bge"||str=="bltu"||str=="bgeu"){
        return true;
    }
    return false;
}

// B-type function
string B_type(string &instruction,ifstream &read,ll line_number,map <string,ll> store_LN,map <string,ll> count)
{
    string instruction_32="";
    string whole;
    streampos pos=read.tellg();
    getline(read,whole);
    istringstream iss(whole);
    string rs1,rs2,label;
    string extra;
    if (iss>>rs1>>rs2>>label>>extra)
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
        if (iss1>>rs1>>rs2>>label)
        {
            goto OK;
        }
        cout<<"Not enough operands specified on line number "<<line_number<<"\n";
        exit(0);
    }
    OK:
    read>>rs1;
    rs1.pop_back();

    read>>rs2;
    rs2.pop_back();

    read>>label;
   
   // convert ABM values into original
    rs1=(convert(rs1)=="")?rs1:convert(rs1);
    rs2=(convert(rs2)=="")?rs2:convert(rs2);

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
        if(stoll(label)>=4095||stoll(label)<-4096){
            cout<<"Immediate value not present in range"<<endl;
            exit(0);
        }
        string imm= to_binary_20(label);
        //imm[12]
        instruction_32 += imm[7];
        // imm[10:5]
        for (ll i=9;i<=14;i++)
        {
            instruction_32 += imm[i];
        }
        // convert ABM values into original
        rs1=(convert(rs1)=="")?rs1:convert(rs1);
        rs2=(convert(rs2)=="")?rs2:convert(rs2);

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
        if(instruction=="beq"){
            instruction_32 += "000";
        }else if(instruction=="bne"){
            instruction_32 += "001";
        }else if(instruction=="blt"){
            instruction_32 += "100";
        }else if(instruction=="bge"){
            instruction_32 += "101";
        }else if(instruction=="bltu"){
            instruction_32 += "110";
        }else if(instruction=="bgeu"){
            instruction_32 += "111";
        }
        

        // imm[4:1]
        for (ll i=15;i<=18;i++)
        {
            instruction_32 += imm[i];
        }
        // imm[11]
        instruction_32 += imm[8];
        
        
    } else 
    {
        // if it is a label
        string read_whole;
        bool label_exists = false;
        ll temp_line_number=line_number;
        // if label already encountered in above instructions
        if(count[label]==1){
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
            if(imm>4095||imm<-4096){
                cout<<"This instruction immediate doesn't fit in the range !";
                exit(0);
            }
            string str_imm = to_string(imm);
            string bin_imm= to_binary_20(str_imm);

            // imm[12]
            instruction_32 += bin_imm[7];

            // imm[10:5]
            for (ll i=9;i<=14;i++)
            {
                instruction_32 += bin_imm[i];
            }

            // convert ABM values into original
            rs1=(convert(rs1)=="")?rs1:convert(rs1);
            rs2=(convert(rs2)=="")?rs2:convert(rs2);
    
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

            // funct3
            if(instruction=="beq"){
                instruction_32 += "000";
            }else if(instruction=="bne"){
                instruction_32 += "001";
            }else if(instruction=="blt"){
                instruction_32 += "100";
            }else if(instruction=="bge"){
                instruction_32 += "101";
            }else if(instruction=="bltu"){
                instruction_32 += "110";
            }else if(instruction=="bgeu"){
                instruction_32 += "111";
            }
            
            // imm[4:1]
            for (ll i=15;i<=18;i++)
            {
                instruction_32 += bin_imm[i];
            }
            // imm[11]
            instruction_32 += bin_imm[8];
        
        }
        
    }
    // opcode
    instruction_32+="1100011";
    
    return instruction_32;
    
}