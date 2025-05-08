from PyQt6.QtCore import Qt

class EventHandler:
    def __init__(self, main_window):
        self.main_window = main_window
        self.press = None
        self.zoom_factor = 1.2
        self.current_zoom = 1.0
        self.setup_mouse_events()

    def setup_mouse_events(self):
        self.main_window.gui_layout.canvas.mpl_connect('scroll_event', self.on_scroll)
        self.main_window.gui_layout.canvas.mpl_connect('button_press_event', self.on_press)
        self.main_window.gui_layout.canvas.mpl_connect('button_release_event', self.on_release)
        self.main_window.gui_layout.canvas.mpl_connect('motion_notify_event', self.on_motion)

    def on_scroll(self, event):
        if not event.inaxes:
            return

        xdata = event.xdata
        ydata = event.ydata

        if event.button == 'up':
            scale_factor = 1 / self.zoom_factor
            self.current_zoom /= self.zoom_factor
        elif event.button == 'down':
            scale_factor = self.zoom_factor
            self.current_zoom *= self.zoom_factor
        else:
            return

        xlim = self.main_window.gui_layout.ax.get_xlim()
        ylim = self.main_window.gui_layout.ax.get_ylim()

        new_xlim = [
            xdata - (xdata - xlim[0]) * scale_factor,
            xdata + (xlim[1] - xdata) * scale_factor
        ]

        new_ylim = [
            ydata - (ydata - ylim[0]) * scale_factor,
            ydata + (ylim[1] - ydata) * scale_factor
        ]

        self.main_window.gui_layout.ax.set_xlim(new_xlim)
        self.main_window.gui_layout.ax.set_ylim(new_ylim)
        self.main_window.gui_layout.canvas.draw()

    def on_press(self, event):
        if event.inaxes and event.button == Qt.MouseButton.LeftButton:
            self.press = (self.main_window.gui_layout.ax.get_xlim(), self.main_window.gui_layout.ax.get_ylim())

    def on_release(self, event):
        self.press = None

    def on_motion(self, event):
        if self.press is None or not event.inaxes or event.xdata is None or event.ydata is None:
            return

        xlim_prev, ylim_prev = self.press
        xdata_curr, ydata_curr = event.xdata, event.ydata
        xdata_prev = sum(xlim_prev) / 2
        ydata_prev = sum(ylim_prev) / 2

        dx = xdata_prev - xdata_curr
        dy = ydata_prev - ydata_curr

        new_xlim = (xlim_prev[0] + dx, xlim_prev[1] + dx)
        new_ylim = (ylim_prev[0] + dy, ylim_prev[1] + dy)

        self.main_window.gui_layout.ax.set_xlim(new_xlim)
        self.main_window.gui_layout.ax.set_ylim(new_ylim)
        self.main_window.gui_layout.canvas.draw()

    def reset_view(self):
        self.current_zoom = 1.0
        self.main_window.gui_layout.ax.set_xlim(self.main_window.plot_handler.xlim)
        self.main_window.gui_layout.ax.set_ylim(self.main_window.plot_handler.ylim)
        self.main_window.gui_layout.canvas.draw()
        self.main_window.gui_layout.input_display.append(">>> 视图已重置")
