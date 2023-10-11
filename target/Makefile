# コンパイラ設定
CXX			= g++
CXXFLAGS	= -O3 -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers
LDFLAGS 	=
# 出力
OUTPUT		= Executable.out
# 対象ソース
SRCDIR		= ./sources
SRCDIRS		= $(shell find $(SRCDIR) -type d)
SOURCES		= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
# 中間ファイル
OBJDIR		= ./obj
OBJECTS		= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SOURCES))
DEPENDS		= $(OBJECTS:.o=.d)
# インクルードパス
INCLUDES	= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.h))
INCLUDE		= $(addprefix -I, $(sort $(dir $(INCLUDES))))

# コンパイル
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@-mkdir -p $(sort $(dir $(OBJECTS)))
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# リンク
$(OUTPUT): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# リビルド
all: clean $(OUTPUT)

# クリーン
clean:
	-rm -rf $(OBJDIR) $(OUTPUT)

-include $(DEPENDS)

# ------------------
# 単体テスト
# ------------------
# 出力
UT_DIR			= ./unittest
UT_OUTPUT		= $(UT_DIR)/Unittest.out
# 対象ソース
UT_SRCDIR		= $(UT_DIR)/sources
UT_SRCDIRS		= $(shell find $(UT_SRCDIR) -type d)
UT_SOURCES		= $(foreach dir, $(UT_SRCDIRS), $(wildcard $(dir)/*.cpp))
# 中間ファイル
UT_OBJDIR		= $(UT_DIR)/obj
UT_OBJECTS		= $(patsubst $(UT_SRCDIR)%.cpp, $(UT_OBJDIR)%.o, $(UT_SOURCES))
UT_DEPENDS		= $(UT_OBJECTS:.o=.d)
# インクルードパス
UT_INCLUDES		= ./sources/wrapper ./unittest/iutest-1.17.1/include
UT_INCLUDE		= $(addprefix -I, $(sort $(UT_INCLUDES)))

# コンパイル
$(UT_OBJDIR)/%.o: $(UT_SRCDIR)/%.cpp
	@-mkdir -p $(sort $(dir $(UT_OBJECTS)))
	$(CXX) $(UT_INCLUDE) -o $@ -c $<

# リンク
$(UT_OUTPUT): $(UT_OBJECTS)
	$(CXX) -o $@ $^

# 単体テスト実行
unittest: ut_clean $(UT_OUTPUT) ut_exec

# クリーン
ut_clean:
	-rm -rf $(UT_OBJDIR) $(UT_OUTPUT)

# 実行
ut_exec:
	$(UT_OUTPUT)
