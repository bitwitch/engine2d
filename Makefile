#Compiler and Linker
CC          := clang++

#The Target Binary Program
TARGET      := demo

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := source
INCDIR      := include
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := data
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#ImGui
IMGUI_DIR := imgui
IMGUI_SOURCES := $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
IMGUI_BACKEND_SOURCES := $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
IMGUI_OBJECTS := $(patsubst $(IMGUI_DIR)/%,$(BUILDDIR)/%,$(IMGUI_SOURCES:.$(SRCEXT)=.$(OBJEXT)))
IMGUI_OBJECTS += $(patsubst $(IMGUI_DIR)/backends/%,$(BUILDDIR)/%,$(IMGUI_BACKEND_SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Flags, Libraries and Includes
CFLAGS      := -g -Wall -std=c++11
LIB         := -lglfw3 -framework Cocoa -framework IOKit -framework CoreVideo
INC         := -I$(INCDIR) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I/usr/local/include
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT))) $(BUILDDIR)/glad.o $(IMGUI_OBJECTS)

#Defauilt Make
all: resources $(TARGET)
all: directories $(TARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
	@cp -r $(RESDIR) $(TARGETDIR)/

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Compile ImGui
$(BUILDDIR)/%.$(OBJEXT): $(IMGUI_DIR)/%.cpp
	$(CC) $(CFLAGS) -DIMGUI_IMPL_OPENGL_LOADER_GLAD $(INC) -c -o $@ $<

$(BUILDDIR)/%.$(OBJEXT): $(IMGUI_DIR)/backends/%.cpp
	$(CC) $(CFLAGS) -DIMGUI_IMPL_OPENGL_LOADER_GLAD $(INC) -c -o $@ $<

#Compile glad
$(BUILDDIR)/glad.o:
	clang -Iinclude -c $(SRCDIR)/glad.c -o $@ $<

#Non-File Targets
.PHONY: all remake clean cleaner resources
