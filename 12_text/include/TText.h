#pragma once
#include <iostream>

#include "TTextNode.h"
class TTextIter;

class TText {
protected:
	TTextNode* root;
public:
	TText(char* s = nullptr);
	~TText();

	TTextIter GetRoot(); 
	TTextIter Find(char c); 
	TTextIter Find(char* c); 
	TTextIter FindWord(char* c);

	void Insert(char* c, TTextIter i); 
	void InsertData(char* c, TTextIter i);
	void Delete(int count, TTextIter i); 
	char* Copy(int count, TTextIter i); 

	friend std::ostream& operator<<(std::ostream& o, const TText& t)
	{
		o << *(t.root);
		return o;
	}
};
