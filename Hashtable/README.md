# Hashtable

Implementation of a Hashtable<string,int> data structure with probing for collision resolution. Input are converted to strings of lowercase letters, and other characters are ignored.

## test method

To test the program, I used [Shakespeare’s Hamlet]( https://gist.github.com/provpup/2fc41686eab7400b796b), which is about 32000 words, and truncated it into files containing about 30, 300, 3000, and 30000 words. [AVL tree implemented previously](https://github.com/StevenLyt/Course-Projects/tree/main/AVL%20Tree) is also include to draw a comparison between hashtable and tree structure.

## result

In the table below, the first number indicates data obtained in normal mode, and the second in debug mode.

|  input size   |     Linear probing      |    Quadratic probing     |     Double hashing      |  AVL tree  |
| :-----------: | :---------------------: | :----------------------: | :---------------------: | :--------: |
|      29       | 0.00002426 / 0.00002395 |  0.0000242 / 0.00002264  | 0.00002812 / 0.00002484 | 0.00001671 |
| per operation | 8.3379e-07 / 8.2586e-07 | 8.3448e-07 / 7.8069e-07  | 9.6966e-07 / 8.5655e-07 | 5.762e-07  |
|      314      | 0.00025813 / 0.0002164  |  0.00022505 / 0.0002332  | 0.00027544 / 0.00025953 | 0.00026737 |
| per operation | 8.2207e-07 / 6.8917e-07 | 7.1672e-07 /  7.4268e-07 | 8.7720e-07 / 8.2653e-07 | 8.5149e-07 |
|     3164      | 0.00168416 / 0.00165811 | 0.00182042 / 0.00176261  | 0.00192542 / 0.00183941 |  0.002192  |
| per operation | 5.3229e-07 / 5.2405e-07 |  5.7535e-07 / 5.571e-07  | 5.5708e-07 / 5.8136e-07 | 6.927e-07  |
|     31955     |  0.0126454 / 0.0124296  |  0.0120437 / 0.0130445   |  0.0139129 / 0.0132659  |  0.01937   |
| per operation | 3.9573e-07 / 3.8897e-07 | 3.7690e-07 / 4.5400e-07  | 4.3539e-07 / 4.1514e-07 | 6.062e-07  |

## remark

I also tried STL map and unordered_map. The time they take for the 31955 case are 0.0171696 and 0.00798552 respectively, which are much faster than my implantation. This makes sense since there are lots of optimizations for STL. 

Compared with my AVL tree, hashtable, regardless of the ways of probing used, tends to be faster given large input size. This is what I expected since each `add` operation takes about linear runtime, whereas in AVL tree it takes logarithmic runtime. 

But what surprise me is that hastables using different probing methods don't show a huge difference in runtime. Also, as input size grows larger, the cost of each operation become less expensive.

