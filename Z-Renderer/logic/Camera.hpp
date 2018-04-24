//
//  Camera.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/24.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Mat4.hpp"

class Camera : public Node {
    
public:
    
    Camera();
    virtual ~Camera();
    
    void init();
    
protected:
    
};

#endif /* Camera_hpp */
