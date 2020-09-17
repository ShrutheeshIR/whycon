#include "whycon.h"
#include <boost/python/numpy.hpp>
namespace np = boost::python::numpy;
BOOST_PYTHON_MODULE(whycon2)
{
    np::initialize();
    // Create the Python type object for our extension class and define __init__ function.
    class_<Whycon>("Whycon", init<int, float>())
        .def("processimage", &Whycon::processimage)
        .def("cleanmem", &Whycon::cleanmem)
    ;

}