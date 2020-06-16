
#include "stats.h"

/// @todo add 3 additional vectors to be initialized (sum and sum square); 

stats::stats(PNG & im){

    for (unsigned y = 0; y < im.height(); y ++) {
        for (unsigned x = 0; x < im.width(); x++) {
            RGBAPixel *pixel = image.getPixel(x, y);
            if (y == 0) {

                if (x == 0) {

                    sumRed[y][x] = (pixel -> r); 
                    sumGreen[y][x] = (pixel -> g); 
                    sumBlue[y][x] = (pixel -> b);
                    sumSqRed[y][x] = pow((pixel -> r), 2); 
                    sumSqGreen[y][x] = pow((pixel -> g), 2);
                    sumSqBlue[y][x] = pow((pixel -> b), 2); 
                
                } else {

                sumRed[y][x] = sumRed[y][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y][x-1] + (pixel -> b);
                sumSqRed[y][x] = sumSqRed[y][x-1] + pow((pixel -> r), 2);
                sumSqGreen[y][x] = sumSqGreen[y][x-1] + pow((pixel -> g), 2);
                sumSqBlue[y][x] = sumSqBlue[y][x-1] + pow((pixel -> b), 2); 
                }
            } if (x == 0) { 

                sumRed[y][x] = sumRed[y-1][x] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + (pixel -> b);
                sumSqRed[y][x] = sumSqRed[y-1][x] + pow((pixel -> r), 2); 
                sumSqGreen[y][x] = sumSqGreen[y-1][x] + pow((pixel -> g), 2);
                sumSqBlue[y][x] = sumSqBlue[y-1][x] + pow((pixel -> b), 2);
                
            } if (x != 0 && y != 0) {

                sumRed[y][x] = sumRed[y-1][x] + sumRed[y][x-1] - sumRed[y-1][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + sumGreen[y][x-1] + sumGreen[y-1][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + sumBlue[y][x-1] + sumBlue[y-1][x-1] + (pixel -> b);
                sumSqRed[y][x] = sumSqRed[y-1][x] + sumSqRed[y][x-1] - sumSqRed[y-1][x-1] + pow((pixel -> r), 2); 
                sumSqGreen[y][x] = sumSqGreen[y-1][x] + sumSqGreen[y][x-1] - sumSqGreen[y-1][x-1] + pow((pixel -> g), 2);
                sumSqBlue[y][x] = sumSqBlue[y-1][x] + sumSqBlue[y][x-1] - sumSqBlue[y-1][x-1] + pow((pixel -> b), 2); 
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

    if (channel == r) {

        sum = sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - // good
        sumRed[ul.second - 1][ul.first + pow(2, dim) - 1] - // good
        sumRed[ul.second + pow(2, dim) - 1][ul.first - 1] + // good
        sumRed[ul.second - 1][ul.first - 1]; //good

    } if (channel == g) {

        sum = sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumGreen[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumGreen[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumGreen[ul.second - 1][ul.first - 1];

    } if (channel = b) {

        sum = sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumBlue[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumBlue[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumBlue[ul.second - 1][ul.first - 1];
    }

    return sum;
/* Your code here!! */
}

// this should be accessing the sumSquare vectors which are populated in the constructor "stats"\

long stats::getSumSq(char channel, pair<int,int> ul, int dim){

    long sumSq = 0; 

    if (channel == r) {

        sumSq = sumSqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - // good
        sumSqRed[ul.second - 1][ul.first + pow(2, dim) - 1] - // good
        sumSqRed[ul.second + pow(2, dim) - 1][ul.first - 1] + // good
        sumSqRed[ul.second - 1][ul.first - 1]; //good

    } if (channel == g) {

        sumSq = sumSqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumSqGreen[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumSqGreen[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumSqGreen[ul.second - 1][ul.first - 1];

    } if (channel = b) {

        sumSq = sumSqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
        sumSqBlue[ul.second - 1][ul.first + pow(2, dim) - 1] - 
        sumSqBlue[ul.second + pow(2, dim) - 1][ul.first - 1] + 
        sumSqBlue[ul.second - 1][ul.first - 1];
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


    long sumSqRed = getSumSq(r, ul, dim);
    long sumSqGreen = getSumSq(g, ul, dim);
    long sumSqBlue = getSumSq(b, ul, dim);

    long area = rectArea(dim);

    long variance = (sumSqRed + sumSqGreen + sumSqBlue) - ((sumSqRed + sumSqGreen + sumSqBlue)/area);
    return variance;

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int dim){

    RGBAPixel pixel; 
    long sumRed = getSum(r, ul, dim); 
    long sumGreen = getSum(g, ul, dim); 
    long sumBlue = getSum(b, ul, dim); 

    long area = rectArea(dim); 

    long avgRed = sumRed/area;
    long avgGreen = sumGreen/area;
    long avgBlue = sumBlue/area;

    pixel -> r = avgRed;
    pixel -> g = avgGreen;
    pixel -> b = avgBlue;
    
    return pixel;

/* Your code here!! */



}
