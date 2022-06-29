//==========================================================================
// contentplugin.h: C++ish TC/WDX plugin API implementations
//==========================================================================
// (C) 2022 Raziel Anarki, based on the official WDX guide 2.12
//--------------------------------------------------------------------------

#include "stdafx.h"

#include "dllmain.h"
#include "strutils.h"

#include "contentplugin.h"

//==========================================================================

PUBLIC
VOID PLUGINAPI ContentGetDetectString
(
    LPSTR DetectString,
    UINT  MaxSize
)
{
    StringCchCopyA(DetectString, MaxSize, ""); // return dummpy empty string
}

PUBLIC
VOID PLUGINAPI ContentSetDefaultParams
(
    LPCONTENTDEFAULTPARAMS Params
)
{
    if( Params->DefaultParamsSize >= sizeof ( CONTENTDEFAULTPARAMS ) )
        StringCchCopyA ( DataPath, MAX_PATH, Params->DefaultIniName );

    PluginInit (); // init on load
}

PUBLIC
VOID PLUGINAPI ContentPluginUnloading ()
{
    PluginDone(); // unload
}

//==========================================================================

PUBLIC
VOID PLUGINAPI ContentSendStateInformation
(
    StateChange StateChange,
    LPSTR       CurrentPath
)
{
    PluginInit(); // refresh on reload
}

PUBLIC
VOID PLUGINAPI ContentSendStateInformationW
(
    StateChange ChangeState,
    LPWSTR      CurrentPathW
)
{
    PluginInit(); // refresh on reload
}

//==========================================================================

PUBLIC
FieldType PLUGINAPI ContentGetSupportedField
(
    UINT  FieldIndex,
    LPSTR FieldName,
    LPSTR FieldUnits,
    UINT  MaxSize
)
{
    UINT32 capture_count;
    pcre2_pattern_info_8 ( code, PCRE2_INFO_CAPTURECOUNT, &capture_count );

    StringCchCopyA ( FieldUnits, MaxSize, "" );

    if( capture_count < FieldIndex )
    {
        StringCchCopyA ( FieldName, MaxSize, "" );
        return FieldType::None;
    }

    AUTOSTR(group_id, 20);
    snprintf(group_id, 20, "$%d", FieldIndex);

    LPSTR group_name = group_id;

    UINT32 name_count, name_length;
    pcre2_pattern_info_8 (code, PCRE2_INFO_NAMECOUNT,     &name_count);
    pcre2_pattern_info_8 (code, PCRE2_INFO_NAMEENTRYSIZE, &name_length);

    PCRE2_SPTR8 name_table;
    pcre2_pattern_info_8 (code, PCRE2_INFO_NAMETABLE,     &name_table);

    PCRE2_SPTR8 name_entry = name_table;
    for( UINT32 i = 0; i < name_count; i++ )
    {
        INT capture_group_index = (name_entry[0] << 8) | name_entry[1];

        if (capture_group_index == FieldIndex)
        {
            group_name = (LPSTR)(name_entry + 2);
            break;
        }

        name_entry += name_length;
    }

    StringCchCopyA(FieldName, MaxSize, group_name);
    return FieldType::String;
}

//==========================================================================

PUBLIC
FieldType PLUGINAPI ContentGetValue
(
    LPSTR  FileName,
    UINT   FieldIndex,
    UINT   UnitIndex,
    LPVOID FieldData,
    UINT   MaxSize,
    UINT   Flags
)
{
    LPSTR const FieldValue = (LPSTR) FieldData;

    PCRE2_SIZE bufsize = MaxSize;

    pcre2_match_data_8* match_data = pcre2_match_data_create_from_pattern_8 ( code, NULL );
    nonstd::scope_exit ( [&] { pcre2_match_data_free_8 ( match_data ); } );

    INT match_result = pcre2_match_8
    (
        code,
        (PCRE2_SPTR8) FileName,
        PCRE2_ZERO_TERMINATED,
        0,
        PCRE2_NO_UTF_CHECK,
        match_data,
        NULL
    );

    if( match_result < 0 )
    {
        if( FieldIndex == 0 )
        {
            pcre2_get_error_message_8 ( match_result, (PCRE2_UCHAR8*) FieldValue, bufsize );
            return FieldType::Error;
        }

        StringCchCopyA ( FieldValue, MaxSize, "" );
        return FieldType::None;
    }

    if (pcre2_substring_length_bynumber_8 (match_data, FieldIndex, NULL) < 0)
        return FieldType::Empty;

    FieldValue[0] = 0;
    pcre2_substring_copy_bynumber_8 ( match_data, FieldIndex, (PCRE2_UCHAR8*) FieldValue, &bufsize );
    FieldValue[bufsize] = 0;

    return FieldType::String;
}

PUBLIC
VOID PLUGINAPI ContentStopGetValue
(
    LPSTR FileName
)
{
    return; // dummy
}

//==========================================================================

PUBLIC
FieldType PLUGINAPI ContentGetValueW
(
    LPWSTR FileNameW,
    UINT   FieldIndex,
    UINT   UnitIndex,
    LPVOID FieldData,
    UINT   MaxSize,
    UINT   Flags
)
{
    LPWSTR const FieldValueW = (LPWSTR) FieldData;

    AUTOSTR(FileName,   MaxSize);
    AUTOSTR(FieldValue, MaxSize);

    FieldType Result = ContentGetValue
    (
        Narrow ( FileNameW, MaxSize, FileName ),
        FieldIndex,
        UnitIndex,
        FieldValue,
        MaxSize,
        Flags
    );

    if (Result == FieldType::String)
    {
        Widen (FieldValue, MaxSize, FieldValueW);
        Result = FieldType::WString;
    }

    return Result;
}

PUBLIC
VOID PLUGINAPI ContentStopGetValueW
(
    LPWSTR FileNameW
)
{
    return; // dummy
}

//==========================================================================
