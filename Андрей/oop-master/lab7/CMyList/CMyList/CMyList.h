#pragma once
#include "UnableChangeIteratorError.h"
#include "UnableDeleteElementError.h"
#include "UnableGetElementError.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>

template <typename T>
class CMyList
{
	class Node
	{
	public:
		Node(Node* prev, std::unique_ptr<Node>&& next)
			: m_prev(prev)
			, m_next(std::move(next))
		{
		}

		virtual T& GetValue()
		{
			throw UnableGetElementError("Error, can't get value");
		}

		virtual ~Node() = default;

		Node* m_prev;
		std::unique_ptr<Node> m_next;
	};

	class NodeWithValue : public Node
	{
	public:
		NodeWithValue(Node* prev, std::unique_ptr<Node>&& next, const T& value)
			: Node(prev, std::move(next))
			, m_value(value)
		{
		}

		T& GetValue() override
		{
			return m_value;
		}

	private:
		T m_value;
	};

	template <bool IsConst>
	class Iterator
	{
		friend class CMyList;

	public:
		using Type = Iterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		
        using difference_type = ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

		explicit Iterator(Node* node)
			: m_node(node)
		{
		}

		Iterator(const Iterator& iterator)
			: m_node(iterator.m_node)
		{
		}

		friend bool operator==(const Type& firstIterator, const Type& secondIterator)
		{
			return firstIterator.m_node == secondIterator.m_node;
		}

		friend bool operator!=(const Type& firstIterator, const Type& secondIterator)
		{
			return firstIterator.m_node != secondIterator.m_node;
		}

		Type operator++(int)
		{
			Iterator temp = *this;
			++(*this);

			return temp;
		}

		Type& operator++()
		{
			if (m_node == nullptr || m_node->m_next == nullptr)
			{
				throw UnableChangeIteratorError("Error, unable increase end()");
			}

			m_node = m_node->m_next.get();

			return *this;
		}

		Type operator--(int)
		{
			Iterator temp = *this;
			--(*this);

			return temp;
		}

		Type& operator--()
		{
			if (m_node == nullptr || m_node->m_prev == nullptr)
			{
				throw UnableChangeIteratorError("Error, unable increase begin()");
			}

			m_node = m_node->m_prev;

			return *this;
		}

		reference& operator*() const
		{
			return m_node->GetValue();
		}

	private:
		Node* m_node = nullptr;
	};

public:
	CMyList()
	{
		auto last = std::make_unique<Node>(nullptr, nullptr);
		Node* lastPtr = last.get();

		m_first = std::make_unique<Node>(nullptr, std::move(last));
		m_last = lastPtr;
		m_last->m_prev = m_first.get();
		m_size = 0;
	}

	~CMyList()
	{
		DeleteList();
	}

	CMyList(const CMyList& list)
	{
		m_first = nullptr;
		m_last = nullptr;
		m_size = 0;

		CMyList<T> tempList;

		for (const auto& element : list)
		{
			tempList.PushBack(element);
		}

		std::swap(*this, tempList);
	}

	CMyList(CMyList&& list)
	{
		m_first = std::move(list.m_first);
		m_last = list.m_last;
		m_size = list.m_size;

		list.m_first = nullptr;
		list.m_last = nullptr;
		list.m_size = 0;
	}

	CMyList& operator=(const CMyList& list)
	{
		if (this == &list)
		{
			return *this;
		}

		CMyList tempList(list);
		std::swap(*this, tempList);

		return *this;
	}

	CMyList& operator=(CMyList&& list)
	{
		if (this == &list)
		{
			return *this;
		}

		DeleteList();

		m_first = std::move(list.m_first);
		m_last = list.m_last;
		m_size = list.m_size;

		list.m_first = nullptr;
		list.m_last = nullptr;
		list.m_size = 0;

		return *this;
	}

	void PushBack(const T& value)
	{
		Insert(end(), value);
	}

	void PushFront(const T& value)
	{
		Insert(begin(), value);
	}

	bool IsEmpty() const
	{
		return m_size == 0;
	}

	int Size() const
	{
		return m_size;
	}

	using iterator = Iterator<false>;
	using const_iterator = Iterator<true>;

	iterator begin()
	{
		return iterator(m_first->m_next.get());
	}

	iterator end()
	{
		return iterator(m_last);
	}

	const_iterator begin() const
	{
		return const_iterator(m_first->m_next.get());
	}

	const_iterator end() const
	{
		return const_iterator(m_last);
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	}

	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
	}

	std::reverse_iterator<const_iterator> rbegin() const
	{
		return std::reverse_iterator<const_iterator>(end());
	}

	std::reverse_iterator<const_iterator> rend() const
	{
		return std::reverse_iterator<const_iterator>(begin());
	}

	void DeleteList()
	{
		while (!IsEmpty())
		{
			Delete(--end());
		}
	}

	void Insert(const const_iterator& it, const T& value)
	{
		Insert(iterator(it.m_node), value);
	}

	void Insert(const iterator& iterator, const T& value)
	{
		auto newNode = std::make_unique<NodeWithValue>(iterator.m_node->m_prev, std::move(iterator.m_node->m_prev->m_next), value);

		newNode->m_next->m_prev = newNode.get();
		newNode->m_prev->m_next = std::move(newNode);

		++m_size;
	}

	T& GetFrontElement()
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_first->m_next->GetValue();
	}

	const T& GetFrontElement() const
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_first->m_next->GetValue();
	}

	T& GetBackElement()
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_last->m_prev->GetValue();
	}

	const T& GetBackElement() const
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_last->m_prev->GetValue();
	}

	void Delete(const const_iterator& it)
	{
		Delete(iterator(it.m_node));
	}

	void Delete(const iterator& iterator)
	{
		if (iterator == end() || iterator == --begin())
		{
			throw UnableDeleteElementError("Error, you can't delete element at that position");
		}

		iterator.m_node->m_next->m_prev = iterator.m_node->m_prev;
		iterator.m_node->m_prev->m_next = std::move(iterator.m_node->m_next);

		m_size--;
	}

private:
	std::unique_ptr<Node> m_first;
	Node* m_last;

	int m_size;
};
