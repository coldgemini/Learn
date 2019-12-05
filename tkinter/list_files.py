import tkinter as tk
import pyperclip
import pysftp
import os


class SettingFrame(tk.LabelFrame):
    def __init__(self, master, label):
        super().__init__(master, text=label)
        self.l_server = tk.Label(self, text="server ip: ")
        self.l_server.grid(row=0, column=0)
        self.e_server = tk.Entry(self)
        self.e_server_str = "47.103.101.41"
        self.e_server.insert(tk.END, self.e_server_str)
        self.e_server.grid(row=0, column=1)

        self.l_port = tk.Label(self, text="port num: ")
        self.l_port.grid(row=1, column=0)
        self.e_port = tk.Entry(self)
        self.e_port_str = "1080"
        self.e_port.insert(tk.END, self.e_port_str)
        self.e_port.grid(row=1, column=1)

        self.l_user_name = tk.Label(self, text="user name: ")
        self.l_user_name.grid(row=2, column=0)
        self.e_user_name = tk.Entry(self)
        self.e_user_name_str = "zhouxiangyong"
        self.e_user_name.insert(tk.END, self.e_user_name_str)
        self.e_user_name.grid(row=2, column=1)

        self.l_password = tk.Label(self, text="password : ")
        self.l_password.grid(row=3, column=0)
        self.e_password = tk.Entry(self)
        self.e_password_str = "password"
        self.e_password.insert(tk.END, self.e_password_str)
        self.e_password.grid(row=3, column=1)


class DirFrame(tk.LabelFrame):
    def __init__(self, master, label):
        super().__init__(master, text=label)
        self.l_server_dir = tk.Label(self, text="server dir: ")
        self.l_server_dir.grid(row=0, column=0)
        self.e_server_dir = tk.Entry(self, width=80)
        self.e_server_dir_str = "/data2/home/zhouxiangyong/Workspace/Dev/AortaSlice/data/aorta_extract_data1_fxc"
        self.e_server_dir.insert(tk.END, self.e_server_dir_str)
        self.e_server_dir.grid(row=0, column=1)

        self.l_local_dir0 = tk.Label(self, text="local dir 0: ")
        self.l_local_dir0.grid(row=1, column=0)
        self.e_local_dir0 = tk.Entry(self, width=80)
        self.e_local_dir0_str = "/home/xiang/mnt/Workspace/Dev/AortaSlice/data/aorta_extract_data1_fxc"
        self.e_local_dir0.insert(tk.END, self.e_local_dir0_str)
        self.e_local_dir0.grid(row=1, column=1)

        self.l_local_dir1 = tk.Label(self, text="local dir 1: ")
        self.l_local_dir1.grid(row=2, column=0)
        self.e_local_dir1 = tk.Entry(self, width=80)
        self.e_local_dir1_str = "/home/xiang/mnt/Workspace/Dev/AortaSlice/data/aorta_extract_data1_fxc"
        self.e_local_dir1.insert(tk.END, self.e_local_dir1_str)
        self.e_local_dir1.grid(row=2, column=1)


class LeftFrame(tk.Frame):
    def __init__(self, master, root):
        super().__init__(master)
        self.root = root
        self.setting_frame = SettingFrame(self, "Setting")
        self.setting_frame.pack()
        self.dir_frame = DirFrame(self, "Directories")
        self.dir_frame.pack()
        self.btn_close = tk.Button(self, text="Get List", command=root._get_list)
        self.btn_close.pack()


class ListFrame(tk.LabelFrame):
    def __init__(self, master, label, root):
        super().__init__(master, text=label)
        self.list = tk.Listbox(self, width=80)
        self.scroll = tk.Scrollbar(self, orient=tk.VERTICAL, command=self.list.yview)
        self.list.config(yscrollcommand=self.scroll.set)
        self.list.pack(side=tk.LEFT)
        self.scroll.pack(side=tk.LEFT, fill=tk.Y)
        self.root = root

    def pop_selection(self):
        index = self.list.curselection()
        if index:
            value = self.list.get(index)
            self.list.delete(index)
            return value

    def insert_item(self, item):
        self.list.insert(tk.END, item)

    def go_up(self):
        cur = self.list.curselection()[0]
        next = cur - 1
        self.list.select_clear(0, tk.END)
        self.list.select_set(next)
        self.list.see(next)
        file_name = self.root._file_list[next]
        e_local_dir0 = self.root.frame_left.dir_frame.e_local_dir0
        local_dir0_str = e_local_dir0.get()
        e_local_dir1 = self.root.frame_left.dir_frame.e_local_dir1
        local_dir1_str = e_local_dir1.get()

        m_local_text = os.path.join(local_dir0_str, file_name)
        m_local = self.root.frame_out.m_output_dir
        m_local.config(text=m_local_text)
        self.root.frame_out.m_output_dir_text = m_local_text

        m_local1_text = os.path.join(local_dir1_str, file_name)
        m_local1 = self.root.frame_out.m_output_dir1
        m_local1.config(text=m_local1_text)
        self.root.frame_out.m_output_dir1_text = m_local1_text

    def go_down(self):
        cur = self.list.curselection()[0]
        print(cur)
        next = cur + 1
        self.list.select_clear(0, tk.END)
        self.list.select_set(next)
        self.list.see(next)
        file_name = self.root._file_list[next]
        e_local_dir0 = self.root.frame_left.dir_frame.e_local_dir0
        local_dir0_str = e_local_dir0.get()
        e_local_dir1 = self.root.frame_left.dir_frame.e_local_dir1
        local_dir1_str = e_local_dir1.get()

        m_local_text = os.path.join(local_dir0_str, file_name)
        m_local = self.root.frame_out.m_output_dir
        m_local.config(text=m_local_text)
        self.root.frame_out.m_output_dir_text = m_local_text

        m_local1_text = os.path.join(local_dir1_str, file_name)
        m_local1 = self.root.frame_out.m_output_dir1
        m_local1.config(text=m_local1_text)
        self.root.frame_out.m_output_dir1_text = m_local1_text


class RightFrame(tk.Frame):
    def __init__(self, master, root):
        super().__init__(master)
        self.list_frame = ListFrame(self, "List", root)
        self.list_frame.pack(side=tk.TOP)
        self.btn_close = tk.Button(self, text="up", command=self.list_frame.go_up)
        self.btn_close.pack(side=tk.LEFT)
        self.btn_close = tk.Button(self, text="down", command=self.list_frame.go_down)
        self.btn_close.pack(side=tk.LEFT)


class OutFrame(tk.LabelFrame):
    def __init__(self, master, label, root):
        super().__init__(master, text=label)
        # output 0
        self.l_output_dir = tk.Label(self, text="output dir0: ")
        self.l_output_dir.grid(row=0, column=0)
        self.m_output_dir_text = "message 0"

        def copy_m():
            pyperclip.copy(self.m_output_dir_text)

        self.m_output_dir = tk.Message(self, text=self.m_output_dir_text, bg='lightgreen', width=1200)
        self.m_output_dir.grid(row=0, column=1)
        self.b_output_dir = tk.Button(self, text="copy", command=copy_m)
        self.b_output_dir.grid(row=0, column=2)

        # output 1
        self.l_output_dir1 = tk.Label(self, text="output dir1: ")
        self.l_output_dir1.grid(row=1, column=0)
        self.m_output_dir1_text = "message 1"

        def copy_m1():
            pyperclip.copy(self.m_output_dir1_text)

        self.m_output_dir1 = tk.Message(self, text=self.m_output_dir1_text, bg='lightgreen', width=1200)
        self.m_output_dir1.grid(row=1, column=1)
        self.b_output_dir1 = tk.Button(self, text="copy", command=copy_m1)
        self.b_output_dir1.grid(row=1, column=2)


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.frame_top = tk.Frame(self)
        self.frame_left = LeftFrame(self.frame_top, root=self)
        self.frame_left.pack(side=tk.LEFT, padx=10, pady=10)
        self.frame_right = RightFrame(self.frame_top, root=self)
        self.frame_right.pack(side=tk.RIGHT, padx=10, pady=10)
        self.frame_top.pack()

        self.frame_btm = tk.Frame(self)
        self.btn_close = tk.Button(self.frame_btm, text="close", command=self.destroy)
        self.btn_close.pack(side=tk.LEFT)
        self.frame_out = OutFrame(self.frame_btm, "Output Dir", root=self)
        self.frame_out.pack(side=tk.LEFT)
        self.frame_btm.pack()

        self._init_params()
        self._list_dir()
        self.frame_right.list_frame.list.insert(0, *self._file_list)
        self.frame_right.list_frame.list.select_set(0)
        print(self.frame_right.list_frame.list.curselection())
        print(self.frame_right.list_frame.list.size())

    def _init_params(self):
        self.server_ip = 's108'
        self.port = 10822
        self.username = 'zhouxiangyong'
        self.password = 'zxy201811'
        self.server_dir = '/data2/home/zhouxiangyong/Workspace/Dev/AortaSlice/data/aorta_extract_data1_fxc'

    def _get_gui_input(self):
        self.server_ip = self.frame_left.setting_frame.e_server.get()
        self.port = int(self.frame_left.setting_frame.e_port.get())
        self.username = self.frame_left.setting_frame.e_user_name.get()
        self.password = self.frame_left.setting_frame.e_password.get()
        self.server_dir = self.frame_left.dir_frame.e_server_dir.get()
        print(self.server_ip)
        print(self.server_dir)

    def _update_info(self):
        pass

    def _print_params(self):
        print(self.server_ip)
        print(self.port)
        print(self.username)
        print(self.password)
        print(self.server_dir)

    def _get_list(self):
        print("get_list")
        self._get_gui_input()
        self._update_info()
        self._list_dir()

    def _list_dir(self):
        print("list_dir")
        self._print_params()
        cnopts = pysftp.CnOpts()
        cnopts.hostkeys = None

        with pysftp.Connection(self.server_ip, port=self.port, username=self.username, password=self.password,
                               cnopts=cnopts) as sftp:
            sftp.cwd(self.server_dir)
            self._file_list = sftp.listdir()
        print(self._file_list)
        # self._file_list = ["file1", "file2"]


if __name__ == "__main__":
    app = App()
    app.mainloop()
