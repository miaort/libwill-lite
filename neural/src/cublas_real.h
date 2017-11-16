#pragma once
#ifndef _NO_CUDA
#include "cublas_v2.h"
#include "blas_types.h"

//Class of cublas, overload functions with the same name for float and double.
class Cublas : Blas
{
#ifdef NORMAL_BLAS
public:
#endif
#ifdef STATIC_BLAS
private:
#endif
    Cublas() {}
    ~Cublas() { destroy(); }
private:
#ifdef STATIC_BLAS
    static cublasHandle_t handle_ = nullptr;
#else
    cublasHandle_t handle_ = nullptr;
#endif
    BLAS_FUNC cublasOperation_t get_trans(MatrixTransType t)
    { return t == MATRIX_NO_TRANS ? CUBLAS_OP_N : CUBLAS_OP_T; }
    BLAS_FUNC cublasFillMode_t get_uplo(MatrixFillType t)
    { return t == MATRIX_UPPER ? CUBLAS_FILL_MODE_UPPER : CUBLAS_FILL_MODE_LOWER; }
    BLAS_FUNC cublasDiagType_t get_diag(MatrixDiagType t)
    { return t == MATRIX_NON_UNIT ? CUBLAS_DIAG_NON_UNIT : CUBLAS_DIAG_UNIT; }
    BLAS_FUNC cublasSideMode_t get_side(MatrixSideType t)
    { return t == MATRIX_LEFT ? CUBLAS_SIDE_LEFT : CUBLAS_SIDE_RIGHT; }
public:
    BLAS_FUNC cublasStatus_t init()
    { return cublasCreate(&handle_); }
    BLAS_FUNC void destroy()
    { if (handle_) { cublasDestroy(handle_); } }
    BLAS_FUNC void set_handle(cublasHandle_t h) { handle_ = h; }
public:
    BLAS_FUNC float dot(const int N, const float* X, const int incX, const float* Y, const int incY)
    { float r; cublasSdot(handle_, N, X, incX, Y, incY, &r); return r; }
    BLAS_FUNC double dot(const int N, const double* X, const int incX, const double* Y, const int incY)
    { double r; cublasDdot(handle_, N, X, incX, Y, incY, &r); return r; }
    BLAS_FUNC float nrm2(const int N, const float* X, const int incX)
    { float r; cublasSnrm2(handle_, N, X, incX, &r); return r; }
    BLAS_FUNC float asum(const int N, const float* X, const int incX)
    { float r; cublasSasum(handle_, N, X, incX, &r); return r; }
    BLAS_FUNC double nrm2(const int N, const double* X, const int incX)
    { double r; cublasDnrm2(handle_, N, X, incX, &r); return r; }
    BLAS_FUNC double asum(const int N, const double* X, const int incX)
    { double r; cublasDasum(handle_, N, X, incX, &r); return r; }
    BLAS_FUNC int iamax(const int N, const float* X, const int incX)
    { int r; cublasIsamax(handle_, N, X, incX, &r); return r - 1; }
    BLAS_FUNC int iamax(const int N, const double* X, const int incX)
    { int r; cublasIdamax(handle_, N, X, incX, &r); return r - 1; }
    BLAS_FUNC void swap(const int N, float* X, const int incX, float* Y, const int incY)
    { cublasSswap(handle_, N, X, incX, Y, incY); }
    BLAS_FUNC void copy(const int N, const float* X, const int incX, float* Y, const int incY)
    { cublasScopy(handle_, N, X, incX, Y, incY); }
    BLAS_FUNC void axpy(const int N, const float alpha, const float* X, const int incX, float* Y, const int incY)
    { cublasSaxpy(handle_, N, &alpha, X, incX, Y, incY); }
    BLAS_FUNC void swap(const int N, double* X, const int incX, double* Y, const int incY)
    { cublasDswap(handle_, N, X, incX, Y, incY); }
    BLAS_FUNC void copy(const int N, const double* X, const int incX, double* Y, const int incY)
    { cublasDcopy(handle_, N, X, incX, Y, incY); }
    BLAS_FUNC void axpy(const int N, const double alpha, const double* X, const int incX, double* Y, const int incY)
    { cublasDaxpy(handle_, N, &alpha, X, incX, Y, incY); }
    BLAS_FUNC void rotg(float* a, float* b, float* c, float* s)
    { cublasSrotg(handle_, a, b, c, s); }
    BLAS_FUNC void rotmg(float* d1, float* d2, float* b1, const float b2, float* P)
    { cublasSrotmg(handle_, d1, d2, b1, &b2, P); }
    BLAS_FUNC void rot(const int N, float* X, const int incX, float* Y, const int incY, const float c, const float s)
    { cublasSrot(handle_, N, X, incX, Y, incY, &c, &s); }
    BLAS_FUNC void rotm(const int N, float* X, const int incX, float* Y, const int incY, const float* P)
    { cublasSrotm(handle_, N, X, incX, Y, incY, P); }
    BLAS_FUNC void rotg(double* a, double* b, double* c, double* s)
    { cublasDrotg(handle_, a, b, c, s); }
    BLAS_FUNC void rotmg(double* d1, double* d2, double* b1, const double b2, double* P)
    { cublasDrotmg(handle_, d1, d2, b1, &b2, P); }
    BLAS_FUNC void rot(const int N, double* X, const int incX, double* Y, const int incY, const double c, const double s)
    { cublasDrot(handle_, N, X, incX, Y, incY, &c, &s); }
    BLAS_FUNC void rotm(const int N, double* X, const int incX, double* Y, const int incY, const double* P)
    { cublasDrotm(handle_, N, X, incX, Y, incY, P); }
    BLAS_FUNC void scal(const int N, const float alpha, float* X, const int incX)
    { cublasSscal(handle_, N, &alpha, X, incX); }
    BLAS_FUNC void scal(const int N, const double alpha, double* X, const int incX)
    { cublasDscal(handle_, N, &alpha, X, incX); }
    BLAS_FUNC void gemv(const MatrixTransType TransA, const int M, const int N, const float alpha, const float* A, const int lda, const float* X, const int incX, const float beta, float* Y, const int incY)
    { cublasSgemv(handle_, get_trans(TransA), M, N, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void gbmv(const MatrixTransType TransA, const int M, const int N, const int KL, const int KU, const float alpha, const float* A, const int lda, const float* X, const int incX, const float beta, float* Y, const int incY)
    { cublasSgbmv(handle_, get_trans(TransA), M, N, KL, KU, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void trmv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const float* A, const int lda, float* X, const int incX)
    { cublasStrmv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, A, lda, X, incX); }
    BLAS_FUNC void tbmv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const int K, const float* A, const int lda, float* X, const int incX)
    { cublasStbmv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, K, A, lda, X, incX); }
    BLAS_FUNC void tpmv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const float* Ap, float* X, const int incX)
    { cublasStpmv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, Ap, X, incX); }
    BLAS_FUNC void trsv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const float* A, const int lda, float* X, const int incX)
    { cublasStrsv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, A, lda, X, incX); }
    BLAS_FUNC void tbsv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const int K, const float* A, const int lda, float* X, const int incX)
    { cublasStbsv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, K, A, lda, X, incX); }
    BLAS_FUNC void tpsv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const float* Ap, float* X, const int incX)
    { cublasStpsv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, Ap, X, incX); }
    BLAS_FUNC void gemv(const MatrixTransType TransA, const int M, const int N, const double alpha, const double* A, const int lda, const double* X, const int incX, const double beta, double* Y, const int incY)
    { cublasDgemv(handle_, get_trans(TransA), M, N, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void gbmv(const MatrixTransType TransA, const int M, const int N, const int KL, const int KU, const double alpha, const double* A, const int lda, const double* X, const int incX, const double beta, double* Y, const int incY)
    { cublasDgbmv(handle_, get_trans(TransA), M, N, KL, KU, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void trmv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const double* A, const int lda, double* X, const int incX)
    { cublasDtrmv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, A, lda, X, incX); }
    BLAS_FUNC void tbmv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const int K, const double* A, const int lda, double* X, const int incX)
    { cublasDtbmv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, K, A, lda, X, incX); }
    BLAS_FUNC void tpmv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const double* Ap, double* X, const int incX)
    { cublasDtpmv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, Ap, X, incX); }
    BLAS_FUNC void trsv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const double* A, const int lda, double* X, const int incX)
    { cublasDtrsv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, A, lda, X, incX); }
    BLAS_FUNC void tbsv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const int K, const double* A, const int lda, double* X, const int incX)
    { cublasDtbsv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, K, A, lda, X, incX); }
    BLAS_FUNC void tpsv(const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int N, const double* Ap, double* X, const int incX)
    { cublasDtpsv(handle_, get_uplo(Uplo), get_trans(TransA), get_diag(Diag), N, Ap, X, incX); }
    BLAS_FUNC void symv(const MatrixFillType Uplo, const int N, const float alpha, const float* A, const int lda, const float* X, const int incX, const float beta, float* Y, const int incY)
    { cublasSsymv(handle_, get_uplo(Uplo), N, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void sbmv(const MatrixFillType Uplo, const int N, const int K, const float alpha, const float* A, const int lda, const float* X, const int incX, const float beta, float* Y, const int incY)
    { cublasSsbmv(handle_, get_uplo(Uplo), N, K, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void spmv(const MatrixFillType Uplo, const int N, const float alpha, const float* Ap, const float* X, const int incX, const float beta, float* Y, const int incY)
    { cublasSspmv(handle_, get_uplo(Uplo), N, &alpha, Ap, X, incX, &beta, Y, incY); }
    BLAS_FUNC void ger(const int M, const int N, const float alpha, const float* X, const int incX, const float* Y, const int incY, float* A, const int lda)
    { cublasSger(handle_, M, N, &alpha, X, incX, Y, incY, A, lda); }
    BLAS_FUNC void syr(const MatrixFillType Uplo, const int N, const float alpha, const float* X, const int incX, float* A, const int lda)
    { cublasSsyr(handle_, get_uplo(Uplo), N, &alpha, X, incX, A, lda); }
    BLAS_FUNC void spr(const MatrixFillType Uplo, const int N, const float alpha, const float* X, const int incX, float* Ap)
    { cublasSspr(handle_, get_uplo(Uplo), N, &alpha, X, incX, Ap); }
    BLAS_FUNC void syr2(const MatrixFillType Uplo, const int N, const float alpha, const float* X, const int incX, const float* Y, const int incY, float* A, const int lda)
    { cublasSsyr2(handle_, get_uplo(Uplo), N, &alpha, X, incX, Y, incY, A, lda); }
    BLAS_FUNC void spr2(const MatrixFillType Uplo, const int N, const float alpha, const float* X, const int incX, const float* Y, const int incY, float* A)
    { cublasSspr2(handle_, get_uplo(Uplo), N, &alpha, X, incX, Y, incY, A); }
    BLAS_FUNC void symv(const MatrixFillType Uplo, const int N, const double alpha, const double* A, const int lda, const double* X, const int incX, const double beta, double* Y, const int incY)
    { cublasDsymv(handle_, get_uplo(Uplo), N, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void sbmv(const MatrixFillType Uplo, const int N, const int K, const double alpha, const double* A, const int lda, const double* X, const int incX, const double beta, double* Y, const int incY)
    { cublasDsbmv(handle_, get_uplo(Uplo), N, K, &alpha, A, lda, X, incX, &beta, Y, incY); }
    BLAS_FUNC void spmv(const MatrixFillType Uplo, const int N, const double alpha, const double* Ap, const double* X, const int incX, const double beta, double* Y, const int incY)
    { cublasDspmv(handle_, get_uplo(Uplo), N, &alpha, Ap, X, incX, &beta, Y, incY); }
    BLAS_FUNC void ger(const int M, const int N, const double alpha, const double* X, const int incX, const double* Y, const int incY, double* A, const int lda)
    { cublasDger(handle_, M, N, &alpha, X, incX, Y, incY, A, lda); }
    BLAS_FUNC void syr(const MatrixFillType Uplo, const int N, const double alpha, const double* X, const int incX, double* A, const int lda)
    { cublasDsyr(handle_, get_uplo(Uplo), N, &alpha, X, incX, A, lda); }
    BLAS_FUNC void spr(const MatrixFillType Uplo, const int N, const double alpha, const double* X, const int incX, double* Ap)
    { cublasDspr(handle_, get_uplo(Uplo), N, &alpha, X, incX, Ap); }
    BLAS_FUNC void syr2(const MatrixFillType Uplo, const int N, const double alpha, const double* X, const int incX, const double* Y, const int incY, double* A, const int lda)
    { cublasDsyr2(handle_, get_uplo(Uplo), N, &alpha, X, incX, Y, incY, A, lda); }
    BLAS_FUNC void spr2(const MatrixFillType Uplo, const int N, const double alpha, const double* X, const int incX, const double* Y, const int incY, double* A)
    { cublasDspr2(handle_, get_uplo(Uplo), N, &alpha, X, incX, Y, incY, A); }
    BLAS_FUNC void gemm(const MatrixTransType TransA, const MatrixTransType TransB, const int M, const int N, const int K, const float alpha, const float* A, const int lda, const float* B, const int ldb, const float beta, float* C, const int ldc)
    { cublasSgemm(handle_, get_trans(TransA), get_trans(TransB), M, N, K, &alpha, A, lda, B, ldb, &beta, C, ldc); }
    BLAS_FUNC void symm(const MatrixSideType Side, const MatrixFillType Uplo, const int M, const int N, const float alpha, const float* A, const int lda, const float* B, const int ldb, const float beta, float* C, const int ldc)
    { cublasSsymm(handle_, get_side(Side), get_uplo(Uplo), M, N, &alpha, A, lda, B, ldb, &beta, C, ldc); }
    BLAS_FUNC void syrk(const MatrixFillType Uplo, const MatrixTransType Trans, const int N, const int K, const float alpha, const float* A, const int lda, const float beta, float* C, const int ldc)
    { cublasSsyrk(handle_, get_uplo(Uplo), get_trans(Trans), N, K, &alpha, A, lda, &beta, C, ldc); }
    BLAS_FUNC void syr2k(const MatrixFillType Uplo, const MatrixTransType Trans, const int N, const int K, const float alpha, const float* A, const int lda, const float* B, const int ldb, const float beta, float* C, const int ldc)
    { cublasSsyr2k(handle_, get_uplo(Uplo), get_trans(Trans), N, K, &alpha, A, lda, B, ldb, &beta, C, ldc); }
    BLAS_FUNC void trmm(const MatrixSideType Side, const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int M, const int N, const float alpha, const float* A, const int lda, float* B, const int ldb)
    { cublasStrmm(handle_, get_side(Side), get_uplo(Uplo), get_trans(TransA), get_diag(Diag), M, N, &alpha, A, lda, B, ldb, B, ldb); }
    BLAS_FUNC void trsm(const MatrixSideType Side, const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int M, const int N, const float alpha, const float* A, const int lda, float* B, const int ldb)
    { cublasStrsm(handle_, get_side(Side), get_uplo(Uplo), get_trans(TransA), get_diag(Diag), M, N, &alpha, A, lda, B, ldb); }
    BLAS_FUNC void gemm(const MatrixTransType TransA, const MatrixTransType TransB, const int M, const int N, const int K, const double alpha, const double* A, const int lda, const double* B, const int ldb, const double beta, double* C, const int ldc)
    { cublasDgemm(handle_, get_trans(TransA), get_trans(TransB), M, N, K, &alpha, A, lda, B, ldb, &beta, C, ldc); }
    BLAS_FUNC void symm(const MatrixSideType Side, const MatrixFillType Uplo, const int M, const int N, const double alpha, const double* A, const int lda, const double* B, const int ldb, const double beta, double* C, const int ldc)
    { cublasDsymm(handle_, get_side(Side), get_uplo(Uplo), M, N, &alpha, A, lda, B, ldb, &beta, C, ldc); }
    BLAS_FUNC void syrk(const MatrixFillType Uplo, const MatrixTransType Trans, const int N, const int K, const double alpha, const double* A, const int lda, const double beta, double* C, const int ldc)
    { cublasDsyrk(handle_, get_uplo(Uplo), get_trans(Trans), N, K, &alpha, A, lda, &beta, C, ldc); }
    BLAS_FUNC void syr2k(const MatrixFillType Uplo, const MatrixTransType Trans, const int N, const int K, const double alpha, const double* A, const int lda, const double* B, const int ldb, const double beta, double* C, const int ldc)
    { cublasDsyr2k(handle_, get_uplo(Uplo), get_trans(Trans), N, K, &alpha, A, lda, B, ldb, &beta, C, ldc); }
    BLAS_FUNC void trmm(const MatrixSideType Side, const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int M, const int N, const double alpha, const double* A, const int lda, double* B, const int ldb)
    { cublasDtrmm(handle_, get_side(Side), get_uplo(Uplo), get_trans(TransA), get_diag(Diag), M, N, &alpha, A, lda, B, ldb, B, ldb); }
    BLAS_FUNC void trsm(const MatrixSideType Side, const MatrixFillType Uplo, const MatrixTransType TransA, const MatrixDiagType Diag, const int M, const int N, const double alpha, const double* A, const int lda, double* B, const int ldb)
    { cublasDtrsm(handle_, get_side(Side), get_uplo(Uplo), get_trans(TransA), get_diag(Diag), M, N, &alpha, A, lda, B, ldb); }

    //extensions of cublas
    BLAS_FUNC void geam(const MatrixTransType TransA, const MatrixTransType TransB, int m, int n, const float alpha, const float* A, int lda, const float beta, const float* B, int ldb, float* C, int ldc)
    { cublasSgeam(handle_, get_trans(TransA), get_trans(TransB), m, n, &alpha, A, lda, &beta, B, lda, C, ldc); }
    BLAS_FUNC void geam(const MatrixTransType TransA, const MatrixTransType TransB, int m, int n, const double alpha, const double* A, int lda, const double beta, const double* B, int ldb, double* C, int ldc)
    { cublasDgeam(handle_, get_trans(TransA), get_trans(TransB), m, n, &alpha, A, lda, &beta, B, lda, C, ldc); }
    BLAS_FUNC void dgem(MatrixSideType Side, int m, int n, const float* A, int lda, const float* x, int incx, float* C, int ldc)
    { cublasSdgmm(handle_, get_side(Side), m, n, A, lda, x, incx, C, ldc); }
    BLAS_FUNC void dgem(MatrixSideType Side, int m, int n, const double* A, int lda, const double* x, int incx, double* C, int ldc)
    { cublasDdgmm(handle_, get_side(Side), m, n, A, lda, x, incx, C, ldc); }
};

#endif
