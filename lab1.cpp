#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;

bool isSeparator(char c) {
    return c == '-' || c == ',' || c == '.' || c == ' ' || c == '\'' || c == '"' || c == '\\' || c == '=' || c == '/';
}

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool containsOnlyVowels(const string& word) {
    for (char c : word) {
        if (!isVowel(c)) {
            return false;
        }
    }
    return true;
}

vector<string> splitWords(const string& line) {
    vector<string> words;
    string word;
    for (char c : line) {
        if (isSeparator(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

void findWordsWithOnlyVowels(const string& filename, int& wordCount) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    set<string> vowelWords;
    string line;
    while (getline(file, line)) {
        vector<string> words = splitWords(line);
        for (const string& word : words) {
            if (word.length() > 30) {
                vowelWords.insert(word.substr(0, 30));
            } else if (!word.empty() && containsOnlyVowels(word)) {
                vowelWords.insert(word);
            }
        }
    }
    file.close();

    wordCount = vowelWords.size();

    if (vowelWords.empty()) {
        cout << "No words with only vowels found in the file." << endl;
    } else {
        cout << "Words with only vowels (up to 30 letters): " << endl;
        for (const auto& word : vowelWords) {
            cout << word << endl;
        }
    }
}

int main() {
    string file_path = R"(C:/Users/miy_PC/CLionProjects/cppnew/testOne.txt)";

    ifstream input_stream(file_path);

    if (!input_stream.is_open()) {
        cerr << "Can't open input file: " << file_path << endl;
        return 1;
    }

    vector<string> text;

    string line;

    while (getline(input_stream, line)) {
        text.push_back(line);
    }

    input_stream.close();
    for (const auto& text_line : text) {
        cout << text_line << "\n" << endl;
    }
    int wordCount = 0;
    findWordsWithOnlyVowels(file_path, wordCount);
    cout << "Total number of words: " << wordCount << endl;
    return 0;
}

