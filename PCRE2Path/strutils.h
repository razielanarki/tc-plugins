#pragma once

//==========================================================================

// tempb buffer deleted at end of the scope
#define AUTOSTR(_VAR_, _SIZE_) \
    LPSTR _VAR_ = new CHAR[_SIZE_] { 0 }; \
    nonstd::scope_exit ( [&_VAR_] { delete[] _VAR_; } );

//==========================================================================

// WCHAR -> CHAR
inline LPSTR Narrow ( LPWSTR In, UINT MaxSize, LPSTR Out )
{
    Out[0] = 0; // sanity check
    WideCharToMultiByte ( CP_UTF8, 0, In, -1, Out, MaxSize, NULL, NULL );
    Out[MaxSize] = 0; // sanity check

    return Out;
}

// CHAR -> WCHAR
inline LPWSTR Widen ( LPSTR In, UINT MaxSize, LPWSTR Out )
{
    const INT MaxWSize = MaxSize / sizeof ( WCHAR );

    Out[0] = 0; // sanity check
    MultiByteToWideChar ( CP_UTF8, 0, In, -1, Out, MaxWSize );
    Out[MaxWSize] = 0; // sanity check

    return Out;
}

//==========================================================================