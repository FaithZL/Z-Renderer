//
//  fileUtil.m
//  Z-Renderer
//
//  Created by SATAN_Z on 2018/5/16.
//  Copyright © 2018年 SATAN_Z. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "fileUtil.hpp"

const char* getFilePath(const char* name, const char* type) {
    NSString* filePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:name]
                                                         ofType:[NSString stringWithUTF8String:type]];
    return [filePath UTF8String];
}

std::string getFullPath(const std::string &fileName) {
    NSString* fname = [NSString stringWithCString:fileName.c_str() encoding:NSUTF8StringEncoding];
    NSString* path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fname];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}
