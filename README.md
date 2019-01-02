# 4th-year-prototype

how to execute:
git clone https://github.com/ArtiomSu/4th-year-prototype.git
cd 4th-year-prototype
rm -r -f build
make
./dist/Debug/GNU-Linux/prototype


or if there are some issues with make you can just do
g++ *.cpp
./a.out


This prototype syncroises two tree parity machines that will end up to produce the same key.
in the main.cpp you can play around with the tree parity machine parameters.
initK = 8;  // k is hidden neurons	
initN = 10; // n is input neurons	
initL = 6; // range of weights eg. with 6 the possible value of each element in the 
              weights is [ -6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6 ]
              
increasing initK, initN will generally produce a larger length key.
increasing initL generally leads to a longer syncronisation time and can increase the length of the key
provided initL <= 6. 
