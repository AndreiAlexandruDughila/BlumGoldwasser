#pragma once;
#include <iostream>
#include <exception>
#include <ostream>
using namespace std;

namespace BITS{

	template<size_t size>
	class SetOfBits {

	private:


	public:

		char* representation;
		unsigned int length;

		SetOfBits() :representation(nullptr), length(0u) {};
		SetOfBits(unsigned int x);
		SetOfBits(const SetOfBits& a);
		SetOfBits& operator=(const SetOfBits& a);
		SetOfBits& operator&=(const SetOfBits& a);
		SetOfBits& operator|=(const SetOfBits& a);
		SetOfBits& operator^=(const SetOfBits& a);
		void setBitsInterval(unsigned int start, unsigned int no_bits, unsigned long long int value);
		unsigned long long int getValueBitsInterval(unsigned int start, unsigned int no_bits);
		template<size_t size> friend std::ostream& operator<< (std::ostream& stream, const SetOfBits<size>& set);
		void afisare();

	};

	template<size_t size>
	SetOfBits<size>::SetOfBits(const SetOfBits& a)
	{
		//if(this->length > a.length)
		this->representation = new char[size];
		std::fill_n(this->representation, size, '0');

	}

	template<size_t size>
	SetOfBits<size>& SetOfBits<size>::operator&=(const SetOfBits& a)
	{
		unsigned int start;
		if (this->length >= a.length)
		{
			start = this->length - a.length;
			for (int i = 0; i < a.length; i++)
			{
				if (this->representation[start + i] == '0' || a.representation[i] == '0')
					this->representation[i] = '0';
				else
					this->representation[i] = '1';
			}

		}
		else
		{
			start = a.length - this->length;
			for (int i = 0; i < this->length; i++)
			{
				if (this->representation[i] == '0' || a.representation[start + i] == '0')
					this->representation[i] = '0';
				else
					this->representation[i] = '1';
			}
		}
		return *this;
	}

	template<size_t size>
	SetOfBits<size>& SetOfBits<size>::operator|=(const SetOfBits& a)
	{
		unsigned int start;
		if (this->length >= a.length)
		{
			start = this->length - a.length;
			for (int i = 0; i < a.length; i++)
			{
				if (this->representation[start + i] == '1' || a.representation[i] == '1')
					this->representation[i] = '1';
				else
					this->representation[i] = '0';
			}

		}
		else
		{
			start = a.length - this->length;
			for (int i = 0; i < this->length; i++)
			{
				if (this->representation[i] == '1' || a.representation[start + i] == '1')
					this->representation[i] = '1';
				else
					this->representation[i] = '0';
			}
		}
		return *this;
	}



	template<size_t size>
	SetOfBits<size>::SetOfBits(unsigned int x)
	{
		this->representation = new char[size];
		this->length = size;
		std::fill_n(this->representation, size, '0');
		int y = size - 1;;
		while (y > -1)
		{
			if (x % 2 == 0)
			{
				this->representation[y] = '0';
			}
			else
			{
				this->representation[y] = '1';
			}
			x /= 2;
			y--;
		}

	}

	template<size_t size>
	SetOfBits<size>& SetOfBits<size>::operator=(const SetOfBits& a)
	{
		if (this->representation != nullptr)
			delete[] this->representation;
		this->length = a.length;
		this->representation = new char[a.length];
		unsigned int x = size - a.length;
		for (int i = 0; x < size; i++, x++)
			this->represantation[x] = a.represantation[i];
		return this;

	}

	template<size_t size>
	SetOfBits<size>& SetOfBits<size>::operator^=(const SetOfBits& a)
	{
		unsigned int start;
		if (this->length >= a.length)
		{
			start = this->length - a.length;
			for (int i = 0; i < a.length; i++)
			{
				if (this->representation[start + i] != a.representation[i])
					this->representation[i] = '1';
				else
					this->representation[i] = '0';
			}

		}
		else
		{
			start = a.length - this->length;
			for (int i = 0; i < this->length; i++)
			{
				if (this->representation[i] != a.representation[start + i])
					this->representation[i] = '1';
				else
					this->representation[i] = '0';
			}
		}
		return *this;
	}



	template<size_t size>
	void SetOfBits<size>::setBitsInterval(unsigned int start, unsigned int no_bits, unsigned long long int value)
	{
		if (this->representation == nullptr)  throw nullptr;
		unsigned int end = size - start - 1;
		start = end - no_bits + 1;
		while (end >= start)
		{
			if (value % 2 == 0)
			{
				this->representation[end] = '0';
			}
			else
			{
				this->representation[end] = '1';
			}
			end--;
			value /= 2;
		}

	}


	template<size_t size>
	unsigned long long int SetOfBits<size>::getValueBitsInterval(unsigned int start, unsigned int no_bits)
	{
		if (this->representation == nullptr)  throw nullptr;
		unsigned long long int s = 0;
		unsigned int end = size - start - 1;
		start = end - no_bits + 1;
		unsigned int i = 0;
		while (end >= start)
		{
			if (this->representation[end] == '1') {
				s += pow(2, i);
			}

			i++;
			end--;
		}
		return s;

	}


	template<size_t size>
	std::ostream& operator<<(std::ostream& stream, const SetOfBits<size>& set)
	{
		for (int i = 0; i < size; i++)
			stream << set.representation[i];
		return stream;
	}


	template<size_t size>
	void afisare() {
		std::cout << *this;
	}

}