# Hashtable

Implementation of a Hashtable<string,int> data structure with probing for collision resolution. Input are converted to strings of lowercase letters, and other characters are ignored.

## test method

To test the program, I used [Shakespeare’s Hamlet]( https://gist.github.com/provpup/2fc41686eab7400b796b), which is about 32000 words, and truncated it into files containing about 30, 300, 3000, and 30000 words. [AVL tree implemented previously](https://github.com/StevenLyt/Course-Projects/tree/main/AVL%20Tree) is also include to draw a comparison between hashtable and tree structure.

## result

In the table below, the first number indicates data obtained in normal mode, and the second in debug mode.

|  input size   |     Linear probing      |    Quadratic probing    |     Double hashing      |  AVL tree  |
| :-----------: | :---------------------: | :---------------------: | :---------------------: | :--------: |
|      29       | 0.00002418 / 0.00002395 | 0.0000242 / 0.00001912  | 0.00002812 / 0.00002484 | 0.00001971 |
| per operation | 8.3379e-07 / 8.2586e-07 | 8.3448e-07 / 6.5931e-07 | 9.6966e-07 / 8.5655e-07 | 6.7966e-07 |
|      314      | 0.00028169 / 0.0002164  |  0.000271 / 0.0002332   | 0.00027544 / 0.00030919 | 0.00032169 |
| per operation | 8.9710e-07 / 6.8917e-07 | 8.631e-07 /  7.427e-07  | 8.7720e-07 / 9.8468e-07 | 1.0245e-06 |
|     3164      | 0.00305936 / 0.00165811 | 0.00307803 / 0.00176261 | 0.00192542 / 0.00183941 | 0.00297397 |
| per operation |  9.669e-07 / 5.241e-07  |  9.728e-07 / 5.571e-07  |  6.085e-07 / 5.814e-07  | 9.399e-07  |
|     31955     |  0.0503572 / 0.0130916  |  0.0517701 / 0.0145077  |   0.016131 / 0.016182   | 0.0348906  |
| per operation | 1.5759e-06 / 4.0969e-07 | 1.6201e-06 / 4.5400e-07 | 5.0480e-07 / 5.0640e-07 | 1.0919e-06 |

## remark

I also tried STL map and unordered_map. The time they take for the 31955 case are 0.0171696 and 0.00798552 respectively, which are much faster than my implantation. This makes sense since there are lots of optimizations for STL. 

Compared with my AVL tree, hashtable, regardless of the ways of probing used, tends to be faster. This is what I expected since each `add` operation takes about linear runtime, whereas in AVL tree it takes logarithmic runtime. 

But what surprise me is that given large input size, hastables using linear probing and quadratic probing in debug mode are much effective than in normal mode. But for hashtable with double hashing, debug mode doesn't make a huge difference. 

