// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2017-2020 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <EASTL/span.h>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

inline namespace Stl
{
	/// Simplified alias of \see bool8_t
	using Bool    = bool8_t;

	/// Simplified alias of \see intmax_t
	using SInt    = intmax_t;

	/// Simplified alias of \see uintmax_t
	using UInt    = uintmax_t;

	/// Simplified alias of \see int8_t
	using SInt8   = int8_t;

	/// Simplified alias of \see uint8_t
	using UInt8   = uint8_t;

	/// Simplified alias of \see int16_t
	using SInt16  = int16_t;

	/// Simplified alias of \see uint16_t
	using UInt16  = uint16_t;

	/// Simplified alias of \see int32_t
	using SInt32  = int32_t;

	/// Simplified alias of \see uint32_t
	using UInt32  = uint32_t;

	/// Simplified alias of \see int64_t
	using SInt64  = int64_t;

	/// Simplified alias of \see uint64_t
	using UInt64  = uint64_t;

	/// Simplified alias of \see float_t
	using Float32 = float_t;

	/// Simplified alias of \see double_t
	using Float64 = double_t;

	/// Simplified alias of \see span
	template<typename Type>
	using Span    = eastl::span<Type>;

	/// TODO: Move this into another file
	template<UInt Count>
	class Handles
	{
	public:

		explicit Handles() : mAllocation { 0 }
		{
			(* mAllocation) |= (1 << 0);
		}

		UInt16 Allocate()
		{
			for (UInt32 i = 0; i < sizeof(mAllocation); ++i)
			{
				if (SInt8 number = ~mAllocation[i]; number != 0)
				{
					const auto bit = static_cast<SInt8>(log2(number & -number));
					mAllocation[i] |= 1u << bit;

					return ((i << 3u) + bit);
				}
			}
			return 0u;
		}

		UInt16 Free(UInt16 index)
		{
			mAllocation[(index >> 3u)] &= ~(1u << (index % 8u));
			return index;
		}

	private:

		UInt8 mAllocation[(Count >> 3) + 1];
	};
}