//solution by Wsl_F
#include <bits/stdc++.h>
#include "ReadBMP.h"

using namespace std;
#pragma comment(linker, "/STACK:1024000000,1024000000")


typedef long long LL;
typedef unsigned long long uLL;
typedef double dbl;
typedef vector<int> vi;
typedef vector<LL> vL;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef pair<LL,LL> pLL;

#define mp(x,y)  make_pair((x),(y))
#define pb(x)  push_back(x)
#define sqr(x) ((x)*(x))
class ReadBMP
{
    typedef vector<vector<RGBQUAD>> MatrixRGB;

public:
    static MatrixRGB GetRGBMatrix(string fileName, BITMAPINFOHEADER &bmiHeader)
    {
        FILE* pFile = fopen(fileName.c_str(), "rb");

        // считываем заголовок файла
        BITMAPFILEHEADER header __attribute__((unused));
        readFileHeader(header, pFile);

        // считываем заголовок изображения
        readBMPHeader(bmiHeader, pFile);

        // считываем непосредственно само изображение
        MatrixRGB rgb= readPicture(bmiHeader, pFile);
        fclose(pFile);
        return rgb;
    }

    static vi readBlackWhiteBMP(string fileName)
    {
        BITMAPINFOHEADER bmiHeader;
        MatrixRGB rgbRotate= GetRGBMatrix(fileName, bmiHeader);

        MatrixRGB rgb= RotatePicture(rgbRotate, bmiHeader.biWidth, bmiHeader.biHeight);

        vi ans= convertColorMatrixToBWvector(rgb,bmiHeader.biWidth,bmiHeader.biHeight);
        // выводим результат
        printBlackWhite(ans, bmiHeader.biWidth,  bmiHeader.biHeight);

        return ans;
    }

    static void printBlackWhite(vi ans, int width, int height)
    {
        int k= 0;
        for (int i= 0; i<height; i++)
        {
            for (int j= 0; j<width; j++)
                if (ans[k++]) cout<<(char)178;
                else cout<<' ';
            cout<<endl;
        }
    }
private:
    static vi convertColorMatrixToBWvector(MatrixRGB rgb, int width, int height)
    {
        vi ans;
        ans.clear();
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (rgb[i][j].rgbRed + rgb[i][j].rgbGreen + rgb[i][j].rgbBlue > 255*1.5)  ans.pb(0);
                else ans.pb(1);
        return ans;
    }

    static MatrixRGB RotatePicture(MatrixRGB rgbRotated, int width, int height)
    {
        MatrixRGB rgb(height);
        vector<RGBQUAD> tmp;
        tmp.clear();
        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                tmp.pb(rgbRotated[i][j]);

        for (int i= height-1; i>=0; i--)
            reverse(tmp.begin()+width*(i),tmp.begin()+width*(i+1));
        reverse(tmp.begin(),tmp.end());

        for (int i= 0; i<height; i++)
            for (int j= 0; j<width; j++)
                rgb[i].pb(tmp[width*i+j]);

        return rgb;
    }

    static void readFileHeader(BITMAPFILEHEADER &header, FILE* pFile)
    {
        header.bfType      = read_u16(pFile);
        header.bfSize      = read_u32(pFile);
        header.bfReserved1 = read_u16(pFile);
        header.bfReserved2 = read_u16(pFile);
        header.bfOffBits   = read_u32(pFile);
    }

    static void readBMPHeader(BITMAPINFOHEADER &bmiHeader, FILE* pFile)
    {
        bmiHeader.biSize          = read_u32(pFile);
        bmiHeader.biWidth         = read_s32(pFile);
        bmiHeader.biHeight        = read_s32(pFile);
        bmiHeader.biPlanes        = read_u16(pFile);
        bmiHeader.biBitCount      = read_u16(pFile);
        bmiHeader.biCompression   = read_u32(pFile);
        bmiHeader.biSizeImage     = read_u32(pFile);
        bmiHeader.biXPelsPerMeter = read_s32(pFile);
        bmiHeader.biYPelsPerMeter = read_s32(pFile);
        bmiHeader.biClrUsed       = read_u32(pFile);
        bmiHeader.biClrImportant  = read_u32(pFile);
    }

    static MatrixRGB readPicture(BITMAPINFOHEADER bmiHeader, FILE* pFile)
    {
        MatrixRGB rgb(bmiHeader.biWidth);

        RGBQUAD tmp;
        for (int i = 0; i < bmiHeader.biWidth; i++)
        {
            for (int j = 0; j < bmiHeader.biHeight; j++)
            {
                tmp.rgbBlue = getc(pFile);
                tmp.rgbGreen = getc(pFile);
                tmp.rgbRed = getc(pFile);
                rgb[i].pb(tmp);
            }

            // пропускаем последний байт в строке
            getc(pFile);
        }
        return rgb;
    }

    static unsigned short read_u16(FILE *fp)
    {
        unsigned char b0, b1;

        b0 = getc(fp);
        b1 = getc(fp);

        return ((b1 << 8) | b0);
    }

    static unsigned int read_u32(FILE *fp)
    {
        unsigned char b0, b1, b2, b3;

        b0 = getc(fp);
        b1 = getc(fp);
        b2 = getc(fp);
        b3 = getc(fp);

        return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }

    static int read_s32(FILE *fp)
    {
        unsigned char b0, b1, b2, b3;

        b0 = getc(fp);
        b1 = getc(fp);
        b2 = getc(fp);
        b3 = getc(fp);

        return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }

};


int main()
{
    ReadBMP r;
    r.readBlackWhiteBMP("1.bmp");
    return 0;
}
