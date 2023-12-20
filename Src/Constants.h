#ifndef SYM_RESOURCES
#define SYM_RESOURCES

#include <stdlib.h>

static const char*  kBackgroundImgFile        = "Resources/SimpleButton.png";
static const char*  kBackgroundPressedImgFile = "Resources/SimpleButtonPressed.png";
static const char*  kCloseImgFile             = "Resources/Close.png";
static const char*  kClosePressedImgFile      = "Resources/ClosePressed.png";
static const char*  kBrushImgFile             = "Resources/Brush.png";
static const char*  kBrushPressedImgFile      = "Resources/BrushPressed.png";
static const char*  kFontFile                 = "Resources/Font.ttf";
static const char*  kCircleImgFile            = "Resources/Circle.png";
static const char*  kCirclePressedImgFile     = "Resources/CirclePressed.png";
static const char*  kRectImgFile              = "Resources/Rect.png";
static const char*  kRectPressedImgFile       = "Resources/RectPressed.png";
static const char*  kLineImgFile              = "Resources/Line.png";
static const char*  kLinePressedImgFile       = "Resources/LinePressed.png";
static const char*  kPolylineImgFile          = "Resources/Polyline.png";
static const char*  kPolylinePressedImgFile   = "Resources/PolylinePressed.png";
static const char*  kSplineImgFile            = "Resources/Spline.png";
static const char*  kSplinePressedImgFile     = "Resources/SplinePressed.png";
static const char*  kFillImgFile              = "Resources/Fill.png";
static const char*  kFillPressedImgFile       = "Resources/FillPressed.png";
static const char*  kPluginNames[]            = {"Plugins/SymCurve.so",
                                                 "Plugins/WhiteBlack.so",
                                                 "Plugins/Ars.so",
                                                 "Plugins/VovaParam.so",
                                                 "Plugins/Ilia.so",
                                                 "Plugins/Ilia_tool.so",
                                                 "Plugins/Vova_tool.so",
                                                 "Plugins/Brush.so"};

const double kDeltaTime      = 0.25;
const char   kWindowHeader[] = "Photoshop";
const int    kMaxTextLength  = 50;
const double kLetterWidth    = 0.57;
const double kLetterHeight   = 1.5;
const double kPrecision      = 1e-7;

const plugin::Color kButtonColor = plugin::Color(199, 181, 173);

#endif //SYM_RESOURCES