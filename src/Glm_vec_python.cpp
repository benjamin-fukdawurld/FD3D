#include <FD3D/Binding/Python/Glm_vec_python.h>

#include <glm/geometric.hpp>
#include <pybind11/operators.h>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_cross_product.hpp>

namespace py = pybind11;

void FD3D::Python::bind_vec(pybind11::module &m)
{
    pybind11::module m_vec = m.def_submodule("vec", "glm vectors");
    bind_vec2(m_vec);
    bind_vec3(m_vec);
    bind_vec4(m_vec);
    bind_quat(m_vec);
}

void FD3D::Python::bind_vec2(pybind11::module &m)
{
    py::class_<glm::vec2> v2 = py::class_<glm::vec2>(m, "vec2")
                               .def(py::init<>())
                               .def(py::init<float>())
                               .def(py::init<float, float>())
                               .def_readwrite("x", &glm::vec2::x)
                               .def_readwrite("s", &glm::vec2::s)
                               .def_readwrite("y", &glm::vec2::y)
                               .def_readwrite("t", &glm::vec2::t)
                               .def_property_readonly("numberOfComponent", &glm::vec2::length, "Return the count of components of the vector")
                               .def("distance", [](const glm::vec2 &a, const glm::vec2 &b)
                               {
                                   return glm::distance(a, b);
                               }, "Returns the distance betwwen p0 and p1, i.e., length(p0 - p1)")
                               .def("dot", [](const glm::vec2 &a, const glm::vec2 &b)
                               {
                                   return glm::dot(a, b);
                               }, "Returns the dot product of x and y, i.e., result = x * y.")
                               .def("length", [](const glm::vec2 &v)
                               {
                                   return glm::length(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("normalize", [](const glm::vec2 &v)
                               {
                                   return glm::normalize(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("reflect", [](const glm::vec2 &a, const glm::vec2 &b)
                               {
                                   return glm::reflect(a, b);
                               }, "For the incident vector I and surface orientation N, returns the reflection direction : result = I - 2.0 * dot(N, I) * N.")
                               .def("refract", [](const glm::vec2 &a, const glm::vec2 &b, float factor)
                               {
                                   return glm::refract(a, b, factor);
                               }, "For the incident vector I and surface normal N, and the ratio of indices of refraction eta, return the refraction vector.")
                               .def("outerProduct ", [](const glm::vec2 &a, const glm::vec2 &b)
                               {
                                   return glm::outerProduct (a, b);
                               }, "Treats the first parameter c as a column vector and the second parameter r as a row vector and does a linear algebraic matrix multiply c * r.")
                               .def(py::self += float())
                               .def(py::self += py::self)
                               .def(py::self -= float())
                               .def(py::self -= py::self)
                               .def(py::self *= float())
                               .def(py::self *= py::self)
                               .def(py::self /= float())
                               .def(py::self /= py::self)
                               .def(-py::self)
                               .def(py::self + float())
                               .def(py::self + py::self)
                               .def(py::self - float())
                               .def(py::self - py::self)
                               .def(py::self * float())
                               .def(py::self * py::self)
                               .def(py::self / float())
                               .def(py::self / py::self)
                               .def(py::self == py::self)
                               .def(py::self != py::self)
                               .def(float() + py::self)
                               .def(float() - py::self)
                               .def(float() * py::self)
                               .def(float() / py::self)
                               .def("__getitem__", [](const glm::vec2 &v, int index) { return v[index]; })
                               .def("__setitem__", [](glm::vec2 &v, int index, float value) { return v[index] = value; });
    v2.doc() = "2 components vector of single-precision floating-point numbers.";
}

void FD3D::Python::bind_vec3(pybind11::module &m)
{
    py::class_<glm::vec3> v3 = py::class_<glm::vec3>(m, "vec3")
                               .def(py::init<>())
                               .def(py::init<float>())
                               .def(py::init<float, float, float>())
                               .def_readwrite("x", &glm::vec3::x)
                               .def_readwrite("s", &glm::vec3::s)
                               .def_readwrite("r", &glm::vec3::r)
                               .def_readwrite("y", &glm::vec3::y)
                               .def_readwrite("t", &glm::vec3::t)
                               .def_readwrite("g", &glm::vec3::g)
                               .def_readwrite("z", &glm::vec3::z)
                               .def_readwrite("p", &glm::vec3::p)
                               .def_readwrite("b", &glm::vec3::b)
                               .def_property_readonly("numberOfComponent", &glm::vec3::length, "Return the count of components of the vector")
                               .def("distance", [](const glm::vec3 &a, const glm::vec3 &b)
                               {
                                   return glm::distance(a, b);
                               }, "Returns the distance betwwen p0 and p1, i.e., length(p0 - p1)")
                               .def("dot", [](const glm::vec3 &a, const glm::vec3 &b)
                               {
                                   return glm::dot(a, b);
                               }, "Returns the dot product of x and y, i.e., result = x * y.")
                               .def("cross", [](const glm::vec3 &a, const glm::vec3 &b)
                               {
                                   return glm::cross(a, b);
                               }, "Returns the cross product of x and y.")
                               .def("length", [](const glm::vec3 &v)
                               {
                                   return glm::length(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("normalize", [](const glm::vec3 &v)
                               {
                                   return glm::normalize(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("reflect", [](const glm::vec3 &a, const glm::vec3 &b)
                               {
                                   return glm::reflect(a, b);
                               }, "For the incident vector I and surface orientation N, returns the reflection direction : result = I - 2.0 * dot(N, I) * N.")
                               .def("refract", [](const glm::vec3 &a, const glm::vec3 &b, float factor)
                               {
                                   return glm::refract(a, b, factor);
                               }, "For the incident vector I and surface normal N, and the ratio of indices of refraction eta, return the refraction vector.")
                               .def("outerProduct ", [](const glm::vec3 &a, const glm::vec3 &b)
                               {
                                   return glm::outerProduct (a, b);
                               }, "Treats the first parameter c as a column vector and the second parameter r as a row vector and does a linear algebraic matrix multiply c * r.")
                               .def(py::self += float())
                               .def(py::self += py::self)
                               .def(py::self -= float())
                               .def(py::self -= py::self)
                               .def(py::self *= float())
                               .def(py::self *= py::self)
                               .def(py::self /= float())
                               .def(py::self /= py::self)
                               .def(-py::self)
                               .def(py::self + float())
                               .def(py::self + py::self)
                               .def(py::self - float())
                               .def(py::self - py::self)
                               .def(py::self * float())
                               .def(py::self * py::self)
                               .def(py::self / float())
                               .def(py::self / py::self)
                               .def(py::self == py::self)
                               .def(py::self != py::self)
                               .def(float() + py::self)
                               .def(float() - py::self)
                               .def(float() * py::self)
                               .def(float() / py::self)
                               .def("__getitem__", [](const glm::vec3 &v, int index) { return v[index]; })
                               .def("__setitem__", [](glm::vec3 &v, int index, float value) { return v[index] = value; });

    v3.doc() = "3 components vector of single-precision floating-point numbers";
}

void FD3D::Python::bind_vec4(pybind11::module &m)
{
    py::class_<glm::vec4> v4 = py::class_<glm::vec4>(m, "vec4")
                               .def(py::init<>())
                               .def(py::init<float>())
                               .def(py::init<float, float, float, float>())
                               .def_readwrite("x", &glm::vec4::x)
                               .def_readwrite("s", &glm::vec4::s)
                               .def_readwrite("r", &glm::vec4::r)
                               .def_readwrite("y", &glm::vec4::y)
                               .def_readwrite("t", &glm::vec4::t)
                               .def_readwrite("g", &glm::vec4::g)
                               .def_readwrite("z", &glm::vec4::z)
                               .def_readwrite("p", &glm::vec4::p)
                               .def_readwrite("b", &glm::vec4::b)
                               .def_readwrite("w", &glm::vec4::w)
                               .def_readwrite("q", &glm::vec4::q)
                               .def_readwrite("a", &glm::vec4::a)
                               .def_property_readonly("numberOfComponent", &glm::vec4::length, "Return the count of components of the vector")
                               .def("distance", [](const glm::vec4 &a, const glm::vec4 &b)
                               {
                                   return glm::distance(a, b);
                               }, "Returns the distance betwwen p0 and p1, i.e., length(p0 - p1)")
                               .def("dot", [](const glm::vec4 &a, const glm::vec4 &b)
                               {
                                   return glm::dot(a, b);
                               }, "Returns the dot product of x and y, i.e., result = x * y.")
                               .def("length", [](const glm::vec4 &v)
                               {
                                   return glm::length(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("normalize", [](const glm::vec4 &v)
                               {
                                   return glm::normalize(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("reflect", [](const glm::vec4 &a, const glm::vec4 &b)
                               {
                                   return glm::reflect(a, b);
                               }, "For the incident vector I and surface orientation N, returns the reflection direction : result = I - 2.0 * dot(N, I) * N.")
                               .def("refract", [](const glm::vec4 &a, const glm::vec4 &b, float factor)
                               {
                                   return glm::refract(a, b, factor);
                               }, "For the incident vector I and surface normal N, and the ratio of indices of refraction eta, return the refraction vector.")
                               .def("outerProduct ", [](const glm::vec4 &a, const glm::vec4 &b)
                               {
                                   return glm::outerProduct (a, b);
                               }, "Treats the first parameter c as a column vector and the second parameter r as a row vector and does a linear algebraic matrix multiply c * r.")
                               .def(py::self += float())
                               .def(py::self += py::self)
                               .def(py::self -= float())
                               .def(py::self -= py::self)
                               .def(py::self *= float())
                               .def(py::self *= py::self)
                               .def(py::self /= float())
                               .def(py::self /= py::self)
                               .def(-py::self)
                               .def(py::self + float())
                               .def(py::self + py::self)
                               .def(py::self - float())
                               .def(py::self - py::self)
                               .def(py::self * float())
                               .def(py::self * py::self)
                               .def(py::self / float())
                               .def(py::self / py::self)
                               .def(py::self == py::self)
                               .def(py::self != py::self)
                               .def(float() + py::self)
                               .def(float() - py::self)
                               .def(float() * py::self)
                               .def(float() / py::self)
                               .def("__getitem__", [](const glm::vec4 &v, int index) { return v[index]; })
                               .def("__setitem__", [](glm::vec4 &v, int index, float value) { return v[index] = value; });

    v4.doc() = "4 components vector of single-precision floating-point numbers";
}


void FD3D::Python::bind_quat(pybind11::module &m)
{
    py::class_<glm::quat> q = py::class_<glm::quat>(m, "quat")
                               .def(py::init<>())
                               .def(py::init<float, float, float, float>())
                               .def(py::init<float, const glm::vec3&>())
                               .def(py::init<const glm::vec3&, const glm::vec3&>())
                               .def(py::init<const glm::vec3&>())
                               .def(py::init<const glm::mat3&>())
                               .def(py::init<const glm::mat4&>())
                               .def_readwrite("x", &glm::quat::x)
                               .def_readwrite("y", &glm::quat::y)
                               .def_readwrite("z", &glm::quat::z)
                               .def_readwrite("w", &glm::quat::w)
                               .def_property_readonly("numberOfComponent", &glm::quat::length, "Return the count of components of the vector")
                               .def_property_readonly("axis", [](const glm::quat &q) { return glm::axis(q); })
                               .def_property_readonly("eulerAngles", [](const glm::quat &q) { return glm::eulerAngles(q); })
                               .def("toMat3", &glm::quat::operator glm::mat3)
                               .def("toMat4", &glm::quat::operator glm::mat3)
                               .def("conjugate", [](const glm::quat &q)
                               {
                                   return glm::conjugate(q);
                               }, "Returns the q conjugate.")
                               .def("cross", [](const glm::quat &q1, const glm::quat &q2)
                               {
                                   return glm::cross(q1, q2);
                               }, "Returns the cross product of q1 and q2.")
                               .def("dot", [](const glm::quat &a, const glm::quat &b)
                               {
                                   return glm::dot(a, b);
                               }, "Returns dot product of q1 and q2, i.e., q1[0] * q2[0] + q1[1] * q2[1] + ...")
                               .def("inverse", [](const glm::quat &q)
                               {
                                   return glm::inverse(q);
                               }, "Returns the q inverse.")
                               .def("length", [](const glm::quat &v)
                               {
                                   return glm::length(v);
                               }, "Returns the length of the quaternion x.")
                               .def("normalize", [](const glm::quat &v)
                               {
                                   return glm::normalize(v);
                               }, "Returns the length of x, i.e., sqrt(x * x).")
                               .def("mix", [](const glm::quat &x, const glm::quat &y, float factor)
                               {
                                   return glm::mix(x, y, factor);
                               }, "Returns a SLERP interpolated quaternion of x and y according a.")
                               .def("rotate", [](const glm::quat &a, const glm::vec3 &b, float angle)
                               {
                                   return glm::rotate(a, angle, b);
                               }, "Rotates a quaternion from an vector of 3 components axis and an angle expressed in degrees.")
                               .def(py::self += py::self)
                               .def(py::self -= py::self)
                               .def(py::self *= float())
                               .def(py::self *= py::self)
                               .def(py::self /= float())
                               .def(-py::self)
                               .def(py::self + py::self)
                               .def(py::self - py::self)
                               .def(py::self * float())
                               .def(py::self * py::self)
                               .def(py::self * glm::vec3())
                               .def(glm::vec3() * py::self)
                               .def(py::self * glm::vec4())
                               .def(glm::vec4() * py::self)
                               .def(py::self / float())
                               .def(py::self == py::self)
                               .def(py::self != py::self)
                               .def(float() * py::self)
                               .def("__getitem__", [](const glm::quat &v, int index) { return v[index]; })
                               .def("__setitem__", [](glm::quat &v, int index, float value) { return v[index] = value; });

    q.doc() = "4 components vector of single-precision floating-point numbers";
}


void FD3D::Python::bind_mat(pybind11::module &m)
{
    pybind11::module m_mat = m.def_submodule("mat", "glm matrix");
    bind_mat2(m_mat);
    bind_mat3(m_mat);
    bind_mat4(m_mat);
}

void FD3D::Python::bind_mat2(pybind11::module &m)
{
    auto mat = py::class_<glm::mat2>(m, "mat2")
               .def(py::init<>())
               .def(py::init<float>())
               .def(py::init<float, float, float, float>())
               .def(py::init<const glm::vec2 &, const glm::vec2 &>())
               .def_property_readonly("numberOfColumn", &glm::mat2::length, "Return the count of columns of the matrix")
               .def_property_readonly("numberOfRow", &glm::mat2::length, "Return the count of rows of the matrix")
               .def("determinant", [](const glm::mat2 &mtx)
               {
                   return glm::determinant(mtx);
               }, "Returns the determinant of a squared matrix.")
               .def("inverse", [](const glm::mat2 &mtx)
               {
                   return glm::inverse(mtx);
               }, "Returns the inverse of a squared matrix")
               .def("matrixCompMult", [](const glm::mat2 &a, const glm::mat2 &b)
               {
                   return glm::matrixCompMult(a, b);
               })
               .def("transpose", [](const glm::mat2 &mtx)
               {
                   return glm::transpose(mtx);
               }, "Returns the transposed matrix of this matrix")
               .def(py::self += float())
               .def(py::self += py::self)
               .def(py::self -= float())
               .def(py::self -= py::self)
               .def(py::self *= float())
               .def(py::self *= py::self)
               .def(py::self /= float())
               .def(py::self /= py::self)
               .def(py::self + float())
               .def(py::self + py::self)
               .def(py::self - float())
               .def(py::self - py::self)
               .def(py::self * float())
               .def(py::self * py::self)
               .def(py::self * glm::vec2())
               .def(py::self / float())
               .def(py::self / py::self)
               .def(py::self / glm::vec2())
               .def(-py::self)
               .def(py::self == py::self)
               .def(py::self != py::self)
               .def(float() + py::self)
               .def(float() - py::self)
               .def(float() * py::self)
               .def(glm::vec2() * py::self)
               .def(float() / py::self)
               .def(glm::vec2() / py::self)
               .def("__getitem__", [](const glm::mat2 &v, int index) { return v[index]; })
               .def("__getitem__", [](const glm::mat2 &v, int row, int col) { return v[col][row]; })
               .def("__setitem__", [](glm::mat2 &v, int index, const glm::vec2 &value) { return v[index] = value; })
               .def("__setitem__", [](glm::mat2 &v, int row, int col, float value) { return v[col][row] = value; });
    mat.doc() = "2 columns of 2 components matrix of single-precision floating-point numbers.";
}

void FD3D::Python::bind_mat3(pybind11::module &m)
{
    auto mat = py::class_<glm::mat3>(m, "mat3")
               .def(py::init<>())
               .def(py::init<float>())
               .def(py::init<float, float, float,
                             float, float, float,
                             float, float, float>())
               .def(py::init<const glm::vec3 &, const glm::vec3 &, const glm::vec3 &>())
               .def_property_readonly("numberOfColumn", &glm::mat3::length, "Return the count of columns of the matrix")
               .def_property_readonly("numberOfRow", &glm::mat3::length, "Return the count of rows of the matrix")
               .def("determinant", [](const glm::mat3 &mtx)
               {
                   return glm::determinant(mtx);
               }, "Returns the determinant of a squared matrix.")
               .def("inverse", [](const glm::mat3 &mtx)
               {
                   return glm::inverse(mtx);
               }, "Returns the inverse of a squared matrix")
               .def("matrixCompMult", [](const glm::mat3 &a, const glm::mat3 &b)
               {
                   return glm::matrixCompMult(a, b);
               })
               .def("transpose", [](const glm::mat3 &mtx)
               {
                   return glm::transpose(mtx);
               }, "Returns the transposed matrix of this matrix")
               .def(py::self += float())
               .def(py::self += py::self)
               .def(py::self -= float())
               .def(py::self -= py::self)
               .def(py::self *= float())
               .def(py::self *= py::self)
               .def(py::self /= float())
               .def(py::self /= py::self)
               .def(py::self + float())
               .def(py::self + py::self)
               .def(py::self - float())
               .def(py::self - py::self)
               .def(py::self * float())
               .def(py::self * py::self)
               .def(py::self * glm::vec3())
               .def(py::self / float())
               .def(py::self / py::self)
               .def(py::self / glm::vec3())
               .def(-py::self)
               .def(py::self == py::self)
               .def(py::self != py::self)
               .def(float() + py::self)
               .def(float() - py::self)
               .def(float() * py::self)
               .def(glm::vec3() * py::self)
               .def(float() / py::self)
               .def(glm::vec3() / py::self)
               .def("__getitem__", [](const glm::mat3 &v, int index) { return v[index]; })
               .def("__getitem__", [](const glm::mat3 &v, int row, int col) { return v[col][row]; })
               .def("__setitem__", [](glm::mat3 &v, int index, const glm::vec3 &value) { return v[index] = value; })
               .def("__setitem__", [](glm::mat3 &v, int row, int col, float value) { return v[col][row] = value; });
    mat.doc() = "3 columns of 3 components matrix of single-precision floating-point numbers.";
}

void FD3D::Python::bind_mat4(pybind11::module &m)
{
    auto mat = py::class_<glm::mat4>(m, "mat4")
               .def(py::init<>())
               .def(py::init<float>())
               .def(py::init<float, float, float, float,
                             float, float, float, float,
                             float, float, float, float,
                             float, float, float, float>())
               .def(py::init<const glm::vec4 &, const glm::vec4 &, const glm::vec4 &, const glm::vec4 &>())
               .def_property_readonly("numberOfColumn", &glm::mat4::length, "Return the count of columns of the matrix")
               .def_property_readonly("numberOfRow", &glm::mat4::length, "Return the count of rows of the matrix")
               .def("determinant", [](const glm::mat4 &mtx)
               {
                   return glm::determinant(mtx);
               }, "Returns the determinant of a squared matrix.")
               .def("inverse", [](const glm::mat4 &mtx)
               {
                   return glm::inverse(mtx);
               }, "Returns the inverse of a squared matrix")
               .def("matrixCompMult", [](const glm::mat4 &a, const glm::mat4 &b)
               {
                   return glm::matrixCompMult(a, b);
               })
               .def("transpose", [](const glm::mat4 &mtx)
               {
                   return glm::transpose(mtx);
               }, "Returns the transposed matrix of this matrix")
               .def("rotate", [](const glm::mat4 &mtx, float angle, const glm::vec3 &v)
               {
                   return glm::rotate(mtx, angle, v);
               }, "Builds a rotation 4 * 4 matrix created from an axis vector and an angle expressed in degrees.")
               .def("scale", [](const glm::mat4 &mtx, const glm::vec3 &v)
               {
                   return glm::scale(mtx, v);
               }, "Builds a scale 4 * 4 matrix created from 3 scalars.")
               .def("scale", [](const glm::mat4 &mtx, float s)
               {
                   return glm::scale(mtx, glm::vec3(s, s, s));
               }, "Builds a scale 4 * 4 matrix created from 1 scalars.")
               .def("translate", [](const glm::mat4 &mtx, const glm::vec3 &v)
               {
                   return glm::translate(mtx, v);
               }, "Builds a translation 4 * 4 matrix created from a vector of 3 components.")
               .def_static("frustum", [](float left, float right, float top, float bottom, float near, float far)
               {
                   return glm::frustum(left, right, top, bottom, near, far);
               }, "Creates a frustum matrix.")
               .def_static("infinitePerspective", [](float fovy, float aspect, float near)
               {
                   return glm::infinitePerspective(fovy, aspect, near);
               }, "Creates a matrix for a symmetric perspective-view frustum with far plane at infinite.")
               .def_static("lookAt", [](const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
               {
                   return glm::lookAt(eye, center, up);
               }, "Build a look at view matrix.")
               .def_static("ortho", [](float left, float right, float top, float bottom)
               {
                   return glm::ortho(left, right, top, bottom);
               }, "Creates a matrix for projecting two-dimensional coordinates onto the screen.")
               .def_static("frustum", [](float left, float right, float top, float bottom, float near, float far)
               {
                   return glm::ortho(left, right, top, bottom, near, far);
               }, "Creates a matrix for an orthographic parallel viewing volume.")
               .def_static("perspective", [](float fovy, float aspect, float near, float far)
               {
                   return glm::perspective(fovy, aspect, near, far);
               }, "Creates a matrix for a symetric perspective-view frustum.")
               .def_static("perspectiveFov", [](float fovy, float width, float height, float near, float far)
               {
                   return glm::perspectiveFov(fovy, width, height, near, far);
               }, "Builds a perspective projection matrix based on a field of view From GLM_GTC_matrix_transform extension.")
               .def(py::self += float())
               .def(py::self += py::self)
               .def(py::self -= float())
               .def(py::self -= py::self)
               .def(py::self *= float())
               .def(py::self *= py::self)
               .def(py::self /= float())
               .def(py::self /= py::self)
               .def(py::self + float())
               .def(py::self + py::self)
               .def(py::self - float())
               .def(py::self - py::self)
               .def(py::self * float())
               .def(py::self * py::self)
               .def(py::self * glm::vec4())
               .def(py::self / float())
               .def(py::self / py::self)
               .def(py::self / glm::vec4())
               .def(-py::self)
               .def(py::self == py::self)
               .def(py::self != py::self)
               .def(float() + py::self)
               .def(float() - py::self)
               .def(float() * py::self)
               .def(glm::vec4() * py::self)
               .def(float() / py::self)
               .def(glm::vec4() / py::self)
               .def("__getitem__", [](const glm::mat4 &v, int index) { return v[index]; })
               .def("__getitem__", [](const glm::mat4 &v, int row, int col) { return v[col][row]; })
               .def("__setitem__", [](glm::mat4 &v, int index, const glm::vec4 &value) { return v[index] = value; })
               .def("__setitem__", [](glm::mat4 &v, int row, int col, float value) { return v[col][row] = value; });
    mat.doc() = "4 columns of 4 components matrix of single-precision floating-point numbers.";
}
