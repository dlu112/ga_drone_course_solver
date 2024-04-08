# Shearwater Challenge Completed (David Lu)

This is an implementation of Genetic Algorithm used to solve the UAV course challenge. This program was compiled and tested using Visual Studio on Windows. Included are the source and header files only. Running the built shearwater_challenge executable with the filename of a text file formatted the same way as the provided sample input.txt files as am inline parameter will read in the input data and output the results to terminal. No error checking is included for the input file data. 

Example execution: ./shearwater_challenge.exe input_file.txt

Solve time for n<=100 is within 5 seconds. Solve time for the provided case with n=300 is approximately 3 minutes. Solve time for the provided case with n=500 is approximately 8 minutes but can get trapped in local minima, although running it with a larger population is able to after a much longer runtime. Various tuning routines have been removed from the code, and several hyperparameters aren't currently in use with the provided parameter set.