import sys
from PyQt6.QtCore import QTimer

class InputHandler:
    def __init__(self, main_window):
        self.main_window = main_window
        self.input_timer = QTimer()
        self.input_timer.timeout.connect(self.check_stdin)
        self.input_lines = []

    def start_input_listener(self):
        self.input_timer.start(100)
        self.main_window.gui_layout.input_display.append(">>> 开始监听标准输入...")

    def stop_input_listener(self):
        self.input_timer.stop()
        self.main_window.gui_layout.input_display.append(">>> 已停止监听输入")

    def check_stdin(self):
        while True:
            line = sys.stdin.readline().strip()
            if not line:
                break

            self.process_input_line(line)

    def process_input_line(self, line):
        self.main_window.gui_layout.input_display.append(f"收到输入: {line}")

        if line == "END":
            #self.input_timer.stop()
            #self.main_window.gui_layout.input_display.append(">>> 收到END指令，停止监听")
            return

        parts = line.split()
        if not parts:
            return

        if parts[0] == 'POINTS':
            coords = list(map(float, parts[1:]))
            try:
                self.main_window.plot_handler.points = [(coords[i], coords[i+1]) for i in range(0, len(coords), 2)]
                print("POINTS 指令处理后，points 内容:", self.main_window.plot_handler.points)  # 调试信息
                self.main_window.gui_layout.input_display.append(">>> 执行 POINTS 指令后，节点数量: {}".format(len(self.main_window.plot_handler.points)))
            except Exception as e:
                print("处理 POINTS 指令时出错:", e)  # 打印错误信息
                self.main_window.gui_layout.input_display.append(">>> 处理 POINTS 指令时出错，请检查日志")
            self.main_window.plot_handler.update_plot()
        elif parts[0] == 'ARROWS':
            arrows = list(map(int, parts[1:]))
            self.main_window.plot_handler.arrows = [(arrows[i], arrows[i+1]) for i in range(0, len(arrows), 2)]
            self.main_window.plot_handler.original_arrows = self.main_window.plot_handler.arrows.copy()
            self.main_window.gui_layout.input_display.append(">>> 执行 POINTS 指令后，节点数量: {}".format(len(self.main_window.plot_handler.points)))
            self.main_window.plot_handler.update_plot()

    def get_plot_points(self):
        return self.main_window.plot_handler.points
    
    def get_plot_arrows(self):
        return self.main_window.plot_handler.arrows
