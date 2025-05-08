from simulation import Simulation
from input_handler import InputHandler
from event_handler import EventHandler
from plot_handler import PlotHandler
from gui_layout import GUILayout
import sys
import math
import heapq
from collections import defaultdict, deque
from PyQt6.QtWidgets import QApplication, QMainWindow
import matplotlib.pyplot as plt
from collections import defaultdict
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

how_to_say=0

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("P2P网络电视模拟")
        self.setGeometry(100, 100, 1000, 800)

        self.gui_layout = GUILayout(self)
        self.plot_handler = PlotHandler(self)
        self.event_handler = EventHandler(self)
        self.input_handler = InputHandler(self)
        self.simulation = Simulation(self)  # 初始化模拟对象
        self.is_first_call = True  # 新增标志位，用于判断是否为首次调用
        
    
    def handle_node_exit(self):
        global how_to_say
        if self.is_first_call:
            self.points = self.input_handler.get_plot_points()
            print(f"初始化时节点坐标: {self.points}")  # 添加调试信息
            self.active_nodes = set(range(len(self.points)))  # 记录活跃节点
            print(f"当前活跃节点: {self.active_nodes}")  # 添加调试信息
            node_id_text = self.gui_layout.node_exit_input.text()
            self.is_first_call = False  # 首次调用后将标志位设为 False
        else:
            node_id_text = self.gui_layout.node_exit_input.text()
        try:
            node_id = int(node_id_text)
            if node_id in self.active_nodes and node_id < len(self.points):
                self.active_nodes.remove(node_id)
                self.update_neighbors_after_exit(node_id)
                self.highlight_exit_node_and_new_connections(node_id)
                self.plot_handler.update_plot()
                self.gui_layout.input_display.append(f">>> 节点 {node_id} 已退出")
            else:
                self.gui_layout.input_display.append(">>> 无效的节点 ID 或节点已退出")
        except ValueError:
            self.gui_layout.input_display.append(">>> 请输入有效的整数节点 ID")

    def update_neighbors_after_exit(self, exited_node):
        max_neighbors = 5
        points = self.points
        distance_matrix = [[0]*len(points) for _ in range(len(points))]

        for i in self.active_nodes:
            for j in range(i+1, len(points)):
                if j in self.active_nodes:
                    dx = points[i][0] - points[j][0]
                    dy = points[i][1] - points[j][1]
                    distance = math.sqrt(dx*dx + dy*dy)
                    distance_matrix[i][j] = distance
                    distance_matrix[j][i] = distance

        neighbor_counts = defaultdict(int)
        new_arrows = [(a, b) for (a, b) in self.plot_handler.arrows if a in self.active_nodes and b in self.active_nodes]

        for arrow in new_arrows:
            neighbor_counts[arrow[0]] += 1
            neighbor_counts[arrow[1]] += 1

        affected_neighbors = set([a for (a, b) in self.plot_handler.arrows if b == exited_node] + 
                                [b for (a, b) in self.plot_handler.arrows if a == exited_node])

        for neighbor in affected_neighbors:
            if neighbor in self.active_nodes:
                candidates = []
                for j in self.active_nodes:
                    if j != neighbor and neighbor_counts[j] < max_neighbors and (neighbor, j) not in new_arrows and (j, neighbor) not in new_arrows:
                        candidates.append((distance_matrix[neighbor][j], j))
                candidates.sort()

                needed = max_neighbors - neighbor_counts[neighbor]
                for dist, j in candidates[:needed]:
                    new_arrows.append((neighbor, j))
                    neighbor_counts[neighbor] += 1
                    neighbor_counts[j] += 1
        # 记录原始箭头
        self.original_arrows = set(self.plot_handler.arrows)
        self.plot_handler.arrows = new_arrows

    def highlight_exit_node_and_new_connections(self, exited_node):
        
        # 退出节点后更新的箭头
        new_arrows = set(self.plot_handler.arrows)
        # 新增的箭头
        added_arrows = new_arrows - self.original_arrows
 
        # 高亮退出节点
        self.plot_handler.highlighted_nodes = [exited_node]
        # 高亮新增连线
        self.plot_handler.highlighted_arrows = list(added_arrows)

    def start_input_listener(self):
        self.input_handler.start_input_listener()

    def start_video_simulation(self):
        simulation_duration = 60  # 模拟时长 60 秒
        # 调用 Simulation 类的清空方法
        self.simulation.clear_client_caches()
        self.gui_layout.input_display.append(">>> 已清空所有点的数据块")
        self.simulation.run(simulation_duration)

    def stop_input_listener(self):
        self.input_handler.stop_input_listener()

    def clear_plot(self):
        self.plot_handler.clear_plot()

    def restore_original_arrows(self):
        self.plot_handler.restore_original_arrows()

    def reset_view(self):
        self.event_handler.reset_view()


    def apply_efficient_p2p_layout(self):
        # 这里可以将布局逻辑提取到单独的模块中
        if not self.plot_handler.points:
            self.gui_layout.input_display.append(">>> 没有节点数据，无法应用高效P2P布局")
            return

        server_index = 0
        max_neighbors = 5
        num_nodes = len(self.plot_handler.points)
        distance_matrix = [[0]*num_nodes for _ in range(num_nodes)]

        for i in range(num_nodes):
            for j in range(i+1, num_nodes):
                dx = self.plot_handler.points[i][0] - \
                    self.plot_handler.points[j][0]
                dy = self.plot_handler.points[i][1] - \
                    self.plot_handler.points[j][1]
                distance = math.sqrt(dx*dx + dy*dy)
                distance_matrix[i][j] = distance
                distance_matrix[j][i] = distance

        new_arrows = []
        neighbor_counts = defaultdict(int)

        server_distances = [(distance_matrix[server_index][i], i)
                            for i in range(num_nodes) if i != server_index]
        server_distances.sort()

        for _, node in server_distances[:max_neighbors]:
            new_arrows.append((server_index, node))
            neighbor_counts[server_index] += 1
            neighbor_counts[node] += 1

        for i in range(1, num_nodes):
            if neighbor_counts.get(i, 0) >= max_neighbors:
                continue

            candidates = []
            for j in range(num_nodes):
                if j == i or neighbor_counts.get(j, 0) >= max_neighbors:
                    continue
                if (i, j) in new_arrows or (j, i) in new_arrows:
                    continue
                candidates.append((distance_matrix[i][j], j))

            candidates.sort()
            needed = max_neighbors - neighbor_counts.get(i, 0)

            for dist, j in candidates[:needed]:
                if neighbor_counts.get(j, 0) < max_neighbors:
                    new_arrows.append((i, j))
                    neighbor_counts[i] += 1
                    neighbor_counts[j] += 1
                    if neighbor_counts.get(i, 0) >= max_neighbors:
                        break

        visited = set()
        queue = deque([server_index])

        while queue:
            node = queue.popleft()
            if node in visited:
                continue
            visited.add(node)

            for (a, b) in new_arrows:
                if a == node and b not in visited:
                    queue.append(b)
                elif b == node and a not in visited:
                    queue.append(a)

        if len(visited) < num_nodes:
            for i in range(num_nodes):
                if i not in visited:
                    new_arrows.append((server_index, i))
                    neighbor_counts[server_index] += 1
                    neighbor_counts[i] += 1
                    visited.add(i)

        final_arrows = []
        neighbor_counts_final = defaultdict(int)

        server_connections = [(a, b) for (
            a, b) in new_arrows if a == server_index or b == server_index]
        for a, b in server_connections:
            if neighbor_counts_final.get(a, 0) < max_neighbors and neighbor_counts_final.get(b, 0) < max_neighbors:
                final_arrows.append((a, b))
                neighbor_counts_final[a] += 1
                neighbor_counts_final[b] += 1

        other_connections = [(a, b) for (
            a, b) in new_arrows if a != server_index and b != server_index]
        other_connections.sort(key=lambda x: distance_matrix[x[0]][x[1]])

        for a, b in other_connections:
            if neighbor_counts_final.get(a, 0) < max_neighbors and neighbor_counts_final.get(b, 0) < max_neighbors:
                final_arrows.append((a, b))
                neighbor_counts_final[a] += 1
                neighbor_counts_final[b] += 1

        self.plot_handler.arrows = final_arrows
        self.plot_handler.update_plot()

        avg_neighbors = sum(neighbor_counts_final.values()) / num_nodes
        self.gui_layout.input_display.append(
            f">>> 已应用高效P2P布局(最大{max_neighbors}邻居)")
        self.gui_layout.input_display.append(f">>> 平均邻居数: {avg_neighbors:.2f}")
        self.gui_layout.input_display.append(f">>> 总连接数: {len(final_arrows)}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()

    if sys.stdin.isatty():
        print("警告: 未检测到标准输入流，请通过管道输入数据")

    sys.exit(app.exec())
