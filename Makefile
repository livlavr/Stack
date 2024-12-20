CXX          = gcc-14

SRC          = main.cpp stack.cpp recalloc.cpp stack_dump.cpp stack_public.cpp stack_security.cpp ../../Color-printf/color_printf.cpp

BUILD_DIR    = ./build/
SRC_DIR      = ./src/
CFLAGS       = -I inc

TARGET       = stack.out
OBJECT       = $(patsubst %.cpp, %.o, $(SRC))
BUILD_OBJ    = $(addprefix $(BUILD_DIR), $(OBJECT))

GREEN_COLOR   = \033[1;32m
YELLOW_COLOR  = \033[1;33m
DEFAULT_TEXT = \033[0m

DED_FLAGS    = -D _DEBUG -ggdb2 -std=c++17 -O0 -Wall -Wextra -Weffc++                                     \
			    -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations                     \
				-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported                      \
				-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral           \
				-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor \
				-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls \
				-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2        \
				-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types                \
				-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef                     \
				-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros                              \
				-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing                        \
				-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation       \
				-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer        \
				-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla

vpath %.o   $(BUILD_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.h   $(INC_DIR)

.PHONY: clean all
all   : $(TARGET)

$(TARGET) :  $(BUILD_DIR) $(OBJECT)
	$(CXX)   $(BUILD_OBJ) -o $(TARGET) -D _NDEBUG
	@printf "$(GREEN_COLOR)$(TARGET) COMPILED$(DEFAULT_TEXT)\n"

$(BUILD_DIR) :
	mkdir -p build

$(OBJECT) : %.o : %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $(addprefix $(BUILD_DIR), $@)

ded : $(addprefix $(SRC_DIR), $(SRC))
	$(CXX) $(CFLAGS) $^ -o $(TARGET) $(DED_FLAGS)
	@printf "$(YELLOW_COLOR)SKOLKO MOJNO BOJE MOY BLYAT'$(DEFAULT_TEXT)\n"

flash:
	clear
	make clean
	make ded
	./$(TARGET)

doxy :
	doxygen

clean :
	@rm -f -r $(addprefix $(BUILD_DIR), *.o) $(TARGET) *.dSYM dump.txt
	@printf  "$(YELLOW_COLOR)$(TARGET) CLEANED$(DEFAULT_TEXT)\n"
