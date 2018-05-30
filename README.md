# Z-Renderer
a tiny software rasterize renderer 
简单的软件光栅化渲染器
QQ:249002031(新手小白一枚，但是非常热爱图形学，有兴趣加我QQ，一起研究图形学)

采用笛卡尔右手坐标系（与OpenGL一致）
#主要功能以及模块
* 可移动摄像机
* 数学库
* 纹理贴图
* 线框模式
* 顶点着色器跟片段着色器
* phong着色
* CVV裁剪（六个平面）
* 天空盒子
* 背面剔除
* obj模型渲染(使用assimp库解析模型文件)
* 法线生成（有些模型的法线不正确或没有法线）

#渲染流程
* 处理顶点，在vertex shader里完成
* 物体坐标系转换至世界坐标系转换到相机坐标系
* 在经过透视投影转换到cvv
* 输出顶点
* 处理输出的顶点输出坐标
* 空间裁剪
* 对齐次坐标进行透视除法转换到标准设备坐标（NDC）
* 通过1/z（z为相机空间纵坐标）插值求得每个片段z值
* 深度测试
* 通过深度测试的片段以执行片段着色器输出颜色
* 写入颜色缓冲

#效果截图 
 * 简单模型(使用生成法线+phong着色)
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/cow.jpg)
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/teapot.jpg)
 * 纹理+phong着色
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/phong.jpg)
 * skyBox
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/skyBoxDemo.jpg)   
 * CVV六面裁剪，线框模式
    ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/cvv3.jpeg)
    ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/cvv.jpeg)
    ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/cvvFill.jpeg)
 * 复杂模型渲染
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/model.jpg)

