
[Longest Flight Route](https://cses.fi/problemset/result/8998372/)
[Submission link](https://cses.fi/paste/71aea740edd72774894de4/)

The problem here asks, in a DAG, to find if there exists a path between the source(0) and the destination(n-1), and if such a path exist, to return the one with the maximum distance (passes through maximum number of vertices).

Solution I:
    To solve this problem we can use DFS, and for each vertex V, update the maximum distance of each child U, and in the case of such an update, also update the parent of the child U as V, in order to retrace the path with the maximum distance.
    At the end, check if we can or not reach destinantion
    If it's possible, retrace the path


Solution II:
    To solve this problem we can use BFS Kanh algo, we will thus process each vertex in the topological order, which makes it possible to guarantee, for each vertex we have already treated the distance of all its parents, we can thus update its distance using the reversed graph
    We can keep track of the path with maximal distance int he same way as in Solution I
    
