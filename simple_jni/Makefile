

all:
	g++ --shared \
        -I/opt/jdk1.6.0_34/include/ \
        -I/opt/jdk1.6.0_34/include/linux \
        HelloWorld.cpp \
        -o libHelloWorldImp.so

run:
	java -Djava.library.path=./ Main

