import os, sys

CurrentDir = os.getcwd()
IncludeDir = os.path.join (CurrentDir, '..', '..', '..', '..', '..', '..', 'MdePkg', 'Include')

if      sys.platform == 'linux':

  define_macros      = [('BUILD_FOR_OS', 1)]
  include_dirs       = [IncludeDir,
                        os.path.join (IncludeDir, 'X64')]
  extra_compile_args = ["-fshort-wchar"]

elif    sys.platform == 'win32':

  define_macros      = [('BUILD_FOR_OS', 1)]
  include_dirs       = [IncludeDir,
                        os.path.join (IncludeDir, 'X64')]
  extra_compile_args = []

elif    sys.platform == 'uefi':

  raise OSError (f'uefi does not support setuptools, yet.')

else:

  raise OSError (f'Unsupported platform {sys.platform}')

from setuptools import Extension, setup

setup(
    ext_modules=[
        Extension(
            name               = "_EfiPy2",
            sources            = ["EfiPyMain.c"],
            define_macros      = [('BUILD_FOR_OS', 1)],
            include_dirs       = include_dirs,
            extra_compile_args = extra_compile_args, # https://review.coreboot.org/c/coreboot/+/76214
        ),
    ]
)
