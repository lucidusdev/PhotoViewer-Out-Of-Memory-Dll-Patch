CFLAGS = -lshlwapi -nostartfiles -lmsvcrt -s

ifeq ($(MSYSTEM), MINGW64)
	arch = x64
	CFLAGS += --entry=DllMain
else
	arch = x86
	CFLAGS += --entry=_DllMain@12
endif

dllname = mscms

all:
	mkdir -p $(arch)
	gcc -shared -o $(arch)/$(dllname).dll $(dllname).c $(dllname).def $(CFLAGS)

clean:
	rm x64/* x86/* 

