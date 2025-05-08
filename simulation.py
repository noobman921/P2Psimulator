from collections import deque, defaultdict
import heapq
import itertools
import math
from input_handler import InputHandler

class Simulation:
    def __init__(self, main_window, M=5, N=200):
        self.main_window = main_window
        self.M = M  # 连续播放所需的分块数
        self.N = N  # 客户端缓存大小
        self.time = 0
        self.event_queue = []  # 事件队列，使用优先队列
        self.server_block_queue = deque()  # 服务器生成的视频块队列
        self.client_caches = defaultdict(deque)  # 客户端缓存
        self.client_play_start_times = defaultdict(float)  # 客户端开始连续播放的时间
        self.client_play_total_times = defaultdict(float)  # 客户端连续播放的总时间
        self.client_last_play_time = defaultdict(float)  # 客户端上次播放的时间
        self.client_playing_status = defaultdict(bool)  # 客户端播放状态
        self.client_block_arrival_times = defaultdict(
            lambda: defaultdict(float))  # 记录每个客户端每个数据块的到达时间
        self.block_generation_times = {}  # 记录每个数据块的生成时间
        self.counter = itertools.count()  # 用于生成唯一标识符
        self.client_next_request = defaultdict(lambda: 1)  # 记录每个客户端下次请求的视频块 ID，初始为 1
        # self.input_handler = InputHandler(self.main_window)
        # 初始化服务器生成视频块事件
        self.schedule_event(0, self.server_generate_block)

    def schedule_event(self, time, event_func):
        unique_id = next(self.counter)  # 生成唯一标识符
        # 将唯一标识符加入元组
        heapq.heappush(self.event_queue, (time, unique_id, event_func))

    def get_transfer_rate(self, node1, node2):
        points = self.main_window.plot_handler.points
        x1, y1 = points[node1]
        x2, y2 = points[node2]
        distance = math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)
        # 传输速率和距离成反比，范围在 [20, 100] Kbyte/s
        max_rate = 100
        min_rate = 20
        rate = max(min_rate, min(max_rate, max_rate / (distance + 1e-6)))
        return rate

    def server_generate_block(self):
        # 服务器每秒生成 30 个视频块
        generated_blocks = []
        for _ in range(30):
            block_id = len(self.server_block_queue) + 1
            self.server_block_queue.append(block_id)
            self.block_generation_times[block_id] = self.time
            generated_blocks.append(block_id)
        self.time += 1
        self.main_window.gui_layout.input_display.append(
            f">>> 时间 {self.time}s: 服务器生成视频块 {generated_blocks}"
        )
        self.schedule_event(self.time, self.server_generate_block)

        # 安排客户端请求数据事件
        for client_id in range(1, 101):
            self.schedule_event(self.time, lambda c=client_id: self.client_request_blocks(c))

    def client_request_blocks(self, client_id):
        self.input_handler = InputHandler(self.main_window)
        client_cache = self.client_caches[client_id]
        self.arrows1 = self.input_handler.get_plot_arrows()
        # 打印 self.arrows1 的值
        # self.main_window.gui_layout.input_display.append(
        #     f">>> 时间 {self.time}s: 客户端 {client_id} 获取的箭头信息 self.arrows1: {self.arrows1}"
        # )
        neighbor_ids = [j for (i, j) in self.arrows1 if i == client_id or j == client_id]
        #neighbor_ids = [n for n in neighbor_ids if n != client_id]

        if not neighbor_ids:
            self.main_window.gui_layout.input_display.append(
                f">>> 时间 {self.time}s: 客户端 {client_id} 没有邻居节点，无法请求数据"
            )
            return  # 没有邻居节点，直接返回
        next_request = self.client_next_request[client_id]
        self.main_window.gui_layout.input_display.append(
                        f">>> 时间 {self.time}s: 客户端 {client_id} 有邻居节点，可以请求数据"
                    )
        # 查找邻居节点拥有的数据块
        available_blocks = defaultdict(list)
        for neighbor_id in neighbor_ids:
            if neighbor_id == 0:  # 假设服务器的 ID 为 0
                self.main_window.gui_layout.input_display.append(
                        f">>> 邻居为服务端"
                    )
                # 从服务器的队列中查找可用数据块
                for block_id in self.server_block_queue:
                    if block_id >= next_request and block_id not in client_cache:
                        available_blocks[block_id].append(neighbor_id)
                        self.main_window.gui_layout.input_display.append(
                        f">>> 缓存服务端成功"
                    )
            else:
                # self.main_window.gui_layout.input_display.append(
                #         f">>> 邻居为客户端 {neighbor_id}"
                #     )
                # 从客户端邻居节点的缓存中查找可用数据块
                for block_id in self.client_caches[neighbor_id]:
                    if block_id >= next_request and block_id not in client_cache:
                        available_blocks[block_id].append(neighbor_id)
                        self.main_window.gui_layout.input_display.append(
                        f">>> 缓存邻居成功" 
                        )


        # 按块 ID 排序请求，从最小的视频块开始请求
        for block_id in sorted(available_blocks.keys()):
            neighbors = available_blocks[block_id]
            # 选择传输速率最快的邻居
            best_neighbor = max(neighbors, key=lambda n: self.get_transfer_rate(client_id, n))
            transfer_rate = self.get_transfer_rate(client_id, best_neighbor)
            transfer_time = 1 / transfer_rate  # 每个数据块 1Kbyte
            receive_time = self.time + transfer_time
            self.schedule_event(receive_time,
                                lambda c=client_id, b=block_id: self.client_receive_block(c, b))
            self.client_next_request[client_id] = block_id + 1  # 更新下次请求的视频块 ID
            break  # 每次只请求一个视频块

        # 检测是否可以连续播放
        self.check_playability(client_id)

    def client_receive_block(self, client_id, block_id):
        client_cache = self.client_caches[client_id]
        if len(client_cache) >= self.N:
            client_cache.popleft()
        client_cache.append(block_id)
        self.client_block_arrival_times[client_id][block_id] = self.time
        self.main_window.gui_layout.input_display.append(
            f">>> 时间 {self.time}s: 客户端 {client_id} 收到视频块 {block_id}"
        )
        self.check_playability(client_id)

    def check_playability(self, client_id):
        client_cache = self.client_caches[client_id]
        sorted_cache = sorted(client_cache)

        can_play = False
        for i in range(len(sorted_cache) - self.M + 1):
            if sorted_cache[i + self.M - 1] - sorted_cache[i] == self.M - 1:
                # 可以连续播放
                can_play = True
                if not self.client_playing_status[client_id]:
                    self.client_play_start_times[client_id] = self.time
                    self.main_window.gui_layout.input_display.append(
                        f">>> 时间 {self.time}s: 客户端 {client_id} 开始连续播放"
                    )
                    # 计算播放延迟
                    first_block = sorted_cache[i]
                    generation_time = self.block_generation_times[first_block]
                    play_delay = self.time - generation_time
                    self.main_window.gui_layout.input_display.append(
                        f">>> 时间 {self.time}s: 客户端 {client_id} 播放数据块 {first_block} 的延迟为 {play_delay:.2f}s"
                    )
                self.client_last_play_time[client_id] = self.time
                self.client_playing_status[client_id] = True
                break

        if not can_play and self.client_playing_status[client_id]:
            # 停止连续播放，计算播放时间
            play_duration = self.time - self.client_play_start_times[client_id]
            self.client_play_total_times[client_id] += play_duration
            self.client_play_start_times[client_id] = 0
            self.client_playing_status[client_id] = False
            self.main_window.gui_layout.input_display.append(
                f">>> 时间 {self.time}s: 客户端 {client_id} 停止连续播放"
            )

        # 更新节点状态可视化
        self.main_window.plot_handler.update_node_status(client_id, can_play)

    def run(self, duration):
        #self.input_handler = InputHandler(self.main_window)
        update_interval = 1  # 每 1 秒更新一次 GUI
        last_update_time = 0
        while self.event_queue and self.time < duration:
            try:
                event = heapq.heappop(self.event_queue)
                if len(event) == 2:  # 兼容旧格式
                    next_time, event_func = event
                else:
                    next_time, _, event_func = event
                self.time = next_time
                event_func()

                if self.time - last_update_time >= update_interval:
                    last_update_time = self.time
                    # 不再在模拟线程中直接更新 GUI，通过信号在主线程更新
                    # self.main_window.plot_handler.update_plot()
            except Exception as e:
                error_msg = f"时间 {self.time}s 模拟事件执行出错: {str(e)}"
                self.main_window.gui_layout.input_display.append(error_msg)
                print(error_msg)  # 同时在控制台输出错误信息

        # 计算最终的流畅度
        for client_id in range(1, len(self.main_window.plot_handler.points)):
            if self.client_playing_status[client_id]:
                play_duration = self.time - self.client_play_start_times[client_id]
                self.client_play_total_times[client_id] += play_duration
            if duration > 0:
                fluency = self.client_play_total_times[client_id] / duration
            else:
                fluency = 0  # 避免除零错误
            self.main_window.gui_layout.input_display.append(
                f">>> 模拟结束: 客户端 {client_id} 的播放流畅度: {fluency:.2f}"
            )
    def clear_client_caches(self):
        """
        清空所有客户端的数据块缓存
        """
        self.client_caches.clear()
        self.client_block_arrival_times.clear()
        self.client_play_start_times.clear()
        self.client_play_total_times.clear()
        self.client_last_play_time.clear()
        self.client_playing_status.clear()
        self.client_next_request = defaultdict(lambda: 1)
        self.server_block_queue.clear()
        self.block_generation_times.clear()
        self.event_queue = []
        self.schedule_event(0, self.server_generate_block)