#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void backtrack(int pos, multiset<char>& remainingFloat, const set<string>& dict, set<string>& results, string& current);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    multiset<char> remF(floating.begin(), floating.end());
    set<string> results;
    string current = in;
    backtrack(0, remF, dict, results, current);
    return results;
}

// Define any helper functions here
void backtrack(int pos, multiset<char>& remainingFloat, const set<string>& dict, set<string>& results, string& current){
    int n = current.size();
    if(pos == n){
        //every position is assigned (base case)
        if(remainingFloat.empty() && dict.count(current)){
            results.insert(current);
        }
        return;
    }
    if(current[pos] != '-'){
        backtrack(pos+1, remainingFloat, dict, results, current);
        return;
    }
    if(current[pos] == '-'){
        size_t blanksLeft = 0; //find how many blanks are left after current pos
        for(size_t i = pos + 1; i < current.size(); ++i){
            if (current[i] == '-'){
            blanksLeft++;
            }
        }
        for(char c = 'a'; c <= 'z'; ++c){
            bool usedAFloat = false;
            //Case 1: c is one of the remaining floating letters
            auto it = remainingFloat.find(c);
            if(it != remainingFloat.end()){
                //choose to use up one
                remainingFloat.erase(it);
                current[pos] = c;
                backtrack(pos+1, remainingFloat,dict, results, current);
                remainingFloat.insert(c);
                usedAFloat = true;
            }
        //Case 2: c is not one of the floating letters
            if(!usedAFloat && blanksLeft >= remainingFloat.size()){
                current[pos] = c;
                backtrack(pos+1, remainingFloat, dict, results, current);
            }
            current[pos] = '-'; //reset for next iteration
        }
    }
}