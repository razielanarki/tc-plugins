#pragma once

//==========================================================================

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <shlwapi.h>
#include <strsafe.h>
#include <limits>

//==========================================================================

#define PCRE2_STATIC 1
#define PCRE2_CODE_UNIT_WIDTH 0

#include <pcre2.h>

//==========================================================================

#include "nonstd/utility.h"
#include "nonstd/scope.h"

//==========================================================================