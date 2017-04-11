# Extended Kalman Filter Project
Self-Driving Car Engineer Nanodegree Program

---

[//]: # (Image References)
[data_1_with_ground_truth]: ./resources/data_1.png
[data_1_without_ground_truth]: ./resources/data_1_wt_gt.png
[data_2_with_ground_truth]: ./resources/data_2.png
[data_2_without_ground_truth]: ./resources/data_2_wt_gt.png


## Dependencies

* cmake >= 3.5
* make >= 4.1
* gcc/g++ >= 5.4

## Basic Build Instructions

1. Make a build directory: `mkdir build && cd build`
2. Compile: `cmake .. && make` 
   * On windows, you may need to run: `cmake .. -G "Unix Makefiles" && make`
3. Run it: `./ExtendedKF path/to/input.txt path/to/output.txt`. You can find
   some sample inputs in 'data/'.
    - eg. `./ExtendedKF ../data/sample-laser-radar-measurement-data-1.txt output.txt`

## Results

For [sample-laser-radar-measurement-data-1.txt](data/sample-laser-radar-measurement-data-1.txt)
the error is:

var | RMSE
----|-----
px  | 0.07
py  | 0.06
vx  | 0.53
vy  | 0.54

Visualization with ground truth:
![alt_text][data_1_with_ground_truth]

Visualization without ground truth:
![alt_text][data_1_without_ground_truth]

For [sample-laser-radar-measurement-data-2.txt](data/sample-laser-radar-measurement-data-2.txt)
the error is: 

var | RMSE
----|-----
px  | 0.17
py  | 0.19
vx  | 0.48
vy  | 0.81

Visualization with ground truth:
![alt_text][data_2_with_ground_truth]

Visualization without ground truth:
![alt_text][data_2_without_ground_truth]


## Reflections

* In general it looks like Kalman filters do the job and track targets quite well.
* But errors are visible, especially on the first data file visualization. At the moment for me it is not clear
how this can be fixed.
* Based on visualizations, the second data file tracking looks better than the first data file tracking,
 but based on on the errors it is the opposite. This may be because of different scales, but still this reminds me of the same problem from almost every project
 of the first term: it is not clear how a particular error metric is related to performance in real life. 