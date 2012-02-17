SRC = UdpSocket.cpp

OBJ = $(SRC:.cpp=.o)

OUT = libUdpSocket.a

INCLUDES = -I. -IC:\WindRiver\vxworks-6.3\target\h\

CCFLAGS = -g

CCC = ccppc

LIBS = -lm

LDFLAGS = -g
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	$(CCC) $(INCLUDES) $(CCLFAGS) -c $< -o $@

$(OUT): $(OBJ)
	arppc rcs $(OUT) $(OBJ)

depend: dep

dep: