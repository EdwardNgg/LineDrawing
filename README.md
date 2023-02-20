# Line Drawing (PA1)

Edward Ng

113789742

edward.ng@stonybrook.edu

## Overview

The Line Drawing (PA1) program is a CSE328: Fundamentals of Computer Graphics assignment and builds on the provided 
template. The program draws the lines of a variety of primitive structures listed below. Each shape is drawn based on 
the Bresenham midpoint algorithm. Furthermore, drawings for poly-lines and polygons build on top of the frame buffers 
with multiple line segments.

## Features Implemented

- [x] P1: Line segment
    - [x] Slope m < -1
    - [x] -1 <= m < 0
    - [x] 0 <= m <= 1
    - [x] 1 < m
    - [x] Vertical
- [x] P2: Ploy-line
- [x] P3: Polygon
- [x] P4: Circle
- [x] P5: Ellipse
- [x] P6: Cubic curve

## Usage
The program completely follows the usage patterns specified in the requirements.

### Line Segments
To start drawing line segments, press key `1`. Left-clicking the mouse will specify the starting position of the line segment. After moving the mouse cursor to the endpoint, a right click finalizes the line segment.

### Poly-Lines
To start drawing poly-lines, press key `2`. Consecutive left clicks will add new vertices to the poly-line. Right-clicking will finalize the poly-line.

### Polygons
To start drawing polygons, press key `3`. Like the poly-line, consecutive left clicks will add new vertices to the polygon. However, right-clicking will connect the last vertex to the first, finalizing the polygon.

### Circles
To start drawing circles, press key `4`. A left click will specify the center, and a right click will indicate any point on the figure.

### Ellipses
To start drawing ellipses, press key `5`. Left-clicking will specify the ellipse's center. Right-clicking will determine the two radii of the ellipse, which aligns to the window.

### Cubic Curves
The equation for a polynomial curve is the following.
```
y = ax^3 + bx^2 + cx + d
```
To start plotting polynomial curves, press key '6'. The program reads the parameters of the polynomial from the text file `./etc/parameters.txt`. The file contains the four space-separated floating-point numbers in one line, denoting 'a', 'b', 'c', and 'd'. For quadratic curves, set 'a' to '0'. For more information, refer to the appendix.


## Appendix

The line-drawing program supports drawing curves, but it has some limitations. The cubic curve functionality supports 
any combination of numbers in the parameter text file as long as they are reasonable. For example, based on the cubic 
equation `y = ax^3 + bx^2 + cx + d`, the following parameter text file works with the program.
```text
0.000003 -0.006 3 500
```
As a suggestion, the values are best in the following ranges.
```
-0.00001 <= a <= 0.00001
-0.01 <= b <= 0.01
-1.0 <= c <= 1.0
0 <= d <= 1000
```

Furthermore, the program supports quadratic curves by setting `a` to 0.0.

> ⚠️ Warning
> 
> The program is limited to curves that start on the left of the window and only intersect the window twice. If a curve 
> intersects the windows more than twice, the program will not draw the second segment. It is a limitation to prevent 
> the program from hanging on curves with massive slopes.
