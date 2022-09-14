#pragma once
#ifndef TOOLS_N_BITSET
#define TOOLS_N_BITSET

#define BYTE_SIZE 8


// Declaration
namespace tools
{
	constexpr int Compute_Min_Bytes_Required(const int NumBits) noexcept
	{
		int BytesNeeded = NumBits / BYTE_SIZE;

		if ( BytesNeeded == (NumBits / (float)BYTE_SIZE))
			return BytesNeeded;
		else if ( BytesNeeded == 0 )
			return 1;
		else
			return BytesNeeded+1;
	}


	template <size_t MAX_BITS = BYTE_SIZE>
	class n_bitset final
	{
	public:
		/*
			Functionality
		*/
		// Set
		void inline Set(const int Index) noexcept;

		// Get
		bool inline Get(const int Index) const noexcept;
		bool inline operator[](const int Index) const noexcept;
		bool inline All(void) const noexcept;
		bool inline Any(void) const noexcept;
		bool inline None(void) const noexcept;

		// Reset
		void inline Reset(void) noexcept;
		void inline Reset(const int Index) noexcept;

		// Flip
		void inline Flip(void) noexcept;

		// Printouts
		std::string inline Display(void) noexcept;


	private:

		std::string inline FlipString(std::string& BitString) const noexcept;

		/*
			Data Members
		*/
		std::array<std::uint8_t, tools::Compute_Min_Bytes_Required(MAX_BITS)> m_Bits{};
	};
}

#endif