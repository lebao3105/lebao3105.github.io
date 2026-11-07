#pragma once

#define ENUM_CLASS_CAST(en, nm, ud) static_cast< ud > ( en :: nm )
#define FONT_SZ(tp)                 ENUM_CLASS_CAST(DefaultFontSizes, tp, int)
#define MARGIN_TYPE(tp)             ENUM_CLASS_CAST(DefaultMargins, tp, int)
#define LAST_BUILD_TIME             __TIMESTAMP__