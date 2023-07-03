#include<bits/stdc++.h>
using namespace std;

int test_vector(vector<vector<int>> &truth_table, map<string,pair<string,int>> &variables,map<int,string> &map_table,int fault,int node,int n){
        for(int i=0;i<16;i++){
            if(truth_table[i][node]==(!fault)){
                int z=truth_table[i][n+3];
                truth_table[i][node]=fault;
                for(int j=node+1;j<n+4;j++){
                    deque<int> ind;
                    deque<char> op;
                    string line=variables[map_table[j-4]].first;
                    int k=0;
                            while(k<line.length()){
                                if(line[k]=='A' || line[k]=='B' || line[k]=='C' || line[k]=='D'){
                                    ind.push_back(line[k]-'A');
                                    k++;
                                 }else{
                                    if(line[k]=='~' || line[k]=='|' || line[k]=='&' || line[k]=='^'){
                                        op.push_back(line[k]);
                                        k++;
                                    }else{
                                        string str="";
                                        while(k<line.length() && line[k]!='~' && line[k]!='|' && line[k]!='&' && line[k]!='^'){
                                            str+=line[k];
                                            k++;
                                        }
                                        if(variables.find(str)!=variables.end()){
                                            ind.push_back((variables[str].second)+4);
                                        }
                                    }
                                }
                            }
                            
                        while(!op.empty()){
                            if(op.front()=='~'){
                                truth_table[i][j]=!truth_table[i][ind.front()];
                                op.pop_front();
                                ind.pop_front();
                                ind.push_front(j);
                            }else{
                                char t=op.front();
                                op.pop_front();
                                if(!op.empty() && op.front()=='~'){
                                    int ind1=ind.front();
                                    ind.pop_front();
                                    truth_table[i][j]=!truth_table[i][ind.front()];
                                    ind.pop_front();
                                    ind.push_front(j);
                                    ind.push_front(ind1);
                                }else{
                                    int ind1=ind.front();
                                    ind.pop_front();
                                    if(t=='&'){
                                        truth_table[i][j]=truth_table[i][ind1] && truth_table[i][ind.front()];
                                        ind.pop_front();
                                        ind.push_front(j);
                                    }else{
                                        if(t=='|'){
                                            truth_table[i][j]=truth_table[i][ind1] || truth_table[i][ind.front()];
                                            ind.pop_front();
                                            ind.push_front(j);                                            
                                        }else{
                                            if(t=='^'){
                                                truth_table[i][j]=truth_table[i][ind1] ^ truth_table[i][ind.front()];
                                                ind.pop_front();
                                                ind.push_front(j);                                            
                                            }
                                        }
                                    }
                                }
                            }
                        }

                }

                if(z!=truth_table[i][n+3]){
                    
                    return i;
                }
            }
        }

        return -1;
}

int main(){
    string fault_at,fault_type;
    cout<<"Fault_At = ";
    cin>>fault_at;
    cout<<"Fault_Type = ";    
    cin>> fault_type;

    fstream myFile;
    myFile.open("circuit_file2.txt", ios::in);
    vector<string> arr;
    if(myFile.is_open()){
        string line;
        while(getline(myFile,line)){
            arr.push_back(line);
        }

        myFile.close();
    }
    //cout<<arr[0];
    map<string,pair<string,int>> variables;
    map<int,string> map_table;
    int n=arr.size();
    
    for(int i=0;i<n;i++){
        string line=arr[i];
        int j=0;
        string key="";
        while(line[j]!='='){
            if(line[j]==' '){
                j++;
                continue;
            }
            key+=line[j];
            j++;
        }
        j++;
        string value="";
        while(j<line.length()){
            if(line[j]==' '){
                j++;
                continue;
            }
            
            value+=line[j];
            j++;
        }
        variables[key]={value,i};
        map_table[i]=key;
    }

    vector<vector<int>> truth_table(16,vector<int>(n+4,0));
    // as given in the instruction the circuit file in this case will always have 4 inputs therefore there will be 16 combinations in total

    for(int i=1;i<16;i++){
        int j=3;
        int num=i;
        while(num>0){
            truth_table[i][j]=num%2;
            num/=2;
            j--;
        }
    }

    for(int i=4;i<n+4;i++){
        deque<int> ind;
        deque<char> op;
        int k=0;
        string line=variables[map_table[i-4]].first;

        while(k<line.length()){
            if(line[k]=='A' || line[k]=='B' || line[k]=='C' || line[k]=='D'){
                ind.push_back(line[k]-'A');
                k++;
            }else{
                if(line[k]=='~' || line[k]=='|' || line[k]=='&' || line[k]=='^'){
                    op.push_back(line[k]);
                    k++;
                }else{
                    string str="";
                    while(k<line.length() && line[k]!='~' && line[k]!='|' && line[k]!='&' && line[k]!='^'){
                        str+=line[k];
                        k++;
                    }
                    if(variables.find(str)!=variables.end()){
                        ind.push_back((variables[str].second)+4);
                    }
                }
            }
        }

        for(int j=0;j<16;j++){
            deque<int> temp=ind;
            deque<char> temp2=op;
            if(ind.size()==1){
                truth_table[j][i]=!truth_table[j][ind.front()];
            }else{
                while(!temp2.empty() && !temp.empty()){
                    if(temp2.front()=='~'){
                        truth_table[j][i]=!truth_table[j][temp.front()];
                        temp.pop_front();
                        temp.push_front(i);
                        temp2.pop_front();
                    }else{
                        char t=temp2.front();
                        temp2.pop_front();
                        if(!temp2.empty() && temp2.front()=='~'){
                            int ind1=temp.front();
                            temp.pop_front();
                            truth_table[j][i]=!truth_table[j][temp.front()];
                            temp.pop_front();
                            temp.push_front(i);
                            temp.push_front(ind1);
                            temp2.pop_front();
                            temp2.push_front(t);
                        }else{
                            int ind1=temp.front();
                            temp.pop_front();
                            if(t=='&'){
                                truth_table[j][i]=truth_table[j][ind1] && truth_table[j][temp.front()];
                                temp.pop_front();
                                temp.push_front(i);
                                
                            }else{
                                if(t=='|'){
                                    truth_table[j][i]=truth_table[j][ind1] || truth_table[j][temp.front()];
                                    temp.pop_front();
                                    temp.push_front(i);
                                                                        
                                }else{
                                    if(t=='^'){
                                        truth_table[j][i]=truth_table[j][ind1] ^ truth_table[j][temp.front()];
                                        temp.pop_front();
                                        temp.push_front(i);
                                                                                                         
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
        }
    }

    int node=(variables[fault_at].second)+4;
    int row;
    if(fault_type=="SA0"){

        row= test_vector(truth_table,variables,map_table,0,node,n);
        
    }else{
         row= test_vector(truth_table,variables,map_table,1,node,n);
        
    }

    myFile.open("output.txt",ios::out);
    if(myFile.is_open()){
        myFile<<"[A,B,C,D] = ["<<truth_table[row][0]<<","<<truth_table[row][1]<<","<<truth_table[row][2]<<","<<truth_table[row][3]<<"], Z = "<<truth_table[row][n+3];
        myFile.close();
    }

}
