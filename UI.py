import matplotlib.pyplot as plt
import matplotlib

matplotlib.use('TkAgg')  # 切换到 TkAgg 后端
print(matplotlib.get_backend())
#初始化坐标系参数
X_MAX = 10
Y_MAX = 10

# 初始化图形
plt.ion()  # 开启交互模式
fig, ax = plt.subplots()
fig.canvas.toolbar.pan()
# 初始化点和线的数据
x_coords = []
y_coords = []

all_lines_x = []
all_lines_y = []

#绘制空图
ax.set_xlim(0, X_MAX)  # 设置 x 轴范围
ax.set_ylim(0, Y_MAX)  # 设置 y 轴范围
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_title('Dynamic Network Graph')
ax.legend()

#加入新的点
def Add_Point(x, y):
    x_coords.append(x)
    y_coords.append(y)
    ax.scatter(x, y, color='b')  # 绘制点

#加入新的线
def Add_Line(x1, y1, x2, y2):
    all_lines_x.extend([x1, x2, None])  # None 用于断开线段
    all_lines_y.extend([y1, y2, None])
    ax.plot([x1, x2], [y1, y2], 'b-')  # 只绘制新线段

Add_Point(3,5)
plt.pause(0.1)

plt.ioff()
plt.show()