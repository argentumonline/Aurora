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

#include "Definition.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic
{
	class IDriver
	{
	public:

		virtual ~IDriver() = default;

		virtual Bool Initialise(UInt window, UInt16 width, UInt16 height) = 0;

		virtual void Reset(UInt16 width, UInt16 height) = 0;

		virtual Bool CreateBuffer(UInt16 id, Bool geometry, UInt32 capacity, Span<UInt8> data) = 0;

		virtual void UpdateBuffer(UInt16 id, Bool discard, UInt32 offset, Span<UInt8> data) = 0;

		virtual void DeleteBuffer(UInt16 id) = 0;

		virtual Bool CreateDescriptor(UInt16 id, Span<UInt16> textures, Span<UInt16> samplers) = 0;

		virtual void DeleteDescriptor(UInt16 id) = 0;

		virtual Bool CreatePass(UInt16 id, UInt window, UInt16 width, UInt16 height) = 0;

		virtual Bool CreatePass(UInt16 id, Span<UInt16> color, UInt16 depth) = 0;

		virtual void DeletePass(UInt16 id) = 0;

		virtual Bool CreatePipeline(UInt16 id, Span<UInt8> vertex, Span<UInt8> pixel, const Descriptor & states) = 0;

		virtual void DeletePipeline(UInt16 id) = 0;

		virtual Bool CreateSampler(UInt16 id, TextureBorder edgeX, TextureBorder edgeY, TextureFilter filter) = 0;

		virtual void DeleteSampler(UInt16 id) = 0;

		virtual Bool CreateTexture(UInt16 id, TextureFormat format, TextureLayout layout, UInt16 width, UInt16 height,
			UInt8 mipmap, Span<UInt8> data) = 0;

		virtual void UpdateTexture(UInt16 id, UInt8 level, Rect offset, UInt32 pitch, Span<UInt8> data) = 0;

		virtual void DeleteTexture(UInt16 id) = 0;

		virtual void Prepare(UInt16 id, Rect viewport, Clear target, UInt32 color, Float32 depth, UInt8 stencil) = 0;

		virtual void Submit(Span<Submission> submissions) = 0;

		virtual void Commit() = 0;
	};
}