import tkinter as tk
from tkinter import ttk

class Input:
    class Number_range(tk.Entry):
        def __init__(self, master, min, max, default=""):
            self.min = min
            self.max = max
            self.value = tk.StringVar()
            self.value.set(default)
            tk.Entry.__init__(self, master, textvariable=self.value)
            self.value.trace("w", self.validate)
            self.old = ""

        def validate(self, *args):
            if self.value.get().isdigit():
                if float(self.value.get()) < self.min or float(self.value.get()) > self.max:
                    self.value.set(self.old)
                else:
                    self.old = self.value.get()
            elif self.value.get() != "":
                self.value.set(self.old)
            else:
                self.old = self.value.get()

        def get(self):
            return int(self.value.get())

    class Input_range(tk.Frame):
        def __init__(self, master, values : list, width = 200, default_index = 0):
            if len(values) == 0:
                raise ValueError("values must contain at least one value")
            if default_index >= len(values):
                raise ValueError("default_index must be inferior to the length of values")

            tk.Frame.__init__(self, master)
            self.value = tk.DoubleVar()
            self.value.set(values[default_index])
            self.values = values

            self.config(width=width)

            space = (width-20) / (len(values))

            self.scale = tk.Canvas(self, width=width, height=200)
            self.scale.pack(side=tk.LEFT)

            self.func_on_change = []
            
            self.positions_values = []

            for i in range(len(values)):
                self.scale.create_text(8+(i+0.5) * space, 120, text=values[i])
                self.positions_values.append((8+(i+0.5) * space, values[i]))

            self.cursor = self.scale.create_oval(self.positions_values[default_index][0]-8, 92, self.positions_values[default_index][0]+8, 108, fill="black", outline="white")
            self.scale.bind("<Button-1>", self.move_cursor)
            self.scale.bind("<B1-Motion>", self.move_cursor)

            
            self.scale.create_line(self.positions_values[0][0], 100, width-self.positions_values[0][0], 100, fill="black")
        
        def move_cursor(self, event):
            #cursor can noly stop on the text
            for i in range(len(self.positions_values)):
                if abs(event.x - self.positions_values[i][0]) < 10:
                    self.scale.coords(self.cursor, self.positions_values[i][0]-8, 92, self.positions_values[i][0]+8, 108)
                    if self.positions_values[i][1] != self.value.get():
                        self.value.set(self.positions_values[i][1])
                        for func in self.func_on_change:
                            func(self)
                    break

        def get(self):
            return self.value.get()

        def add_on_change(self, function):
            #function is called when the value change
            self.func_on_change.append(function)

        def get(self):
            return self.value.get()


    class Size_input(tk.Frame):
        def __init__(self, master, default_width = 100, default_height = 100):
            tk.Frame.__init__(self, master)
            self.value = tk.StringVar()
            self.value.set("%dx%d" % (default_width, default_height))
            choice = [0.1, 0.25, 0.5, 0.75, 1, 2, 5, 10]
            self.cursor = Input.Input_range(self, choice, 400, 4)
            self.cursor.pack(side=tk.BOTTOM)

            self.width = default_width
            self.height = default_height

            self.show_coef = round(1000 / max(self.width, self.height), 1)

            self.canvas = tk.Canvas(self, width=default_height*self.show_coef*2, height=default_width*self.show_coef*2)
            self.canvas.pack(side=tk.TOP)


            self.default_size = self.canvas.create_rectangle(0, 0, (default_width/10)*self.show_coef, (default_height/10)*self.show_coef, fill="#dddddd", outline="white")
            self.new_size = self.canvas.create_rectangle(0, 0, (default_width/10)*self.show_coef, (default_height/10)*self.show_coef, fill="#bbbbbb", outline="white")
            self.text = self.canvas.create_text((default_width/20)*self.show_coef, (default_height/20)*self.show_coef, text=self.value.get())
            self.cursor.add_on_change(self.change_size)

            if self.height*self.cursor.get()*self.show_coef >= 300 and self.width*self.cursor.get()*self.show_coef >= 500:
                self.canvas.itemconfigure(self.text, state="normal")
            else:
                self.canvas.itemconfigure(self.text, state="hidden")

        def change_size(self, *args):
            self.canvas.coords(self.new_size, 0, 0, (self.width/10)*self.cursor.get()*self.show_coef, (self.height/10)*self.cursor.get()*self.show_coef)
            self.canvas.coords(self.text, (self.width/20)*self.cursor.get()*self.show_coef, (self.height/20)*self.cursor.get()*self.show_coef)
            self.value.set("%dx%d" % (int(self.height*self.cursor.get()), int(self.width*self.cursor.get())))
            #show the size only if the square is big enough (more than 500x500)
            if self.height*self.cursor.get()*self.show_coef >= 300 and self.width*self.cursor.get()*self.show_coef >= 500:
                self.canvas.itemconfigure(self.text, state="normal")
            else:
                self.canvas.itemconfigure(self.text, state="hidden")
            self.canvas.itemconfig(self.text, text=self.value.get())

            #set the default_size on top of the new_size if the new_size is bigger, else set the new_size on top of the default_size
            if self.height*self.cursor.get() >= self.height and self.width*self.cursor.get() >= self.width:
                self.canvas.tag_raise(self.default_size)
                self.canvas.tag_raise(self.text)
            else:
                self.canvas.tag_raise(self.new_size)
                self.canvas.tag_raise(self.text)
                
        def add_on_change(self, function):
            self.cursor.add_on_change(function)

        def get(self):
            return self.cursor.get()

class Window(tk.Toplevel):
    def __init__(self, master, inside_widget = None, *args, **kwargs):
        '''inside_widget is the widget that will be inside the window\n
        args and kwargs are the arguments of the inside_widget'''
        tk.Toplevel.__init__(self, master)
        self.title(inside_widget.__name__)
        
        self.args = args
        self.kwargs = kwargs
        self.inside_widget = inside_widget

        self.protocol("WM_DELETE_WINDOW", self.close)
        self.close_btn = tk.Button(self, text="Close", command=self.close)
        self.close_btn.pack(side=tk.BOTTOM)

    def call(self):
        self.inside_widget = self.inside_widget(self, *self.args, **self.kwargs)
        self.inside_widget.pack()

    def close(self):
        self.destroy()

    def add_on_change(self, function):
        self.inside_widget.add_on_change(function)

    def __get_attribute__(self, name):
        return getattr(self.inside_widget, name)


def trace(master):
    print("value : ", master.get())

if __name__ == "__main__":
    root = tk.Tk()
    root.title("Test")
    
    size_input = Window(root, Input.Size_input ,1920, 1080)
    size_input.call()
    root.mainloop()