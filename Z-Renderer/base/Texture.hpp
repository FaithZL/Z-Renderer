//
//  Texture.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/15.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "Ref.hpp"
#include "Color.hpp"
#include "Bitmap.hpp"

class Texture : public Ref {
    
public:
    Color sample(double u , double v) const;
    
    Texture();
    
    ~Texture();
    
    static Texture * create(const std::string &fileName);
    
    inline std::string getFileName() const {
        return _bitmap->getFileName();
    }
    
    inline void setType(const std::string &type) {
        _type = type;
    }
    
    inline std::string getType() const {
        return _type;
    }
    
    inline void bind() const;
    
    inline void unbind() const;
    
protected:
    
    std::string _type;
    
    Bitmap * _bitmap;
};

#endif /* Texture_hpp */
