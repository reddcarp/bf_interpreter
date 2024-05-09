# source: codingame dot com

,>,            read A and B
[-<->>+<]      double trick : computes A minus B on the left and copy B on the right
<[             A != B
  >>[-<+<+>>]  reconstruct A and B original values from B copy
  <<.[-]       print A and clean
  >.[-]        print B and clean
<]             loop (on null value)
>>[            go to B copy (if not deleted then it means A == B)
  .[-]         print B (aka A and print only once) and clean
]<<            cleansing