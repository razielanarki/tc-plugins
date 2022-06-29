//==========================================================================
// stdafx.g: precomiled headers
//==========================================================================
// (C) 2022 Raziel Anarki
//--------------------------------------------------------------------------

#pragma once

//==========================================================================

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <shlwapi.h>
#include <strsafe.h>

//==========================================================================

// link to static PCRE2 lib, cpmpiled /MD /MDd
#define PCRE2_STATIC 1

// we use pcre_*_8 internally as lax UTF(
#define PCRE2_CODE_UNIT_WIDTH 0

#include <pcre2.h>

//==========================================================================