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

#pragma once

#include <Eigen/Core>
#include <vector>

#include "open3d/core/Device.h"
#include "open3d/core/Dtype.h"
#include "open3d/core/Tensor.h"
#include "open3d/core/TensorList.h"

namespace open3d {
namespace core {
namespace eigen_converter {

/// Converts a Eigen matrix of shape (M, N) with alignment A and type T to a
/// Tensor.
/// \param matrix A templated Eigen matrix.
/// \return A tensor converted from the eigen matrix.
template <class T, int M, int N, int A>
core::Tensor EigenMatrixToTensor(const Eigen::Matrix<T, M, N, A> &matrix) {
    core::Dtype dtype = core::Dtype::FromType<T>();
    Eigen::Matrix<T, M, N, Eigen::RowMajor> matrix_row_major = matrix;
    return core::Tensor(matrix_row_major.data(), {matrix.rows(), matrix.cols()},
                        dtype);
}

template <typename T>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
TensorToEigenMatrix(const core::Tensor &tensor);

Eigen::Matrix<double, 4, 4, Eigen::RowMajor> TensorToEigenMatrix4d(
        const core::Tensor &tensor);

Eigen::Matrix<float, 4, 4, Eigen::RowMajor> TensorToEigenMatrix4f(
        const core::Tensor &tensor);

Eigen::Matrix<int, 4, 4, Eigen::RowMajor> TensorToEigenMatrix4i(
        const core::Tensor &tensor);

Eigen::Matrix<double, 6, 6, Eigen::RowMajor> TensorToEigenMatrix6d(
        const core::Tensor &tensor);

Eigen::Matrix<float, 6, 6, Eigen::RowMajor> TensorToEigenMatrix6f(
        const core::Tensor &tensor);

Eigen::Matrix<int, 6, 6, Eigen::RowMajor> TensorToEigenMatrix6i(
        const core::Tensor &tensor);

/// Converts a tensor of shape (N, 3) to std::vector<Eigen::Vector3d>. An
/// exception will be thrown if the tensor shape is not (N, 3). Regardless of
/// the tensor dtype, the output will be converted to to double.
///
/// \param tensor A tensor of shape (N, 3).
/// \return A vector of N Eigen::Vector3d values.
std::vector<Eigen::Vector3d> TensorToEigenVector3dVector(
        const core::Tensor &tensor);

/// Converts a tensor of shape (N, 3) to std::vector<Eigen::Vector3i>. An
/// exception will be thrown if the tensor shape is not (N, 3). Regardless of
/// the tensor dtype, the output will be converted to to double.
///
/// \param tensor A tensor of shape (N, 3).
/// \return A vector of N Eigen::Vector3i values.
std::vector<Eigen::Vector3i> TensorToEigenVector3iVector(
        const core::Tensor &tensor);

/// Converts a vector of Eigen::Vector3d to a (N, 3) tensor. This
/// function also takes care of dtype conversion and device transfer if
/// necessary.
///
/// \param values A vector of Eigen::Vector3d values, e.g. a list of 3D points.
/// \param dtype Dtype of the output tensor.
/// \param device Device of the output tensor.
/// \return A tensor of shape (N, 3) with the specified dtype and device.
core::Tensor EigenVector3dVectorToTensor(
        const std::vector<Eigen::Vector3d> &values,
        core::Dtype dtype,
        const core::Device &device);

/// Converts a vector of Eigen::Vector3i to a (N, 3) tensor. This
/// function also takes care of dtype conversion and device transfer if
/// necessary.
///
/// \param values A vector of Eigen::Vector3i values, e.g. a list of 3D points.
/// \param dtype Dtype of the output tensor.
/// \param device Device of the output tensor.
/// \return A tensor of shape (N, 3) with the specified dtype and device.
core::Tensor EigenVector3iVectorToTensor(
        const std::vector<Eigen::Vector3i> &values,
        core::Dtype dtype,
        const core::Device &device);

}  // namespace eigen_converter
}  // namespace core
}  // namespace open3d
