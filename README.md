# Algorithms

> The codes containing the executable algorithms along with the driver function are available as 4 C++ files in the directory 'codes' attached alongside. (brute.cpp, kmp2.cpp, ModifiedBoyerMoore.cpp and main.cpp)

> To execute the program, you can run main.exe on the terminal, or individually as an application.

> if there are build errors, you can compile and build the main.cpp file by using the following command on the Windows terminal in the directory where the file main.cpp is present: 
>> g++ -o main main.cpp
> Make sure the search algorithm files (brute.cpp, kmp2.cpp, ModifiedBoyerMoore.cpp) are in the same directory as main.cpp

> Once the program begins execution, you will be displayed a menu, where you can upload a file, enter search patterns and also run the search algorithm of your choice.

>while entering the input file name, enter the full name along with the proper extension. if the file is in a different directory as main, enter the full path of the file.

> To serve as a delimiter while handling large files, you have a choice to limit number of sequences extracted from the file. Entering -1 will extract all sequences in the file. Appropriate instructions are given during the execution of the files

>> A few test genomes (.fna files) have been included in the codes directory as a sample reference.

******************************** A note on handling large files *********************************************

We have tested for handling the honey bee genome, which has a file size of around 222 MB. However, all memory allocation in the program is done dynamically on the heap, so the theoretical limit of file size is in between the max length of long int and max length of string, which is approx 2GB to 4GB

We postulate that given that there is no issues or limitaions associated with your CPU/ RAM, the program should be able to handle files in the range  of ~ 2GB
 *****************************************  END OF NOTE  *****************************************************
