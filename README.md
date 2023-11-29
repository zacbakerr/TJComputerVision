
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
