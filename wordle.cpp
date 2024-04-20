#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(const std::string& in, const std::string& floating, std::set<std::string>& results, const std::set<std::string>& dict, std::string current, int idx, std::vector<bool>& used,int usedCount);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results; //results for strings
    std::vector<bool> used(floating.size(), false); // track usage of floating letters
    generateWords(in, floating, results, dict, "", 0, used,0);
    return results;

}
// Recursive helper function to generate all combinations of words meeting the criteria
void generateWords(const std::string& in, const std::string& floating, std::set<std::string>& results, const std::set<std::string>& dict, std::string current, int idx, std::vector<bool>& used,int usedCount) {
    if (idx == in.size()) {
        if (dict.find(current) != dict.end() && usedCount == static_cast<int>(floating.size())) {
            results.insert(current);
        }
        return;
    }

    if (in[idx] != '-') {
        // Fixed position, use the given letter and continue
        //current is the index were inserting into
        generateWords(in, floating, results, dict, current + in[idx], idx + 1, used,usedCount); //we skip that index
    } else {
        // Try every floating letter that has not been used yet
        for (size_t i = 0; i < floating.size(); ++i) {
            if (!used[i]) { //if the letter hasnt been used yet
                used[i] = true;
                generateWords(in, floating, results, dict, current + floating[i], idx + 1, used,usedCount + 1); //now we use the floating letter at th
                used[i] = false; // Backtrack after doing all the other options
            }
        }
                // Try every letter from 'a' to 'z' only if all floating letters haven't been used yet
        if (usedCount < static_cast<int>(floating.size())) {
            return;
        }
        // Try every letter from 'a' to 'z'
        for (char c = 'a'; c <= 'z'; ++c) {
            generateWords(in, floating, results, dict, current + c, idx + 1, used, usedCount);
        }
    }
}
