CC = g++
CXXFLAGS = -std=c++11 -Wall -Werror


SRC_UINT256 = $(wildcard uint256_t/*.cpp)
OBJ_UINT256 = $(patsubst %.cpp, %.o, $(wildcard $(SRC_UINT256)))

SRC_CXX = $(wildcard src/*.cpp)
OBJ_SRC = $(patsubst %.cpp, %.o, $(wildcard $(SRC_CXX)))


app.out: $(OBJ_UINT256) $(OBJ_SRC) 
	$(CC) -o $@ $^ -lcrypto

$(OBJ_SRC):		CXXFLAGS += -lcrypto
$(OBJ_UINT256): CXXFLAGS += -fPIC


split: app.out
	./$^ split


recover: app.out
	./$^ recover


clean:
	$(RM) -rf *.out src/*.o uint256_t/*.o
