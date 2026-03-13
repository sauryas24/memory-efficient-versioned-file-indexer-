#include<bits/stdc++.h>
using namespace std;
class TrieNode{
    public: 
    vector<TrieNode*> children;
    int val[3];
    int frequency;

    TrieNode(){
        frequency=0;
        val[0]=-1;
        val[1]=-1;
        val[2]=-1;
    }

};

class Trie{
    public:
    vector<string> word_set;
    TrieNode* root;
    vector<pair<string,int>> results;


    void CreateTrie(){
        root = new TrieNode();
    }

    int Search(string str ){
        int i=0;
        TrieNode* curr = root;
        while(i<=str.length()-1){
            if (curr->children.size() == 0) return 0;
            int flag=0;
            for(int j=0;j<curr->children.size();j++ ){
                if(i<str.length()&& str[i]==word_set[curr->children[j]->val[0]][curr->children[j]->val[1]]){
                    flag++;
                    int temp=i;
                    for(int k=curr->children[j]->val[1];k<=curr->children[j]->val[2];k++){
                        if(str[i]==word_set[curr->children[j]->val[0]][k]) i++;
                        else return 0;
                    }
                    if((i-temp)==(curr->children[j]->val[2]-curr->children[j]->val[1]+1)){
                    curr=curr->children[j];
                    break;
                    }
                }
            }
            if(!flag) return 0;

        }
        if(curr->frequency>0&&i==str.length()) return curr->frequency;
        else return 0;

    }

    void Insert(string str){
        
        int i=0;
        TrieNode* curr = root;
        while(i<str.length()){
            bool found_child = false;
            for(int j=0;j<curr->children.size();j++ ){
                if(i<str.length()&& str[i]==word_set[curr->children[j]->val[0]][curr->children[j]->val[1]]){
                    found_child=true;
                    int temp=i;
                    for(int k=curr->children[j]->val[1];k<=curr->children[j]->val[2];k++){
                        if(str[i]==word_set[curr->children[j]->val[0]][k]) i++;
                        else{
                            TrieNode* new_child= new TrieNode();
                            new_child->frequency=curr->children[j]->frequency;
                            new_child->children=curr->children[j]->children;
                            new_child->val[0]=curr->children[j]->val[0];
                            new_child->val[1]=k;
                            new_child->val[2]=curr->children[j]->val[2];
                            curr->children[j]->val[2]=k-1;
                            curr->children[j]->frequency=0;
                            curr->children[j]->children.clear();
                            curr->children[j]->children.push_back(new_child);
                            if(i<str.length()){
                                word_set.push_back(str);
                                int new_row= word_set.size()-1;
                                TrieNode* new_child1 = new TrieNode();
                                new_child1->val[0]=new_row;
                                new_child1->val[1]=i;
                                new_child1->val[2]=str.length()-1;
                                new_child1->frequency=1;
                                curr->children[j]->children.push_back(new_child1);
                                return;
                                }
                            else{
                                curr->children[j]->frequency++;
                            }
                            return;
                        }

                    }
                    if((i-temp)==(curr->children[j]->val[2]-curr->children[j]->val[1]+1)){
                        if(i==str.length()){
                            curr->children[j]->frequency++;
                            return;
                        }
                        else{
                            curr=curr->children[j];
                            break;
                        } 
                        
                    }
                    
                }
            }
            if(!found_child){
                word_set.push_back(str);
                int new_row= word_set.size()-1;
                TrieNode* new_child = new TrieNode();
                new_child->val[0]=new_row;
                new_child->val[1]=i;
                new_child->val[2]=str.length()-1;
                new_child->frequency=1;
                curr->children.push_back(new_child);
                return;
                }
        }
    }

    void frequency_sort(TrieNode* curr, string accumulated){
        if(curr->frequency>0) results.push_back({accumulated, curr->frequency});
        for(int j=0;j<curr->children.size();j++ ){
            string branch_string = accumulated;
            for(int k=curr->children[j]->val[1];k<=curr->children[j]->val[2];k++){
                branch_string.push_back(word_set[curr->children[j]->val[0]][k]);
            }
            frequency_sort(curr->children[j],branch_string);
        }

    }
};

template <typename T>
void printResult(string label, T value){
    cout << label << ": "<< value<< endl;
}

class VersionedIndex{
    private:
    unordered_map<string, Trie> versions;
    public: 
    void versionExists(string version_name){
        if(versions.find(version_name)==versions.end()){
            versions[version_name].CreateTrie();
        }
    }
    void Insert(string word){
    Insert(word, "default_version");
    }
    void Insert(string word, string version_name){
        versionExists(version_name);
        versions[version_name].Insert(word);
    }
    int getWordCount(string word, string version_name){
        if(versions.find(version_name)!= versions.end()){
            return versions[version_name].Search(word);
        }
        return 0;
    }
    Trie& getTrie(string version_name){
        return versions[version_name];
    }

};

class Tokenizer{
    private:
    string leftWord="";
    public:
    void processBuffer(const vector<char>& buffer, int bytes_read, VersionedIndex& index, string version){
        for(int i=0;i< bytes_read; i++){
            char c= buffer[i];
            if(isalnum(c)){
                leftWord+= tolower(c);
            }
            else {
                if(!leftWord.empty()){
                    index.Insert(leftWord, version);
                    leftWord="";
                }
            }
        }
    }
    void flush(VersionedIndex& index, string version){
        if(!leftWord.empty()){
            index.Insert(leftWord, version);
        }

    }


};

class FileReader{
    private:
    int buffer_size;
    Tokenizer tokenizer;

    public:
    FileReader(int kb){
        buffer_size=kb;
    }
    void read(string filepath, string version_name, VersionedIndex& index){
        if(buffer_size<256 || buffer_size>1024){
            throw invalid_argument("Buffer size must be between 256Kb and 1024Kb");
        }
        ifstream file(filepath, ios::binary);

        if(!file.is_open()){
            throw runtime_error("Failed to open file: " + filepath);
        }
        int chunk_size = buffer_size*1024;
        vector<char> buffer(chunk_size);
        while(file){
            file.read(buffer.data(), chunk_size);
            int bytes_read = file.gcount();
            if(bytes_read==0) break;

            tokenizer.processBuffer(buffer, bytes_read, index, version_name);

        }
        tokenizer.flush(index, version_name);
        file.close();

    }
};

class QueryProcessing{
    public:
    virtual void execute(VersionedIndex& index) =0;
    virtual ~QueryProcessing(){};

};

class WordQuery: public QueryProcessing{
    private:
    string word, version;
    public:
    WordQuery(string w, string v){
        word = w;
        version =v;
    }
    void execute(VersionedIndex& index) override{
        int count = index.getWordCount(word, version);
        printResult("Frequency in: "+ version, count);
    }

};
class DiffQuery: public QueryProcessing{
    private:
    string word, version1, version2;
    public: 
    DiffQuery(string w, string v1, string v2){
        word =w;
        version1=v1;
        version2=v2;
    }
    void execute(VersionedIndex& index) override{
        int count1 = index.getWordCount(word, version1);
        int count2= index.getWordCount(word, version2);
        int diff = count2-count1;
        printResult("Difference between the word in " + version1 + " and " + version2, diff);
    }
};

class TopKQuery: public QueryProcessing{
    private:
    int k_value;
    string target_version;
    public:
    TopKQuery(int k, string version){
        k_value= k;
        target_version = version;
    }
    void execute(VersionedIndex& index) override{
        Trie& my_trie= index.getTrie(target_version);
        my_trie.results.clear();
        my_trie.frequency_sort(my_trie.root, "");
        sort(my_trie.results.begin(), my_trie.results.end(), [](const pair<string, int>& a, const pair<string, int>& b){
            return a.second > b.second;
        });
        cout << "Top " << k_value << " results:" << endl;
        int limit = min(k_value, (int)my_trie.results.size());
        for(int i = 0; i < limit; i++){
            cout << my_trie.results[i].first << " " << my_trie.results[i].second << endl;
        }
    }

};


int main(int argc, char* argv[]){
    auto start_time = chrono::high_resolution_clock::now();

    try{
        unordered_map<string, string> args;
        for(int i=1;i< argc;i+=2){
            if(i+1<argc){
                args[argv[i]]= argv[i+1];
            }

        }
        if(args.find("--buffer")==args.end()||args.find("--query")==args.end()){
            throw invalid_argument("--buffer and --query are mandatory arguments");
        }
        int buffer_kb = stoi(args["--buffer"]);
        string query_type= args["--query"];

        VersionedIndex my_index;
        FileReader reader(buffer_kb);
        QueryProcessing* active_query = nullptr;

        if(query_type=="word" || query_type=="top"){
            string filepath = args["--file"];
            string version_name = args["--version"];
            reader.read(filepath, version_name, my_index);
            cout << "Version: "<<version_name << endl;
            if(query_type=="word"){
                active_query = new WordQuery(args["--word"], version_name);
            }
            else if(query_type=="top"){
                active_query = new TopKQuery(stoi(args["--top"]), version_name);
            }

        }
        else if(query_type=="diff"){
            string file1= args["--file1"];
            string version1 = args["--version1"];
            string file2 = args["--file2"];
            string version2= args["--version2"];
            reader.read(file1, version1,my_index);
            reader.read(file2,version2, my_index);
            cout << "Version 1: "<< version1<< endl;
            cout << "Version 2: "<< version2<< endl;
            active_query = new DiffQuery(args["--word"], version1, version2);
        }
        else {
            throw invalid_argument("Unknown Query Type");
        }
        if(active_query!=nullptr){
            active_query->execute(my_index);
            delete active_query;
        }

        auto end_time= chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_seconds = end_time-start_time;

        cout<< "Allocated buffer size: " << buffer_kb<< endl;
        cout<< "execution time: "<< elapsed_seconds.count()<< endl;


        

    }
    catch(const exception& e){
        cerr<< "Error: "<< e.what()<< endl;
        return 1;
    }










    return 0;
}
