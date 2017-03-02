import os
import shutil

def abspath(path):
    return os.path.abspath(path)

def exists(path):
    path = abspath(path)
    return os.path.exists(path)

def isdir(path):
    path = abspath(path)
    return os.path.isdir(path)

def isfile(path):
    path = abspath(path)
    return os.path.isfile(path)

def mkdir(path):
    path = abspath(path)
    if exists(path):
        print "[error]already exists:" + path
        return
    os.mkdir(path)

def remove(path):
    path = abspath(path)
    if exists(path):
        if isfile(path):
            os.remove(path)
        elif isdir(path):
            shutil.rmtree(path)
        else:
            print "[error]not file or dir"
    else:
        print "[error]no such:" + path

def files_filter(rootdir, func):
    if not exists(rootdir) or not isdir(rootdir):
        print "[error]invalid rootdir:" + rootdir
        return
    filepaths = []
    for curroot, subdirs, fns in os.walk(rootdir):
        for fn in fns:
            if func(fn):
                filepath = curroot + "/" + fn
                filepath = abspath(filepath)
                filepaths.append(filepath)
    return filepaths

def run(cmd):
    print cmd
    return os.system(cmd)

def print_with_frame(title):
    middle = "|" + title + "|"
    side = "-" * len(middle)
    print side
    print middle
    print side

def main():

    print_with_frame("test")

    path = "./tmp"
    print abspath(path)

    print "exists:" + str(exists(path))
    print "isdir:" + str(isdir(path))
    print "isfile:" + str(isfile(path))

    print_with_frame("mkdir:" + path)
    mkdir(path)

    print "exists:" + str(exists(path))
    print "isdir:" + str(isdir(path))
    print "isfile:" + str(isfile(path))

    print_with_frame("mkdir and remove:" + path)
    mkdir(path)
    remove(path)

    print "exists:" + str(exists(path))
    print "isdir:" + str(isdir(path))
    print "isfile:" + str(isfile(path))

    print_with_frame("create file:" + path)
    run("touch " + path)

    print "exists:" + str(exists(path))
    print "isdir:" + str(isdir(path))
    print "isfile:" + str(isfile(path))

    print_with_frame("remove:" + path)
    remove(path)

    print "exists:" + str(exists(path))
    print "isdir:" + str(isdir(path))
    print "isfile:" + str(isfile(path))

    print_with_frame("test files_filter")
    path = "/Users/xxx/Documents/tmp"

    def foo(path):
        return path[-4:] == ".jar"
    filepaths = files_filter(path, foo)
    print filepaths

if __name__ == '__main__':
    main()
