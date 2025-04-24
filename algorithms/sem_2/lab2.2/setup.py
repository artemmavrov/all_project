from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "lr_module",
        sources=["lr_bindings.cpp", "hashing_mod.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++"
    ),
]

setup(
    name="lr_module",
    ext_modules=ext_modules,
)