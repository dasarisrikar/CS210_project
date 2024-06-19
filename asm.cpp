/**********************
Name:Dasari Srikar
Roll no.:2201CS21
***********************/
#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class print{
	public:
		string first,second,third,four;
};
multimap<string,string> memory;
unordered_map<string,string> labelMap;
bool check(string &s) {
    for (int i = 0; i < s.length(); ++i) {
        if (i == 0 && s[i] == '-') {
            continue; // Skip the negative sign at the beginning
        }
        if (i == 0 && s[i] == '+') {
            continue; // Skip the negative sign at the beginning
        }
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}


string hexadecimal(int a) {
    int x;
    string hex;
    while (a != 0) {
        x = a % 16;
        a = a / 16;
        if (x < 10) {
            hex.insert(0, 1, '0' + x); // Convert integer x to character and insert
        } else {
            hex.insert(0, 1, 'a' + (x - 10)); // Convert integer x to character and insert
        }
    }
    int y = 6 - hex.size();
    for (int i = 0; i < y; i++) {
        hex.insert(0, 1, '0');
    }
    return hex;
}
string twocomp(const string &s) {
    int num=stoi(s);
    int a=pow(2,24);
    if(num>=0){
       return hexadecimal(num);
    }
    else{
       return hexadecimal(a+num);
    }
}
void replaceLabelsWithValues(vector<print>& passfunc) {
    int current_address = 0;
    unordered_map<string, int> labelAddresses;

    // Find addresses of all labels
    for (int i = 0; i < passfunc.size(); ++i) {
        if (!passfunc[i].first.empty()) {
            labelAddresses[passfunc[i].first] = i;
        }
    }

    // Replace labels with values
    current_address = 0;
    for (int i = 0; i < passfunc.size(); ++i) {
        if (!passfunc[i].third.empty() && labelMap.find(passfunc[i].third) != labelMap.end()) {
            passfunc[i].third = labelMap[passfunc[i].third];
        }

        if (passfunc[i].second == "brz" || passfunc[i].second == "brlz" || passfunc[i].second == "br" || passfunc[i].second == "call") {
            if (!check(passfunc[i].third)) {
                int target_address = i;
                int label_address = labelAddresses[passfunc[i].third];
                passfunc[i].third = to_string(label_address-target_address);
            }
        }

        ++current_address;
    }
}


void error(vector<print> &passfunc,int stop){
    int sonta=0;
    string e;
    vector<string> error;
     multimap<string, string>::iterator iter;
    for (iter = memory.begin(); iter != memory.end(); ++iter) {
        if (iter != memory.end() && next(iter) != memory.end() && iter->first == next(iter)->first) {
            string e = iter->first + " label repeated";
            error.push_back(e);
            sonta++;
        }
    }
    for(int i=0;i<passfunc.size();i++){
        if(passfunc[i].second=="ldc"||passfunc[i].second=="SET"||passfunc[i].second=="data"||passfunc[i].second=="adc"||passfunc[i].second=="ldl"||passfunc[i].second=="stl"||passfunc[i].second=="ldnl"||passfunc[i].second=="stnl"||passfunc[i].second=="adj"||passfunc[i].second=="call"||passfunc[i].second=="brz"||passfunc[i].second=="brlz"||passfunc[i].second=="br"){
            if(!check(passfunc[i].third)){
               e=hexadecimal(i);
               e=e+" ";
               e=e+" not a number";
               error.push_back(e);
               sonta++;
            }
        }
        else if(passfunc[i].second=="add"||passfunc[i].second=="a2sp"||passfunc[i].second=="sub"||passfunc[i].second=="shl"||passfunc[i].second=="shr"||passfunc[i].second=="sp2a"||passfunc[i].second=="return"||passfunc[i].second=="HALT"){
            if (!passfunc[i].third.empty()) {
                    e=hexadecimal(i);
                    e=e+" ";
                    e=e+" incorrect syntax";
                    error.push_back(e);
                    sonta++;
            }
        }
        else{ if(!passfunc[i].second.empty()){
                sonta++;
            e=hexadecimal(i);
            e=e+" ";
            e=e+" warning incorrect mnemonic";
            error.push_back(e);
        }}
    }
if (sonta > 0) {
    ofstream pb("error.txt");
    if (pb.is_open()) {
        for (const string &st : error) {
            pb << st << endl;
        }
        pb.close();
    }
    else{
        cout <<"failed to open error"<<endl;
    }
    cout<<"no.of errors "<<sonta<<endl;
}
else {
    cout<<"Compiled successfully"<<endl;

}
}
void pass2(vector<print> &passfunc,int stop){
	vector<string> print2;
	string st;
	vector<string> obj;
	string str;
	int addr;
	for(int i=0;i<passfunc.size();i++){
	    addr=i;
		if(passfunc[i].second=="ldc"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"ldc";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"00";
			    print2.push_back(st);
			    str=twocomp(passfunc[i].third)+"00";
			    obj.push_back(str);
			}
        else if(passfunc[i].second=="adc"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"adc";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"01";
			    print2.push_back(st);
			   
			    str=twocomp(passfunc[i].third)+"01";
			    obj.push_back(str);
        }
		else if(passfunc[i].second=="ldl"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"ldl";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"02";
			    print2.push_back(st);
			  
			    str=twocomp(passfunc[i].third)+"02";
			    obj.push_back(str);
			}
		else if(passfunc[i].second=="stl"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"stl";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"03";
			    print2.push_back(st);
			    
			    str=twocomp(passfunc[i].third)+"03";
			    obj.push_back(str);
			}
		else if(passfunc[i].second=="ldnl"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"ldnl";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"04";
			    print2.push_back(st);
			   
			    str=twocomp(passfunc[i].third)+"04";
			    obj.push_back(str);
			}
        else if(passfunc[i].second=="stnl"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"stnl";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"05";
			    print2.push_back(st);
			   
			    str=twocomp(passfunc[i].third)+"05";
			    obj.push_back(str);
			}
		else if(passfunc[i].second=="add"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"add";
			    st=st+" 00000006";
			    print2.push_back(st);
			    obj.push_back("00000006");
			}
        else if(passfunc[i].second=="sub"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"sub";
			    st=st+" 00000007";
			    print2.push_back(st);
			    obj.push_back("00000007");
			}
		else if(passfunc[i].second=="shl"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"shl";
			    st=st+" 00000008";
			    print2.push_back(st);
			    obj.push_back("00000008");
			}
        else if(passfunc[i].second=="shr"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"shr";
			    st=st+" 00000009";
			    print2.push_back(st);
			    obj.push_back("00000009");
			}
		else if(passfunc[i].second=="adj"){
			st=hexadecimal(i);
			    st=st+" ";
			    st=st+"adj";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"0a";
			    
			    print2.push_back(st);
			    str=twocomp(passfunc[i].third)+"0a";
			    obj.push_back(str);
		}
		else if(passfunc[i].second=="a2sp"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"a2sp";
			    st=st+" 0000000b";
			    print2.push_back(st);
			    obj.push_back("0000000b");
		}
		else if(passfunc[i].second=="sp2a"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"sp2a";
			    st=st+" 0000000c";
			    print2.push_back(st);
			    obj.push_back("0000000c");
			}
         else if(passfunc[i].second=="call"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"call";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"0d";
			    print2.push_back(st);
			    str=twocomp(passfunc[i].third)+"0d";
			    obj.push_back(str);
			}
		else if(passfunc[i].second=="return"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"return";
			    st=st+" 0000000e";
			    print2.push_back(st);
			    obj.push_back("0000000e");
			}
		else if(passfunc[i].second=="brz"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"brz";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"0f";
			    print2.push_back(st);
			    str=twocomp(passfunc[i].third)+"0f";
			    obj.push_back(str);
			}
		else if(passfunc[i].second=="brlz"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"brlz";
			    st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"10";
			    print2.push_back(st);
			    str=twocomp(passfunc[i].third)+"10";
			    obj.push_back(str);
			}
		else if(passfunc[i].second=="br"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"br";
			   st=st+" ";
			    st=st+twocomp(passfunc[i].third);
			    st=st+"11";
			    print2.push_back(st);
			    str=twocomp(passfunc[i].third)+"11";
			    obj.push_back(str);
			}
        else if(passfunc[i].second=="return"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+"return";
			    st=st+" 00000012";
			    print2.push_back(st);
			    obj.push_back("00000012");
			}
	    else if(passfunc[i].second=="HALT"){
			    st=hexadecimal(i);
			    st=st+" ";
			    st=st+" 00000013";
			    print2.push_back(st);
			    obj.push_back("00000013");
			}
	}
	string sasya;
	for(auto it = labelMap.begin(); it != labelMap.end(); ++it){
         st = hexadecimal(addr) + " " +"0000000"+it->second;
         print2.push_back(st);
         sasya="0000000"+it->second;
         obj.push_back(sasya);
	}
    // Do something with st, such as storing it

    ofstream pc("listing.txt");
    if (pc.is_open()) {
        for (const string &st : print2) {
            pc << st << endl;
        }
        pc.close();
    }
    else{
        cout << "failed to open pass2"<<endl;
    }
     ofstream pd("obj.txt");
    if (pd.is_open()) {
        for (const string &st : obj) {
            pd << st << endl;
        }
        pd.close();
    }
    else{
        cout << "failed to open obj"<<endl;
    }

	//emulator(passfunc,stop);
}


void pass1(vector<print> &passfunc){
int stop;
    vector<string> print1;
    unordered_map<string, int> label_addresses; // Map to store addresses of labels
    int address = 0;

    for (int i = 0; i < passfunc.size(); i++) {
        // Check if the current instruction has a label
        if (!passfunc[i].first.empty()) {
            // Assign address to the label
            label_addresses[passfunc[i].first] = address;
        }

        // Increment addres

        // Check if instruction is HALT
        if (passfunc[i].second == "HALT") {
            stop=address; // Stop processing further instructions

        }
         address++;

    }
    

    // Output labels with their addresses
    for (const auto& pair : label_addresses) {
        string format1 = pair.first + " " + hexadecimal(pair.second);
        print1.push_back(format1);
    }

    ofstream pa("1.txt");
    if (pa.is_open()) {
        for (const string &str : print1) {
            pa << str << endl;
        }
        pa.close();
        cout << "Output written to 1.txt successfully." << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
error(passfunc,stop);

pass2(passfunc,stop);

//print1(vector)->address label
}

int main() {
    print help;
    vector<print> passfunc;
    ifstream infile("bubblesort.txt"); // Input file containing assembly code
    string line;

    int current_address = 0;
    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        bool label_found = false;

        string label = "";
        string mnemonic = "";
        string value = "";

        while (ss >> token) {
            if (token[0] == ';') // Ignore comments
                break;

            if (!label_found && token[token.size() - 1] == ':') {
                // This token is a label
                label = token.substr(0, token.size() - 1);
                label_found = true;
            } else if (mnemonic.empty()) {
                // This token is the mnemonic
                mnemonic = token;
            } else {
                // This token is the value
                value = token;
            }
        }
        if (!label.empty() && !value.empty() && mnemonic=="data") {
            labelMap[label] = value;
        }
        if (!label.empty() && !value.empty() && mnemonic=="SET") {
            labelMap[label] = value;
        }
        if(!label.empty()){
            memory.insert({label,value});
        }
        // Output the formatted instruction
        if(!label.empty()||!mnemonic.empty()){
            help.first = label;
            help.second = mnemonic;
            help.third = value;
            passfunc.push_back(help);
        }

        // Increment address only if the line is not a comment
        if (token[0] != ';') {
            ++current_address;
        }
    }
    replaceLabelsWithValues(passfunc);
    pass1(passfunc);
    return 0;
}
