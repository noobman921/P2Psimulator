from PyQt6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QTextEdit, QScrollArea)
from PyQt6.QtWidgets import QLineEdit

class GUILayout:
    def __init__(self, main_window):
        self.main_window = main_window
        self.setup_main_widget()
        self.setup_plot_area()
        self.setup_control_panel()
        self.setup_input_display()

    def setup_main_widget(self):
        main_widget = QWidget()
        self.main_window.setCentralWidget(main_widget)
        self.main_layout = QVBoxLayout(main_widget)

    def setup_plot_area(self):
        from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
        from matplotlib.figure import Figure
        self.figure = Figure(figsize=(10, 8), dpi=100)
        self.canvas = FigureCanvas(self.figure)
        self.ax = self.figure.add_subplot(111)
        self.main_layout.addWidget(self.canvas)

    def setup_control_panel(self):
        control_panel = QWidget()
        control_layout = QHBoxLayout(control_panel)

        self.btn_start = QPushButton("网络初始化")
        self.btn_start.clicked.connect(self.main_window.start_input_listener)
        control_layout.addWidget(self.btn_start)

        # self.btn_stop = QPushButton("停止监听")
        # self.btn_stop.clicked.connect(self.main_window.stop_input_listener)
        # control_layout.addWidget(self.btn_stop)

        # self.btn_clear = QPushButton("清除图形")
        # self.btn_clear.clicked.connect(self.main_window.clear_plot)
        # control_layout.addWidget(self.btn_clear)
        self.node_exit_input = QLineEdit()
        self.node_exit_input.setPlaceholderText("输入要退出的节点 ID")
        control_layout.addWidget(self.node_exit_input)

        self.btn_exit_node = QPushButton("节点退出")
        self.btn_exit_node.clicked.connect(self.main_window.handle_node_exit)
        control_layout.addWidget(self.btn_exit_node)

        self.btn_efficient = QPushButton("高效P2P布局")
        self.btn_efficient.clicked.connect(self.main_window.apply_efficient_p2p_layout)
        control_layout.addWidget(self.btn_efficient)

        self.btn_restore = QPushButton("恢复原始连接")
        self.btn_restore.clicked.connect(self.main_window.restore_original_arrows)
        control_layout.addWidget(self.btn_restore)

        self.btn_reset_view = QPushButton("重置视图")
        self.btn_reset_view.clicked.connect(self.main_window.reset_view)
        control_layout.addWidget(self.btn_reset_view)

        self.btn_simulate_video = QPushButton("模拟视频数据流")
        self.btn_simulate_video.clicked.connect(self.main_window.start_video_simulation)
        control_layout.addWidget(self.btn_simulate_video)

        self.main_layout.addWidget(control_panel)

    def setup_input_display(self):
        self.input_display = QTextEdit()
        self.input_display.setReadOnly(True)
        scroll_area = QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setWidget(self.input_display)
        self.main_layout.addWidget(scroll_area)
