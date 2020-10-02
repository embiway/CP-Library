/*
    Binary lifting is a very important tree technique which is mostly used for LCA problems but can also serve other important purposes
*/

#include <bits/stdc++.h>
using namespace std;

const int l = 32;       //maximum height that tree can take

int timer;      //timer variable . Maintains the current time
vector<int> tin , tout;         //tin -> stores the time at which a node enters the dfs     tout -> time at which node exits dfs
vector<vector<int>> up;         //used for binary lifting  up[node][height] stores the (2 ^ height)th ancestor of node
vector<vector<int>> a;          //adjacency list of tree

void dfs(int s , int p){
    tin[s] = ++timer;
    up[s][0] = p;       //immediated ancestor of s is its parent
    for(int i = 1 ; i < l ; i++){
        up[s][i] = up[up[s][i-1]][i-1];         //binary lifting
    }

    for(auto it : a[s]){
        if(it != p){
            dfs(it , s);
        }
    }

    tout[s] = ++timer;
}

bool is_ancestor(int x , int y){
    return tin[x] <= tin[y] && tout[x] >= tout[y];
    //fundamental condition to check if x is an ancestor of y;
}

int lca(int x , int y){
    if(is_ancestor(x , y))return x;
    if(is_ancestor(y , x))return y;

    for(int i = l - 1 ; i >= 0 ; i--){
        if(!is_ancestor(up[x][i] , y)){
            x = up[x][i];
            //we're trying to find the highest element which is an ancestor of x but not y
            //the parent of this node would be our required lca
        }
    }

    return up[x][0];
}

void preprocess(int n , int root){
    tin.resize(n+1);
    tout.resize(n+1);
    up.resize(n+1 , vector<int>(l , 0));
    timer = 0;
    dfs(root , root);
}