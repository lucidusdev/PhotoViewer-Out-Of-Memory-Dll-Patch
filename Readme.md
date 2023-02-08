## Windows Photo Viewer "not enough memory" Patch



### About

This project is inspired by [PhotoViewerOutOfMemoryNoMore](https://github.com/PaaaulZ/PhotoViewerOutOfMemoryNoMore).

Directly modifying the `ImagingEngine.dll` works fine, however, while Windows wouldn't try to 
restore the DLL, `sfc /scannow` will report file corruption. So I make a simple in-memory patch to keep
the original `ImagingEngine.dll` intact with [dll hijacking](https://github.com/tothi/dll-hijack-by-proxying).



### How to use

Download the `mscms.dll` from release and put it in `C:\Program Files\Windows Photo Viewer` folder.



### Build from source

Run `make` under MingW.



### Tested

* Windows 10 21H2

* Windows 11 22H2

Should work for Windows 7 or later.

### Thanks

[PaaaulZ's original work](https://github.com/PaaaulZ/PhotoViewerOutOfMemoryNoMore)

[DLL Hijacking guide by tothi](https://github.com/tothi/dll-hijack-by-proxying)



