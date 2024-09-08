#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;

// checks U-type or not
bool is_U(string str)
{
    if(str=="lui"||str=="auipc"){
        return true;
    }
    return false;
}

//  U-type instruction execution
string U_type(string &instruction,ifstream &read,ll line_number){
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
            if (iss1>>rd>>imm)
            {
                goto OK;
            }
            cout<<"Not enough operands specified on line number "<<line_number<<"\n";
            exit(0);
        }

        OK:
        read>>rd;
        rd.pop_back();
        rd=(convert(rd)=="")?rd:convert(rd);

        read>>imm;
        bool is_Hex=false;
        ll count_dig=0;
        bool legal=true;
        // checks number or hexadecimal
        for (auto elem:imm)
        {
            if (isdigit(elem))
            {
                count_dig++;
            } else if (elem=='x'||elem=='a'||elem=='b'||elem=='c'||elem=='d'||elem=='e'||elem=='f')
            {
                is_Hex=true;
            } else
            {
                legal=false;
                break;
            }
        }

        // if it is not any thing then report and exit
        if (legal==false)
        {
            cout << "Error encountered on the line number "<<line_number<<"\n";
            exit(0);
        }

        // if it is number
        if (is_Hex == false)
        {
            ll temp= stoll(imm);
            if(temp<0||temp>1048575){
                cout<<"Immediate value not present in range"<<endl;
                exit(0);
            }
            imm = to_string(temp);
            string ll_imm= to_binary_20(imm);
            instruction_32 += ll_imm;
        }else{
            // hexadecimal
            string Hex_str ="";
            if (imm[1]!='x')
            {
                cout << "Error encountered on the line number "<<line_number<<"\n";
                return 0;
            }
            for (ll i=imm.size()-5;i<imm.size();i++)
            {
                Hex_str += imm[i];
            }

            ll decimal_of_Hex=0;
            // hexadecimal to decimal
            for (ll i=0;i<Hex_str.size();i++)
            {
                char ch=Hex_str[i];
                if (ch >= '0' && ch <= '9') {
                    decimal_of_Hex += (ch - '0') * (pow(16, Hex_str.size() - 1 - i));
                }
                    else if (ch >= 'a' && ch <= 'f') {
                    decimal_of_Hex += (ch - 'a' + 10) * (pow(16, Hex_str.size() - 1 - i));
                } else {
                    cout << "Invalid hex digit encountered on line " << line_number << "\n";
                    exit(0);
                }
            }

            if(decimal_of_Hex<0||decimal_of_Hex>1048575){
                cout<<"Immediate value not present in range"<<endl;
                exit(0);
            }
            string str_dec_of_hex = to_string(decimal_of_Hex);
            instruction_32 += to_binary_20(str_dec_of_hex);
        }



        string ll_rd="";
        for (auto elem:rd)
        {
            if (isdigit(elem))
            {
                ll_rd+=elem;
            }
        }
        instruction_32 += to_binary_reg(ll_rd);

        //opcode
        if(instruction=="lui"){
            instruction_32 += "0110111";
        }else if(instruction=="auipc"){
            instruction_32 += "0010111";
        }

        return instruction_32;
}