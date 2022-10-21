Count and Say

class Solution {
public:
    string countAndSay(int n) {
        if(n==1)
            return "1";
        
        string small=countAndSay(n-1);
        //cout<<small<<",";
        string ans="";
        int i=0;
        while(i<small.size()){
            int j=i;
            int c=0;
            while(i<small.size() && small[i]==small[j]){
               c++;
                i++;
            }
            ans+=to_string(c);
            ans+=small[j];
        }
       // cout<<ans<<endl;
        return ans;
    }
};