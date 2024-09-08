#ifndef Assembler_hh
#define Assembler_hh
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Deaclarations of all conversions function
string to_binary_12(string &str);
string to_hexadecimal(string &str);
string to_binary_reg(string &str);
string convert(string &str);
string to_binary_20(string &str);

// Declarations of all instruction check functions
bool is_R(string str);
bool is_I(string str);
bool is_J(string str);
bool is_B(string str);
bool is_S(string str);
bool is_U(string str);

// Declarations of all functions
string R_type(string &instruction,ifstream &read,ll line_number);
string I_type(string &instruction,ifstream &read,ll line_number);
string J_type(string &instruction,ifstream &read,ll line_number,map <string,ll> store_LN,map <string,ll> count);
string B_type(string &instruction,ifstream &read,ll line_number,map <string,ll> store_LN,map <string,ll> count);
string S_type(string &instruction,ifstream &read,ll line_number);
string U_type(string &instruction,ifstream &read,ll line_number);


#endif