import matplotlib.pyplot as plt


class PlotHandler:
    def __init__(self, main_window):
        self.main_window = main_window
        self.points = []
        self.arrows = []
        self.original_arrows = []
        self.xlim = [0, 100000]
        self.ylim = [0, 100000]
        self.main_window.gui_layout.ax.set_xlim(self.xlim)
        self.main_window.gui_layout.ax.set_ylim(self.ylim)
        self.main_window.gui_layout.ax.set_title('动态箭头网络')
        self.node_status = {}  # 新增：节点播放状态
        self.highlighted_nodes = []
        self.highlighted_arrows = []

    def update_plot(self):
        xlim1 = self.main_window.gui_layout.ax.get_xlim()
        ylim1 = self.main_window.gui_layout.ax.get_ylim()
        self.main_window.gui_layout.ax.clear()
        self.main_window.gui_layout.ax.set_xlim(xlim1)
        self.main_window.gui_layout.ax.set_ylim(ylim1)
        self.main_window.gui_layout.ax.set_title('动态箭头网络')

        if self.points:
            x, y = zip(*self.points)
            node_colors = ['blue'] * len(self.points)
            node_sizes = [30] * len(self.points)

            for node_id in self.highlighted_nodes:
                node_colors[node_id] = 'red'
                node_sizes[node_id] = 60

            self.main_window.gui_layout.ax.scatter(x, y, color=node_colors, s=node_sizes)
            # 新增：根据节点状态设置颜色
            colors = []
            for i in range(len(self.points)):
                if i == 0:
                    colors.append('red')
                else:
                    colors.append('green' if self.node_status.get(
                        i, False) else 'blue')
            sizes = [50 if i == 0 else 30 for i in range(len(self.points))]
            self.main_window.gui_layout.ax.scatter(x, y, color=colors, s=sizes)

            if len(self.points) > 0:
                self.main_window.gui_layout.ax.scatter(
                    [self.points[0][0]], [self.points[0][1]], color='red', s=50, label='Server')
                self.main_window.gui_layout.ax.text(self.points[0][0], self.points[0][1], 'Server',
                                                    fontsize=9, ha='right', va='bottom')

        for (i, j) in self.arrows:
                if i < len(self.points) and j < len(self.points):
                    start = self.points[i]
                    end = self.points[j]
                    line_color = 'black'
                    line_width = 1
                    if (i, j) in self.highlighted_arrows:
                        line_color = 'green'
                        line_width = 3
                    self.main_window.gui_layout.ax.plot([start[0], end[0]], [start[1], end[1]], 
                                                        color=line_color, alpha=0.5, linewidth=line_width)

        self.main_window.gui_layout.canvas.draw()

    def clear_plot(self):
        self.points = []
        self.arrows = []
        self.original_arrows = []
        self.node_status = {}  # 新增：清除节点状态
        self.update_plot()
        self.main_window.gui_layout.input_display.append(">>> 已清除图形")

    def restore_original_arrows(self):
        if not self.original_arrows:
            self.main_window.gui_layout.input_display.append(">>> 没有保存的原始连接关系")
            return

        self.arrows = self.original_arrows.copy()
        self.update_plot()
        self.main_window.gui_layout.input_display.append(">>> 已恢复原始连接关系")

    def update_node_status(self, client_id, is_playing):
        """
        更新客户端节点的播放状态

        :param client_id: 客户端节点的 ID
        :param is_playing: 是否正在播放
        """
        self.node_status[client_id] = is_playing
