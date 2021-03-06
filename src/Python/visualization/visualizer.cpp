// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "visualization.h"
#include "visualization_trampoline.h"

#include <Open3D/Geometry/Image.h>
#include <Open3D/Visualization/Visualizer/Visualizer.h>
#include <Open3D/Visualization/Visualizer/VisualizerWithKeyCallback.h>
#include <Open3D/Visualization/Visualizer/VisualizerWithEditing.h>

using namespace open3d;

void pybind_visualizer(py::module &m) {
    py::class_<visualization::Visualizer, PyVisualizer<>,
               std::shared_ptr<visualization::Visualizer>>
            visualizer(m, "Visualizer", "Visualizer");
    py::detail::bind_default_constructor<visualization::Visualizer>(visualizer);
    visualizer
            .def("__repr__",
                 [](const visualization::Visualizer &vis) {
                     return std::string(
                                    "visualization::Visualizer with name ") +
                            vis.GetWindowName();
                 })
            .def("create_window",
                 &visualization::Visualizer::CreateVisualizerWindow,
                 "Function to create a window and initialize GLFW",
                 "window_name"_a = "Open3D", "width"_a = 1920,
                 "height"_a = 1080, "left"_a = 50, "top"_a = 50,
                 "visible"_a = true)
            .def("destroy_window",
                 &visualization::Visualizer::DestroyVisualizerWindow,
                 "Function to destroy a window")
            .def("register_animation_callback",
                 &visualization::Visualizer::RegisterAnimationCallback,
                 "Function to register a callback function for animation",
                 "callback_func"_a)
            .def("run", &visualization::Visualizer::Run,
                 "Function to activate the window")
            .def("close", &visualization::Visualizer::Close,
                 "Function to notify the window to be closed")
            .def("reset_view_point", &visualization::Visualizer::ResetViewPoint,
                 "Function to reset view point")
            .def("update_geometry", &visualization::Visualizer::UpdateGeometry,
                 "Function to update geometry")
            .def("update_renderer", &visualization::Visualizer::UpdateRender,
                 "Function to inform render needed to be updated")
            .def("poll_events", &visualization::Visualizer::PollEvents,
                 "Function to poll events")
            .def("add_geometry", &visualization::Visualizer::AddGeometry,
                 "Function to add geometry to the scene and create "
                 "corresponding shaders",
                 "geometry"_a)
            .def("get_view_control", &visualization::Visualizer::GetViewControl,
                 "Function to retrieve the associated "
                 "visualization::ViewControl",
                 py::return_value_policy::reference_internal)
            .def("get_render_option",
                 &visualization::Visualizer::GetRenderOption,
                 "Function to retrieve the associated "
                 "visualization::RenderOption",
                 py::return_value_policy::reference_internal)
            .def("capture_screen_float_buffer",
                 &visualization::Visualizer::CaptureScreenFloatBuffer,
                 "Function to capture screen and store RGB in a float buffer",
                 "do_render"_a = false)
            .def("capture_screen_image",
                 &visualization::Visualizer::CaptureScreenImage,
                 "Function to capture and save a screen image", "filename"_a,
                 "do_render"_a = false)
            .def("capture_depth_float_buffer",
                 &visualization::Visualizer::CaptureDepthFloatBuffer,
                 "Function to capture depth in a float buffer",
                 "do_render"_a = false)
            .def("capture_depth_image",
                 &visualization::Visualizer::CaptureDepthImage,
                 "Function to capture and save a depth image", "filename"_a,
                 "do_render"_a = false, "depth_scale"_a = 1000.0)
            .def("get_window_name", &visualization::Visualizer::GetWindowName);

    py::class_<visualization::VisualizerWithKeyCallback,
               PyVisualizer<visualization::VisualizerWithKeyCallback>,
               std::shared_ptr<visualization::VisualizerWithKeyCallback>>
            visualizer_key(m, "VisualizerWithKeyCallback", visualizer,
                           "VisualizerWithKeyCallback");
    py::detail::bind_default_constructor<
            visualization::VisualizerWithKeyCallback>(visualizer_key);
    visualizer_key
            .def("__repr__",
                 [](const visualization::VisualizerWithKeyCallback &vis) {
                     return std::string(
                                    "visualization::VisualizerWithKeyCallback "
                                    "with name ") +
                            vis.GetWindowName();
                 })
            .def("register_key_callback",
                 &visualization::VisualizerWithKeyCallback::RegisterKeyCallback,
                 "Function to register a callback function for a key press "
                 "event",
                 "key"_a, "callback_func"_a);

    py::class_<visualization::VisualizerWithEditing,
               PyVisualizer<visualization::VisualizerWithEditing>,
               std::shared_ptr<visualization::VisualizerWithEditing>>
            visualizer_edit(m, "VisualizerWithEditing", visualizer,
                            "VisualizerWithEditing");
    py::detail::bind_default_constructor<visualization::VisualizerWithEditing>(
            visualizer_edit);
    visualizer_edit.def(py::init<double, bool, const std::string &>())
            .def("__repr__",
                 [](const visualization::VisualizerWithEditing &vis) {
                     return std::string(
                                    "visualization::VisualizerWithEditing with "
                                    "name ") +
                            vis.GetWindowName();
                 })
            .def("get_picked_points",
                 &visualization::VisualizerWithEditing::GetPickedPoints,
                 "Function to get picked points");
}

void pybind_visualizer_method(py::module &m) {}
