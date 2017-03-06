import HelloPythonC


def argc(*args):
    print("Argument count:", HelloPythonC.argc())


def multiply(*args):
    if not args:
        return 0
    c = 1
    for arg in args:
        c *= arg
    return c
