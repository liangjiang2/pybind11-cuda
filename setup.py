#!/usr/bin/env python
# coding=utf-8
import os
from setuptools import setup,find packages
from setuptools.command.install import install
setup(
    name="pydemo",
    version="1.0",
    description="demo of pybind",
    author="jiangliang",
    author email="",
    url="",
    install requires=["pybind11",'onnx'],
    ext modules=[],
    cmdclass={
    },
    packages=find packages(),
    include package data=True,
    classifiers=[
        "Operating system :: OS Independent",
        "Intended Audience :: Developers and Researchers",
        "License :: OSI Approved :: xxx",
        "Programming Language :: python",
    ],
)
