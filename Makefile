CXXFLAGS = -I./include -O2 -g -Wall -fmessage-length=0 -pg -DDEBUG_ALGO
LIBFLAGS = -L./lib -lgtest -lboost_filesystem -lboost_system

TARGET = chp


APP_SRC = src/Engine.cpp src/StlFileLoader.cpp src/Set.cpp src/ConstantString.cpp src/Problem.cpp 

TEST_SRC = test/

chp : 	$(APP_SRC)
	@echo "\nCompiling Software\n"
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(APP_SRC) $(LIBFLAGS)
	@echo "\nDone.\n\nUsage: ./chp [folder_path] [file_path] \n"

test: 	test/Engine.cpp test/Test.cpp 
	$(CXX) -o $(TARGET) $(CXXFLAGS) ../test/Test.cpp $(LIBFLAGS)


all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
