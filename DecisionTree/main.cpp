#include <bits/stdc++.h>

using namespace std;

const int N = 1001;
const int maxDepth = 4;
const int minSize = 1;
const vector<char> s = {'L', 'R', 'B'};
struct Data {
    char y;
    float x[5];
};

struct nodeInfo {
    int id, value;
    vector<Data> dataSet;
};
struct Node {
    Node* left;
    Node* right;
    nodeInfo nodeInfo;
    char ans;
};

struct Tree
{
    Node* root;
};
vector<Data> trainSet, validSet;


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

nodeInfo getSplit(vector<Data> dataSet, Node* Node) {
    float minGini = 1.0;
    nodeInfo tmp;
    for(int index = 1; index <= 4; index++) {
        for(auto row : dataSet) {
            vector< vector<Data> > groups = splitGroups(index, row.x[index], dataSet);
            float  gini = getGiniScore(groups, s);
            if(gini < minGini) {
                minGini = gini;
                tmp.id = index;
                tmp.value = row.x[index];
                ((Node->left)->nodeInfo).dataSet = groups[0];
                ((Node->right)->nodeInfo).dataSet = groups[1];
            }
        }
    }
//    cout << minGini << " " << tmp.id << " " << tmp.value << " " << "\n";
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
    Node->nodeInfo = getSplit(dataSet, Node);
    vector<Data> left = ((Node->left)->nodeInfo).dataSet;
    vector<Data> right = ((Node->right)->nodeInfo).dataSet;
//    cout << left.size() << " " << right.size() << "\n" ;
    if(left.size() == 0 || right.size() == 0) {
        vector<Data> v;
        v.insert(v.begin(), left.begin(), left.end());
        v.insert(v.end(), right.begin(), right.end());
        ((Node->left))->ans = ((Node->right))->ans = toTerminal(v);
        left.clear();
        right.clear();
        v.clear();
        return ;
    }
    if(depth >= maxDepth) {
        ((Node->left))->ans = toTerminal(left);
        ((Node->right))->ans = toTerminal(right);
        left.clear();
        right.clear();
        return;
    }
    if(left.size() <= minSize) {
        ((Node->left))->ans = toTerminal(left);
    }
    else{
        splitTree(Node->left, left, depth+1);
    }
    if(right.size() <= minSize) {
        ((Node->right))->ans = toTerminal(right);
    }
    else{
        splitTree(Node->right, right, depth+1);
    }
}
void printTree(Node* Node, int depth) {
    if(depth > maxDepth || Node == NULL) return;
    cout << (Node->nodeInfo).value << "\n" ;
    if(Node->left != NULL)
        printTree(Node->left, depth+1);
    if(Node->right != NULL)
        printTree(Node->right, depth+1);
}
void buildTree() {
    Node* root = new Node;
    splitTree(root, trainSet, 1);
    printTree(root, 1);
}
int main()
{
    freopen("inp_test.txt", "r", stdin);
    freopen("test.txt", "w", stdout);
    string s;
    while(getline(cin, s)) {
        Data inp = read(s);
        trainSet.push_back(inp);
    }
    buildTree();
    return 0;
}
