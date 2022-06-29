# PCRE2Path.wdx64

A WDX x64 Unicode content plugin that splits the file name/path into fields based on matching _(named) capture groups_ of a regular expression using PCRE2

## Dependencies

- MSVC 2022
- vcpkg
- `vcpkg integrate install`
- `vcpkg install pcre2:x64-windows-static-md`

## Config / Setup

strores config in (the default plugin INI location):
`%APPDATA%\GHISLER\` **`pcre2path.pat`**
(if that fails: then in the same folder as the .wcx64)

The config (for now) is a text file containing
the regexp which parses the pathname.

### default/demo pattern:

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

which breaks up
`...Path\To\ArtistName - AlbumTitle - LBL01 + Misc`
format "tagged" file/folder naming into custom fields/colums:


```
[=pcre2path.$0]          => "...Path\To\ArtistName - AlbumTitle - LBL01 + Misc"
[=pcre2path.Path]        => "...Path\To"
[=pcre2path.AlbumArtist] => "ArtistName"
[=pcre2path.AlbumTitle]  => "AlbumTitle"
[=pcre2path.CatId]       => "LBL"
[=pcre2path.CatNo]       => "01"
[=pcre2path.Extra]       => "Misc"
```

(`$0` is the full match string, or the pcre error message)

# Notes

The plugin tries to reload+recompile the pattern whenever it can
(tc restart, tc custom column edit also seems to reload it, plus folder reload events), so you can refine the your on the go, but please be aware that _adding new capturing groups_ without restarting TC may shift the indexes of the current loaded set.
