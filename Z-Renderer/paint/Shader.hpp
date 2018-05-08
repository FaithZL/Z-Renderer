//
//  Shader.hpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/4/23.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "Vertex.hpp"
#include "Mat4.hpp"
#include "Ref.hpp"

class Shader : public Ref {
public:
    Shader():
    _model(Mat4::identity()),
    _view(Mat4::identity()),
    _projection(Mat4::identity()) {
        updateMvp();
        updateMv();
    }
    
    virtual ~Shader() {
        
    }
    
    virtual VertexOut vs(const Vertex &vert) const;
    
    virtual VertexOut fs(const VertexOut &vert) const;
    
    virtual void setMvp(const Mat4 &m , const Mat4 &v , const Mat4 &p) {
        _model = m;
        _view = v;
        _projection = p;
        updateMv();
        updateMvp();
    }
    
    virtual void setModelMat(const Mat4 &mat) {
        _model = mat;
        updateMv();
        updateMvp();
    }
    
    virtual Mat4 getModelMat() const {
        return _model;
    }
    
    virtual void setViewMat(const Mat4 &mat) {
        _view = mat;
        updateMv();
        updateMvp();
    }
    
    virtual Mat4 getViewMat() const {
        return _view;
    }
    
    virtual void setProjectionMat(const Mat4 &mat) {
        _projection = mat;
        updateMvp();
    }
    
    virtual Mat4 getProjectionMat() const {
        return _projection;
    }
    
    virtual Mat4 getMv() const {
        return _mv;
    }
    
    virtual Mat4 getMvp() const {
        return _mvp;
    }
    
protected:
    
    virtual void updateMv() {
        _mv = _model * _view;
    }
    
    virtual void updateMvp() {
        _mvp = _model * _view * _projection;
    }
    
    Mat4 _model;
    Mat4 _view;
    Mat4 _projection;
    
    Mat4 _mv;
    
    Mat4 _mvp;
    
};

#endif /* Shader_hpp */









