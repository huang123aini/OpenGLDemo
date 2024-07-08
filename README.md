### glViewport

glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
作用:将opengl的位置坐标转换为屏幕坐标，opengl的坐标范围只为(-1,1),因此我们事实上将(-1到1)范围内的坐标映射到(0, 800)和(0, 600).

### glfwSwapBuffers
glfwSwapBuffers函数会交换颜色缓冲.