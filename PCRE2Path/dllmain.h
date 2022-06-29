#pragma once

//==========================================================================

constexpr CHAR DataFile[] = "pcre2path.pat";
constexpr LPCSTR default_pattern = R"((?xU)
^
(?:
    (?<Path>.*?)
    \\
)
(?:
    (?P<AlbumArtist>.*)
    \s+\-\s+
    (?P<AlbumTitle>.*)
    \s+\-\s+
)
(?:
    (?P<CatId>1605|H880|47|0055|753|SINDEX|TC|\d\d\d|[A-Z0-9]*?[A-Z]+?)
    (?P<CatNo>[0-9.]+?[A-Z.0-9]*|DL)
)
(?:
    \s+\+\s+
    (?P<Extra>.*)
)?
$)";

//==========================================================================

extern HMODULE hInstance;
extern CHAR DataPath[];

extern pcre2_code_8 *code;

extern INT errcode;
extern PCRE2_SIZE erroffs;

//==========================================================================

VOID PluginInit ();
VOID PluginDone ();

//==========================================================================