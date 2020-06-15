
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
                    sumSqRed[y][x] = pow(sumRed[y][x], 2); 
                    sumSqGreen[y][x] = pow(sumGreen[y][x], 2);
                    sumSqBlue[y][x] = pow(sumBlue[y][x], 2); 
                
                } else {

                sumRed[y][x] = sumRed[y][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y][x-1] + (pixel -> b);
                sumSqRed[y][x] = pow(sumRed[y][x], 2); 
                sumSqGreen[y][x] = pow(sumGreen[y][x], 2);
                sumSqBlue[y][x] = pow(sumBlue[y][x], 2); 
                }
            } if (x == 0) {

                sumRed[y][x] = sumRed[y-1][x] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + (pixel -> b);
                sumSqRed[y][x] = pow(sumRed[y][x], 2); 
                sumSqGreen[y][x] = pow(sumGreen[y][x], 2);
                sumSqBlue[y][x] = pow(sumBlue[y][x], 2); 
                
            } if (x != 0 && y != 0) {

                sumRed[y][x] = sumRed[y-1][x] + sumRed[y][x-1] - sumRed[y-1][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + sumGreen[y][x-1] + sumGreen[y-1][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + sumBlue[y][x-1] + sumBlue[y-1][x-1] + (pixel -> b);
                sumSqRed[y][x] = pow(sumRed[y][x], 2); 
                sumSqGreen[y][x] = pow(sumGreen[y][x], 2);
                sumSqBlue[y][x] = pow(sumBlue[y][x], 2); 
            }
        }
    }



/* Your code here!! */

}
// calculates the sum (for each color channel) for a square
// whose position is by ul value and size by 2^dim.  
/// @todo need to revise power statements: power in C++ is pow(base, exponent); 


long stats::getSum(char channel, pair<int,int> ul, int dim){
    long sum = 0; 

    if (channel == r) {

        sum = sumRed[ul.second + pow(2, dim)][ul.first + pow(2, dim)] - 
        sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim)] - 
        sumRed[ul.second + pow(2, dim)][ul.first + pow(2, dim) -1] + 
        sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];

    } if (channel == g) {

        sum = sumGreen[ul.second + pow(2, dim)][ul.first + pow(2, dim)] - 
        sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim)] - 
        sumGreen[ul.second + pow(2, dim)][ul.first + pow(2, dim) - 1] + 
        sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];

    } if (channel = b) {

        sum = sumBlue[ul.second + pow(2, dim)][ul.first + pow(2, dim)] - 
        sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim)] - 
        sumBlue[ul.second + pow(2, dim)][ul.first + pow(2, dim) -1] + 
        sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
    }

    return sum;
/* Your code here!! */
}

// this should be accessing the sumSquare vectors which are populated in the constructor "stats"\

/// @todo  potentially change power sign here

long stats::getSumSq(char channel, pair<int,int> ul, int dim){

    long sumSq = 0; 

    if (channel == r) {

        sumSq = sumSqRed[ul.second + pow(2, dim)][ul.first + pow(2, dim)] - 
        sumSqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim)] - 
        sumSqRed[ul.second + pow(2, dim)][ul.first + pow(2, dim) -1] + 
        sumSqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];

    } if (channel == g) {

        sumSq = sumSqGreen[ul.second + pow(2, dim)][ul.first + pow(2, dim)] - 
        sumSqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim)] - 
        sumSqGreen[ul.second + pow(2, dim)][ul.first + pow(2, dim) - 1] + 
        sumSqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];

    } if (channel = b) {

        sumSq = sumBlue[ul.second + pow(2, dim)][ul.first + pow(2, dim)] - 
        sumSqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim)] - 
        sumSqBlue[ul.second + pow(2, dim)][ul.first + pow(2, dim) -1] + 
        sumSqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
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
