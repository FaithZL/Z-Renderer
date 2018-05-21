# Z-Renderer
a tiny software rasterize renderer 
简单的软件光栅化渲染器

采用笛卡尔右手坐标系（与OpenGL一致）
#主要功能以及模块
* 可移动摄像机
* 数学库
* 纹理贴图
* 线框模式
* 简单着色器
* phong着色
* 简单粗暴的CVV裁剪
* 面剔除
* obj模型渲染(使用assimp库解析模型文件)
* 法线修正

#渲染流程
* 处理顶点，在vertex shader里完成
* 物体坐标系转换至世界坐标系转换到相机坐标系
* 在经过透视投影转换到cvv
* 输出顶点
* 处理输出的顶点输出坐标
* 空间裁剪
* 对齐次坐标进行透视除法转换到标准设备坐标（NDC）
* 转换到屏幕坐标
* 深度测试
* 绘制

#效果截图 
 * 简单模型(使用法线修正+phong着色)
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/cow.jpg"简单模型")
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/teapot.jpg"简单模型")
 * 纹理+phong着色
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/phong.jpg"纹理+phong着色")
 * 复杂模型渲染
   ![](https://github.com/FaithZL/Z-Renderer/blob/master/Z-Renderer/res/pic/model.jpg"复杂模型渲染")

