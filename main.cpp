#include "opencv2/core/core.hpp"
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <math.h>
#include <ctime>

using namespace std;
using namespace cv;

class neuron
{
public:
    float sinapsis[50][50];
    float value = 0;

    neuron()
    {
        for(int x = 0; x < 50; x++)
        {
            for(int y = 0; y < 50; y++)
            {
                sinapsis[x][y] = 1;
            }
        }
    }
};

int main()
{
    cout << "Hello world!" << endl;

    neuron* pixels[50][50];
    neuron* saidas[10];
    for(int x = 0; x < 50; x++)
    {
        for(int y = 0; y < 50; y++)
        {
            pixels[x][y] = new neuron();
        }
    }
    for(int x = 0; x < 10; x++)
    {

        saidas[x] = new neuron();

    }

    cout << pixels[1][1]->sinapsis[1][1] << endl;

    cv::Mat images[50];
    char alph[5] = {  'a', 'b', 'c','d','e'};
    int pos = 0;

    for(int o = 0; o < 50; o++)
    {
        images[o] = cv::imread("numbers/"+std::to_string(o%10)+"_"+alph[pos%5]+".png", CV_LOAD_IMAGE_GRAYSCALE);
        if(o%10 == 9) pos++;
    }

    int cicle = 0;
    pos = 0;
    int teachFor = 500;

    while(true)
    {
        cicle++;
        for(int out = 0; out < 10; out++)
        {
            saidas[out]->value = 0;
        }
        int imgN = (cicle % 50);
        Mat image = images[imgN];

        cout << "image: " + std::to_string(cicle%10)+"_"+alph[pos%5] << endl;
        if(cicle%10 == 9) pos++;
        imgN = (imgN %10);



        for(int out = 0; out < 10; out++)
        {

            for(int x = 0; x < 50; x++)
            {
                for(int y = 0; y < 50; y++)
                {
                    uint pix = image.at<uchar>(x,y);
                    if(pix < 50)
                    {
                        saidas[out]->value += saidas[out]->sinapsis[x][y];
                    }
                }
            }
        }

        for(int out = 0; out < 10; out++)
        {
            cout << out << ": " + std::to_string(saidas[out]->value) << endl;
        }



        int gueesed = -1;
        int maxd = 0;

        for(int out = 0; out < 10; out++)
        {
            if(saidas[out]->value >= maxd)
            {
                gueesed = out;
                maxd = saidas[out]->value;
            }
        }

        namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
        imshow( "Display window", image );                   // Show our image inside it.

        waitKey(30);

        cout << "I think it is: " << gueesed << " - Is it correct? " << endl;
        string img;
        if(cicle >= teachFor)
            cin >> img;
        else
            img = std::to_string(imgN);

        int correct = atoi(img.c_str());
        cout << "correct: " << correct << imgN<< endl;

        if(correct != gueesed)
        {
            cout << "incorrect" << endl;
            for(int x = 0; x < 50; x++)
            {
                for(int y = 0; y < 50; y++)
                {
                    uint pix = image.at<uchar>(x,y);
                    if(pix < 50)
                    {
                        //saidas[out]->value += saidas[out]->sinapsis[x][y];

                        saidas[correct]->sinapsis[x][y] += 1;
                    }
                }
            }
        }

        //cout << std::to_string(pix) << endl;

    }

    return 0;
}
