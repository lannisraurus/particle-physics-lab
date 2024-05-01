EIGEN_INC := $(shell pkg-config eigen3 --cflags)
ROOT_INC := -I$(shell root-config --cflags)
ROOT_LIBS := $(shell root-config --libs)

SRC := $(wildcard src/*.cpp)

C_FLAGS := -std=c++17

bin/%.exe: main/%.cpp $(SRC)
	echo "compiling $< --> $@"
	g++ $(C_FLAGS) $^ -o $@ -I src $(EIGEN_INC) $(ROOT_INC) $(ROOT_LIBS)

dump:
	@echo $(EIGEN_INC)
	@echo $(ROOT_INC)
	@echo $(ROOT_LIBS)
	@echo $(SRC)

clean:
	@rm -fv $(wildcard main/*~)
	@rm -fv $(wildcard src/*~)
	@rm -fv $(wildcard bin/*.exe)
	@rm -fv $(wildcard *~)

#comando: bin/nome_de_um_ficheiro.exe
# O "comando" é o que será colocado depois de "make" para ele executar o Makefile
# O "nome_de_um_ficheiro" é o nome do ficheiro onde tenho o código
# Se o comando "make" não estiver a funcionar, posso experimentar fazer o "make clean"