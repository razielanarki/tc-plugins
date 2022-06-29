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

//==========================================================================

/** /
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

INT ContentSetValue
(
    LPTSTR FileName,
    INT FieldIndex,
    INT UnitIndex,
    INT FieldType,
    LPVOID FieldValue,
    INT Flags
);


INT TNAME(ContentFindValue)
(
    LPTSTR FileName,
    INT FieldIndex,
    INT UnitIndex,
    INT OperationIndex,
    INT FieldType,
    INT Flags,
    LPVOID FieldValue
);

INT TNAME(ContentCompareFiles)
(
    PROGRESSCALLBACKPROC ProgressCallback,
    INT CompareIndex,
    LPTSTR FileName1,
    LPTSTR FileName2,
    LPFILEDETAILS FileDetails
);
/**/
