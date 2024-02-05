#include <iostream>
#include <Python.h>

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

    // Set the path to the Python file
    std::string pythonFilePath = "path/to/your/pythonfile.py";

    // Initialize the Python file path as a Python object
    PyObject *pythonFilePathObj = PyUnicode_FromString(pythonFilePath.c_str());

    // Import the Python file as a Python module
    PyObject *pythonFileModule = PyImport_Import(pythonFilePathObj);

    // Check if the Python file was imported successfully
    if (!pythonFileModule) {
        std::cerr << "Failed to import the Python file." << std::endl;
        PyErr_Print();
        return 1;
    }

    // Call the main function of the Python file
    PyObject *mainFunction = PyObject_GetAttrString(pythonFileModule, "main");
    if (!mainFunction) {
        std::cerr << "Failed to get the main function from the Python file." << std::endl;
        PyErr_Print();
        return 1;
    }

    // Call the main function with no arguments
    PyObject *mainFunctionResult = PyObject_CallObject(mainFunction, nullptr);
    if (!mainFunctionResult) {
        std::cerr << "Failed to call the main function of the Python file." << std::endl;
        PyErr_Print();
        return 1;
    }

    // Clean up the Python objects
    Py_DECREF(pythonFilePathObj);
    Py_DECREF(pythonFileModule);
    Py_DECREF(mainFunction);
    Py_DECREF(mainFunctionResult);

    // Finalize the Python interpreter
    Py_Finalize();

    return 0;
}
