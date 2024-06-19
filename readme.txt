/*****************************************************************************

TITLE: CLAIMS																														
AUTHOR:   DASARI SRIKAR [ 2201CS21 ]

** Declaration of Authorship **

This txt file, claims.txt, is part of the miniproject of CS209/CS210 at the 
department of Computer Science and Engg, IIT Patna . 

*****************************************************************************/

Files:
==========
*All the files I submitted, asm.cpp and emu.cpp and claims.txt, have my name and student id at the start, along with a declaration of authorship.

The evidence for Assembler including the output files from the 4 test examples has also been uploaded.

They are:
test0.asm:(3 output files: test0.asm, test0.o, test0.l)
test1.asm:(3 output files: test1.asm, test1.o, test1.l)
test2.asm:(3 output files: test2.asm, test2.o, test2.l)
test3.asm: (2 outputfiles: test3.asm, test3.log)

format:
file.o(pass 1 output)
file.l(pass 2 output)
file.log(error checking output)

explaining each test case in assembler:
file to be executed:asm.cpp
test0.asm->It is a correct test file which shows pass1 and pass 2 output and error file is ignored.
test1.asm->It is a correct test file which shows pass1 and pass 2 output and error file is ignored.
test2.asm->It is a correct test file which shows pass1 and pass 2 output and error file is ignored.
test3.asm->It contains 5 error and each one are printed in error file.

Similary to show the working of emulator I submitted
(emu.cpp,bubblesort.txt,sumofnnumbers.cpp)
the output format will be memory dump.

All the test files have been tested and work properly. 

Each of the object files that have been produced are also inputted into the emulator to create the dump files.

explaining each test case in emulator
file to be executed:emu.cpp
bubblesort.txt->It is a n input bubble sort algorithm.In the code it is assumed that n is to be 4 by default for working sample example and 
mem[0]=first input
mem[1]=second input
mem[2]=third input
mem[3]=fourth input
mem[4]=n-1=3
outout comes in sorted order in mem[0-3] positions.
sumofnnumbers.txt->It gives sum of first n numbers starting from zero.
mem[0]=input=n
mem[1]=output

*Two programs are compilable with :
g++ emu.cpp -o emuexe 

as they are written in cpp.

