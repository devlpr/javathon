PYTHON_VERSION = 2.7
JDK = /opt/jdk1.8.0_144


all: jcompile generate compile


compile:
	g++ --shared \
	    -g3 -DDEBUG -std=c++0x -fPIC \
	    -L/usr/lib \
      -I${JDK}/include/ \
      -I${JDK}/include/linux \
      -I/usr/include/python2.7 \
      Javathon.cpp \
      -lpython$(PYTHON_VERSION) \
      -o libJavathonImp.so


jcompile:
	javac Javathon.java Main.java


generate:
	javah Javathon


run: all
	# Set LD_LIBRARY_PATH and java.library.path
	# Make sure to set your PYTHONPATH to the directory of your python script.
	java -Djava.library.path=./ Main


clean:
	rm libJavathonImp.so
	rm Javathon.class Main.class

