CXXFLAGS = -I./include -O2 -g -Wall -fmessage-length=0 -pg -DDEBUG_ALGO

TARGET = chp

LIBS = -L./lib -lgtest -lboost_filesystem -lboost_system

APP_SRC = src/Engine.cpp src/StlFileLoader.cpp src/Set.cpp src/ConstantString.cpp src/Problem.cpp 

TEST_SRC = test/

chp : 	$(APP_SRC)
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(APP_SRC) $(LIBS)

#$(TARGET): 	../test/Engine.cpp
#	$(CXX) -o $(TARGET) $(CXXFLAGS) ../test/Test.cpp $(LIBS)


all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
