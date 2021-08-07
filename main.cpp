#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
using namespace std;

map<string, vector<string> > readFiles(string fileName);
int parseScore(string score);
int min(string root, string state, map<string, vector<string> >graph, bool verbose, bool ab, int alpha, int beta);
int max(string root, string state, map<string, vector<string> >graph, bool verbose, bool ab, int alpha, int beta);
vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

int parseScore(string score) {
    int i;
    if (score.at(0) == '-') {
        sscanf(score.substr(1, score.length()-1).c_str(), "%d", &i);
        return -1 * i;
    } else {
        sscanf(score.c_str(), "%d", &i);
        return i;
    }
}

int min(string root, string state, map<string, vector<string> >graph, bool verbose, bool ab, int alpha, int beta) {
    //check if the state is the terminal state
    if (graph[state].size() == 1) {
        return parseScore(graph[state][0]);
    }
    int v = INT_MAX;
    string best;
    for(int i = 0; i < graph[state].size(); i ++){
        string child = graph[state][i];
        int temp = max(root, child, graph, verbose, ab, alpha, beta);

        if (temp < v) {
            v = temp;
            best = child;
        }
        if (ab) {
            if (v <= alpha) return v;
            if (v < beta) beta = v;
        }
    }
    // for (string child : graph[state]) {
    //     int temp = max(root, child, graph, verbose, ab, alpha, beta);

    //     if (temp < v) {
    //         v = temp;
    //         best = child;
    //     }
    //     if (ab) {
    //         if (v <= alpha) return v;
    //         if (v < beta) beta = v;
    //     }

    // }
    if (verbose) cout << "min(" << state << ") choose " << best << " for " << v << endl;
    else if (state.compare(root) == 0) cout << "min(" << state << ") choose " << best << " for " << v << endl;
    return v;
}

int max(string root, string state, map<string, vector<string> >graph, bool verbose, bool ab, int alpha, int beta) {
    //check if the state is the terminal state
    if (graph[state].size() == 1) {
        return parseScore(graph[state][0]);
    }
    int v = INT_MIN;
    string best;
    for (int i = 0; i < graph[state].size(); i ++) {
        string child = graph[state][i];
        int temp = min(root, child, graph, verbose, ab, alpha, beta);
        if (temp > v){
            v = temp;
            best = child;
        }
        if (ab) {
            if (v >= beta) return v;
            if (v > alpha) alpha = v;
        }
    }
    // for (string child : graph[state]) {
    //     int temp = min(root, child, graph, verbose, ab, alpha, beta);
    //     if (temp > v){
    //         v = temp;
    //         best = child;
    //     }
    //     if (ab) {
    //         if (v >= beta) return v;
    //         if (v > alpha) alpha = v;
    //     }
    // }
    if (verbose) cout << "max(" << state << ") choose " << best << " for " << v << endl;
    else if (state.compare(root) == 0) cout << "max(" << state << ") choose " << best << " for " << v << endl;
    return v;
}

map<string, vector<string> > readFiles(string fileName)
{
    const char * cstr = fileName.c_str();
    // ifstream ifs;
    // ifs.open(cstr, ifstream::in);
    // string line;

    FILE * fp;
    char * linec = NULL;
    size_t len = 0;
    ssize_t read;
    map<string, vector<string> > graph;
    fp = fopen(cstr, "r");
    if (fp == NULL) {
        cout << "File not exist" << endl;
        exit(EXIT_FAILURE);
    }
    
    while ((read = getline(&linec, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        string line(linec);
        line = line.substr(0,line.length()-1);
        // cout << "line";
        // cout << line << endl;
        //If the last char of the line is ']', we are not yet at the the leaf nodes
        if (line[line.length() - 1] == ']')
        {
            //we should add the element into the graph
            vector<string> res = split(line, ":");
            string later;
            if (res[1].at(0) == ' ') later = res[1].substr(2, res[1].length() - 3);
            else later = res[1].substr(1, res[1].length() - 2);
            vector<string> child = split(later, ",");
            for (int i = 1; i < child.size(); i++)
            {
                string newchild = child[i].substr(1, child[i].length() - 1);
                child[i] = newchild;
            }
            graph.insert(pair<string, vector<string> >(res[0], child));
        } else {
            vector<string> res = split(line, "=");
            vector<string> score;
            score.push_back(res[1]);
            graph.insert(pair<string, vector<string> >(res[0], score));
            
        }
        // printf("%s", line);
    }

    // while (getline(ifs, line))
    // {
    //     cout << line << endl;
    //     //If the last char of the line is ']', we are not yet at the the leaf nodes
    //     if (line[line.length() - 1] == ']')
    //     {
    //         //we should add the element into the graph
    //         vector<string> res = split(line, ":");
    //         string later;
    //         if (res[1].at(0) == ' ') later = res[1].substr(2, res[1].length() - 3);
    //         else later = res[1].substr(1, res[1].length() - 2);
    //         vector<string> child = split(later, ",");
    //         for (int i = 1; i < child.size(); i++)
    //         {
    //             string newchild = child[i].substr(1, child[i].length() - 1);
    //             child[i] = newchild;
    //         }
    //         graph.insert(pair<string, vector<string> >(res[0], child));
    //     } else {
    //         vector<string> res = split(line, "=");
    //         vector<string> score;
    //         score.push_back(res[1]);
    //         graph.insert(pair<string, vector<string> >(res[0], score));
            
    //     }
    // }
    return graph;
}

//a node with no incoming edges is a root
string findRoot(map<string, vector<string> > graph, vector<string> keys){
    map <string, int> edges;
    vector<string> count;
    for (int i = 0; i < keys.size(); i ++) {
        string node = keys[i];
        edges.insert(pair<string, int>(node, 0));
    }
    // for (string node : keys){
    //     edges.insert(pair<string, int>(node, 0));
    // }
    for (int j = 0; j < keys.size(); j ++) {
        string node = keys[j];
        for (int p = 0; p < graph[node].size(); p++) {
            string child = graph[node][p];
            edges[child] ++;
        }
    }
    // for (string node : keys){
    //     for (string child: graph[node]) {
    //         edges[child] ++;
    //     }
    // }
    map<string ,int >::iterator it;
    for (it = edges.begin(); it != edges.end(); it ++) {
        if (edges[it->first] == 0) count.push_back(it->first);
    }
    // for (auto const& element : edges){
    //     if (edges[element.first] == 0) count.push_back(element.first);
    // }
    if (count.size() == 1) return count[0];
    return "none";
}

// bool DFS(map<string, vector<string> > graph, string node, vector<string> visited) {
//     if (find(visited.begin(), visited.end(), node) == visited.end()) {
//         visited.push_back(node);
//         for (int i = 0; i < graph[node])
//         for (string child: graph[node]) {
//             if (!DFS(graph, child, visited)) return false;
//         }
//         return true;
//     } else return false;
// }

// bool noCycle(map<string, vector<string> > graph, string root){
//     vector <string> visited;
//     return DFS(graph, root, visited);
// }

bool checkNumber(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false) return false;
    return true;
}

vector<pair<string, string> > endWithNumber(map<string, vector<string> > graph, vector<string> keys){
    vector< pair<string,string> > missingLeaf;
    for (int i = 0; i < keys.size(); i ++){
        string each = keys[i];
        for (int j = 0; j < graph[each].size(); j ++) {
            string child = graph[each][j];
            if(!checkNumber(child) && find(keys.begin(), keys.end(), child) == keys.end()) missingLeaf.push_back(pair<string, string>(child, each));
        }
    }
    // for(string each: keys){
    //     for(string child: graph[each]){
    //         if(!checkNumber(child) && find(keys.begin(), keys.end(), child) == keys.end()) missingLeaf.push_back(pair<string, string>(child, each));
    //     }
    // }
    return missingLeaf;
}

//we can detect the missing nodes by counting the levels from the root
// map<string, int> countLevels(map<string, vector<string> > graph, string root, ){
    
// }

int main(int argc, char *argv[]){
    // readFiles("example.txt");
    bool verbose = false;
    bool ab = false;
    bool isMax = false;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    vector <string> args;
    string fileName;
    for (int i = 1; i < argc; i ++) {
        string arg (argv[i]);
        // cout << arg << endl;
        args.push_back(arg);
        if (arg.length() >= 4 && arg.substr(arg.length() - 3, arg.length()).compare("txt") == 0){
            fileName = arg;
        } 
    }
    if (find(args.begin(), args.end(), "-v") != args.end()) {
        verbose = true;
    }
    if (find(args.begin(),args.end(),"-ab") != args.end()) {
        ab = true;
    }
    if (find(args.begin(),args.end(),"max") != args.end()) {
        isMax = true;
    } else if (find(args.begin(),args.end(),"min") == args.end()) {
        cout << "Please specify which player (min or max) you want the root player to be." << endl;
        return 0;
    }
    // for (string arg: args) {
    //     if (arg.substr(arg.length() - 3, arg.length()).compare("txt") == 0) fileName = arg;
    // }
    // for ()
    map<string, vector<string> > graph = readFiles(fileName);
    vector<string> keys;


    map<string, vector<string> > :: iterator it;
    for (it = graph.begin(); it != graph.end(); it ++) {
        keys.push_back(it->first);
    }
    // for (auto const& element : graph) {
    //     keys.push_back(element.first);
    // }
    string root = findRoot(graph, keys);
    // cout << root << endl;
    if (root.compare("none") != 0) {
        if (endWithNumber(graph, keys).size() == 0){
            if (isMax) cout << max(root, root, graph, verbose, ab, alpha, beta) << endl;
            else cout << min(root, root, graph, verbose, ab, alpha, beta) << endl;
        } else {
            vector<pair<string, string> > res = endWithNumber(graph, keys);
            for (int i = 0; i < res.size(); i ++) {
                pair<string, string> each = res[i];
                cout << "child node " << "\""<< each.first << "\"" << "of " << "\""<< each.second << "\"" << " not found" << endl;
            }
            // for(pair<string, string> each: res) cout << "child node " << "\""<< each.first << "\"" << "of " << "\""<< each.second << "\"" << " not found" << endl;
        }
    } else {
        cout << "There is no root" << endl;
    }
}