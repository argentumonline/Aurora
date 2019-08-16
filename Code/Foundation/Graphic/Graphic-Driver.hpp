// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2019 Agustin L. Alvarez. All rights reserved.
//
// This work is licensed under the terms of the Apache License, Version 2.0.
//
// See <https://opensource.org/licenses/Apache-2.0>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Graphic-Pipeline.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Aurora::Graphic
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // [Missing Documentation]
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    class Driver
    {
    public:

        // [Missing Documentation]
        virtual Bool Initialise(void * Display, UInt16 Width, UInt16 Height) = 0;

        // [Missing Documentation]
        virtual void Dispose() = 0;

        // [Missing Documentation]
        virtual Bool CreateBuffer(UInt16 ID, Bool Vertex, Span<UInt8> Data) = 0;

        // [Missing Documentation]
        virtual void UpdateBuffer(UInt16 ID, Bool Discard, UInt32 Offset, Span<UInt8> Data) = 0;

        // [Missing Documentation]
        virtual void DeleteBuffer(UInt16 ID) = 0;

        // [Missing Documentation]
        virtual Bool CreatePass(UInt16 ID, Span<UInt16> Color, UInt16 Depth) = 0;

        // [Missing Documentation]
        virtual void DeletePass(UInt16 ID) = 0;

        // [Missing Documentation]
        virtual Bool CreatePipeline(UInt16 ID, UInt16 Program, const State & States) = 0;

        // [Missing Documentation]
        virtual void DeletePipeline(UInt16 ID) = 0;

        // [Missing Documentation]
        virtual Bool CreateProgram(UInt16 ID, Span<UInt8> Vertex, Span<UInt8> Fragment) = 0;

        // [Missing Documentation]
        virtual void DeleteProgram(UInt16 ID) = 0;

        // [Missing Documentation]
        virtual Bool CreateTexture(UInt16 Handle, TextureFormat Format, Bool Renderable,
            UInt16 Width, UInt16 Height, UInt8 Mipmap, UInt8 Samples, Span<UInt8> Data) = 0;

        // [Missing Documentation]
        virtual void UpdateTexture(UInt16 ID, UInt8 Level,
            UInt16 X, UInt16 Y, UInt16 Width, UInt16 Height, UInt16 Pitch, Span<UInt8> Data) = 0;

        // [Missing Documentation]
        virtual void DeleteTexture(UInt16 ID) = 0;

        // [Missing Documentation]
        virtual void SetBinding(UInt16 Vertex, UInt32 Offset, UInt16 Index) = 0;

        // [Missing Documentation]
        virtual void SetPass(UInt16 Pass, Clear Flag, UInt32 Color, Float Depth, UInt8 Stencil) = 0;

        // [Missing Documentation]
        virtual void SetPipeline(UInt16 Pipeline, UInt8 Ref) = 0;

        // [Missing Documentation]
        virtual void SetScissor(UInt16 X, UInt16 Y, UInt16 Width, UInt16 Height) = 0;

        // [Missing Documentation]
        virtual void SetTexture(Phase Stage, Span<UInt16> Textures, Span<Sampler> Samplers) = 0;

        // [Missing Documentation]
        virtual void SetUniform(Phase Stage, UInt32 Block, Span<UInt8> Data) = 0;

        // [Missing Documentation]
        virtual void SetViewport(UInt16 X, UInt16 Y, UInt16 Width, UInt16 Height) = 0;

        // [Missing Documentation]
        virtual void Submit(UInt32 Count, UInt32 Offset) = 0;

        // [Missing Documentation]
        virtual void Commit() = 0;

        // [Missing Documentation]
        virtual void Reset(UInt16 Width, UInt16 Height) = 0;
    };
}
