build:tema1.exe
	
tema1.exe:tema1.obj t1_f.obj t1.h
	link /out:tema1.exe tema1.obj t1_f.obj hash.lib 
tema1.obj:tema1.c
	cl /c tema1.c
	
t1_f.obj:t1_f.c
	cl /c t1_f.c

clean:
	del *.obj
