#pragma once
#ifndef TOOLS_N_BITSET_INLINE
#define TOOLS_N_BITSET_INLINE

namespace tools
{
	// Set
	template <size_t MAX_BITS>
	void n_bitset<MAX_BITS>::Set(const int Index) noexcept
	{
		auto byte_index = Index / BYTE_SIZE;
		auto bit_index  = Index % BYTE_SIZE;

		m_Bits[byte_index] |= (1ull << bit_index);
	}


	// Get
	template <size_t MAX_BITS>
	bool n_bitset<MAX_BITS>::Get(const int Index) const noexcept
	{
		auto byte_index = Index / BYTE_SIZE;
		auto bit_index  = Index % BYTE_SIZE;
		
		return !!( m_Bits[byte_index] & (1ull << bit_index) );
	}

	template <size_t MAX_BITS>
	bool n_bitset<MAX_BITS>::operator[](const int Index) const noexcept
	{
		return Get(Index);
	}

	template <size_t MAX_BITS>
	bool n_bitset<MAX_BITS>::All(void) const noexcept
	{
		for (const auto& Value : m_Bits)
			if (Value != UINT8_MAX) return false;
		return true;
	}

	template <size_t MAX_BITS>
	bool n_bitset<MAX_BITS>::Any(void) const noexcept
	{
		for (const auto& Value : m_Bits)
			if (Value) return true;
		return false;
	}

	template <size_t MAX_BITS>
	bool n_bitset<MAX_BITS>::None(void) const noexcept
	{
		for (const auto& Value : m_Bits)
			if (Value) return false;
		return true;
	}


	// Reset
	template <size_t MAX_BITS>
	void n_bitset<MAX_BITS>::Reset(void) noexcept
	{
		for (auto& Value : m_Bits)
			Value = 0;
	}

	template <size_t MAX_BITS>
	void n_bitset<MAX_BITS>::Reset(const int Index) noexcept
	{
		auto byte_index = Index / BYTE_SIZE;
		auto bit_index  = Index % BYTE_SIZE;
		
		m_Bits[byte_index] &= ~(1ull << bit_index);
	}


	// Flip
	template <size_t MAX_BITS>
	void n_bitset<MAX_BITS>::Flip(void) noexcept
	{
		for (auto& Value : m_Bits)
			Value = ~Value;
	}


	// Printouts
	template <size_t MAX_BITS>
	std::string n_bitset<MAX_BITS>::Display(void) noexcept
	{
		std::string Output;

		for (size_t i = 0, max = m_Bits.size(); i < max; ++i)
		{
			for (int j = 0; j < BYTE_SIZE; ++j)
			{
				Output += std::to_string( Get(i * BYTE_SIZE + j) );
			}
		}
		FlipString(Output);

		return Output;
	}

	template <size_t MAX_BITS>
	std::string n_bitset<MAX_BITS>::FlipString(std::string& BitString) const noexcept
	{
		for (size_t i = 0, max = BitString.size(); i < max / 2; ++i)
		{
			std::swap(BitString[i], BitString[max - 1 - i]);
		}
		return BitString;
	}

	template <size_t MAX_BITS>
	std::ostream& operator<<(std::ostream& Stream, n_bitset<MAX_BITS>& Bitset) noexcept
	{
		Stream << Bitset.Display();
		return Stream;
	}
}

namespace TestCase
{
	void inline Test1()
	{
		tools::n_bitset<9> test_bitset;
		test_bitset.Set(1);

		std::cout << "Test Subscript: " << test_bitset[1] << std::endl;
		std::cout << "Test All: " << test_bitset.All() << std::endl;
		std::cout << "Test Any: " << test_bitset.Any() << std::endl;
		std::cout << "Test None: " << test_bitset.None() << std::endl;
		std::cout << "Test Display: " << test_bitset.Display() << std::endl;

		test_bitset.Reset(0);
		std::cout << "Test Reset Wrong Index: " << test_bitset.Display() << std::endl;
		test_bitset.Reset(1);
		std::cout << "Test Reset Right Index: " << test_bitset.Display() << std::endl;

		test_bitset.Set(1);
		std::cout << "Test Set Again: " << test_bitset.Display() << std::endl;
		test_bitset.Reset();
		std::cout << "Test Reset All: " << test_bitset.Display() << std::endl;

		test_bitset.Set(1);
		test_bitset.Set(3);
		std::cout << "Test Set Again: " << test_bitset.Display() << std::endl;
		test_bitset.Flip();
		std::cout << "Test Flip All: " << test_bitset << std::endl;
	}
}

#endif