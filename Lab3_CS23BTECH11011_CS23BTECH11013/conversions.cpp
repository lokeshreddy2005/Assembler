#include "Assembler.hh"
#include <bits/stdc++.h>
using namespace std;

// converts ABM values and retruns original registers
string convert(string &str){
    if(str=="zero"){
        return "x0";
    }else if(str=="ra"){
        return "x1";
    }else if(str=="sp"){
        return "x2";
    }else if(str=="gp"){
        return "x3";
    }else if(str=="tp"){
        return "x4";
    }else if(str=="t0"){
        return "x5";
    }else if(str=="t1"){
        return "x6";
    }else if(str=="t2"){
        return "x7";
    }else if(str=="s0"||str=="fp"){
        return "x8";
    }else if(str=="s1"){
        return "x9";
    }else if(str=="a0"){
        return "x10";
    }else if(str=="a1"){
        return "x11";
    }else if(str=="a2"){
        return "x12";
    }else if(str=="a3"){
        return "x13";
    }else if(str=="a4"){
        return "x14";
    }else if(str=="a5"){
        return "x15";
    }else if(str=="a6"){
        return "x16";
    }else if(str=="a7"){
        return "x17";
    }else if(str=="s2"){
        return "x18";
    }else if(str=="s3"){
        return "x19";
    }else if(str=="s4"){
        return "x20";
    }else if(str=="s5"){
        return "x21";
    }else if(str=="s6"){
        return "x22";
    }else if(str=="s7"){
        return "x23";
    }else if(str=="s8"){
        return "x24";
    }else if(str=="s9"){
        return "x25";
    }else if(str=="s10"){
        return "x26";
    }else if(str=="s11"){
        return "x27";
    }else if(str=="t3"){
        return "x28";
    }else if(str=="t4"){
        return "x29";
    }else if(str=="t5"){
        return "x30";
    }else if(str=="t6"){
        return "x31";
    }


    return "";
}


// Converts integer into 12 bit binary
string to_binary_12(string &str)
{
    ll inp = stoll(str);
    bool neg = false;
    if (inp < 0) {
        neg = true;
        inp *= -1;
    }

    string result = "";
    while (inp > 0) {
        result += (inp % 2 == 0) ? "0" : "1";
        inp /= 2;
    }

    // Pad the result to 12 bits
    while (result.size() < 12) {
        result += "0";
    }

    reverse(result.begin(), result.end());

    // If the input is negative, apply two's complement
    if (neg) {
        // Flip bits
        for (int i = 0; i < 12; i++) {
            result[i] = (result[i] == '1') ? '0' : '1';
        }

        // Add 1 to the flipped bits (two's complement)
        for (int i = 11; i >= 0; i--) {
            if (result[i] == '0') {
                result[i] = '1';
                break;
            } else {
                result[i] = '0';
            }
        }
    }

    return result;
}

// converts 4 bit binary into hexadecimal
string to_hexadecimal(string &str){
    map <string,string>hex;
    hex["0000"]="0";
    hex["0001"]="1";
    hex["0010"]="2";
    hex["0011"]="3";
    hex["0100"]="4";
    hex["0101"]="5";
    hex["0110"]="6";
    hex["0111"]="7";
    hex["1000"]="8";
    hex["1001"]="9";
    hex["1010"]="a";
    hex["1011"]="b";
    hex["1100"]="c";
    hex["1101"]="d";
    hex["1110"]="e";
    hex["1111"]="f";

    string hexa_decimal="";

    for(int i=0;i<str.size();i+=4){
        hexa_decimal+=hex[str.substr(i,4)];
    }

    return hexa_decimal;
}

// returns 5 bits for each register number 
string to_binary_reg(string &str){
    map <string,string> Binary_Storage;
    Binary_Storage["0"]  = "00000";
    Binary_Storage["1"]  = "00001";
    Binary_Storage["2"]  = "00010";
    Binary_Storage["3"]  = "00011";
    Binary_Storage["4"]  = "00100";
    Binary_Storage["5"]  = "00101";
    Binary_Storage["6"]  = "00110";
    Binary_Storage["7"]  = "00111";
    Binary_Storage["8"]  = "01000";
    Binary_Storage["9"]  = "01001";
    Binary_Storage["10"] = "01010";
    Binary_Storage["11"] = "01011";
    Binary_Storage["12"] = "01100";
    Binary_Storage["13"] = "01101";
    Binary_Storage["14"] = "01110";
    Binary_Storage["15"] = "01111";
    Binary_Storage["16"] = "10000";
    Binary_Storage["17"] = "10001";
    Binary_Storage["18"] = "10010";
    Binary_Storage["19"] = "10011";
    Binary_Storage["20"] = "10100";
    Binary_Storage["21"] = "10101";
    Binary_Storage["22"] = "10110";
    Binary_Storage["23"] = "10111";
    Binary_Storage["24"] = "11000";
    Binary_Storage["25"] = "11001";
    Binary_Storage["26"] = "11010";
    Binary_Storage["27"] = "11011";
    Binary_Storage["28"] = "11100";
    Binary_Storage["29"] = "11101";
    Binary_Storage["30"] = "11110";
    Binary_Storage["31"] = "11111";

    return Binary_Storage[str];
}

// converts number into 20 bit number
string to_binary_20(string &str)
{
    ll inp = stoll(str);
    bool neg = false;
    if (inp < 0) {
        neg = true;
        inp *= -1;
    }

    string result = "";
    while (inp > 0) {
        result += (inp % 2 == 0) ? "0" : "1";
        inp /= 2;
    }

    // Pad the result to 20 bits
    while (result.size() < 20) {
        result += "0";
    }

    reverse(result.begin(), result.end());

    // If the input is negative, apply two's complement
    if (neg) {
        // Flip bits
        for (int i = 0; i < 20; i++) {
            result[i] = (result[i] == '1') ? '0' : '1';
        }

        // Add 1 to the flipped bits (two's complement)
        for (int i = 19; i >= 0; i--) {
            if (result[i] == '0') {
                result[i] = '1';
                break;
            } else {
                result[i] = '0';
            }
        }
    }

    return result;
}
