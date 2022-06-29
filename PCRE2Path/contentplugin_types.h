//==========================================================================
// contentplugin_types.h: C++ -ish TC/WDX plugin API types
//==========================================================================
// (C) 2022 Raziel Anarki, based on the official WDX guide 2.12
//--------------------------------------------------------------------------

#pragma once

//==========================================================================

// ContentDefaultParamStruct
typedef struct tagCONTENTDEFAULTPARAMS
{
    WORD  DefaultParamsSize;        // = sizeof(WORD) + (2 * sizeof(DWORD)) + MAX_PATH)
    DWORD InterfaceVersionMajor;    // = 2
    DWORD InterfaceVersionMinor;    // = 12
    CHAR  DefaultIniName[MAX_PATH];
} CONTENTDEFAULTPARAMS, *LPCONTENTDEFAULTPARAMS;

//==========================================================================

// ContentSendStateInformation
enum StateChange:UINT
{
    FolderLoad = 0x01,  // contst_readnewdir
    Refresh    = 0x02,  // contst_refreshpressed
    ShowHint   = 0x04,  // contst_showhint
};

//==========================================================================

// tdateformat, pdateformat
typedef struct tagDATEFORMAT
{
    WORD Year;
    WORD Month;
    WORD Day;
} DATEFORMAT, *LPDATEFORMAT;

// ttimeformat, ptimeformat
typedef struct tagTIMEFORMAT
{
    WORD Hour;
    WORD Minute;
    WORD Second;
} TIMEFORMAT, *LPTIMEFORMAT;

//==========================================================================

#define FILESIZE ULARGE_INTEGER

// FileDetailsStruct
typedef struct tagCOMPAREFILEDETAILS
{
    FILESIZE FileA_Size;
    FILESIZE FileB_Size;
    FILETIME FileA_Time;
    FILETIME FileB_Time;
    DWORD    FileA_Attr;
    DWORD    FileB_Attr;
} COMPAREFILEDETAILS, *LPCOMPAREFILEDETAILS;

//==========================================================================


enum class ProgressInfo:BOOL
{
    OK = FALSE,
    Abort
};

typedef ProgressInfo (APIENTRY *PROGRESSUPDATEPROC)(UINT ComparedBytes);

//==========================================================================

enum class FieldType:INT
{
    NotFound    = -8, // ft_notfound        // ContentFindValue : value NOT found
//  Delayed     = -7, // ?
    Aborted     = -6, // ft_setcancel       // User canceled in Field Editor
    NotImpl     = -5, // ft_notsupported    // Function not supported
    OnDemand    = -4, // ft_ondemand        // Field only loads if user oresses SPACE
    Empty       = -3, // ft_fieldempty      // Valid, but empty
    Error       = -2, // ft_fileerror       // I/O error
    NotDefined  = -1, // ft_nosuchfield     // invalid field index

    Delayed     =  0, // ft_delayed         // field takes long time to retrieve -> poll in brackground
    Last        =  0, // ft_nomorefields
    None        =  0, // ft_nomorefields
    Success     =  0, // ft_setsuccess      // set attr succeeded

    Found       =  1, // ft_found           // ContentFindValue = value found
    Int32       =  1, // ft_numeric_32
    Int64       =  2, // ft_numeric_64
    Float       =  3, // ft_nueric_floating
    Date        =  4, // ft_date
    Time        =  5, // ft_time
    Bool        =  6, // ft_boolean
    Choice      =  7, // ft_multiplechoice
    String      =  8, // ft_string
    Text        =  9, // ft_fulltext
    DateTime    = 10, // ft_dateime
    WString     = 11, // ft_stringw
    WText       = 12, // ft_fulltextw

    Comparable = 100, // ft_comparecontent
};

enum class ContentFlags:UINT
{
    Edit          = 0b00000001, // contflags_edit

    SubstSize     = 0b00000010, // contflags_substsize

    SubstDateTime = 0b00000100, // contflags_substdatetime
    SubstDate     = 0b00000110, // contflags_substdate
    SubstTime     = 0b00001000, // contflags_substtime

    SubstAttrs    = 0b00001010, // contflags_substattributes
    SubstAttrStr  = 0b00001100, // contflags_substattributestr

    SubstMask     = 0b00001110, // contflags_substmask
    PassFloaT     = 0b00001110, // contflags_passthrough_size_float

    FieldEdit     = 0b00010000, // contflags_fieldedit
    FieldFind     = 0b00100000, // contflags_fieldsearch
    FieldFindPage = 0b01000000, // contflags_fieldsearchpageonly
};

//
enum class SortOrder:INT
{
    Desc    = -1,   // Z..A, 9..0, SIZE:LARGE->SMALL, DATE/TIME:RECENT->OLD
    // Default =  0,// ?? ASC ??
    Asc     =  1    // DEFAULT:A..Z, 0..9
};

enum class CompareResult:INT // ContentCompareFiles return
{
    CantComp =   -3, // Plugin Cant Compare Files
    Aborted  =   -2, // Compare Aborted
    IOErrorr =   -1, // IO error in t least one side
    NotEq    =    0, // Not Eqiual
    Eq       =    1, // Equal, show = sign
    EqTxt    =    2, // Equal show  =TXT sign
    EqResIco =  100, // Equal shiw cusomt icon (RC ID)
};
