//
// Created by Kylian Lee on 2021/04/29.
//
#include <iostream>
#include <vector>
#include <algorithm>
#define SIZE 200005

using namespace std;

int cache[SIZE];
vector<vector<int>> roads(SIZE);
vector<vector<int>> parents(SIZE);

int dfs(int i);
int main(){
  int cities;
  cin >> cities;
  int from, to;
  for(int i = 1; i < cities; i++){
    cin >> from >> to;
    roads[from].push_back(to);
    parents[to].push_back(from);
  }
//  for(int i = 1; i <= cities; i++){
//    for(int j = 0; j < roads[i].size(); j++)
//      cout << roads[i][j] << endl;
//  }
  for(int i = 1; i <= cities; i++){
    cache[i] = dfs(i);
  }
  int ansCache[SIZE];
  for(int i = 1; i <= cities; i++){
    ansCache[i] = cache[i];
  }
  for(int i = 1; i <= cities; i++){
    for(int j = 0; j < roads[i].size(); j++){
      if(parents[roads[i][j]].size() != 1){
        for(int k = 0; k < parents[roads[i][j]].size(); k++){
          if(parents[roads[i][j]][k] != i){
            ansCache[i] += 1;
            ansCache[i] += cache[parents[roads[i][j]][k]];
          }
        }
      }
    }
  }
  int min = SIZE;
  vector<int> ansVec;
  for(int i = 1; i <= cities; i++){
    if(min > ansCache[i]) {
      min = ansCache[i];
      ansVec.clear();
      ansVec.resize(0);
      ansVec.push_back(i);
    }
    else if(min == ansCache[i]){
      ansVec.push_back(i);
    }
  }
  cout << min << endl;
  for(int i = 0; i < ansVec.size(); i++){
    cout << ansVec[i] << " ";
  }
}
int dfs(int i){
  int size = parents[i].size();
  if(size == 0)
    return 0;
  if(cache[i])
    return cache[i];
  int sum = size;
  for(int j = 0; j < size; j++){
    sum += dfs(parents[i][j]);
  }
  return sum;
}