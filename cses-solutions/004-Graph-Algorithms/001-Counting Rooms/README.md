
[Counting Rooms](https://cses.fi/problemset/task/1192/)
[Submission link](https://cses.fi/paste/c5e25281d3fed1248780c3/)

The problem asks to count the number of rooms in a NxM matrix

Solution I:
    - if we define a room as a set of squares (floors) that are connected, it suffices to traverse the matrix, with a BFS and DFS from all unvisited floor square
    -when we traverse the matrix, we know that all the visited square from the same traversial belong to the same room,
    -so we increment the number of rooms when we find an unvisited point after a traversial

