

	# check if user is root
	user = $(shell whoami)
	ifeq ($(user),root)
	INSTALL_DIR = /usr/lib/lv2
	else 
	INSTALL_DIR = ~/.lv2
	endif


	# check LD version
	ifneq ($(shell xxd --version 2>&1 | head -n 1 | grep xxd),)
		USE_XXD = 1
	else ifneq ($(shell $(LD) --version 2>&1 | head -n 1 | grep LLD),)
		ifneq ($(shell uname -a | grep  x86_64), )
			LDEMULATION := elf_x86_64
		else ifneq ($(shell uname -a | grep amd64), )
			LDEMULATION := elf_x86_64
		else ifneq ($(shell uname -a | grep i386), )
			LDEMULATION := elf_i386
		endif
		USE_LDD = 1
	else ifneq ($(shell gold --version 2>&1 | head -n 1 | grep gold),)
		LD = gold
	endif


	NAME = PreAmps
	space := $(subst ,, )
	EXEC_NAME := $(subst $(space),_,$(NAME))
	BUNDLE = $(EXEC_NAME).lv2
	RESOURCES_DIR :=../resources/
	LIB_DIR := ../libxputty/libxputty/
	HEADER_DIR := $(LIB_DIR)include/
	UI_LIB:= $(LIB_DIR)libxputty.a
	STRIP ?= strip

	RESOURCES := $(wildcard $(RESOURCES_DIR)*.png)
	RESOURCES_OBJ := $(notdir $(patsubst %.png,%.o,$(RESOURCES)))
	RESOURCES_LIB := $(notdir $(patsubst %.png,%.a,$(RESOURCES)))
	RESOURCE_EXTLD := $(notdir $(patsubst %.png,%_png,$(RESOURCES)))
	RESOURCEHEADER := xresources.h
	GUI_LDFLAGS += -I$(HEADER_DIR) -Wl,-Bstatic -L. $(UI_LIB) \
	-Wl,-Bdynamic `pkg-config --cflags --libs cairo x11` 
	LDFLAGS += -I./DSP -fvisibility=hidden -shared -lm -fPIC \
	-Wl,-z,noexecstack -Wl,--no-undefined -Wl,--gc-sections
	CXXFLAGS += -fPIC -DPIC -O2 -Wall -funroll-loops \
	-fomit-frame-pointer -fstrength-reduce -fstack-protector -fvisibility=hidden \
	-fdata-sections -Wl,--gc-sections -Wl,--exclude-libs,ALL
	SLP_LDFLAGS += -I./DSP -fvisibility=hidden -Wl,-Bstatic `pkg-config --cflags --libs xputty` \
	-Wl,-Bdynamic `pkg-config --cflags --libs cairo x11 lilv-0` \
	-shared -lm -fPIC -Wl,-z,noexecstack -Wl,--no-undefined -Wl,--gc-sections
	CFLAGS := -O2 -D_FORTIFY_SOURCE=2 -Wall -fstack-protector -fvisibility=hidden \
	-fdata-sections -Wl,--gc-sections -Wl,-z,relro,-z,now -Wl,--exclude-libs,ALL
	FAUSTFLAGS := 

.PHONY : all mod install uninstall

.NOTPARALLEL:

all: $(RESOURCEHEADER) $(EXEC_NAME)

	@mkdir -p ./$(BUNDLE)
	@cp ./*.ttl ./$(BUNDLE)
	@cp ./*.so ./$(BUNDLE)
	@if [ -f ./$(BUNDLE)/$(EXEC_NAME).so ]; then echo "build finish, now run make install"; \
	else echo "sorry, build failed"; fi

mod : clean nogui
	@mkdir -p ./$(BUNDLE)
	@cp -R ./MOD/* ./$(BUNDLE)
	@mv ./*.so ./$(BUNDLE)
	@if [ -f ./$(BUNDLE)/$(EXEC_NAME).so ]; then echo $(BLUE)"build finish, now run make install"; \
	else echo $(RED)"sorry, build failed"; fi
	@echo $(NONE)

$(RESOURCEHEADER): $(RESOURCES_OBJ)
	rm -f $(RESOURCEHEADER)
	for f in $(RESOURCE_EXTLD); do \
		echo 'EXTLD('$${f}')' >> $(RESOURCEHEADER) ; \
	done

ifdef USE_XXD
$(RESOURCES_OBJ): $(RESOURCES)
	@#use this line to regenerate the *.c files from used images
	@#cd $(RESOURCES_DIR) && xxd -i $(patsubst %.o,%.png,$@) > $(patsubst %.o,%.c,$@)
	$(CC) -c $(RESOURCES_DIR)$(patsubst %.o,%.c,$@) -o $@
	$(AR) rcs $(patsubst %.o,%.a,$@) $@
else ifdef USE_LDD
$(RESOURCES_OBJ): $(RESOURCES)
	cd $(RESOURCES_DIR) && $(LD) -r -b binary -m $(LDEMULATION) -z noexecstack $(patsubst %.o,%.png,$@) -o ../$@
	$(AR) rcs $(patsubst %.o,%.a,$@) $@
	LDFLAGS += -DUSE_LD=1
else
$(RESOURCES_OBJ): $(RESOURCES)
	cd $(RESOURCES_DIR) && $(LD) -r -b binary -z noexecstack --strip-all $(patsubst %.o,%.png,$@) -o ../$@
	$(AR) rcs $(patsubst %.o,%.a,$@) $@
	LDFLAGS += -DUSE_LD=1
endif

$(EXEC_NAME):$(RESOURCES_OBJ)
	@# use this line when you include libxputty as submodule
	@$(CC)   $(CFLAGS) '$(NAME).c' -L. $(RESOURCES_LIB) $(UI_LIB) -o '$(EXEC_NAME)_ui.so' $(LDFLAGS) $(GUI_LDFLAGS) -I./
	$(CXX) $(CXXFLAGS) $(FAUSTFLAGS) $(EXEC_NAME).cpp $(LDFLAGS) -o $(EXEC_NAME).so
	@#$(CC)   $(CFLAGS) '$(NAME).c' -L. $(RESOURCES_LIB) -o '$(EXEC_NAME)_ui.so' $(SLP_LDFLAGS) -I./
	$(STRIP) -s -x -X -R .comment -R .note.ABI-tag $(EXEC_NAME).so
	$(STRIP) -s -x -X -R .comment -R .note.ABI-tag $(EXEC_NAME)_ui.so

nogui : clean
	$(CXX) $(CXXFLAGS) $(EXEC_NAME).cpp $(LDFLAGS) -o $(EXEC_NAME).so
	$(STRIP) -s -x -X -R .comment -R .note.ABI-tag $(EXEC_NAME).so

install :
ifneq ("$(wildcard ./$(BUNDLE))","")
	@mkdir -p $(DESTDIR)$(INSTALL_DIR)/$(BUNDLE)
	cp -r ./$(BUNDLE)/* $(DESTDIR)$(INSTALL_DIR)/$(BUNDLE)
	@echo ". ., done"
else
	@echo ". ., you must build first"
endif

uninstall :
	@rm -rf $(INSTALL_DIR)/$(BUNDLE)
	@echo ". ., done"

clean:
	rm -f *.a *.o *.so xresources.h
	@rm -rf ./$(BUNDLE)

