import utils

def main():
    cmds = [
        "rm -rf bin build",
        "cmake -H. -Bbuild",
        "make -C build/",
    ]
    for cmd in cmds:
        r = utils.run(cmd)
        if r != 0:
            print "[error]cmd:" + cmd
            return

if __name__ == '__main__':
    main()
