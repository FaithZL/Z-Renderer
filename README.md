# Z-Renderer
a tiny software rasterize renderer 

渲染流程

处理顶点，在vertex shader里完成
    物体坐标系转换至世界坐标系转换到相机坐标系
    在经过透视投影转换到cvv
输出顶点

处理输出的顶点输出坐标
    空间裁剪
    齐次坐标进行透视除法，转换到标准设备坐标（NDC）
    深度测试
    绘制