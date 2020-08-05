#pragma once

#include "SDL.h"
#include <windows.h>
#include <iostream>

namespace nc
{
	struct Color
	{
		float r, g, b, a;

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {}
		Color(float r, float g, float b, float a = 1.0f) : r{ r }, g{ g }, b{ b }, a{ a } {}

		float& operator [] (size_t index) { return (&r)[index]; } // &r -> g -> b -> ?
		const float& operator [] (size_t index) const { return (&r)[index]; }

		void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }

		Color operator + (const Color& c) const { return { r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return { r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return { r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return { r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return { r + s, g + s, b + s }; }
		Color operator - (float s) const { return { r - s, g - s, b - s }; }
		Color operator * (float s) const { return { r * s, g * s, b * s }; }
		Color operator / (float s) const { return { r / s, g / s, b / s }; }

		friend std::istream& operator >> (std::istream& stream, Color& c);

		SDL_Color Pack888() const;
		operator SDL_Color() const { return Pack888(); }

		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
	};

	inline SDL_Color Color::Pack888() const
	{
		// BYTE  = 1 byte | 8  bits
		// WORD  = 2 byte | 16 bits
		// DWORD = 4 byte | 32 bits
		BYTE _r = static_cast<BYTE>(r * 255.0f); // (0 - 1) -> (0 - 255)
		BYTE _g = static_cast<BYTE>(g * 255.0f);
		BYTE _b = static_cast<BYTE>(b * 255.0f);
		BYTE _a = static_cast<BYTE>(a * 255.0f);

		return { _r, _g, _b, _a };
	}

}
