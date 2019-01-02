# 4th-year-prototype

how to execute: <br />
git clone https://github.com/ArtiomSu/4th-year-prototype.git <br />
cd 4th-year-prototype <br />
rm -r -f build <br />
make <br />
./dist/Debug/GNU-Linux/prototype <br />
<br /> 
this was simplified into a script ./run.sh <br />
<br />
or if there are some issues with make you can just do <br />
g++ *.cpp <br />
./a.out <br />
<br />
<br />
This prototype syncroises two tree parity machines that will end up to produce the same key.<br />
in the main.cpp you can play around with the tree parity machine parameters.<br />
initK = 8;  // k is hidden neurons	<br />
initN = 10; // n is input neurons	<br />
initL = 6; // range of weights eg. with 6 the possible value of each element in the <br />
              weights is [ -6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6 ]<br />
              
increasing initK, initN will generally produce a larger length key.<br />
increasing initL generally leads to a longer syncronisation time and can increase the length of the key<br />
provided initL <= 6. <br />
