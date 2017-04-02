# Extended Kalman Filter Project Starter Code
Self-Driving Car Engineer Nanodegree Program

---

[//]: # (Image References)
[data_1_with_ground_truth]: ./resources/data_1.png
[data_1_without_ground_truth]: ./resources/data_1_wt_gt.png
[data_2_with_ground_truth]: ./resources/data_2.png
[data_2_without_ground_truth]: ./resources/data_2_wt_gt.png


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make` 
   * On windows, you may need to run: `cmake .. -G "Unix Makefiles" && make`
4. Run it: `./ExtendedKF path/to/input.txt path/to/output.txt`. You can find
   some sample inputs in 'data/'.
    - eg. `./ExtendedKF ../data/sample-laser-radar-measurement-data-1.txt output.txt`

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Results

For [sample-laser-radar-measurement-data-1.txt](data/sample-laser-radar-measurement-data-1.txt)
the RMSE is:

[0.07, 0.06, 0.53, 0.54]

Visualization with ground truth:
![alt_text][data_1_with_ground_truth]

Visualization without ground truth:
![alt_text][data_1_without_ground_truth]

For [sample-laser-radar-measurement-data-2.txt](data/sample-laser-radar-measurement-data-2.txt)
the RMSE is: 

[0.17, 0.19, 0.48, 0.81]

Visualization with ground truth:
![alt_text][data_2_with_ground_truth]

Visualization without ground truth:
![alt_text][data_2_without_ground_truth]


##Reflections

*In general it looks like Kalman filters do the job and track targets quite well.
*But errors are visible, especially on the first data file visualization. At the moment for me it is not clear
how this can be fixed.
*Based on visualizations, the second data file tracking looks better than the first data file tracking,
 but based on on the errors it is the opposite. This reminds me of the same problem from almost every project
 of the first term: it is not clear how a particular error metric is related to performance in real life. 