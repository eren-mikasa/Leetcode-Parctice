#include<bits/stdc++.h>
using namespace std;

struct mnemonics
{
    string section;
    int code;
    int length;
};


struct mcline{
	int f;
	int s;
	int t;
};

map<string,mnemonics> mot;
vector<vector<pair<string,int> > > intermediate;
map<string,pair<int,int > > syb_tab;
map<string,pair<int,int > > lit_tab;
vector<int> pool_tab;
vector<mcline> machinecode;

void init()
{
    mot["STOP"] = {"IS",0,1};
    mot["ADD"] = {"IS",1,1};
    mot["SUB"] = {"IS",2,1};
    mot["MULTI"] = {"IS",3,1};
    mot["MOVER"] = {"IS",4,1};
    mot["MOVEM"] = {"IS",5,1};
    mot["COMB"] = {"IS",6,1};
    mot["BC"] = {"IS",7,1};
    mot["DIV"] = {"IS",8,1};
    mot["READ"] = {"IS",9,1};
    mot["PRINT"] = {"IS",10,1};
    mot["START"] = {"AD",1,0};
    mot["END"] = {"AD",2,0};
    mot["LTORG"] = {"AD",5,0};
    mot["DS"] = {"DL",1,0};
    mot["DC"] = {"DL",2,1};
    mot["AREG"] = {"RG",1,0};
    mot["BREG"] = {"RG",2,0};
    mot["CREG"] = {"RG",3,0};
    mot["EQ"] = {"CC",1,0};
    mot["LT"] = {"CC",2,0};
    mot["GT"] = {"CC",3,0};
    mot["LE"] = {"CC",4,0};
    mot["GE"] = {"CC",5,0};
    mot["NE"] = {"CC",6,0};
    pool_tab.push_back(0);
}

vector<string> split(string str)
{
    vector<string> res;
    istringstream ss(str);
    do {
        string word;
        ss >> word;
        res.push_back(word);
    } while (ss);
    return res;
}

int findlit(int val){
	map<string,pair<int,int > >::iterator itr = lit_tab.begin();
	for(;itr!=lit_tab.end();itr++){
		if(itr->second.first == val){
			return itr->second.second;
		}
	}
	return -1;
}

int findsyb(int val){
	map<string,pair<int,int > >::iterator itr = syb_tab.begin();
	for(;itr!=syb_tab.end();itr++){
		if(itr->second.first == val){
			return itr->second.second;
		}
	}
	return -1;
}

string decToBinary(int n) 
{ 
    int binaryNum[32]; 
    int i = 0; 
    while (n > 0) { 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
    string ans = "";
    for (int j = i - 1; j >= 0; j--) 
        ans = ans+char(binaryNum[j]+'0'); 
    if(ans.length()<8){
    	for(int i=ans.length();i<8;i++){
    		ans = "0"+ans;
		}
	}
    return ans;
} 

void pass1()
{
    int counter = -1;
    while(true){
        string str;
        getline(cin,str);
        vector<pair<string,int> > inter_line;
        vector<string> line = split(str);
        if(line[0]=="LTORG"){
            int len = lit_tab.size();
            mnemonics x = mot[line[0]];
            int i= pool_tab[pool_tab.size()-1];
            map<string,pair<int,int > >::iterator itr = lit_tab.begin();
            for(int j = 0;j<i;j++){
                itr++;
            }
            for(;i<lit_tab.size();i++){
                inter_line.push_back({"AD",5});
                inter_line.push_back({"DL",2});
                inter_line.push_back({"C",itr->first[2]-'0'});
                lit_tab[itr->first].second = counter;
                itr++;
                counter++;
            }
            intermediate.push_back(inter_line);
            pool_tab.push_back(lit_tab.size());
            continue;
        }
        if(line[0]=="START"){
            counter = std::atoi(line[1].c_str());
            mnemonics x = mot[line[0]];
            inter_line.push_back({x.section,x.code});
            inter_line.push_back({"C",counter});
            intermediate.push_back(inter_line);
            counter++;
            continue;
        }
        if(line[0]=="END"){
            int len = lit_tab.size();
            int i= pool_tab[pool_tab.size()-1];
            map<string,pair<int,int > >::iterator itr = lit_tab.begin();
            for(int j = 0;j<i;j++){
                itr++;
            }
            for(;i<lit_tab.size();i++){
                inter_line.push_back({"AD",5});
                inter_line.push_back({"DL",2});
                inter_line.push_back({"C",itr->first[2]-'0'});
                lit_tab[itr->first].second = counter;
                itr++;
                counter++;
            }
            intermediate.push_back(inter_line);

            mnemonics x = mot[line[0]];
            inter_line.push_back({x.section,x.code});
            intermediate.push_back(inter_line);
            
            pool_tab.push_back(lit_tab.size());
            return;
        }


        if(mot.find(line[0])==mot.end()){
            if(syb_tab.find(line[0]) == syb_tab.end()){
                syb_tab[line[0]] = {syb_tab.size(),counter};
            }else{
                syb_tab[line[0]] = {syb_tab[line[0]].first,counter};
            }
            inter_line.push_back({"S",syb_tab[line[0]].first});
            line.erase(line.begin());
        }
        for(int i=0;i<line.size();i++){
            int toadd = 0;
            if(line[i]=="," || line[i].length()==0){
                continue;
            }
            if(mot.find(line[i])==mot.end()){
                if(line[i][0]=='='){
                    lit_tab[line[i]] = {lit_tab.size(),-1};
                    inter_line.push_back({"L",lit_tab[line[0]].first});
                }else{
                	if(line[i][0]>='0' && line[i][0]<='9'){
                		inter_line.push_back({"C",line[i][0]-'0'});
					}
                    else{
                    	if(syb_tab.find(line[i]) !=syb_tab.end()){
	                        continue;
	                    }
	                    syb_tab[line[i]] = {syb_tab.size(),-1};
	                    inter_line.push_back({"S",syb_tab[line[i]].first});
					}
                }
            }else{
                mnemonics x = mot[line[i]];
                inter_line.push_back({x.section,x.code});
                toadd += x.length;
            }
            counter += toadd;
        }
        intermediate.push_back(inter_line);
    }

}
void pass2(){
	for(int i=0;i<intermediate.size();i++){;
        for(int j=0;j<intermediate[i].size();){
        	if(intermediate[i][j].first=="IS"){
        		mcline myaddi;
        		myaddi.f = intermediate[i][j].second;
        		myaddi.s = 0;
        		if(intermediate[i][j+1].first=="RG"){
        			myaddi.s = intermediate[i][j+1].second;
				}
				if(intermediate[i][j+2].first=="L"){ 
					int val = intermediate[i][j+2].second;
					int topush = findlit(val);
					myaddi.t = topush;
				}else{
					int val = intermediate[i][j+2].second;
					int topush = findsyb(val);
					myaddi.t = topush;
				}
				machinecode.push_back(myaddi);
				j+=3;
			}else if(intermediate[i][j].first=="AD" && intermediate[i].size()>2){
				mcline myaddi;
        		myaddi.f = 0;
        		myaddi.s = 0;
				myaddi.t = intermediate[i][j+2].second;
				machinecode.push_back(myaddi);
				j+=3;
			}else{
				j++;
			}
        }
    }
}

int main()
{
    init();
    pass1();
    cout<<endl<<endl;
    cout<<"INTERMEDIATE CODE: ";
    for(int i=0;i<intermediate.size();i++){
    	if(intermediate[i].size()!=0)
            cout<<endl;
        for(int j=0;j<intermediate[i].size();j++){
            cout<<"("<<intermediate[i][j].first<<","<<intermediate[i][j].second<<") ";
        }
    }
    pass2();
    cout<<endl<<endl;
    cout<<"MACHINE CODE: "<<endl;
    for(int i=0;i<machinecode.size();i++){
    	cout<<"("<<decToBinary(machinecode[i].f)<<") ("<<decToBinary(machinecode[i].s)<<") ("<<decToBinary(machinecode[i].t)<<")";
    	cout<<endl;
	}
    return 0;
}

/*

START 200
MOVER AREG , ='5'
MOVEM AREG , X
MOVER BREG , ='2'
LTORG
X DS 1
END


INTERMEDIATE CODE:
(AD,1) (C,200)
(IS,4) (RG,1) (L,0)
(IS,5) (RG,1) (S,1)
(IS,4) (RG,2) (L,0)
(AD,5) (DL,2) (C,2) (AD,5) (DL,2) (C,5) (AD,5) (DL,2) (C,38)
(S,1) (DL,1) (C,1)
(AD,2)

MACHINE CODE:
(00000100) (00000001) (11001110)
(00000101) (00000001) (11001111)
(00000100) (00000010) (11001110)
(00000000) (00000000) (00000010)
(00000000) (00000000) (00000101)
(00000000) (00000000) (00100110)

--------------------------------
Process exited after 7.781 seconds with return value 0
Press any key to continue . . .

*/


