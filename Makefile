####### Compiler, tools and options

CC	=	g++
CFLAGS	=	-O3 -g -Wno-deprecated
INCPATH	=	
LINK	=	g++
LFLAGS	=	


####### Directories

OBJ = objs
SOURCE = source
HEADER = headers
DRIVERS = drivers
BIN = bin
LIB = libs

OBJECTS = $(OBJ)/Framework.o \
	       $(OBJ)/Z_Rewards.o \
	       $(OBJ)/random_sample.o \
	       $(OBJ)/Count_Rewards.o



#driver make programs

MAIN_OBJ = $(OBJ)/ghin.o
LIBS = $(LIB)/libcorelib.a


TARGET = $(BIN)/ghin

#targets


ghin: $(OBJECTS) $(MAIN_OBJ)
		$(LINK) -o $(TARGET) $(OBJECTS) $(MAIN_OBJ) $(LIBS)


#install and setup scripts
install:
		mkdir -p $(OBJ) 
		mkdir -p $(BIN)

clean:
		rm -rf $(OBJ)
		rm -rf $(BIN)
# main data structures and functionality



$(OBJ)/Framework.o: $(SOURCE)/Framework.cpp
		$(CC) $(CFLAGS) -c  $(SOURCE)/Framework.cpp -o $@
$(OBJ)/ghin.o: ghin.cpp
		$(CC) $(CFLAGS) -c ghin.cpp -o $@ $(LIBS)
$(OBJ)/Z_Rewards.o: $(SOURCE)/Z_Rewards.cpp
		$(CC) $(CFLAGS) -c $(SOURCE)/Z_Rewards.cpp -o $@
$(OBJ)/random_sample.o: $(SOURCE)/random_sample.cpp
		$(CC) $(CFLAGS) -c $(SOURCE)/random_sample.cpp -o $@
$(OBJ)/Count_Rewards.o: $(SOURCE)/Count_Rewards.cpp
		$(CC) $(CFLAGS) -c $(SOURCE)/Count_Rewards.cpp -o $@


