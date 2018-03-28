//g++ f.cpp -I./include/ -std=c++11 -L./libs/ -lpython36  
//https://habrahabr.ru/post/111306/
#include <cmath>
#define _hypot hypot
#include <Python.h>
#include <iostream>
int main(int argc, char *argv[]){
	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       // "print('Today is', ctime(time()))\n");
    						"print('Хороший день', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);



    PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;
	Py_Initialize();
	pName = PyUnicode_FromString("MyPythonFile");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule == NULL){
		PyRun_SimpleString("print('Модуль не подключен')");
		return 1;
	}
	pFunc = PyObject_GetAttrString(pModule, "MyGreatFunc");
	if (!(pFunc && PyCallable_Check(pFunc))){
		PyRun_SimpleString("print('MyGreatFunc')");
		return 2;
	}
	pArgs = PyTuple_New(1);
	double x=9;
	PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(x));
	pValue = PyObject_CallObject(pFunc, pArgs);
	Py_DECREF(pArgs);
	double result = 0.0;
	if (pValue != NULL){
		result = PyFloat_AsDouble(pValue);
		Py_DECREF(pValue);
	}
	std::cout<<result<<std::endl;
	return 0;
}
