#include "common_libs.h"
#include "CStringStack.h"

int main()
{
	CStringStack stack;

	stack.Push("first");
	stack.Push("second");
	stack.Push("third");

	CStringStack newStack(stack);

	return 0;
}