#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <regex>
using namespace std;
// we allocate function in same class (to applicate Encapsulation princeple)
class clsString {

private:
	string _Value;
public:
	// parameterized and non-parameterized Constractors
	clsString() {
		_Value = "";
	}
	clsString(string Value) {
		_Value = Value;
	}
	// Setter and Getter (to applicate Abstraction princeple)
	void setValue(string Value) {
		_Value = Value;
	}
	string getValue() const {
		return _Value;
	}
	__declspec(property(put = setValue, get = getValue)) string Value;
	// Other Functions
	static size_t Length(string Str) 
	{
		return Str.length();
	}
	size_t Length()
	{
		return _Value.length();
	}
	static void PrintFirstLetterOfEachWord(string str) {

		bool isFirstLetter = true;//Flag

		cout << "\nFirst Letter Of Each Word :  ";

		for (size_t i = 0; i < str.length(); i++) {//I am a mahmoud

			if (isFirstLetter && str[i] != ' ') {
				cout << str[i] << '\t';// I 
			}

			isFirstLetter = (str[i] == ' ') ? true : false;

		}
	}
	void PrintFirstLetterOfEachWord() {

		PrintFirstLetterOfEachWord(_Value);

	}
	static string UpperFirstLetterOfEachWord(string str) {
		
		bool isFirstLetter = true;

		for (size_t i = 0; i < str.length(); i++) {

			if (isFirstLetter && str[i] != ' ') {
				str[i] = toupper(str[i]);
			}

			isFirstLetter = (str[i] == ' ') ? true : false;
		}

		return str;
	}
	void UpperFirstLetterOfEachWord() {

		_Value=UpperFirstLetterOfEachWord(_Value);

	}
	static string LowerFirstLetterOfEachWord(string str) {

		bool isFirstLetter = true;

		for (size_t i = 0; i < str.length(); i++) {

			if (isFirstLetter && str[i] != ' ') {

				str[i] = tolower(str[i]);

			}

			isFirstLetter = (str[i] == ' ') ? true : false;
		}

		return str;
	}
	void LowerFirstLetterOfEachWord() {

		_Value = LowerFirstLetterOfEachWord(_Value);

	}
	static string UpperAllLetterOfString(string str) {

		for (size_t i = 0; i < str.length(); i++) {
			str[i] = toupper(str[i]);
		}
		return str;
	}
	void UpperAllLetterOfString() {

		_Value = UpperAllLetterOfString(_Value);

	}
	static string LowerAllLetterOfString(string str) {

		for (size_t i = 0; i < str.length(); i++) {
			str[i] = tolower(str[i]);
		}
		return str;
	}
	void LowerAllLetterOfString() {

		_Value = LowerAllLetterOfString(_Value);

	}
	static char InvertLetterCase(char ch) {

		return (isupper(ch)) ? tolower(ch) : toupper(ch);

	}
	static string InvertAllLettersCase(string str) {

		for (size_t i = 0; i < str.length(); i++) {

			str[i] = InvertLetterCase(str[i]);

		}

		return str;

	}
	void InvertAllLettersCase() {

		_Value= InvertAllLettersCase(_Value);

	}
	enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };
	static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All) {
			if (WhatToCount == enWhatToCount::All) 
			{
				return short(S1.length());
			}
			short Counter = 0;
			for (size_t i = 0; i < S1.length(); i++) {
				if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
					Counter++;
				if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
					Counter++;
			}
			return Counter;
	}
	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All) {

		return  CountLetters(_Value, WhatToCount);

	}
	static short CountSpecificLetter(string Str, char LetterIteration,bool MatchCase=true) {

		short Counter = 0;

		for (size_t i = 0; i < Str.length(); i++) {

			if(MatchCase) {
				if (Str[i] == LetterIteration)
					Counter++;
			}
			else {
				if (tolower(Str[i]) == tolower(LetterIteration))
					Counter++;
			}
		}
		return Counter;

	}
	short CountSpecificLetter(char LetterIteration, bool MatchCase = true) {

		return CountSpecificLetter(_Value, LetterIteration, MatchCase);

	}
	static bool IsVowel(char Ch1) {

		Ch1 = tolower(Ch1);

		return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i')|| (Ch1== 'o') || (Ch1 == 'u'));

	}
	static short CountVowels(string str) {

		short counter = 0;

		for (size_t i = 0; i < str.length(); i++) {
			if (IsVowel(str[i])) {
				counter++;
			}
		}

		return counter;
	}
	short CountVowels() {

		return  CountVowels(_Value);

	}
	static void PrintVowels(string Str) {

		cout << "\nVowels in string are: ";

		for (size_t i = 0; i < Str.length(); i++) {
			
			if (IsVowel(Str[i]))
				cout << Str[i] << " ";

		}
	}
	void PrintVowels() {

		PrintVowels(_Value);

	}
	static void PrintEachWordInString(string Str, string delim = " ")
	{
		cout << "\nYour string wrords are: \n\n";
		size_t pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = Str.find(delim)) != std::string::npos)
		{
			sWord = Str.substr(0, pos); // store the word
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			Str.erase(0, pos + delim.length()); /* erase() until
			positon and move to next word. */
		}
		if (Str != "")
		{
			cout << Str << endl; // it print last word of the string.
		}
	}
	void PrintEachWordInString() {
		
		PrintEachWordInString(_Value);

	}
	static short CountWords(string str, string delim = " ") {

		size_t Pos = 0, WordCounter = 0;
		string sWord;

		while ((Pos = str.find(delim)) != string::npos)
		{
			sWord = str.substr(0, Pos);
			if (sWord != "")
			{
				WordCounter++;
			}
			str.erase(0, Pos + delim.length());
		}

		if (str != "")
		{
			WordCounter++;;
		}
		return WordCounter;
	}
	short CountWords() {

		return CountWords(_Value);

	}
	static vector<string> Split(string S1, string Delim= " ")
	{
		vector<string> vString;
		size_t pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S1.erase(0, pos + Delim.length()); /* erase() until
			positon and move to next word. */
		}
		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}
		return vString;
	}
	vector<string> Split(string Delim = " ") {

		return Split(_Value, Delim);

	}
	static string TrimLeft(string str) {
		for (size_t i = 0; i < str.length() ;i++) {//  i am
			if (str[i] != ' ') {
				return str.substr(i, str.length() - i);
			}
		}
		return str;
	}
	void TrimLeft() {
		_Value = TrimLeft(_Value);
	}
	static string TrimRight(string str) {
		for (size_t i = str.length() - 1; i > 0; i--) {//iam   
			if (str[i] != ' ') {
				return str.substr(0, i + 1);
			}
		}
		return str;
	}
	void TrimRight() {
		_Value =  TrimRight(_Value);
	}
	static string Trim(string str) {
		return TrimLeft(TrimRight(str));
	}
	void Trim() {
		_Value = Trim(_Value);
	}
	static string JoinString(const vector<string>&vString, string Seperator = " ") {
		string Str = "";
		if (vString.empty()) return "";
		for (const string& S : vString) {
			Str += (S + Seperator);
		}
		return Str.substr(0, Str.length() - Seperator.length());//for ignore last seperator
	}
	static string JoinString(const string arrString[], short LengthOfArray, string Seperator = " ") {
		string Str = "";
		for (size_t i = 0; i < LengthOfArray;i++) {
			Str += (arrString[i] + Seperator);
		}
		return Str.substr(0, Str.length() - Seperator.length());//for ignore last seperator
	}
	static string RevreseWordInString(string Str,string Delim = " ") {
		vector<string>vString = Split(Str,Delim);
		string RevStr = "";
		vector<string>::iterator iter = vString.end();
		while (iter != vString.begin()) {
			--iter;
			RevStr += *iter + Delim;
		}
		return RevStr.substr(0, RevStr.length() - 1);
	}
	void RevreseWordInString() {
		_Value = RevreseWordInString(_Value);
	}
	static string ReplaceWordInStringUsingBuiltInFunction(string str, string WordToReplace, string ReplaceTo) {
		size_t pos = str.find(WordToReplace);
		while (pos != std::string::npos) {
			str = str.replace(pos, WordToReplace.length(), ReplaceTo);
			pos = str.find(WordToReplace);
		}
		return str;
	}
	void ReplaceWordInStringUsingBuiltInFunction(string WordToReplace, string ReplaceTo) {
		_Value = ReplaceWordInStringUsingBuiltInFunction(_Value, WordToReplace, ReplaceTo);
	}
	static string ReplaceWordUsingSplit(string str, string WordToReplace, string ReplaceTo,bool MatchCase = true) {

		vector<string>vString = Split(str," ");
		vector<string>::iterator iter = vString.begin();
		while (iter != vString.end()) {
			if (MatchCase) {
				if (*iter == WordToReplace) {
					*iter = ReplaceTo;
			}
				}
				else {
				if (LowerAllLetterOfString(*iter) == LowerAllLetterOfString(WordToReplace)) {
					*iter = ReplaceTo;
				}
			}
			iter++;
		}
		return JoinString(vString," ");
	}
	void ReplaceWordUsingSplit(string WordToReplace, string ReplaceTo, bool MatchCase = true) 
	{
		_Value =  ReplaceWordUsingSplit(_Value, WordToReplace, ReplaceTo, MatchCase);
	}
	static string RemovePunctuationsFromString(string str) {
		string S1 = "";
		for (size_t i = 0; i < str.length(); i++) {
			if (!ispunct(str[i])) {
				S1 += str[i];
			}
		}
		return S1;
	}
	void RemovePunctuationsFromString()
	{
		_Value = RemovePunctuationsFromString(_Value);
	}
	static string RemoveSpaceFromString(string str) {
		string S1 = "";
		for (size_t i = 0; i < str.length(); i++) {
			if (str[i] != ' ') {
				S1 += str[i];
			}
		}
		return S1;
	}
	string RemoveSpaceFromString()
	{
		_Value = RemoveSpaceFromString(_Value);
	}
	static bool isValidFormatting(string str, const string& regexPattern,bool WithSpace = false)
	{
		regex pattern(regexPattern);

		str = (WithSpace) ? str : RemoveSpaceFromString(str);

		return regex_match(str, pattern);
	}
	static bool isWordInString(string str, string Word)
	{
		if (Word.empty()) return false;
		// Normalize to lower-case for case-insensitive search
		string s = LowerAllLetterOfString(str);
		string w = LowerAllLetterOfString(Word);
		// Extract alphanumeric tokens (words) using regex
		regex re("\\w+");
		auto begin = sregex_iterator(s.begin(), s.end(), re);
		auto end = sregex_iterator();
		bool foundToken = false;
		for (auto it = begin; it != end; ++it) {
			foundToken = true;
			if (it->str() == w) return true; // exact token match
		}
		// If tokens exist but no exact match, return false
		if (foundToken) return false;
		// No tokens found (rare) -> fallback to substring search
		return (s.find(w) != string::npos);
	}
	bool isWordInString(string Word) 
	{
		return isWordInString(_Value, Word);
	}
};

