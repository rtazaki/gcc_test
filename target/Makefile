# コンパイラ設定
CXX			= g++
CXXFLAGS	= -O3 -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers
LDFLAGS 	=
# 出力
BINDIR		= ./bin
OUTPUT		= $(BINDIR)/Executable.out
# 対象ソース
SRCDIR		= ./src
SRCDIRS		= $(shell find $(SRCDIR) -type d)
SOURCES		= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
# 中間ファイル
OBJDIR		= ./obj
OBJECTS		= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SOURCES))
DEPENDS		= $(OBJECTS:.o=.d)
# インクルードパス
INCLUDES	= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.h))
INCLUDE		= $(addprefix -I, $(sort $(dir $(INCLUDES))))

# リンク
$(OUTPUT): $(OBJECTS)
	@-mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

# コンパイル
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(sort $(dir $(OBJECTS)))
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# リビルド
all: clean $(OUTPUT)

# フォルダごとクリア
clean:
	-rm -rf $(BINDIR) $(OBJDIR)
# 実行
exec:
	$(OUTPUT)

.PHONY: all clean exec

# Makefileデバッグ用
test1:
	@echo $(SOURCES)
test2:
	@echo $(OBJECTS)
test3:
	@echo $(INCLUDE)

-include $(DEPENDS)
