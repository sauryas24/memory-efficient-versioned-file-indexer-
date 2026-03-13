This is a program for a memory efficient file indexer. It takes a user defined buffer size and processes a file in chunks of those buffers, due to which large files can be processed very efficiently. Three queries can be performed on the processed files, namely word, diff and top.

Requirements: <br>
1. For a Linux OS:<br>
	a. g++ compiler(version 9.0 or higher reccomended)<br>
	b. C++17 standard<br>
	c. Required libraries: STL and fstream<br>
2. For a Windows OS:<br>
	a. Compatible with MinGW-W64<br>
	b. g++ compiler(version 9.0 or higher reccomended)<br>
	c. C++17 standard<br>
	d. Required libraries: STL and fstream<br>

To use the program, first download the C++ file named 240950_saurya.cpp, navigate to the folder containing the file on your device's terminal.<br>
1. To compile the program use the following command:<br>
	g++ -O2 240950_saurya.cpp -o analyzer <br>
2. every command must  be one of the following formats:<br>
	a. To find the Word count of a particular word in a file:<br>
		./analyzer --file [file path] --version [version name] --buffer [buffer size] --query word --word [word]<br>
	b. To find the difference between the number of a word in two files:<br>
		./analyzer --file1 [file path 1] --version1 [version name 1] --file2 [file path 2] --version2 [version name 2] --buffer [buffer size] --query diff --word [word]<br>
	c. To find the Top K words sorted by frequency in a decreasing order:<br>
		./analyzer --file [file path] --version [version name] --buffer [buffer size] --query top --top [K]<br>
NOTE: If running in windows, change in the commands:<br>
	a. for compilation: g++ -O2 CS253.cpp -o analyzer.exe<br>
	b. for the queries: change ./analyser to analyzer.exe or .\analyzer.exe, rest remaining the same<br>
