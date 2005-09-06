#include "PosteRazor.h"
#include "PosteRazorImageIO.h"
#include <string.h>
#include <math.h>

#define MIN(a, b) ((a)<=(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MINMAX(a, min, max) (MIN((max), MAX((a), (min))))

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO*     m_imageIO;

	enum eDistanceUnits    m_distanceUnit;

	double                 m_overlappingWidth;
	double                 m_overlappingHeight;
	enum eOverlappingPositions m_overlappingPosition;

	enum ePosterSizeModes  m_posterSizeMode;
	double                 m_posterDimension;
	bool                   m_posterDimensionIsWidth;
	enum eHorizontalAlignments m_posterHorizontalAlignment;
	enum eVerticalAlignments m_posterVerticalAlignment;

	bool                   m_useCustomPaperSize;
	ePaperFormats          m_paperFormat;
	ePaperOrientations     m_paperOrientation;
	double                 m_paperBorderTop;
	double                 m_paperBorderRight;
	double                 m_paperBorderBottom;
	double                 m_paperBorderLeft;
	double                 m_customPaperWidth;
	double                 m_customPaperHeight;
	
public:
	PosteRazorImplementation()
	{
		m_imageIO                      = PosteRazorImageIO::CreatePosteRazorImageIO();

		m_posterSizeMode               = ePosterSizeModePages;
		m_posterDimension              = 2.0;
		m_posterDimensionIsWidth       = true;
		m_posterHorizontalAlignment    = eHorizontalAlignmentLeft;
		m_posterVerticalAlignment      = eVerticalAlignmentTop;

		m_useCustomPaperSize           = false;
		m_paperFormat                  = ePaperFormatA4;
		m_paperOrientation             = ePaperOrientationPortrait;
		m_paperBorderTop               = 1.5;
		m_paperBorderRight             = 1.5;
		m_paperBorderBottom            = 1.5;
		m_paperBorderLeft              = 1.5;
		m_customPaperWidth             = 20;
		m_customPaperHeight            = 20;

		m_overlappingWidth             = 1.0;
		m_overlappingHeight            = 1.0;
		m_overlappingPosition          = eOverlappingPositionBottomRight;

		m_distanceUnit                 = eDistanceUnitCentimeter;
	}

	~PosteRazorImplementation()
	{
		delete m_imageIO;
	}

	PosteRazorImageIO *GetImageIO(void) {return m_imageIO;}

	bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		return m_imageIO->LoadImage(imageFileName, errorMessage, errorMessageSize);
	}
	bool IsImageLoaded(void) {return m_imageIO->IsImageLoaded();}

	int GetInputImageWidthPixels(void) {return m_imageIO->GetWidthPixels();}
	int GetInputImageHeightPixels(void) {return m_imageIO->GetHeightPixels();}

	double GetInputImageHorizontalDpi(void) {return m_imageIO->GetHorizontalDotsPerDistanceUnit(eDistanceUnitInch);}
	double GetInputImageVerticalDpi(void) {return m_imageIO->GetVerticalDotsPerDistanceUnit(eDistanceUnitInch);}

	double GetInputImageWidth(void) {return m_imageIO->GetWidth(m_distanceUnit);}
	double GetInputImageHeight(void) {return m_imageIO->GetHeight(m_distanceUnit);}

	int GetInputImageBitsPerPixel(void) {return m_imageIO->GetBitsPerPixel();}
	enum eColorTypes GetInputImageColorType(void) {return m_imageIO->GetColorDataType();}

	void SetDistanceUnit(enum eDistanceUnits unit) {m_distanceUnit = unit;}
	enum eDistanceUnits GetDistanceUnit(void) {return m_distanceUnit;}
	const char* GetDistanceUnitName(void) {return DistanceUnits::GetDistanceUnitName(m_distanceUnit);}

	void SetPaperFormat(enum ePaperFormats format) {m_paperFormat = format;}
	void SetPaperOrientation(enum ePaperOrientations orientation) {m_paperOrientation = orientation;}
	void SetPaperBorderTop(double border) {m_paperBorderTop = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderRight(double border) {m_paperBorderRight = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderBottom(double border) {m_paperBorderBottom = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderLeft(double border) {m_paperBorderLeft = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}

	enum ePaperFormats GetPaperFormat(void) {return m_paperFormat;}
	enum ePaperOrientations GetPaperOrientation(void) {return m_paperOrientation;}
	double GetPaperBorderTop(void) {return MINMAX(ConvertBetweenDistanceUnits(m_paperBorderTop, eDistanceUnitCentimeter, m_distanceUnit), 0, GetMaximalHorizontalPaperBorder());}
	double GetPaperBorderRight(void) {return MINMAX(ConvertBetweenDistanceUnits(m_paperBorderRight, eDistanceUnitCentimeter, m_distanceUnit), 0, GetMaximalVerticalPaperBorder());}
	double GetPaperBorderBottom(void) {return MINMAX(ConvertBetweenDistanceUnits(m_paperBorderBottom, eDistanceUnitCentimeter, m_distanceUnit), 0, GetMaximalHorizontalPaperBorder());}
	double GetPaperBorderLeft(void) {return MINMAX(ConvertBetweenDistanceUnits(m_paperBorderLeft, eDistanceUnitCentimeter, m_distanceUnit), 0, GetMaximalVerticalPaperBorder());}

	double GetMaximalVerticalPaperBorder(void) {return GetPaperWidth() / 2.0 - ConvertBetweenDistanceUnits(1.0, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetMaximalHorizontalPaperBorder(void) {return GetPaperHeight() / 2.0 - ConvertBetweenDistanceUnits(1.0, eDistanceUnitCentimeter, m_distanceUnit);}

	void SetCustomPaperWidth(double width) {m_customPaperWidth = ConvertBetweenDistanceUnits(width, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetCustomPaperHeight(double height) {m_customPaperHeight = ConvertBetweenDistanceUnits(height, m_distanceUnit, eDistanceUnitCentimeter);}

	double GetCustomPaperWidth(void) {return MAX(GetCustomMinimalPaperWidth(), ConvertBetweenDistanceUnits(m_customPaperWidth, eDistanceUnitCentimeter, m_distanceUnit));}
	double GetCustomPaperHeight(void) {return MAX(GetCustomMinimalPaperHeight(), ConvertBetweenDistanceUnits(m_customPaperHeight, eDistanceUnitCentimeter, m_distanceUnit));}

	double GetCustomMinimalPaperWidth(void) {return ConvertBetweenDistanceUnits(4.0, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetCustomMinimalPaperHeight(void) {return ConvertBetweenDistanceUnits(4.0, eDistanceUnitCentimeter, m_distanceUnit);}

	void SetUseCustomPaperSize(bool useIt) {m_useCustomPaperSize = useIt;}
	bool GetUseCustomPaperSize(void) {return m_useCustomPaperSize;}

	double GetPaperWidth(void) {return GetUseCustomPaperSize()?GetCustomPaperWidth():PaperFormats::GetPaperWidth(GetPaperFormat(), GetPaperOrientation(), m_distanceUnit);}
	double GetPaperHeight(void) {return GetUseCustomPaperSize()?GetCustomPaperHeight():PaperFormats::GetPaperHeight(GetPaperFormat(), GetPaperOrientation(), m_distanceUnit);}

	double GetPrintablePaperAreaWidth(void) {return GetPaperWidth() - GetPaperBorderLeft() - GetPaperBorderRight();}
	double GetPrintablePaperAreaHeight(void) {return GetPaperHeight() - GetPaperBorderTop() - GetPaperBorderBottom();}

	double ConvertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width)
	{
		double posterDimension = dimension;

		double printablePaperAreaWidth = GetPrintablePaperAreaWidth();
		double printablePaperAreaHeight = GetPrintablePaperAreaHeight();
		double printablePaperAreaDimension = ConvertBetweenDistanceUnits(width?printablePaperAreaWidth:printablePaperAreaHeight, m_distanceUnit, eDistanceUnitCentimeter);
		double overlappingDimension = ConvertBetweenDistanceUnits(width?GetOverlappingWidth():GetOverlappingHeight(), m_distanceUnit, eDistanceUnitCentimeter);

		if (pagesToAbsolute)
		{
			double posterDimensionAbsolute = 0;
			if (posterDimension >= 1.0)
			{
				posterDimension -= 1.0;
				posterDimensionAbsolute += printablePaperAreaDimension;
			}
			else
			{
				posterDimensionAbsolute = posterDimension * printablePaperAreaDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
	                        posterDimensionAbsolute += (posterDimension * (printablePaperAreaDimension - overlappingDimension));

			posterDimension = posterDimensionAbsolute;
		}
		else
		{
			double posterDimensionPages = 0;
			if (posterDimension >= printablePaperAreaDimension)
			{
				posterDimension -= printablePaperAreaDimension;
				posterDimensionPages += 1.0;
			}
			else if (posterDimension < printablePaperAreaDimension)
			{
				posterDimensionPages = posterDimension / printablePaperAreaDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
	                        posterDimensionPages += (posterDimension / (printablePaperAreaDimension - overlappingDimension));

			posterDimension = posterDimensionPages;
		}

		return posterDimension;
	}

	// Since m_posterDimension holds only height or width of the poster,
	// here we calculate the other dimension considering the aspect ratio.
	double CalculateOtherPosterDimension()
	{
		double otherDimension = 0;

		if (m_posterSizeMode != ePosterSizeModePercentual)
		{
			double sourceReference = m_posterDimensionIsWidth?GetInputImageWidth():GetInputImageHeight();
			double targetReference = m_posterDimensionIsWidth?GetInputImageHeight():GetInputImageWidth();
			
			double aspectRatio = sourceReference/targetReference;

			if (m_posterSizeMode != ePosterSizeModePages)
			{
				otherDimension = m_posterDimension / aspectRatio;
			}
			else
			{
				double sourceAbsolute = ConvertBetweenAbsoluteAndPagesPosterDimension(m_posterDimension, true, m_posterDimensionIsWidth);
				double targetAbsolute = sourceAbsolute/aspectRatio;
				otherDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(targetAbsolute, false, !m_posterDimensionIsWidth);
			}
		}
		else
			otherDimension = m_posterDimension;

		return otherDimension;
	}

	void SetPosterDimension(enum ePosterSizeModes mode, double dimension, bool dimensionIsWidth)
	{
		m_posterSizeMode = mode;

		if (m_posterSizeMode == ePosterSizeModeAbsolute)
			dimension = ConvertBetweenDistanceUnits(dimension, m_distanceUnit, eDistanceUnitCentimeter);

		m_posterDimension = dimension;
		m_posterDimensionIsWidth = dimensionIsWidth;
	}

	void SetOverlappingWidth(double width) {m_overlappingWidth = ConvertBetweenDistanceUnits(width, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetOverlappingHeight(double height) {m_overlappingHeight = ConvertBetweenDistanceUnits(height, m_distanceUnit, eDistanceUnitCentimeter);}
	double GetOverlappingWidth(void) {return MINMAX(ConvertBetweenDistanceUnits(m_overlappingWidth, eDistanceUnitCentimeter, m_distanceUnit), 0, GetMaximalOverLappingWidth());}
	double GetOverlappingHeight(void) {return MINMAX(ConvertBetweenDistanceUnits(m_overlappingHeight, eDistanceUnitCentimeter, m_distanceUnit), 0, GetMaximalOverLappingHeight());}
	double GetMaximalOverLappingWidth(void) {return GetPaperWidth() - GetPaperBorderLeft() - GetPaperBorderRight() - ConvertBetweenDistanceUnits(1.0, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetMaximalOverLappingHeight(void) {return GetPaperHeight() - GetPaperBorderTop() - GetPaperBorderBottom() - ConvertBetweenDistanceUnits(1.0, eDistanceUnitCentimeter, m_distanceUnit);}
	void SetOverlappingPosition(enum eOverlappingPositions position) {m_overlappingPosition = position;}
	enum eOverlappingPositions GetOverlappingPosition(void) {return m_overlappingPosition;}

	void SetPosterWidth(enum ePosterSizeModes mode, double width)
	{
		SetPosterDimension(mode, width, true);
	}

	void SetPosterHeight(enum ePosterSizeModes mode, double height)
	{
		SetPosterDimension(mode, height, false);
	}

	double GetPosterDimension(enum ePosterSizeModes mode, bool width)
	{
		double posterDimension = (width==m_posterDimensionIsWidth)?m_posterDimension:CalculateOtherPosterDimension();
		
		posterDimension = MAX
		(
			(mode == ePosterSizeModeAbsolute)?0.001
			:(mode == ePosterSizeModePages)?0.001
			:0.001
			, posterDimension
		);

		if (m_posterSizeMode != mode) // anything to convert?
		{
			// These are needed for conversion from and to ePosterSizeModePercentual
			double inputImageDimension = width?GetInputImageWidth():GetInputImageHeight();
			inputImageDimension = ConvertBetweenDistanceUnits(inputImageDimension, m_distanceUnit, eDistanceUnitCentimeter);

			// First convert to absolute size mode (cm)
			if (m_posterSizeMode == ePosterSizeModePages)
			{
				posterDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(posterDimension, true, width);
			}
			else if (m_posterSizeMode == ePosterSizeModePercentual)
			{
				posterDimension *= inputImageDimension;
				posterDimension /= 100.0;
			}

			// Then convert to the wanted size mode
			if (mode == ePosterSizeModePages)
			{
				posterDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(posterDimension, false, width);
			}
			else if (mode == ePosterSizeModePercentual)
			{
				posterDimension /= inputImageDimension;
				posterDimension *= 100.0;
			}
		}

		if (mode == ePosterSizeModeAbsolute)
			posterDimension = ConvertBetweenDistanceUnits(posterDimension, eDistanceUnitCentimeter, m_distanceUnit);

                return posterDimension;
	}

	double GetPosterWidth(enum ePosterSizeModes mode)
	{
		return GetPosterDimension(mode, true);
	}

	double GetPosterHeight(enum ePosterSizeModes mode)
	{
		return GetPosterDimension(mode, false);
	}

	enum ePosterSizeModes GetPosterSizeMode(void) {return m_posterSizeMode;}

	void SetPosterHorizontalAlignment(enum eHorizontalAlignments alignment) {m_posterHorizontalAlignment = alignment;}
	void SetPosterVerticalAlignment(enum eVerticalAlignments alignment) {m_posterVerticalAlignment = alignment;}
	enum eHorizontalAlignments GetPosterHorizontalAlignment(void) {return m_posterHorizontalAlignment;}
	enum eVerticalAlignments GetPosterVerticalAlignment(void) {return m_posterVerticalAlignment;}

	void GetPreviewSize(double imageWidth, double imageHeight, int boxWidth, int boxHeight, int &previewWidth, int &previewHeight, bool enlargeToFit)
	{
		double aspectRatio = imageWidth / imageHeight;

		if (enlargeToFit)
		{
			double widthFactor = imageWidth/(double)boxWidth;
			double heightFactor = imageHeight/(double)boxHeight;
			double factor = widthFactor<heightFactor?widthFactor:heightFactor;
			imageWidth /= factor;
			imageHeight /= factor;
		}

		previewWidth = MIN((int)imageWidth, boxWidth);
		previewHeight = (int)((double)previewWidth / aspectRatio);

                if (previewHeight > boxHeight)
		{
			previewWidth = (int)((double)boxHeight * aspectRatio);
			previewHeight = boxHeight;
		}
	}

	void GetInputImagePreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), boxWidth, boxHeight, previewWidth, previewHeight, false);
	}

	virtual void GetPaperPreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		GetPreviewSize(GetPaperWidth(), GetPaperHeight(), boxWidth, boxHeight, previewWidth, previewHeight, true);
	}
	
	void GetImage(PaintCanvasInterface *paintCanvas)
	{
		unsigned char *rgbData = NULL;
		int imageWidth;
		int imageHeight;
		
		m_imageIO->GetImageAsRGB(&rgbData, imageWidth, imageHeight);
		paintCanvas->SetImage(rgbData, imageWidth, imageHeight);
	}

	void PaintOnCanvas(PaintCanvasInterface *paintCanvas, void* options = 0)
	{
		int canvasWidth = 0, canvasHeight = 0;
		paintCanvas->GetSize(canvasWidth, canvasHeight);
		int boxWidth = 0, boxHeight = 0;
		int x_offset, y_offset;
		
		const char *state = (const char*)options;
		
		if (strcmp(state, "image") == 0)
		{
			if (IsImageLoaded())
			{
				GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), canvasWidth, canvasHeight, boxWidth, boxHeight, false);
				x_offset = (canvasWidth - boxWidth) / 2;
				y_offset = (canvasHeight - boxHeight) / 2;

				paintCanvas->DrawImage(0 + x_offset, 0 + y_offset, boxWidth, boxHeight);
			}
		}
		else if (strcmp(state, "paper") == 0 || strcmp(state, "overlapping") == 0)
		{
			double paperWidth = GetPaperWidth();
			double paperHeight = GetPaperHeight();
			GetPreviewSize(paperWidth, paperHeight, canvasWidth, canvasHeight, boxWidth, boxHeight, true);
			x_offset = (canvasWidth - boxWidth) / 2;
			y_offset = (canvasHeight - boxHeight) / 2;
			double distanceUnitToPixelfactor = (double)boxWidth/paperWidth;
			double borderTop = GetPaperBorderTop() * distanceUnitToPixelfactor;
			double borderRight = GetPaperBorderRight() * distanceUnitToPixelfactor;
			double borderBottom = GetPaperBorderBottom() * distanceUnitToPixelfactor;
			double borderLeft = GetPaperBorderLeft() * distanceUnitToPixelfactor;
			double printableAreaWidth = boxWidth - borderLeft - borderRight;
			double printableAreaHeight = boxHeight - borderTop - borderBottom;
			
			paintCanvas->DrawFilledRect(0 + x_offset, 0 + y_offset, boxWidth, boxHeight, 128, 128, 128);
			paintCanvas->DrawFilledRect(0 + borderLeft + x_offset, 0 + borderTop + y_offset, printableAreaWidth, printableAreaHeight, 230, 230, 230);

			if (strcmp(state, "overlapping") == 0)
			{
				int overlappingWidth = GetOverlappingWidth() * distanceUnitToPixelfactor;
				int overlappingHeight = GetOverlappingHeight() * distanceUnitToPixelfactor;
				enum eOverlappingPositions overlappingPosition = GetOverlappingPosition();
				double overlappingTop =
					(overlappingPosition == eOverlappingPositionTopLeft || overlappingPosition == eOverlappingPositionTopRight)?
					borderTop
					:boxHeight - borderBottom - overlappingHeight;
				double overlappingLeft = 
					(overlappingPosition == eOverlappingPositionTopLeft || overlappingPosition == eOverlappingPositionBottomLeft)?
					borderLeft
					:boxWidth - borderRight - overlappingWidth;
				
				paintCanvas->DrawFilledRect(borderLeft + x_offset, overlappingTop + y_offset, printableAreaWidth, overlappingHeight, 255, 128, 128);
				paintCanvas->DrawFilledRect(overlappingLeft + x_offset, borderTop + y_offset, overlappingWidth, printableAreaHeight, 255, 128, 128);
			}
		}
		else if (strcmp(state, "poster") == 0)
		{
			double pagePrintableAreaWidth = GetPrintablePaperAreaWidth();
			double pagePrintableAreaHeight = GetPrintablePaperAreaHeight();
			int pagesHorizontal = (int)ceil(GetPosterWidth(ePosterSizeModePages));
			int pagesVertical = (int)ceil(GetPosterHeight(ePosterSizeModePages));
			double posterWidth = pagesHorizontal*pagePrintableAreaWidth - (pagesHorizontal-1)*GetOverlappingWidth() + GetPaperBorderLeft() + GetPaperBorderRight();
			double posterHeight = pagesVertical*pagePrintableAreaHeight - (pagesVertical-1)*GetOverlappingHeight() + GetPaperBorderTop() + GetPaperBorderBottom();
			GetPreviewSize(posterWidth, posterHeight, canvasWidth, canvasHeight, boxWidth, boxHeight, true);
			x_offset = (canvasWidth - boxWidth) / 2;
			y_offset = (canvasHeight - boxHeight) / 2;
			double distanceUnitToPixelfactor = (double)boxWidth/posterWidth;

			double borderTop = GetPaperBorderTop() * distanceUnitToPixelfactor;
			double borderRight = GetPaperBorderRight() * distanceUnitToPixelfactor;
			double borderBottom = GetPaperBorderBottom() * distanceUnitToPixelfactor;
			double borderLeft = GetPaperBorderLeft() * distanceUnitToPixelfactor;
			double posterPrintableAreaWidth = boxWidth - borderLeft - borderRight;
			double posterPrintableAreaHeight = boxHeight - borderTop - borderBottom;

			paintCanvas->DrawFilledRect(x_offset, y_offset, boxWidth, boxHeight, 128, 128, 128);
			paintCanvas->DrawFilledRect(borderLeft + x_offset, borderTop + y_offset, posterPrintableAreaWidth, posterPrintableAreaHeight, 230, 230, 230);

			double imageWidth = GetPosterWidth(ePosterSizeModeAbsolute) * distanceUnitToPixelfactor;
			double imageHeight = GetPosterHeight(ePosterSizeModeAbsolute) * distanceUnitToPixelfactor;

			enum eVerticalAlignments verticalAlignment = GetPosterVerticalAlignment();
			enum eHorizontalAlignments horizontalAlignment = GetPosterHorizontalAlignment();

			paintCanvas->DrawImage
			(
				(
					horizontalAlignment == eHorizontalAlignmentLeft?borderLeft
					:horizontalAlignment == eHorizontalAlignmentCenter?
						MINMAX((boxWidth - imageWidth) / 2, borderLeft, (int)borderLeft + (int)posterPrintableAreaWidth - (int)imageWidth)
					:((int)borderLeft + (int)posterPrintableAreaWidth - (int)imageWidth)
				)
				+ x_offset,

				(
					verticalAlignment == eVerticalAlignmentTop?borderTop
					:verticalAlignment == eVerticalAlignmentMiddle?
						MINMAX((boxHeight - imageHeight) / 2, borderTop, (int)borderTop + (int)posterPrintableAreaHeight - (int)imageHeight)
					:((int)borderTop + (int)posterPrintableAreaHeight - (int)imageHeight)
					)
				+ y_offset,
				imageWidth, imageHeight
			);

			double overlappingHeight = GetOverlappingHeight() * distanceUnitToPixelfactor;
			double overlappingWidth = GetOverlappingWidth() * distanceUnitToPixelfactor;
			pagePrintableAreaWidth *= distanceUnitToPixelfactor;
			pagePrintableAreaHeight *= distanceUnitToPixelfactor;
			enum eOverlappingPositions overlappingPosition = GetOverlappingPosition();

			double lineYPosition = borderTop;
			for (int pagesRow = 0; pagesRow < pagesVertical - 1; pagesRow++)
			{
				lineYPosition += pagePrintableAreaHeight;
				if (
					(
						pagesRow < (pagesVertical - 1)
						&& (overlappingPosition == eOverlappingPositionBottomLeft
						|| overlappingPosition == eOverlappingPositionBottomRight)
					)
					||
					(
						pagesRow > 0 
						&& (overlappingPosition == eOverlappingPositionTopRight
						|| overlappingPosition == eOverlappingPositionTopLeft)
					))
				{
					lineYPosition -= overlappingHeight;
				}
				paintCanvas->DrawLine(x_offset, lineYPosition + y_offset, boxWidth - 1 + x_offset, lineYPosition + y_offset, 255, 128, 128);
			}

			double lineXPosition = borderLeft;
			for (int pagesColumn = 0; pagesColumn < pagesHorizontal - 1; pagesColumn++)
			{
				lineXPosition += pagePrintableAreaWidth;
				if (
					(
						pagesColumn < (pagesHorizontal - 1)
						&& (overlappingPosition == eOverlappingPositionTopRight
						|| overlappingPosition == eOverlappingPositionBottomRight)
					)
					||
					(
						pagesColumn > 0 
						&& (overlappingPosition == eOverlappingPositionTopLeft
						|| overlappingPosition == eOverlappingPositionBottomLeft)
					))
				{
					lineXPosition -= overlappingWidth;
				}
				paintCanvas->DrawLine(lineXPosition + x_offset, y_offset, lineXPosition + x_offset, boxHeight - 1 + y_offset, 255, 128, 128);
			}
		}
	}
};

PosteRazor* PosteRazor::CreatePosteRazor()
{
	return (PosteRazor*)new PosteRazorImplementation();
}