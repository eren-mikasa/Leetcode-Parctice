class Solution {
    public boolean checkIfPangram(String sentence) {
        HashSet<Character>st = new HashSet<>();
        for(int i=0;i<sentence.length();i++){
            st.add(sentence.charAt(i));
        }
        if(st.size()!=26) return false;
        return true;
    }
}