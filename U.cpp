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
string U_type(string &instruction, ifstream &read, ll line_number) {
    string instruction_32 = "";
    string whole;
    streampos posi = read.tellg();
    getline(read, whole);
    istringstream iss(whole);
    string rd, imm, extra;

    if (iss >> rd >> imm >> extra) {
        cout << "Extra number of operands on line number " << line_number << "\n";
        exit(0);
    } 

    rd.pop_back();
    rd = (convert(rd) == "") ? rd : convert(rd);

    bool isHex = (imm.substr(0, 2) == "0x");
    ll immediate_value;

    if (isHex) {
        immediate_value = stoll(imm, nullptr, 16);
    } else {
        immediate_value = stoll(imm);
    }

    if (immediate_value > 1048575) {
        cout << "Immediate value not present in range" << endl;
        exit(0);
    }
    string imm_str=to_string(immediate_value);

    instruction_32 += to_binary_20(imm_str);

    string ll_rd = "";
    for (auto elem : rd) {
        if (isdigit(elem)) {
            ll_rd += elem;
        }
    }
    instruction_32 += to_binary_reg(ll_rd);

    // opcode
    if (instruction == "lui") {
        instruction_32 += "0110111";
    } else if (instruction == "auipc") {
        instruction_32 += "0010111";
    }

    return instruction_32;
}
