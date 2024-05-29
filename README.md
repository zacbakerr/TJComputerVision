
# Computer Vision
The labs I completed as part of the computer vision course I took during my senior year of high school.

### Lab 1: The Basics
- Create a triangle
- Draw the circumcircle, incircle, and nine-point circle
- Draw eulers line

### Lab 2: Smallest Square
- Generate three random points and then generate a fourth point so that none of the points lie within the other points
- Generate all possible squares that have these four points on their sides or extensions of their sides
- Generate an image of the smallest of these squares

### Lab 3: Closest pair of points
- Determine the closest pair of points
    - Part 1: brute force
    - Part 2: intermediate recursive method: split vector into two sorted by x or y values. Continue to split into two until you are left with 2 or 3 points and then return the min distance. Create a strip of mindist on the opposite axis the points were sorted and bruteforce a mindist for all the points in the strip.
    - Part 3: full recursive method: Create a strip of mindist but instead of brute forcing, sort the list of points by the opposite axis to which they were sorted origanally. For each point, iterate through the list until you reach mindist away and keep track if you reach a new mindist.
    - Part 4: linear method: Shuffle points using knuth shuffle. Use the randomazied algorithm to find the mindist (pdf in folder).

### Lab 4: Convex Hull
- Given a list of points, generate a convex hull
     - Part 1: using (quickhull algorithm)[https://en.wikipedia.org/wiki/Quickhull]
     - Part 2: using (graham scan algorithm)[https://en.wikipedia.org/wiki/Graham_scan]

### Lab 5: Canny Edge Detection
- Part 1
    - Convert image to greyscale using (algorithm) [https://en.wikipedia.org/wiki/Grayscale]
    - Identify edges on image using (Sobel Operator)[https://en.wikipedia.org/wiki/Sobel_operator]
- Part 2
    - Implement the hysteresis algorithm with a low and high threshold
- Part 3
    - Implement non-max supression and hysteresis + non-max supression

### Lab 6: Coin Detection
- Part 1
    - Identify center candidates for all coins
- Part 2
     - Identify each coin and its amount
- Part 3
    - Refine code from part 3

### Lab 7: Coin Detection with OpenCV
- Part 1
    - Implement the code from lab 6 using OpenCV

### Lab 8: Projection and rotation of shapes onto different planes using OpenCV

### Lab 9: Augmented reality using OpenCV
