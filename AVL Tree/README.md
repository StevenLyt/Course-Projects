# bst.h
A templated binary search tree class, with the implementation of `insert()`, `remove()` and other functions.

# avlbst.h
Derived AVL tree class inherited from the bst class. Add the auto-balance property and other helper functions: `rotateLeft()`,`rotateRight()`,`insertFix()`,  `removeFix()`.

# floorplan.cpp
Using backtracking to find a layout of a set of rectangular tiles within a N*M rectangular surface. `floorplan_map_version.cpp` uses the STL map as the container, while `floorplan.cpp` uses the AVL tree implemented in `avlbst.h`.