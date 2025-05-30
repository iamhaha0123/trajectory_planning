// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from conveyorbelt_msgs:msg/ConveyorBeltState.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "conveyorbelt_msgs/msg/detail/conveyor_belt_state__struct.h"
#include "conveyorbelt_msgs/msg/detail/conveyor_belt_state__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool conveyorbelt_msgs__msg__conveyor_belt_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[61];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("conveyorbelt_msgs.msg._conveyor_belt_state.ConveyorBeltState", full_classname_dest, 60) == 0);
  }
  conveyorbelt_msgs__msg__ConveyorBeltState * ros_message = _ros_message;
  {  // power
    PyObject * field = PyObject_GetAttrString(_pymsg, "power");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->power = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // enabled
    PyObject * field = PyObject_GetAttrString(_pymsg, "enabled");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->enabled = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * conveyorbelt_msgs__msg__conveyor_belt_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ConveyorBeltState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("conveyorbelt_msgs.msg._conveyor_belt_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ConveyorBeltState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  conveyorbelt_msgs__msg__ConveyorBeltState * ros_message = (conveyorbelt_msgs__msg__ConveyorBeltState *)raw_ros_message;
  {  // power
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->power);
    {
      int rc = PyObject_SetAttrString(_pymessage, "power", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // enabled
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->enabled ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "enabled", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
