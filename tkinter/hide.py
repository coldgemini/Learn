import tkinter as tk

root = tk.Tk()
button = tk.Button(root, text="Button", command=root.destroy)
button.pack(padx=20, pady=20)
button0 = tk.Button(root, text="show", command=button.pack)
button0.pack(padx=20, pady=20)
button1 = tk.Button(root, text="hide", command=button.pack_forget)
button1.pack(padx=20, pady=20)
root.mainloop()
