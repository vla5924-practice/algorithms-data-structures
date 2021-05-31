#include <iostream>
#include <TTextNode.h>

int main()
{
	char c[] = "Privet";
	TTextNode* str1 = new TTextNode(c, 2);
	std::cout << *str1 << std::endl;
	TTextNode::FreeMem();
}
