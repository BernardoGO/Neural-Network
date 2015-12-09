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
#include "opencv2/imgcodecs.hpp"
#include <ctime>
#include <stdio.h>
#include <unistd.h>
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

cv::Mat frame;
const char* src_window = "Display window";

int drag = 0, select_flag = 0;

cv::Point point1, point2;
bool callback = false;

void mouseHandler(int event, int x, int y, int flags, void* param);

void mouseHandler(int event, int x, int y, int flags, void* param)
{
    if (event == CV_EVENT_LBUTTONDOWN && !drag && !select_flag)
    {
        /* left button clicked. ROI selection begins */
        point1 = cv::Point(x, y);
        drag = 1;
    }

    if (event == CV_EVENT_MOUSEMOVE && drag && !select_flag)
    {
        /* mouse dragged. ROI being selected */
        cv::Mat img1 = frame.clone();
        point2 = cv::Point(x, y);

        img1.at<uchar>(y,x) = 0;
        img1.at<uchar>(y+1,x) = 0;
        img1.at<uchar>(y,x+1) = 0;
        img1.at<uchar>(y+1,x+1) = 0;
        img1.at<uchar>(y-1,x) = 0;
        img1.at<uchar>(y,x-1) = 0;
        img1.at<uchar>(y-1,x-1) = 0;

        //cv::rectangle(img1, point1, point2, CV_RGB(255, 0, 0), 3, 8, 0);
        frame = img1;
        cv::imshow(src_window, img1);
    }

    if (event == CV_EVENT_LBUTTONUP && drag && !select_flag)
    {
        cv::Mat img2 = frame.clone();
        point2 = cv::Point(x, y);
        drag = 0;
        select_flag = 1;
        cv::imshow(src_window, img2);
        frame = img2;
        callback = true;
    }
}

int main()
{
    
   cv::namedWindow(src_window,CV_WINDOW_AUTOSIZE);
   frame = cv::imread("empty.png", CV_LOAD_IMAGE_GRAYSCALE);
    cv::imshow(src_window,frame);
    cv::setMouseCallback(src_window,mouseHandler,0);


    
    
    cout << "Started" << endl;

    neuron* pixels[50][50];
    neuron* outpts[10];
    for(int x = 0; x < 50; x++)
    {
        for(int y = 0; y < 50; y++)
        {
            pixels[x][y] = new neuron();
        }
    }
    for(int x = 0; x < 10; x++)
    {

        outpts[x] = new neuron();

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
    int teachFor = 100;
    int testFor = 10;

    while(true)
    {
        cicle++;
        for(int out = 0; out < 10; out++)
        {
            outpts[out]->value = 0;
        }
        int imgN = (cicle % 50);
        Mat image;
        if(cicle >= teachFor)
        {
            if(cicle >= teachFor+testFor)
            {
                cout << "Use a pointing device to draw in the blank window. Only a single drag is allowed. It may guess wrongly in the first tries with different handwrittings." << endl;
                drag = 0, select_flag = 0;
                callback = false;
                frame = cv::imread("empty.png", CV_LOAD_IMAGE_GRAYSCALE);
                cv::imshow(src_window,frame);
                
                for (;;)
                {
                    if(callback)
                    {
                        if( callback )
                                break;
                        cv::imshow(src_window,frame);
                    }

                    cv::waitKey(30);
                }
                image = frame;
            }
            else
            {
                image = images[imgN];
            }
        }
        else
            image = images[imgN];

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
                        outpts[out]->value += outpts[out]->sinapsis[x][y];
                    }
                }
            }
        }

        for(int out = 0; out < 10; out++)
        {
            cout << out << ": " + std::to_string(outpts[out]->value) << endl;
        }



        int gueesed = -1;
        int maxd = 0;

        for(int out = 0; out < 10; out++)
        {
            if(outpts[out]->value >= maxd)
            {
                gueesed = out;
                maxd = outpts[out]->value;
            }
        }

        namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
        imshow( "Display window", image );                   // Show our image inside it.

        waitKey(30);

        cout << "Neural Network Guess: " << gueesed << " - The correct number is? " << endl;
        string img;
        int correct;

        if(cicle >= teachFor)
        {
            cin >> img;
            correct = atoi(img.c_str());
        }
        else
        {
            img = std::to_string(imgN);
            correct = atoi(img.c_str());
            cout << correct << endl;
        }

        
        //cout << "correct: " << correct << imgN<< endl;

        if(correct != gueesed)
        {
            //cout << "incorrect" << endl;
            for(int x = 0; x < 50; x++)
            {
                for(int y = 0; y < 50; y++)
                {
                    uint pix = image.at<uchar>(x,y);
                    if(pix < 50)
                    {
                        outpts[correct]->sinapsis[x][y] += 1;
                    }
                }
            }
        }

    }

    return 0;
}
