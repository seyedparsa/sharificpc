1- Find a spanning tree of the given graph and choose a root for the tree.
2- Determine, for each edge uv that is not part of the tree, the distance between the root and the lowest common ancestor of u and v.
3- For each edge uv that is part of the tree, find the corresponding "master edge", a non-tree edge wx such that the cycle formed by adding wx to the tree passes through uv and such that, among such edges, w and x have a lowest common ancestor that is as close to the root as possible (with ties broken by edge identifiers).
4- Form an ear for each non-tree edge, consisting of it and the tree edges for which it is the master, and order the ears by their master edges' distance from the root (with the same tie-breaking rule).
