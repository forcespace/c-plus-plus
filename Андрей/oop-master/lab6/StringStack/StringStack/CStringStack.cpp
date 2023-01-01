#include "CStringStack.h"
#include "CEmptyStackError.h"
#include "common_libs.h"

CStringStack::CStringStack()
{
	m_size = 0;
	m_first = nullptr;
}

CStringStack::~CStringStack()
{
	while (!IsEmpty())
	{
		DeleteTop();
	}
}

CStringStack::CStringStack(const CStringStack& stack)
{
	CStringStack tempStack;

	auto originStackPtr = stack.m_first;

	while (tempStack.m_size != stack.m_size)
	{
		tempStack.Push(originStackPtr->GetValue());
		originStackPtr = originStackPtr->m_next;
	}

	tempStack.Reverse();

	m_first = tempStack.m_first;
	m_size = tempStack.m_size;

	tempStack.m_size = 0;
	tempStack.m_first = nullptr;
}

void CStringStack::Reverse()
{
	if (m_size < 2)
	{
		return;
	}

	NodeWithValue* last = nullptr;
	NodeWithValue* future = nullptr;
	NodeWithValue* curr = m_first;

	while (curr != nullptr)
	{
		future = curr->m_next;
		curr->m_next = last;
		last = curr;
		curr = future;
	}

	m_first = last;
}

CStringStack::CStringStack(CStringStack&& stack)
{
	m_size = stack.m_size;
	m_first = stack.m_first;

	stack.m_size = 0;
	stack.m_first = nullptr;
}

void CStringStack::DeleteTop() noexcept
{
	if (IsEmpty())
	{
		return;
	}

	auto futureFirst = m_first->m_next;
	delete m_first;
	m_first = futureFirst;

	m_size--;
}

void CStringStack::Push(const std::string& value)
{
	auto newNode = new NodeWithValue(m_first, value);
	
	m_first = newNode;

	m_size++;
}

std::string CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw CEmptyStackError("Error, stack is empty");
	}

	std::string popValue = std::move(m_first->GetValue());

	DeleteTop();

	return popValue;
}

bool CStringStack::IsEmpty() const
{
	return m_size == 0;
}

int CStringStack::Size() const
{
	return m_size;
}

CStringStack& CStringStack::operator=(const CStringStack& stack)
{
	if (this == &stack)
	{
		return *this;
	}

	CStringStack tempStack(stack);
	m_first = tempStack.m_first;
	m_size = tempStack.m_size;

	tempStack.m_size = 0;
	tempStack.m_first = nullptr;

	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& stack)
{
	if (this == &stack)
	{
		return *this;
	}

	m_first = stack.m_first;

	stack.m_size = 0;
	stack.m_first = nullptr;
	
	return *this;
}