#include <stdio.h>
#include <string>

#include <Python.h>

#include "Javathon.h"

int
runPythonCode(const std::string &json)
{
  std::string file("foo");
  std::string functionName("foo");
  PyObject *pDict;
  PyObject *pArgs;
  PyObject *pValue;
  int i;
  long returnValue;

  PyObject *fileName = PyString_FromString(file.c_str());
  PyObject *module = PyImport_Import(fileName);
  Py_DECREF(fileName);

  if (module != nullptr) {
    // FunctionToCall is a new reference
    PyObject *functionToCall = PyObject_GetAttrString(module,
                                                      functionName.c_str());

    if (functionToCall && PyCallable_Check(functionToCall)) {
      pArgs = PyTuple_New(1);
      PyTuple_SetItem(pArgs, 0, PyString_FromString(json.c_str()));

      pValue = PyObject_CallObject(functionToCall, pArgs);
      Py_DECREF(pArgs);
      if (pValue != nullptr) {
        returnValue = PyInt_AsLong(pValue);
        Py_DECREF(pValue);
      }
      else {
        Py_DECREF(functionToCall);
        Py_DECREF(module);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        return -1;
      }
    }
    else {
      if (PyErr_Occurred()) {
        PyErr_Print();
      }
      fprintf(stderr, "Cannot find function \"%s\"\n", functionName.c_str());
    }
    Py_XDECREF(functionToCall);
    Py_DECREF(module);
  }
  else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", file.c_str());
    return -1;
  }
  return returnValue;
}


void
GetJStringContent(JNIEnv *env, jstring AStr, std::string &ARes) {
  if (!AStr) {
    ARes.clear();
    return;
  }

  const char *s = env->GetStringUTFChars(AStr, nullptr);
  ARes = s;
  env->ReleaseStringUTFChars(AStr, s);
}


JNIEXPORT jint JNICALL
Java_Javathon_startPython()
{
  Py_Initialize();
}


JNIEXPORT jint JNICALL
Java_Javathon_handleEvent(JNIEnv *env,
                          jclass cls,
                          jstring jjson)
{
  std::string json;
  GetJStringContent(env, jjson, json);
  return runPythonCode(json.c_str());
}


JNIEXPORT jint JNICALL
Java_Javathon_stopPython()
{
  Py_Finalize();
}
