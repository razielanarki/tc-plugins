# PCRE2Path

A WDX x64 Unicode content plugin that splits the file paths intoconfigurable (named) capture groups using PCRE2

## Dependencies

- MSVC 2022
- vpcpkg
- `vcpkg integrate install`
- `vcpkg install pcre2:x64-windows-static-md`

## Config

strores config in (the default plugin INI location):
`%APPDATA%\GHISLER\` `pcre2path.pat`
(if that fails: then in the same folder as the .wcx64)

The config (for now) is a text file containing
the regexp which parses the pathname.

### default settings:

```pcre
(?xU)
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
$
```

parses '...Path\To\ArtistName - AlbumTitle - LBL01 + EXTRA' folders into sortable colums
($0 contains an error or the full matched string)

```
[=pcre2path.$0]
[=pcre2path.Path]
[=pcre2path.AlbumArtist]
[=pcre2path.AlbumTitle]
[=pcre2path.CatId]
[=pcre2path.CatNo]
[=pcre2path.Extra]
```
