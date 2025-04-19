import sys
import matplotlib
matplotlib.use('TkAgg')  # 使用Tkinter交互式后端
import matplotlib.pyplot as plt
import numpy as np

plt.ion()  # 启用交互模式
fig, ax = plt.subplots(figsize=(10, 8))
ax.set_xlim(0, 10)
ax.set_ylim(0, 10)
ax.set_title('Dynamic Arrow Network')

points = []  # 存储所有点坐标
arrows = []  # 存储箭头对象

def update_plot():
    """清空并重绘所有元素"""
    ax.clear()
    ax.set_xlim(0, 100000)
    ax.set_ylim(0, 100000)
    
    # 重新绘制所有点
    if points:
        x, y = zip(*points)
        ax.scatter(x, y, color='blue', s=30)
    
    # 重新绘制所有箭头
    for (i, j) in arrows:
        if i < len(points) and j < len(points):
            start = points[i]
            end = points[j]
            dx = end[0] - start[0]
            dy = end[1] - start[1]
            ax.arrow(start[0], start[1], dx, dy, 
                    head_width=0.2, head_length=0.3, 
                    fc='red', ec='black', alpha=0.5)
    
    plt.draw()
    fig.canvas.flush_events()

while True:
    line = sys.stdin.readline().strip()
    if not line or line == "END":
        break
    
    parts = line.split()
    if parts[0] == 'POINTS':
        # 解析点数据：x1 y1 x2 y2 ... 
        coords = list(map(float, parts[1:]))
        points = [(coords[i], coords[i+1]) for i in range(0, len(coords), 2)]
        update_plot()
    
    elif parts[0] == 'ARROWS':
        # 解析连接关系：from1 to1 from2 to2 ...
        arrows = list(map(int, parts[1:]))
        arrows = [(arrows[i], arrows[i+1]) for i in range(0, len(arrows), 2)]
        update_plot()

plt.ioff()
plt.show()  # 保持窗口打开