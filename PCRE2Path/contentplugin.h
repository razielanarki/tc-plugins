//==========================================================================
// contentplugin.h: C++ -ish TC/WDX plugin API interface
//==========================================================================
// (C) 2022 Raziel Anarki, based on the official WDX guide 2.12
//--------------------------------------------------------------------------

#pragma once

#include "contentplugin_types.h"

//==========================================================================

#ifdef DLL_EXPORTS
#define PUBLIC extern "C" __declspec(dllexport)
#else
#define PUBLIC extern "C" __declspec(dllimport)
#endif

#define PLUGINAPI __stdcall

//==========================================================================

PUBLIC
VOID PLUGINAPI ContentGetDetectString
(
    LPSTR DetectString,
    UINT  MaxSize
);

PUBLIC
VOID PLUGINAPI ContentSetDefaultParams
(
    LPCONTENTDEFAULTPARAMS Params
);

PUBLIC
VOID PLUGINAPI ContentSendStateInformation
(
    StateChange ChangeFlags,
    LPSTR       CurrentPath
);

PUBLIC
VOID PLUGINAPI ContentSendStateInformationW
(
    StateChange ChangeFlags,
    LPWSTR      CurrentPathW
);

PUBLIC
VOID PLUGINAPI ContentPluginUnloading();

//==========================================================================

PUBLIC
FieldType PLUGINAPI ContentGetSupportedField
(
    UINT  FieldIndex,
    LPSTR FieldName,
    LPSTR FieldUnits,
    UINT  MaxSize
);

PUBLIC
SortOrder PLUGINAPI ContentGetDefaultSortOrder
(
    UINT FieldIndex
);

PUBLIC
FieldType PLUGINAPI ContentGetValue
(
    LPSTR  FileName,
    UINT   FieldIndex,
    UINT   UnitIndex,
    LPVOID FieldData,
    UINT   MaxSize,
    UINT   Flags
);

PUBLIC
VOID PLUGINAPI ContentStopGetValue
(
    LPSTR FileName
);

PUBLIC
FieldType PLUGINAPI ContentGetValueW
(
    LPWSTR FileNameW,
    UINT   FieldIndex,
    UINT   UnitIndex,
    LPVOID FieldData,
    UINT   MaxSize,
    UINT   Flags
);

PUBLIC
VOID PLUGINAPI ContentStopGetValueW
(
    LPWSTR FileNameW
);

/** /
//==========================================================================
// TODO: API-s

INT ContentGetSupportedFieldFlags
(
    INT FieldIndex
);

INT ContentEditValue
(
    HWND ParentWin,
    INT FieldIndex,
    INT UnitIndex,
    INT FieldType,
    LPVOID FieldValue,
    INT MaxSize,
    INT Flags,
    LPSTR LangID
);

INT ContentGetSupportedOperators
(
    INT FieldIndex,
    LPSTR FieldOperators,
    INT MaxSize
);

//==========================================================================
// TODO: Unicode API-s

INT ContentSetValue
(
    LPTSTR FileName,
    INT FieldIndex,
    INT UnitIndex,
    INT FieldType,
    LPVOID FieldValue,
    INT Flags
);

INT ContentFindValue
(
    LPTSTR FileName,
    INT FieldIndex,
    INT UnitIndex,
    INT OperationIndex,
    INT FieldType,
    INT Flags,
    LPVOID FieldValue
);

INT ContentCompareFiles
(
    PROGRESSCALLBACKPROC ProgressCallback,
    UINT CompareIndex,
    LPSTR FileName1,
    LPSTR FileName2,
    LPFILEDETAILS FileDetails
);

/**/
//==========================================================================
