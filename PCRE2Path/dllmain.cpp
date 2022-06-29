#include "stdafx.h"

#include "dllmain.h"

//==========================================================================

BOOL APIENTRY DllMain
(
    HMODULE hModule,
    DWORD   dwReason,
    LPVOID  lpReserved
)
{
    hInstance = hModule;
/** /
    switch( dwReason )
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:  break;
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH: break;
    }
/**/
    return TRUE;
}

//==========================================================================

HMODULE hInstance = {};
CHAR DataPath[MAX_PATH + sizeof(DataFile)] {0};

LPSTR pattern = (LPSTR) default_pattern;

pcre2_code_8 *code = NULL;
INT errcode = 0;
PCRE2_SIZE erroffs = 0;

//==========================================================================

// fw decl
void plugin_path ();
void plugin_load ();
void plugin_data ();

//==========================================================================

VOID PluginInit()
{
    if ( code ) PluginDone();

    plugin_load();

    code = pcre2_compile_8
    (
        (PCRE2_SPTR8) pattern,
        lstrlenA ( pattern ),
        PCRE2_UCP | PCRE2_UTF /** / | PCRE2_MATCH_INVALID_UTF /**/,
        &errcode,
        &erroffs,
        NULL
    );
/** /
    pcre2_jit_compile_8
    (
        code,
        PCRE2_JIT_COMPLETE |
        PCRE2_JIT_PARTIAL_HARD |
        PCRE2_JIT_PARTIAL_SOFT
    );
/**/
}

//  free mem + cleanup
VOID PluginDone ()
{
    if( !code ) return;

    // pcre2_jit_stack_free_8 ( NULL );
    pcre2_code_free_8 ( code );
    code = NULL;
}

//==========================================================================

void plugin_path ()
{
    if( strlen ( DataPath ) == 0 )
        GetModuleFileNameA ( hInstance, DataPath, MAX_PATH );

    lstrcpyA ( strrchr ( DataPath, '\\' ) + 1, DataFile );
};

void plugin_load ()
{
    plugin_path (); // get default setttings file path
    plugin_data (); // create settings if not exists

    // load settings
    HANDLE file = CreateFileA
    (
        DataPath,       FILE_GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING,  FILE_ATTRIBUTE_NORMAL, NULL
    );

    if( file != INVALID_HANDLE_VALUE )
    {
        DWORD fileSize = GetFileSize ( file, NULL );
        CHAR* fileBuf = new CHAR[fileSize];

        if( ReadFile ( file, fileBuf, fileSize, NULL, NULL ) )
        {
            if ( pattern != default_pattern )
                delete[] pattern;

            pattern = fileBuf;
        }

        CloseHandle ( file );
    }
};

void plugin_data ()
{
    // write default rules to new file, if none exist
    HANDLE file = CreateFileA
    (
        DataPath,       FILE_GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
        CREATE_NEW,     FILE_ATTRIBUTE_NORMAL, NULL
    );

    if( file != INVALID_HANDLE_VALUE )
    {
        WriteFile ( file, pattern, lstrlenA ( pattern ), NULL, NULL );
        CloseHandle ( file );
    }
}

//==========================================================================