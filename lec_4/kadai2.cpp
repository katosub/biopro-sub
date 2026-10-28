#include"image.hpp"
#include<iostream>
#include<vector>

using namespace std;
typedef unsigned char uchar;

int main(void){
    Image sample("grey.png");
    Image binary_image(sample.w,sample.h,3);
    vector<int> histgram(256,0);

    for(int y=0;y<sample.h;y++){
        uchar v;
        for(int x=0;x<sample.w;x++){
            int sum=0;
            for(int c=0;c<3;c++){   
                sum+=sample.GetPixel(y,x,c); 
            }
            int v=sum/3;
            histgram[v]++;
            
        }    
    }
    
    int total=sample.w*sample.h;
    double totalSum = 0;
    for(int i=0;i<256;i++){
        totalSum+= i*histgram[i];
    }
    double mt=totalSum/total;

    int blacknumber= 0;
    double blackSum= 0;
    double maxVariance=-1;
    int bestT=0;

    for(int t=0;t<=254;t++) {
        blacknumber+=histgram[t];
        blackSum+=t*histgram[t];

        int whitenumber=total-blacknumber;

        if(blacknumber==0 || whitenumber==0){
            continue;
        }

        double blackaverage=blackSum/blacknumber;
        double whiteaverage=(totalSum-blackSum)/whitenumber;

        double numerator=blacknumber*(blackaverage-mt)*(blackaverage-mt)+
                         whitenumber*(whiteaverage-mt)*(whiteaverage-mt);
        if(numerator>maxVariance){
            maxVariance=numerator;
            bestT=t;
        }
    }

    cout<<"閾値t = "<<bestT<< endl;
    
for(int y=0;y<sample.h;y++) {
        for (int x = 0;x<sample.w;x++){
            int sum=0;

            for(int c=0;c<3;c++){
                sum+=sample.GetPixel(y,x,c);
            }

            int v=sum/3;

            uchar binary_value;
            if(v<=bestT){
                binary_value=0;
            }else{
                binary_value=255;
            }

            for (int c=0;c<3;c++){
                binary_image.SetPixel(y,x,c,binary_value);
            }
        }
    }
binary_image.save("binary.png");
return 0; 
}