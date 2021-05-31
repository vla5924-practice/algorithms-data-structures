#pragma once

#include "TText.h"
#include "TStack.h"

class TTextIter {
protected:
	TText& text;
	TTextNode* node;
	TStack<TTextNode*> st;
public:
	TTextIter(TText& _text, TTextNode* _node, TStack<TTextNode*> _st);
	TTextIter(const TTextIter& t);

	bool GoNext();
	bool GoNextChar();
	bool IsEnd();

	void ResetToString();
	void ResetToWord();

	TTextNode* Get();
};
