#pragma once
#include "CAccessToNonExistentElementError.h"
#include "common_libs.h"

class CStringStack
{
public:

	CStringStack();

	CStringStack(const CStringStack& stack);

	CStringStack(CStringStack&& stack);

	~CStringStack();
	
	CStringStack& operator=(const CStringStack& stack);

	CStringStack& operator=(CStringStack&& stack);

	void Push(const std::string& value);

	std::string Pop();

	bool IsEmpty() const;
	
	int Size() const;

private:
	class NodeWithValue
	{
	public:
		NodeWithValue(NodeWithValue* next = nullptr, const std::string& value = "")
			: m_next(next)
			, m_value(value)
		{
			this->m_next = next;
		}

		std::string& GetValue()
		{
			return m_value;
		}

		NodeWithValue* m_next;

	private:
		std::string m_value;
	};

	void DeleteTop() noexcept;

	void Reverse();

	int m_size;

	NodeWithValue* m_first;
};
