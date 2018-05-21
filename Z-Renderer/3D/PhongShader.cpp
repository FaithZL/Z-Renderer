//
//  BoxShader.cpp
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/19.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#include "PhongShader.hpp"
#include "Canvas.hpp"
#include <algorithm>

void PhongShader::setLight(const Light &light) {
    _light = light;
}

void PhongShader::setMaterial(const Material &material) {
    _material = material;
}

void PhongShader::setAmbient(const Ambient &ambient) {
    _ambient = ambient;
}

VertexOut PhongShader::vs(const Vertex &vertex) const {
    return Shader::vs(vertex);
}

Color PhongShader::getAmbient(const VertexOut &frag) const {
    Color ambient = _ambient.color * _ambient.factor;
    return ambient;
}

Color PhongShader::getDiffuse(const VertexOut &frag) const {
    Vec3 fragPos = frag.posWorld;
    Vec3 normal = frag.normal.getNormalize();
    
    Vec3 ray = (_light.pos - fragPos).getNormalize();
    double cosTheta = ray.dot(normal);
    double diff = max(cosTheta , (double)0.0f);
    Color diffuse = _light.color* _light.factor * diff * _material.diffuseFactor;
    return diffuse;
}

Color PhongShader::getSpecular(const VertexOut &frag) const {
    Vec3 fragPos = frag.posWorld;
    Vec3 normal = frag.normal.getNormalize();
    Vec3 ray = (_light.pos - fragPos).getNormalize();
    Vec3 cameraPos = Camera::getInstance()->getPosition();
    Vec3 viewDir = (cameraPos - fragPos).getNormalize();
    Vec3 reflectDir = (-ray).reflect(normal);
    
    auto spec = pow(max(viewDir.dot(reflectDir), 0.0), _material.shininess);
    Color specular = _light.color * _light.factor * spec * _material.specularFactor;
    return specular;
}

Color PhongShader::fs(const VertexOut &frag) const {
    auto texture = Canvas::getInstance()->getTexture();
    auto fragColor = texture->sample(frag.tex.u, frag.tex.v);
    
    Color ambient = getAmbient(frag);
    
    Color diffuse = getDiffuse(frag);
    
    Color specular = getSpecular(frag);

    return frag.color * (ambient + specular + diffuse);
}







