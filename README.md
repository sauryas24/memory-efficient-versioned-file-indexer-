This is a program for a memory efficient file indexer. It takes a user defined buffer size and processes a file in chunks of those buffers, due to which large files can be processed very efficiently. Three queries can be performed on the processed files, namely word, diff and top.

Requirements: 
1. For a Linux OS:
	a. g++ compiler(version 9.0 or higher reccomended)
	b. C++17 standard
	c. Required libraries: STL and fstream
2. For a Windows OS:
	a. Compatible with MinGW-W64
	b. g++ compiler(version 9.0 or higher reccomended)
	c. C++17 standard
	d. Required libraries: STL and fstream

To use the program, first download the C++ file named 240950_saurya.cpp, navigate to the folder containing the file on your device's terminal.
1. To compile the program use the following command:
	g++ -O2 240950_saurya.cpp -o analyzer 
2. every command must  be one of the following formats:
	a. To find the Word count of a particular word in a file:
		./analyzer --file [file path] --version [version name] --buffer [buffer size] --query word --word [word]
	b. To find the difference between the number of a word in two files:
		./analyzer --file1 [file path 1] --version1 [version name 1] --file2 [file path 2] --version2 [version name 2] --buffer [buffer size] --query diff --word [word]
	c. To find the Top K words sorted by frequency in a decreasing order:
		./analyzer --file [file path] --version [version name] --buffer [buffer size] --query top --top [K]
NOTE: If running in windows, change in the commands:
	a. for compilation: g++ -O2 CS253.cpp -o analyzer.exe
	b. for the queries: change ./analyser to analyzer.exe or .\analyzer.exe, rest remaining the same
