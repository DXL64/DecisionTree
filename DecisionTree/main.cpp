#include <bits/stdc++.h>

using namespace std;

const int maxDepth = 4;
const int minSize = 1;
const vector<char> s = {'L', 'R', 'B'};
const int numberOfTree = 3;
const vector<vector<int> > combination
{ {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4},
  {1,2,3}, {1,2,4}, {2,3,4},
  {1,2,3,4}
};
int indexTree = 9;
vector< vector<char> > ans;
struct Data {
    char y;
    float x[5];
};

struct nodeInfo {
    bool isLeaf = 0;
    int id, value;
};
struct Node {
    Node* left;
    Node* right;
    nodeInfo nodeInfo;
    char ans;
};

struct Tree
{
    Node* root = new Node;
};
vector<Data> trainSet, validSet;
Tree T[numberOfTree+1], TrainSet;

Data read(string s) {
    Data tmp;
    tmp.y = s[0];
    int cnt = 0;
    for(int i = 2; i < s.size(); i++) {
        if(s[i] == ',') continue;
        int num = 0;
        cnt++;
        while(s[i] != ',' && i < s.size())
        {
            num = num*10 + s[i] - '0';
            i++;
        }
        i--;
        tmp.x[cnt] = num;
    }
    return tmp;
}
void print(Data tmp) {
    cout << tmp.y << " " << tmp.x[1] << " " << tmp.x[2] << " " << tmp.x[3] << " " << tmp.x[4] << "\n";
}
int calculate_Number_Of_Class_In_Group(char _class, vector<Data> _group) {
    int cnt = 0;
    for(int i = 0; i < _group.size(); i++) {
        if(_group[i].y == _class)
            ++cnt;
    }
    return cnt;
}

float getGiniScore(vector< vector<Data> > groups, vector<char> classes) {
    int n = 0;
    for(auto i : groups) {
        n = n + i.size();
    }
    float gini = 0.0;
    for(auto group : groups) {
        int _size = group.size();
        if(!_size) continue;
        float score = 0.0;
        for(auto _class : classes) {
            float p = (float)calculate_Number_Of_Class_In_Group(_class, group) / _size;
            score += p * p;
        }
        gini += (1 - score) * ((float)_size / n);
    }
    return gini;
}
vector< vector<Data> > splitGroups(int index, int value, vector<Data> dataSet) {
    vector< vector<Data> > g;
    vector<Data> g1, g2;
    for(auto i : dataSet) {
        if(i.x[index] < value)
            g1.push_back(i);
        else
            g2.push_back(i);
    }
    g.push_back(g1);
    g.push_back(g2);
    return g;
}

nodeInfo getSplit(vector<Data> dataSet, Node* Node, vector<Data> &left, vector<Data> &right) {
    float minGini = 1.0;
    nodeInfo tmp;
    for(auto index : combination[indexTree]) {
        for(auto row : dataSet) {
            vector< vector<Data> > groups = splitGroups(index, row.x[index], dataSet);
            float  gini = getGiniScore(groups, s);
            if(gini < minGini) {
                minGini = gini;
                tmp.id = index;
                tmp.value = row.x[index];
                left = groups[0];
                right = groups[1];
            }
        }
    }
    return tmp;
}

char toTerminal(vector<Data> group) {
    int cntL = 0, cntR = 0, cntB = 0;
    for(auto itr : group)
    {
        if(itr.y == 'L') cntL++;
        if(itr.y == 'R') cntR++;
        if(itr.y == 'B') cntB++;
    }
    if(max(cntL, max(cntR, cntB)) == cntL) return 'L';
    if(max(cntL, max(cntR, cntB)) == cntR) return 'R';
    if(max(cntL, max(cntR, cntB)) == cntB) return 'B';
}

void splitTree(Node* Node, vector<Data> dataSet, int depth) {
    (Node->left) = new struct Node;
    Node->right = new struct Node;
    vector<Data> left;
    vector<Data> right;
    Node->nodeInfo = getSplit(dataSet, Node, left, right);
//    cout << left.size() << " " << right.size() << "\n" ;
    if(left.size() == 0 || right.size() == 0) {
        vector<Data> v;
        v.insert(v.begin(), left.begin(), left.end());
        v.insert(v.end(), right.begin(), right.end());
        char tmp = toTerminal(v);
        ((Node->right))->ans = tmp;
        ((Node->right)->nodeInfo).isLeaf = 1;
        ((Node->left))->ans = tmp;
        ((Node->left))->nodeInfo.isLeaf = 1;
        left.clear();
        right.clear();
        v.clear();
        return ;
    }
    if(depth >= maxDepth) {
        (Node->left)->ans = toTerminal(left);
        ((Node->left)->nodeInfo).isLeaf = 1;
        (Node->right)->ans = toTerminal(right);
        ((Node->right)->nodeInfo).isLeaf = 1;
        left.clear();
        right.clear();
        return;
    }
    if(left.size() <= minSize) {
        (Node->left)->ans = toTerminal(left);
        ((Node->left)->nodeInfo).isLeaf = 1;
    }
    else{
        splitTree(Node->left, left, depth+1);
    }
    if(right.size() <= minSize) {
        (Node->right)->ans = toTerminal(right);
        ((Node->right)->nodeInfo).isLeaf = 1;
    }
    else{
        splitTree(Node->right, right, depth+1);
    }
    return;
}
void printTree(Node* Node, int depth) {
//    cout << (Node->nodeInfo).dataSet.size() << "\n";
    if(depth > maxDepth || Node == NULL || (Node->nodeInfo).isLeaf) return;
//    cout << depth << " " << Node << " " << Node->left << " " << Node->right << "\n" ;
    if(Node->left != NULL)
        printTree(Node->left, depth+1);
    if(Node->right != NULL)
        printTree(Node->right, depth+1);
}
char predict(Node* Node, Data row) {
    if(row.x[(Node->nodeInfo.id)] < Node->nodeInfo.value) {
        if((Node->left)->nodeInfo.isLeaf)
            return (Node->left)->ans;
        else
            return predict(Node->left, row);
    }
    else {
        if((Node->right)->nodeInfo.isLeaf)
            return (Node->right)->ans;
        else
            return predict(Node->right, row);
    }
}
void buildTree(Node* root, vector<Data> _trainSet) {
    splitTree(root, _trainSet, 1);
//    printTree(root, 1);
    int cnt = 0;
    for(auto test : validSet) {
        char tmp = predict(root, test);
        ans[cnt].push_back(tmp);
        if(indexTree == 9)
        {
            ans[cnt].push_back(tmp);
        }
        cnt++;
//        if(predict(root, test) == test.y) cnt++;
    }

//    cout << "Percent: " << (float)cnt / validSet.size() * 100 << "%";
}
void RandomData(vector<Data> &trainSample) {
    int trainSize = trainSet.size();
    srand(time(NULL));
    for(int i = 0; i < trainSize; i++)
    {
        int index = rand() % trainSize;
        trainSample.push_back(trainSet[index]);
    }
    indexTree = rand()%9;
//    indexTree--;

}
void RandomForest() {
    vector<Data> trainSample;
    for(int i = 1; i <= numberOfTree; i++) {
        RandomData(trainSample);
        buildTree(T[i].root, trainSample);
    }
}
void printAns() {
    int cnt[100];
    int accurancy = 0;
    for(int i = 0; i < validSet.size(); i++) {
        cnt['L'] = 0;
        cnt['R'] = 0;
        cnt['B'] = 0;
        cout << validSet[i].y << " ";
        for(auto tmp : ans[i])
        {
            cnt[tmp]++;
            cout << tmp << " ";
        }
        cout << "\n";
        if(cnt['L'] >= cnt['R'] && cnt['L'] >= cnt['B'])
            if('L' == validSet[i].y)
                accurancy++;
        if(cnt['R'] >= cnt['L'] && cnt['R'] >= cnt['B'])
            if('R' == validSet[i].y)
                accurancy++;
        if(cnt['B'] >= cnt['R'] && cnt['B'] >= cnt['B'])
            if('B' == validSet[i].y)
                accurancy++;
    }
    cout << "Accurancy :" << (float)accurancy / validSet.size() * 100 << "%";
}
int main()
{
    ifstream inFile1, inFile2;
    ofstream outFile;
    string s;
    outFile.open("test.txt");
    inFile1.open("train.txt", ios::in);
    inFile2.open("valid.txt", ios::in);
    while(getline(inFile1, s)) {
        Data inp = read(s);
        trainSet.push_back(inp);
    }
    while(getline(inFile2, s)) {
        Data inp = read(s);
        validSet.push_back(inp);
    }
    for(int i = 0; i < validSet.size(); i++)
    ans.push_back(vector<char>());
    buildTree(TrainSet.root, trainSet);
    RandomForest();
    printAns();
    return 0;
}
