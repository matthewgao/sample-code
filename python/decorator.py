#!/usr/bin/env python
# coding=utf-8

def decorator(func):
    i = 0
    def wrapper(*arg):
        nonlocal i 
        print(i)
        i = i + 1
        return func(*arg)
    return wrapper

@decorator
def test():
    print('I am test')

if __name__ == '__main__':
    test()
    test() 
    test()
