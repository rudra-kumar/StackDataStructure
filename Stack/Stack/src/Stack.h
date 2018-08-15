#pragma once

template<typename T>
class Stack
{
public:
	Stack() = default;
	Stack<T>(const Stack& source)
	{
		*this = source;
	}
	Stack<T>& operator=(const Stack<T>& rhs)
	{
		// If it is the same object, i.e. they are pointing to the same memory, just return the current object.
		if (this == &rhs)
			return *this;
		if (m_Size != 0)
		{
			delete m_Top;
			m_Top = nullptr;
		}
		if (rhs.Size() != 0)
		{
			m_Size = rhs.m_Size;
			m_Top = new Element<T>(*rhs.m_Top);
		}
		return *this;
	}
	~Stack()
	{
		// Recursively destroy all the elements 
		delete m_Top;
		m_Top = nullptr;
	}
	void Push(T value)
	{
		m_Top = new Element<T>(value, m_Top);
		m_Size++;
	}
	T Pop()
	{
		if (m_Size == 0)
			return -1;
		else
		{
			m_Size--;
			// Store a pointer to that element and its value in temp variables.
			Element<T>* temp = m_Top;
			T value = m_Top->GetValue();
			// Change the top to point to the next element 
			m_Top = m_Top->Disconnect();
			delete temp;
			temp = nullptr;
			return value;
		}
	}
	bool Empty() const
	{
		if (m_Size == 0)
			return true;
		else
			return false;
	}
	int Size() const
	{
		return m_Size;
	}
private:
	template <typename T>
	class Element
	{
	public:
		Element<T>(T value, Element* nextElement)
			: m_Value(value), m_NextElement(nextElement)
		{

		}
		Element<T>(const Element<T>& source)
			: m_Value(source.m_Value)
		{
			if (source.m_NextElement != nullptr)
				m_NextElement = new Element(*source.m_NextElement);
		}
		Element<T>& operator=(const Element<T>& rhs) = delete;
		~Element()
		{
			// Recursively destroying all the elements 
			delete m_NextElement;
			m_NextElement = nullptr;
		}
		Element* Disconnect()
		{
			Element<T>* tempNext = m_NextElement;
			m_NextElement = nullptr;
			return tempNext;
		}
		T GetValue() const
		{
			return m_Value;
		}
	private:
		Element<T>* m_NextElement = nullptr;
		T m_Value;
	};
private:
	Element<T>* m_Top = nullptr;
	int m_Size = 0;
};