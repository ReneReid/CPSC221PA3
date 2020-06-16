
#include "stats.h"

/// @todo add 3 additional vectors to be initialized (sum and sum square); 

stats::stats(PNG & im){

    for (unsigned y = 0; y < im.height(); y ++) {
        for (unsigned x = 0; x < im.width(); x++) {
            RGBAPixel *pixel = im.getPixel(x, y);
            sumRed.resize(2);
            sumRed[0].resize(2);
            if (y == 0) {

                if (x == 0) {
                    std::cout << sumRed.capacity() << std::endl;
                    sumRed[y][x] = pixel->r; 
                    sumGreen[y][x] = (pixel -> g); 
                    sumBlue[y][x] = (pixel -> b);
                    sumsqRed[y][x] = pow((pixel -> r), 2); 
                    sumsqGreen[y][x] = pow((pixel -> g), 2);
                    sumsqBlue[y][x] = pow((pixel -> b), 2); 
                
                } else {

                sumRed[y][x] = sumRed[y][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y][x-1] + (pixel -> b);
                sumsqRed[y][x] = sumsqRed[y][x-1] + pow((pixel -> r), 2);
                sumsqGreen[y][x] = sumsqGreen[y][x-1] + pow((pixel -> g), 2);
                sumsqBlue[y][x] = sumsqBlue[y][x-1] + pow((pixel -> b), 2); 
                }
            } if (x == 0) { 

                sumRed[y][x] = sumRed[y-1][x] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + (pixel -> b);
                sumsqRed[y][x] = sumsqRed[y-1][x] + pow((pixel -> r), 2); 
                sumsqGreen[y][x] = sumsqGreen[y-1][x] + pow((pixel -> g), 2);
                sumsqBlue[y][x] = sumsqBlue[y-1][x] + pow((pixel -> b), 2);
                
            } if (x != 0 && y != 0) {

                sumRed[y][x] = sumRed[y-1][x] + sumRed[y][x-1] - sumRed[y-1][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + sumGreen[y][x-1] + sumGreen[y-1][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + sumBlue[y][x-1] + sumBlue[y-1][x-1] + (pixel -> b);
                sumsqRed[y][x] = sumsqRed[y-1][x] + sumsqRed[y][x-1] - sumsqRed[y-1][x-1] + pow((pixel -> r), 2); 
                sumsqGreen[y][x] = sumsqGreen[y-1][x] + sumsqGreen[y][x-1] - sumsqGreen[y-1][x-1] + pow((pixel -> g), 2);
                sumsqBlue[y][x] = sumsqBlue[y-1][x] + sumsqBlue[y][x-1] - sumsqBlue[y-1][x-1] + pow((pixel -> b), 2); 
            }
        }
    }



/* Your code here!! */

}


// calculates the sum (for each color channel) for a square
// whose position is by ul value and size by 2^dim.  
// refer to diagram for visual explanation (ask Rene)
long stats::getSum(char channel, pair<int,int> ul, int dim){
    long sum = 0; 

    if (channel == 'r') {

        sum = sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - // good
        sumRed[ul.second - 1][ul.first + pow(2, dim) - 1] - // good
        sumRed[ul.second + pow(2, dim) - 1][ul.first - 1] + // good
        sumRed[ul.second - 1][ul.first - 1]; //good

    } if (channel == 'g') {

        sum = sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumGreen[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumGreen[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumGreen[ul.second - 1][ul.first - 1];

    } if (channel == 'b') {

        sum = sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumBlue[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumBlue[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumBlue[ul.second - 1][ul.first - 1];
    }

    return sum;
/* Your code here!! */
}

// this should be accessing the sumSquare vectors which are populated in the constructor "stats"

long stats::getSumSq(char channel, pair<int,int> ul, int dim){

    long sumSq = 0; 

    if (channel == 'r') {

        sumSq = sumsqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - // good
        sumsqRed[ul.second - 1][ul.first + pow(2, dim) - 1] - // good
        sumsqRed[ul.second + pow(2, dim) - 1][ul.first - 1] + // good
        sumsqRed[ul.second - 1][ul.first - 1]; //good

    } if (channel == 'g') {

        sumSq = sumsqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumsqGreen[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumsqGreen[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumsqGreen[ul.second - 1][ul.first - 1];

    } if (channel == 'b') {

        sumSq = sumsqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumsqBlue[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumsqBlue[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumsqBlue[ul.second - 1][ul.first - 1];
    }

    return sumSq;
    
    
    //long sum = getSum(channel, ul, dim); 
    //return sum^2; 
/* Your code here!! */
}

/// @todo change the power sign here too 

long stats::rectArea(int dim) {

    long area = pow(pow(2, dim), 2); 
    return area;

/* Your code here!! */

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
long stats::getVar(pair<int,int> ul, int dim){
/* Your code here!! */


    long sumsqRed = getSumSq('r', ul, dim);
    long sumsqGreen = getSumSq('g', ul, dim);
    long sumsqBlue = getSumSq('b', ul, dim);

    long area = rectArea(dim);

    long variance = (sumsqRed + sumsqGreen + sumsqBlue) - ((sumsqRed + sumsqGreen + sumsqBlue)/area);
    return variance;

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int dim){

    RGBAPixel pixel; 
    long sumRed = getSum('r', ul, dim); 
    long sumGreen = getSum('g', ul, dim); 
    long sumBlue = getSum('b', ul, dim); 

    long area = rectArea(dim); 

    long avgRed = sumRed/area;
    long avgGreen = sumGreen/area;
    long avgBlue = sumBlue/area;

    pixel.r = avgRed;
    pixel.g = avgGreen;
    pixel.b = avgBlue;
    
    return pixel;

/* Your code here!! */



}
