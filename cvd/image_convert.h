#ifndef CVD_IMAGE_CONVERT_H
#define CVD_IMAGE_CONVERT_H

#include <cvd/internal/convert_pixel_types.h>
#include <cvd/internal/rgb_components.h>
#include <cvd/image.h>

namespace CVD
{

	/// Some standard image conversion classes.
	/// @ingroup gImageIO
	namespace Pixel
	{
		/// The standard (0.299, 0.587, 0.114) weightings
		extern WeightedRGB<> CIE;
		/// Extract only the red component
		extern WeightedRGB<> red_only;
		/// Extract only the green component
		extern WeightedRGB<> green_only;
		/// Extract only the blue component
		extern WeightedRGB<> blue_only;
		/// Weight red, green and blue seperately
		extern WeightedRGB<> uniform;
	}

	/// Convert an image from one type to another using a specified conversion.
	/// @param D The destination image pixel type
	/// @param C The source image pixel type
	/// @param Conv The conversion class to use
	/// @param from The image to convert from
	/// @param cv The instance of the conversion to use. See Pixel for a list of common conversions.
	/// @ingroup gImageIO
	template<class D, class C, class Conv> 
	Image<D> convert_image(const BasicImage<C>& from, Conv& cv)
	{
		Image<D> to(from.size());

		const C *fp, *fpe;
		D* tp;

		fp = from.data();
		fpe = fp + from.totalsize();

		tp = to.data();

		
		for(; fp < fpe; fp++, tp++)
			cv.convert_pixel(*fp, *tp);

		return to;
	}

	/// Convert an image from one type to another using the default conversion (Pixel::CIE).
	/// This converts Rgb to greyscale using the usual (0.299, 0.587, 0.114) weightings
	/// and maps [0,1] floating point numbers onto the maximum ranges of integer datatypes and
	/// vice-versa.
	/// @param D The destination image pixel type
	/// @param C The source image pixel type
	/// @param from The image to convert
	/// @ingroup gImageIO
	template<class D, class C> Image<D> 
	convert_image(const BasicImage<C>& from)
	{
		return convert_image<D>(from, Pixel::CIE);
	}

}

#endif