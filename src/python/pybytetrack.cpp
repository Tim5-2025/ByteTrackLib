#include <string>
#include <stdio.h>
#include <future>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "ByteTracker.h"

namespace py = pybind11;

PYBIND11_MODULE(pybytetrack, m)
{

    py::class_<bytetrack::Rect>(m, "Rect")
        .def(py::init<float, float, float, float>(),
            py::arg("x") = 0.0,
            py::arg("y") = 0.0,
            py::arg("width") = 0.0,
            py::arg("height") = 0.0)
		.def_property("x",        [](bytetrack::Rect& self){return self.x;}, [](bytetrack::Rect& self, float nv){self.x = nv;})
		.def_property("y",        [](bytetrack::Rect& self){return self.y;}, [](bytetrack::Rect& self, float nv){self.y = nv;})
        .def_property("width",    [](bytetrack::Rect& self){return self.width;}, [](bytetrack::Rect& self, float nv){self.width = nv;})
        .def_property("height",   [](bytetrack::Rect& self){return self.height;}, [](bytetrack::Rect& self, float nv){self.height = nv;})
		.def("__repr__", [](bytetrack::Rect& rect){
			auto str =std::string("\n") + "x:" + std::to_string(rect.x) + " "
					 + "y:" + std::to_string(rect.y) + " "
                     + "width:" + std::to_string(rect.width) + " "
                     + "height:" + std::to_string(rect.height);
			return str;
			}
		);

    py::class_<bytetrack::Object>(m, "Object")
        .def(py::init<float, unsigned int, const bytetrack::Rect&>(),
            py::arg("prob") = 0.0,
            py::arg("label") = 0,
            py::arg("rect") = bytetrack::Rect())
		.def_property("prob",        [](bytetrack::Object& self){return self.prob;}, [](bytetrack::Object& self, float nv){self.prob = nv;})
		.def_property("label",        [](bytetrack::Object& self){return self.label;}, [](bytetrack::Object& self, unsigned int nv){self.label = nv;})
        .def_property("rect",    [](bytetrack::Object& self){return self.rect;}, [](bytetrack::Object& self, bytetrack::Rect& nv){self.rect = nv;})
        .def("__repr__", [](bytetrack::Object& object){
            auto str =std::string("\n") + "prob:" + std::to_string(object.prob) + " "
					 + "label:" + std::to_string(object.label) + " "
                     + "x:" + std::to_string(object.rect.x) + " "
                     + "y:" + std::to_string(object.rect.y) + " "
                     + "width:" + std::to_string(object.rect.width) + " "
                     + "height:" + std::to_string(object.rect.height);
                     return str;
			}
		);

    py::class_<bytetrack::Track>(m, "Track")
        .def(py::init<bool, unsigned long long, unsigned long long, const bytetrack::Object&>(),
            py::arg("b_activated") = 0,
            py::arg("track_id") = 0,
            py::arg("frame_id") = 0,
            py::arg("object") = bytetrack::Object())
        .def_property("b_activated",        [](bytetrack::Track& self){return self.b_activated;}, [](bytetrack::Track& self, bool nv){self.b_activated = nv;})
        .def_property("track_id",        [](bytetrack::Track& self){return self.track_id;}, [](bytetrack::Track& self, unsigned long long nv){self.track_id = nv;})
        .def_property("frame_id",        [](bytetrack::Track& self){return self.frame_id;}, [](bytetrack::Track& self, unsigned long long nv){self.frame_id = nv;})
        .def_property("object",        [](bytetrack::Track& self){return self.object;}, [](bytetrack::Track& self, bytetrack::Object& nv){self.object = nv;})
        .def("__repr__", [](bytetrack::Track& track){
            auto str =std::string("\n") + "b_activated:" + std::to_string(track.b_activated) + " "
					 + "track_id:" + std::to_string(track.track_id) + " "
                     + "frame_id:" + std::to_string(track.frame_id) + " "
                     + "prob:" + std::to_string(track.object.prob) + " "
                     + "label:" + std::to_string(track.object.label) + " "
                     + "x:" + std::to_string(track.object.rect.x) + " "
                     + "y:" + std::to_string(track.object.rect.y) + " "
                     + "width:" + std::to_string(track.object.rect.width) + " "
                     + "height:" + std::to_string(track.object.rect.height);
                     return str;;
        });


    py::class_<bytetrack::ByteTracker>(m, "ByteTracker")
    .def(py::init<unsigned int, float, float, float>(),
        py::arg("max_age") = 30,
        py::arg("track_thresh") = 0.5,
        py::arg("heigh_thresh") = 0.6,
        py::arg("match_thresh") = 0.8)
    .def("update", &bytetrack::ByteTracker::update,
        py::arg("objects"));
}