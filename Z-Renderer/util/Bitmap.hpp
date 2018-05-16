//
//  Bitmap.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/15.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Bitmap_hpp
#define Bitmap_hpp

#include <stdio.h>
#include <string>
#include "stb_image/stb_image.h"

using namespace std;

class Bitmap {

public:
    
    enum Format {
        Format_Grayscale = 1, /**< one channel: grayscale */
        Format_GrayscaleAlpha = 2, /**< two channels: grayscale and alpha */
        Format_RGB = 3, /**< three channels: red, green, blue */
        Format_RGBA = 4 /**< four channels: red, green, blue, alpha */
    };
    
    Bitmap();
    
    Bitmap(const string &fileName);
    
    Bitmap(const Bitmap &other);
    
    Bitmap & operator = (const Bitmap &other);
    
    ~Bitmap();
    
//    static Bitmap * create(const string &fileName);
    
    void init(int width , int height , Format format ,unsigned char * pixel);
    
protected:
    
    string _path;
    
    Format _format;
    
    unsigned char * _pixels = nullptr;
    
    int _width;
    
    int _height;
};

#endif /* Bitmap_hpp */
