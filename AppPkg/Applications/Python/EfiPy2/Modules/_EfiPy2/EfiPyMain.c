/*
 * EfiPyMain.c
 *
 * Copyright (C) 2014 - 2023 MaxWu efipy.core@gmail.com All rights reserved.
 *
 * EfiPyMain.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * EfiPy2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EfiPy2.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <Python.h>
#include "structmember.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Pi/PiDxeCis.h>
#include <Library/DxeServicesTableLib.h>

#if BUILD_FOR_OS == 1
#endif // BUILD_FOR_OS

UINT16                  EFIPY_SIGNATURE[] = L"EFIPYE_SIGNALTURE_001";

// EFI_SYSTEM_TABLE        Efi_ST;
// EFI_RUNTIME_SERVICES    Efi_RT;
// EFI_BOOT_SERVICES       Efi_BS;
// EFI_DXE_SERVICES        Efi_DS;

// EFI_HANDLE              gImageHandle = (EFI_HANDLE)EFIPY_SIGNATURE;

// EFI_SYSTEM_TABLE       *gST = &Efi_ST;
// EFI_RUNTIME_SERVICES   *gRT = &Efi_RT;
// EFI_BOOT_SERVICES      *gBS = &Efi_BS;
// EFI_DXE_SERVICES       *gDS = &Efi_DS;

#if (0) // EfiPy2
extern EFI_HANDLE pImageHandle;
#endif // EfiPy2

/*************************************************************************
 * PRIVATE EfiPy_Processor_Init
 *************************************************************************/
int EfiPy_Processor_Init (PyObject *Module)
{
  int       ret;

#define EFIPY_MDE_CPU_IA32          0
#define EFIPY_MDE_CPU_X64           1
#define EFIPY_MDE_CPU_ARM           2
#define EFIPY_MDE_CPU_AARCH64       3
#define EFIPY_MDE_CPU_EBC           4
#define EFIPY_MDE_CPU_RISCV64       5
#define EFIPY_MDE_CPU_LOONGARCH64   6

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_IA32);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_X64);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_ARM);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_AARCH64);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_EBC);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_RISCV64);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddIntMacro (Module, EFIPY_MDE_CPU_LOONGARCH64);
  if (ret != 0) {
    return ret;
  }

#define EFIPY_REMOVABLE_MEDIA_FILE_NAME_IA32         "\\EFI\\BOOT\\BOOTIA32.EFI"
#define EFIPY_REMOVABLE_MEDIA_FILE_NAME_X64          "\\EFI\\BOOT\\BOOTX64.EFI"
#define EFIPY_REMOVABLE_MEDIA_FILE_NAME_ARM          "\\EFI\\BOOT\\BOOTARM.EFI"
#define EFIPY_REMOVABLE_MEDIA_FILE_NAME_AARCH64      "\\EFI\\BOOT\\BOOTAA64.EFI"
#define EFIPY_REMOVABLE_MEDIA_FILE_NAME_RISCV64      "\\EFI\\BOOT\\BOOTRISCV64.EFI"
#define EFIPY_REMOVABLE_MEDIA_FILE_NAME_LOONGARCH64  "\\EFI\\BOOT\\BOOTLOONGARCH64.EFI"

  ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME_IA32",         EFIPY_REMOVABLE_MEDIA_FILE_NAME_IA32);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME_X64",          EFIPY_REMOVABLE_MEDIA_FILE_NAME_X64);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME_ARM",          EFIPY_REMOVABLE_MEDIA_FILE_NAME_ARM);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME_AARCH64",      EFIPY_REMOVABLE_MEDIA_FILE_NAME_AARCH64);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME_RISCV64",      EFIPY_REMOVABLE_MEDIA_FILE_NAME_RISCV64);
  if (ret != 0) {
    return ret;
  }

  ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME_LOONGARCH64",  EFIPY_REMOVABLE_MEDIA_FILE_NAME_LOONGARCH64);
  if (ret != 0) {
    return ret;
  }

  #if   defined (MDE_CPU_IA32)
// #define EFIPY_REMOVABLE_MEDIA_FILE_NAME  EFIPY_REMOVABLE_MEDIA_FILE_NAME_IA32
    ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME", EFIPY_REMOVABLE_MEDIA_FILE_NAME_IA32);
    if (ret != 0) {
      return ret;
    }

  #elif defined (MDE_CPU_X64)
// #define EFIPY_REMOVABLE_MEDIA_FILE_NAME  EFIPY_REMOVABLE_MEDIA_FILE_NAME_X64
    ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME", EFIPY_REMOVABLE_MEDIA_FILE_NAME_X64);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_EBC)
  #elif defined (MDE_CPU_ARM)
// #define EFIPY_REMOVABLE_MEDIA_FILE_NAME  EFIPY_REMOVABLE_MEDIA_FILE_NAME_ARM
    ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME", EFIPY_REMOVABLE_MEDIA_FILE_NAME_ARM);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_AARCH64)
// #define EFIPY_REMOVABLE_MEDIA_FILE_NAME  EFIPY_REMOVABLE_MEDIA_FILE_NAME_AARCH64
    ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME", EFIPY_REMOVABLE_MEDIA_FILE_NAME_AARCH64);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_RISCV64)
// #define EFIPY_REMOVABLE_MEDIA_FILE_NAME  EFIPY_REMOVABLE_MEDIA_FILE_NAME_RISCV64
    ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME", EFIPY_REMOVABLE_MEDIA_FILE_NAME_RISCV64);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_LOONGARCH64)
// #define EFIPY_REMOVABLE_MEDIA_FILE_NAME  EFIPY_REMOVABLE_MEDIA_FILE_NAME_LOONGARCH64
    ret = PyModule_AddStringConstant (Module, "EFI_REMOVABLE_MEDIA_FILE_NAME", EFIPY_REMOVABLE_MEDIA_FILE_NAME_LOONGARCH64);
    if (ret != 0) {
      return ret;
    }
  #else
    #error Unknown Processor Type
  #endif

  #if defined (MDE_CPU_IA32)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_IA32);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_X64)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_X64);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_ARM)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_ARM);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_AARCH64)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_AARCH64);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_EBC)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_EBC);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_RISCV64)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_RISCV64);
    if (ret != 0) {
      return ret;
    }
  #elif defined (MDE_CPU_LOONGARCH64)
    ret = PyModule_AddIntConstant (Module, "EFIPY_MDE_CPU_TYPE", EFIPY_MDE_CPU_LOONGARCH64);
    if (ret != 0) {
      return ret;
    }
  #else
    #error Unknown Processor Type
  #endif

  return 0;

} // EfiPy_Processor_Init

/*************************************************************************
 * PRIVATE EfiPy_Constant_Init
 *************************************************************************/
int EfiPy_Constant_Init (PyObject *Module)
{

  PyObject *PyObject_MAX_BIT                = NULL;
  PyObject *PyObject_MAX_2_BITS             = NULL;
  PyObject *PyObject_MAX_ADDRESS            = NULL;
  PyObject *PyObject_CPU_STACK_ALIGNMENT    = NULL;
  PyObject *PyObject_gImageHandle           = NULL;
#if (0) // EfiPy2
  PyObject *PyObject_pImageHandle           = NULL;
#endif // // EfiPy2
  PyObject *PyObject_gST                    = NULL;
  PyObject *PyObject_gRT                    = NULL;
  PyObject *PyObject_gBS                    = NULL;
  PyObject *PyObject_gDS                    = NULL;

  //
  // ProcessorBind
  //

  PyObject_MAX_BIT = PyLong_FromUnsignedLongLong (MAX_BIT);
  if (PyModule_AddObject (Module, "MAX_BIT", PyObject_MAX_BIT) < 0) {
    // Py_XDECREF (PyObject_MAX_BIT);
    goto EfiPy_Constant_Init_Fail;
  }

  PyObject_MAX_2_BITS = PyLong_FromUnsignedLongLong (MAX_2_BITS);
  if (PyModule_AddObject (Module, "MAX_2_BITS", PyObject_MAX_2_BITS) < 0) {
    // Py_XDECREF (PyObject_MAX_2_BITS);
    goto EfiPy_Constant_Init_Fail;
  }

  PyObject_MAX_ADDRESS = PyLong_FromUnsignedLongLong (MAX_ADDRESS);
  if (PyModule_AddObject (Module, "MAX_ADDRESS", PyObject_MAX_ADDRESS) < 0) {
    // Py_XDECREF (PyObject_MAX_ADDRESS);
    goto EfiPy_Constant_Init_Fail;
  }

  PyObject_CPU_STACK_ALIGNMENT  = PyLong_FromUnsignedLongLong (CPU_STACK_ALIGNMENT);
  if (PyModule_AddObject (Module, "CPU_STACK_ALIGNMENT", PyObject_CPU_STACK_ALIGNMENT) < 0) {
    // Py_XDECREF (PyObject_CPU_STACK_ALIGNMENT);
    goto EfiPy_Constant_Init_Fail;
  }

  //
  // Process Handles
  //

  PyObject_gImageHandle = PyLong_FromVoidPtr(&gImageHandle);
  if (PyModule_AddObject (Module, "gImageHandle", PyObject_gImageHandle) < 0) {
    // Py_XDECREF (PyObject_gImageHandle);
    goto EfiPy_Constant_Init_Fail;
  }

#if (0) // EfiPy2
  PyObject_pImageHandle = PyLong_FromVoidPtr(&pImageHandle);
  if (PyModule_AddObject (Module, "pImageHandle", PyObject_pImageHandle) < 0) {
    // Py_XDECREF (PyObject_pImageHandle);
    goto EfiPy_Constant_Init_Fail;
  }
#endif // EfiPy2

  //
  // Table address
  //

  PyObject_gST = PyLong_FromVoidPtr(gST);
  if (PyModule_AddObject (Module, "EfiPygStAddr", PyObject_gST) < 0) {
    // Py_XDECREF (PyObject_gST);
    goto EfiPy_Constant_Init_Fail;
  }

  PyObject_gRT = PyLong_FromVoidPtr(gRT);
  if (PyModule_AddObject (Module, "EfiPygRtAddr", PyObject_gRT) < 0) {
    // Py_XDECREF (PyObject_gRT);
    goto EfiPy_Constant_Init_Fail;
  }

  PyObject_gBS = PyLong_FromVoidPtr(gBS);
  if (PyModule_AddObject (Module, "EfiPygBsAddr", PyObject_gBS) < 0) {
    // Py_XDECREF (PyObject_gBS);
    goto EfiPy_Constant_Init_Fail;
  }

  PyObject_gDS = PyLong_FromVoidPtr(gDS);
  if (PyModule_AddObject (Module, "EfiPygDsAddr", PyObject_gDS) < 0) {
    // Py_XDECREF (PyObject_gDS);
    goto EfiPy_Constant_Init_Fail;
  }

  return (0);

EfiPy_Constant_Init_Fail:

  Py_XDECREF (PyObject_MAX_BIT);
  Py_XDECREF (PyObject_MAX_2_BITS);
  Py_XDECREF (PyObject_MAX_ADDRESS);
  Py_XDECREF (PyObject_CPU_STACK_ALIGNMENT);
  Py_XDECREF (PyObject_gImageHandle);
  Py_XDECREF (PyObject_gST);
  Py_XDECREF (PyObject_gRT);
  Py_XDECREF (PyObject_gBS);
  Py_XDECREF (PyObject_gDS);

#if (0)
  Py_XDECREF (PyObject_pImageHandle);
#endif

  return (-1);

} // EfiPy_Constant_Init

/***************************************************************************
 *
 * Module structure
 *
 ***************************************************************************/
static struct PyModuleDef gEfiPyModule = {

  PyModuleDef_HEAD_INIT,

  "_EfiPy2",             /* name of module */
  "_EfiPy2 module",      /* Doc string (may be NULL) */
  -1,                   /* Size of per-interpreter state or -1 */
  NULL                  /* Method table */

}; // gEfiPyModule


/*************************************************************************
 * PUBLIC EfiPy Module initialize
 *************************************************************************/
#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
PyInit__EfiPy2(void)
{
  PyObject *EfiPyModule = NULL;

  EfiPyModule = PyModule_Create(&gEfiPyModule);

  if (EfiPyModule == NULL) {
    return NULL;
  }

  if (0 != EfiPy_Constant_Init(EfiPyModule)) {
    Py_DECREF (EfiPyModule);
    return NULL;
  }

  if (0 != EfiPy_Processor_Init(EfiPyModule)) {
    Py_DECREF (EfiPyModule);
    return NULL;
  }

  return (EfiPyModule);

} // PyInit_EfiPy

