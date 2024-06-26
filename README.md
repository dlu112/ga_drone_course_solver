# Drone Course Challenge Completed (David Lu)

This is an implementation of Genetic Algorithm used to solve the UAV course challenge. This program was compiled and tested using Visual Studio on Windows. Included are the source and header files only. Running the built course_solver executable with the filename of a text file formatted the same way as the provided sample input.txt files as am inline parameter will read in the input data and output the results to terminal. No error checking is included for the input file data. 

Example execution: ./course_solver.exe input_file.txt

Solve time for n<=100 is within 5 seconds. Solve time for the provided case with n=300 is approximately 3 minutes. Solve time for the provided case with n=500 is approximately 8 minutes but can get trapped in local minima, although running it with a larger population is able to after a much longer runtime. Various tuning routines have been removed from the code, and several hyperparameters aren't currently in use with the provided parameter set.

# Challenge Description

You have been provided with a challenge for a delivery UAV. A course is set up in a 100m by 100m area. Certain points are identified within the space as waypoints to visit to deliver goods. They are ordered -- there is a waypoint 1, a waypoint 2, etc. Your UAV must start at (0,0). From there, it should go to waypoint 1, stop for 10 seconds, go to waypoint 2, stop for 10 seconds, and so on. It must finally end up at, and stop for 10 seconds on (100,100).

Each waypoint except (0,0) and (100,100) has a time penalty for missing the delivery to reflect the time needed for a human to handle the work later. So, if your UAV went straight from waypoint 1 to waypoint 3, skipping waypoint 2, it would incur waypoint 2's penalty. Note that once it hits waypoint 3, it cannot go back to waypoint 2. It must hit the waypoint in order. Since your UAV must stop for 10 seconds on each waypoint to deliver the package, it is not in danger of hitting a waypoint accidentally too soon. For example, if waypoint 3 lies directly between waypoints 1 and 2, your UAV can go straight from 1 to 2, right over 3, without stopping. Since it didn't stop to deliver the package, waypoint 3's penalty will not be incurred. Your final score is the amount of time (in seconds) your UAV takes to reach (100,100), completing the course, plus all penalties. Smaller scores are better.

UAV is very manoeuvrable, but a bit slow. It moves at 2 m/s, but can turn very quickly. During the 10 seconds it stops on a waypoint point, it can easily turn to face the next waypoint. Thus, it can always move in a straight line between target points.

Because UAV is a bit slow, it might be advantageous to skip some waypoints and incur their penalty, rather than actually manoeuvring to them. Given a description of a course, determine UAV's best (lowest) possible time.

Implement your submission in C++.

## Input  

There will be several test cases. Each test case will begin with a line with one integer, N (1 <= N <= 1000) which is the number of waypoints on the course. Each of the next N lines will describe a waypoint with three integers, X, Y and P, where (X, Y) is a location on the course ( 1 <= X, Y <= 99, X and Y in meters) and P is the penalty incurred if UAV misses that waypoint (1 <= P <= 100). The waypoints will be given in order -- the first line after N is target 1, the next is waypoint 2, and so on. All the waypoints on a given course will be unique -- there will be at most one waypoint point at any location on the course. End of input will be marked by a line with a single `0'.

## Output  

For each test case, output a single decimal number, indicating the smallest possible time for that factory. Output this number rounded (NOT truncated) to three decimal places. Print each answer on its own line, and do not print any blank lines between answers.

See `sample_input_*.txt` and `sample_output_*.txt`, where:

```
cat sample_input_small.txt | ./solution_executable | tee sample_output_small.txt
```



