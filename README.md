# Z-Renderer
a tiny software rasterize renderer 

渲染流程

处理顶点，在vertex shader里完成
    物体坐标系转换至世界坐标系转换到相机坐标系
    透视转换输出裁剪空间坐标（cvv）（齐次坐标）
输出顶点坐标

处理输出的顶点输出坐标
    空间裁剪
    齐次坐标进行透视除法，转换到标准设备坐标（NDC）
    深度测试
    绘制