rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
gxx = gcc

############# SETTINGS ############
bin-dir = bin
src-dir = src
inc-dir = include
output = bin/libsensible
flags = -O9
###################################

sources = $(call rwildcard,$(src-dir),*.c)
binaries = $(patsubst $(src-dir)/%.c,$(bin-dir)/%.o,$(sources))

ifeq ($(sources), )
$(error No innput files)
endif

build: clear $(output).so
build-win: clear-win $(output).dll

debug-build: flags=-g
debug-build-win: flags=-g
debug-build: build
debug-build-win: build-win

clear:
	rm -R -f $(bin-dir)
	mkdir -p $(bin-dir)
clear-win:
	if exist "$(bin-dir)" rmdir /s/q "$(bin-dir)"
	if not exist "$(bin-dir)" mkdir "$(bin-dir)"

bin/%.o: src/%.c
	$(gxx) -Wall -Wno-main -Wno-trigraphs -fpic -c $(flags) $^ -o $@ "-I$(inc-dir)"

$(output): $(binaries)
	$(gxx) -shared $(flags) $(binaries) -o $@
$(output)%: $(binaries)
	$(gxx) -shared $(flags) $(binaries) -o $@