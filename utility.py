import os
import subprocess

def new_name(original_name, directory):
    '''Returns a new name for a file or a directory in the given directory\n
    If directory is empty, it will use the current directory'''
    if directory == "":
        directory = os.getcwd()
    if os.path.exists(os.path.join(directory, original_name)):
        name, extension = os.path.splitext(original_name)
        i = 1
        while os.path.exists(os.path.join(directory, name + "(" + str(i) + ")" + extension)):
            i += 1
        return name + "(" + str(i) + ")" + extension
    else:
        return original_name

def run(cmd):
    '''Runs a command in a terminal'''
    print(cmd)
    subprocess.call(cmd, shell=True)

if __name__ == "__main__":
    print(new_name("charge.jpg", ""))