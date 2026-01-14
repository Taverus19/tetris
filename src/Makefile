CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra -Wpedantic -g
CURSES := -lncurses

LIB := s21_tetris.a
COVFLAGS := --coverage
TEST_LDFLAGS := -lcheck -lm -lpthread -lsubunit

TEST_TARGET := main_test_tetris
TEST_SRC = $(wildcard test/*.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

BINDIR = ../bin

GAME = brickgame
GAME_VERSION = 1.0
GAME_CONSOLE = console

OBJ_GUI := out/display_tetris.o out/fronted.o
OBJ_TETRIS := out/tetris.o

OBJS := $(OBJ_GUI) $(OBJ_TETRIS)

MANUAL = tetris_manual
DOC_SRC = $(MANUAL).tex
DVI_TARGET = $(MANUAL).dvi
PDF_TARGET = $(MANUAL).pdf
LATEX = latex
PDFLATEX = pdflatex

.PHONY: all install uninstall dvi view-dvi view-pdf dist test memory check style clean

all: $(LIB) $(TEST_TARGET) $(GAME_CONSOLE) $(DVI_TARGET) $(PDF_TARGET) dist

$(LIB) : $(OBJS) 
	ar rcs $(LIB) $(OBJS)

$(TEST_TARGET): $(TEST_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(TEST_LDFLAGS)

$(GAME_CONSOLE): $(OBJS) $(LIB)
	mkdir -p build_cli
	$(CC) $(CFLAGS) -o $@ $^ $(CURSES)
	mv console ./build_cli

$(DVI_TARGET): $(DOC_SRC)
	$(LATEX) $(DOC_SRC)
	$(LATEX) $(DOC_SRC)

$(PDF_TARGET): $(DOC_SRC)
	$(PDFLATEX) $(DOC_SRC)
	$(PDFLATEX) $(DOC_SRC)

install: clean $(GAME_CONSOLE)
	mkdir $(BINDIR)
	cp build_cli/$(GAME_CONSOLE) $(BINDIR)
	cp -r brick_game $(BINDIR)
	cp -r gui $(BINDIR)
	cp -r test $(BINDIR)
	cp Makefile $(BINDIR)
	
uninstall:
	rm -rf $(BINDIR)

dvi: $(DVI_TARGET) $(PDF_TARGET)

view-dvi: $(DVI_TARGET)
	xdvi $(DVI_TARGET) &

view-pdf: $(PDF_TARGET)
	evince $(PDF_TARGET) &

dist:
	mkdir $(GAME)-$(GAME_VERSION)
	cp -r brick_game gui Makefile $(GAME)-$(GAME_VERSION)
	tar -czf $(GAME)-$(GAME_VERSION).tar.gz $(GAME)-$(GAME_VERSION)
	rm -rf $(GAME)-$(GAME_VERSION)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean
	$(MAKE) CFLAGS="$(CFLAGS) $(COVFLAGS)" $(TEST_TARGET)
	./$(TEST_TARGET)
	gcovr -r . \
			--filter="brick_game/tetris/.*" \
			--exclude="test/" \
			--exclude="gui/.*" \
			--html --html-details -o coverage.html
	gcovr -r . --filter="brick_game/tetris/.*" --exclude="test/.*" --exclude="gui/.*"
	
out/%.o: gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

memory:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main_test_tetris

check:
	@echo "Running static analysis..."
	cppcheck --enable=all --std=c11 \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude \
	--suppress=checkersReport \
	brick_game/tetris/ gui/cli/

style:
	clang-format -style=Google -n brick_game/tetris/*.c brick_game/tetris/*.h
	clang-format -style=Google -i brick_game/tetris/*.c brick_game/tetris/*.h
	clang-format -style=Google -n gui/cli/*.c gui/cli/*.h
	clang-format -style=Google -i gui/cli/*.c gui/cli/*.h
	clang-format -style=Google -n test/*.c test/*.h 
	clang-format -style=Google -i test/*.c test/*.h 
clean:
	rm -rf $(OBJS)
	rm -rf $(LIB)
	rm -rf high_score_tetris.txt build_cli *.gz
	rm -rf $(TEST_TARGET) *.o *.gcno *.gcda *.gcov coverage*.css coverage.*html test/*.o test/*.gcno test/*.gcda test/*.gcov out/*.gcno out/*.gcda
	rm -f *.aux *.log *.toc *.out *.dvi *.pdf