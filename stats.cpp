
#include "stats.h"

stats::stats(PNG & im){

    for (unsigned y = 0; y < im.height(); y ++) {
        for (unsigned x = 0; x < im.width(); x++) {
            RGBAPixel *pixel = image.getPixel(x, y);
            if (y == 0) {

                if (x == 0) {

                    sumRed[y][x] = (pixel -> r); 
                    sumGreen[y][x] = (pixel -> g); 
                    sumBlue[y][x] = (pixel -> b);
                
                } else {

                sumRed[y][x] = sumRed[y][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y][x-1] + (pixel -> b);
                }
            } if (x == 0) {

                sumRed[y][x] = sumRed[y-1][x] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + (pixel -> b);
                
            } if (x != 0 && y != 0) {

                sumRed[y][x] = sumRed[y-1][x] + sumRed[y][x-1] - sumRed[y-1][x-1] + (pixel -> r);
                sumGreen[y][x] = sumGreen[y-1][x] + sumGreen[y][x-1] + sumGreen[y-1][x-1] + (pixel -> g);
                sumBlue[y][x] = sumBlue[y-1][x] + sumBlue[y][x-1] + sumBlue[y-1][x-1] + (pixel -> b);
            }
        }
    }



/* Your code here!! */

}


long stats::getSum(char channel, pair<int,int> ul, int dim){
    long sum = 0; 

    if (channel == r) {

        sum = sumRed[ul.second + 2^k][ul.first + 2^k] - 
        sumRed[ul.second + 2^k - 1][ul.first + 2^k] - 
        sumRed[ul.second + 2^k][ul.first + 2^k -1] + 
        sumRed[ul.second + 2^k - 1][ul.first + 2^k - 1];

    } if (channel == g) {

        sum = sumGreen[ul.second + 2^k][ul.first + 2^k] - 
        sumGreen[ul.second + 2^k - 1][ul.first + 2^k] - 
        sumGreen[ul.second + 2^k][ul.first + 2^k -1] + 
        sumGreen[ul.second + 2^k - 1][ul.first + 2^k - 1];

    } if (channel = b) {

        sum = sumBlue[ul.second + 2^k][ul.first + 2^k] - 
        sumBlue[ul.second + 2^k - 1][ul.first + 2^k] - 
        sumBlue[ul.second + 2^k][ul.first + 2^k -1] + 
        sumBlue[ul.second + 2^k - 1][ul.first + 2^k - 1];
    }

    return sum;
/* Your code here!! */
}

long stats::getSumSq(char channel, pair<int,int> ul, int dim){

    long sum = getSum(channel, ul, dim); 
    return sum^2; 
/* Your code here!! */
}

long stats::rectArea(int dim) {

    long area = (2^dim)*(2^dim); 
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
