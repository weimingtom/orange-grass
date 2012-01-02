ZLIBPATH := engine/src/zlib

LOCAL_SRC_FILES +=  $(ZLIBPATH)/adler32.c \
                    $(ZLIBPATH)/compress.c \
                    $(ZLIBPATH)/crc32.c \
                    $(ZLIBPATH)/deflate.c \
                    $(ZLIBPATH)/gzio.c \
                    $(ZLIBPATH)/infback.c \
                    $(ZLIBPATH)/inffast.c \
                    $(ZLIBPATH)/inflate.c \
                    $(ZLIBPATH)/inftrees.c \
                    $(ZLIBPATH)/trees.c \
                    $(ZLIBPATH)/uncompr.c \
                    $(ZLIBPATH)/zutil.c
