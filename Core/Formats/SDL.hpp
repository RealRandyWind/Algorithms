#pragma once

#include <Types>
#include <Iterator>
#include <Point>

namespace Format
{
	struct FSDL
	{

	};

	struct FSDL2D : public FSDL
	{
		template<typename TypePoint>
		using TPoints = TIterator<TPoint2D<TypePoint>>;

		template<typename TypePixel>
		using TPixels = TIterator<TypePixel>;

		template<typename TypePoint>
		struct TPlacement
		{
			TPoint2D<TypePoint> Position, Up, Left, Scale;
			FReal Layer;
		};

		template<typename TypePoint>
		struct FStyle
		{
			TypePoint Width, Height;
			FReal Opacity, 
		};

		template<typename TypePoint>
		FSize Path(
				TPoints<TypePoint>,
				TPlacement<TypePoint>);

		template<typename TypePixel, typename TypePoint>
		FSize Image(
				TPixels<TypePixel>,
				TPlacement<TypePoint>);

		template<typename TypePoint>
		FSize Points(
				TPoints<TypePoint>,
				TPlacement<TypePoint>);
		
		template<typename TypePoint>
		FSize Lines(
				TPoints<TypePoint>,
				TPlacement<TypePoint>);
	};
}
