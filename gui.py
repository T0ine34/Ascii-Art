import tkinter as tk
import tkinterp as tkp
from PIL import Image
from os import path
from utility import new_name, run

#this is the gui of the program, it allow the user to choose options and start the program.
#options are :
# - the input image path (for the moment, only .jpg)
# - the output image path (for the moment, only .jpg) (not implemented yet, disable for the moment)
# - the number of ascii characters in the output image (default 64)
# - the colors mode (can be "bw" for black and white, "color" for color (default), "negative" for negative image, "negative_bw" for negative black and white image)
# - the mode of the output image (can be "ascii", "colored", "both" (default))
# - the relative size of the output image (default 1)
# - the number of colors in the output image ("8", "16", "64", "256" (default), "1024", "4096", "65536") (only for "color" and "negative" mode) (not implemented yet, disable for the moment)

class GUI(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.title("Ascii Art Generator")
        self.geometry("400x200")
        self.resizable(width=False, height=False)
        self.create_widgets()

    def create_widgets(self):
        self.input_label = tk.Label(self, text="Input path :")
        self.input_label.grid(row=0, column=0)
        self.input_path = tk.StringVar()
        self.input_entry = tk.Entry(self, textvariable=self.input_path)
        self.input_entry.grid(row=0, column=1)
        self.input_path.trace_add("write", self.input_path_changed)

        self.width = tk.IntVar()
        self.height = tk.IntVar()

        self.output_label = tk.Label(self, text="Output path :")
        self.output_label.grid(row=1, column=0)
        self.output_entry = tk.Entry(self)
        self.output_entry.grid(row=1, column=1)

        self.ascii_label = tk.Label(self, text="Number of ascii characters (1-64) :")
        self.ascii_label.grid(row=2, column=0)
        self.ascii_entry = tkp.Input.Number_range(self, 1, 64, 64)
        self.ascii_entry.grid(row=2, column=1)

        self.color_label = tk.Label(self, text="Number of colors :")
        self.color_label.grid(row=3, column=0)
        self.color_var = tk.StringVar(self)
        self.color_var.set("256")
        self.color_entry = tk.OptionMenu(self, self.color_var, "8", "16", "64", "256")
        self.color_entry.grid(row=3, column=1)

        self.mode_label = tk.Label(self, text="Mode :")
        self.mode_label.grid(row=4, column=0)
        self.mode_var = tk.StringVar()
        self.mode_var.set("both")
        self.mode_menu = tk.OptionMenu(self, self.mode_var, "ascii", "colored", "both")
        self.mode_menu.grid(row=4, column=1)

        self.size_label = tk.Label(self, text="Size :")
        self.size_label.grid(row=5, column=0)
        self.size_btn = tk.Button(self, text="Size", command=self.choose_size, state=tk.DISABLED)
        self.size_btn.grid(row=5, column=1)

        self.size_coef = tk.DoubleVar()
        self.size_coef.set(1)

        self.start_button = tk.Button(self, text="Start", command=self.start)
        self.start_button.grid(row=6, column=0, columnspan=2)

    def choose_size(self):
        self.size_menu = tkp.Window(self, tkp.Input.Size_input, self.width.get(), self.height.get())
        self.size_menu.call()
        self.size_menu.add_on_change(self.set_size)

    def set_size(self, cursor):
        #set the size of the output image
        print("new size : %s" % cursor.get())
        self.size_coef.set(cursor.get())

    def start(self):
        #format of the options :
        # - input path
        # - output path
        # - number of ascii characters
        # - colors mode
        # - mode of the output image
        # - relative size of the output image
        # - number of colors in the output image
        run("AsciiArt.exe %s %s %s %s %s %s" % (self.input_path.get(), self.output_entry.get(), self.ascii_entry.get(), self.color_var.get(), self.mode_var.get(),self.size_coef.get()))

    def input_path_changed(self, *args):
        #if the path is a valid jpg image path, the output path is set to the same path, and self.width and self.height are set to the image size
        if path.isfile(self.input_path.get()) and self.input_path.get().endswith(".jpg"):
            self.output_entry.delete(0, tk.END)
            self.output_entry.insert(0, new_name(self.input_path.get(), ""))
            img = Image.open(self.input_path.get())
            self.width.set(img.size[0])
            self.height.set(img.size[1])
            img.close()
            self.size_btn.config(state=tk.NORMAL)
        else:
            self.size_btn.config(state=tk.DISABLED)


    

if __name__ == "__main__":
    gui = GUI()
    gui.mainloop()