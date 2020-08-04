JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	Tarea3_ConHebra.java \
	Tarea3_SinHebra.java

default: classes

SH:Tarea3_SinHebra.java
	java Tarea3_SinHebra

CH:Tarea3_ConHebra.java
	java Tarea3_ConHebra

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class