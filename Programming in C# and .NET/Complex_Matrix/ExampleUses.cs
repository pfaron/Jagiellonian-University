namespace Complex_Matrix;

public static class ExampleUses
{
    public static void Run()
        {
            Complex<double> t1 = new(2.2, 5.5);
            Complex<double> t2 = new(1.2, 4.2);
            Console.WriteLine(t1);
            Console.WriteLine(t1+t2);
            Console.WriteLine(t1*t2);

            Matrix<int> mat = new Matrix<int>(2, 4);
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    mat.Array[i, j] = i + 2 * j;
                }
            }
            
            Matrix<int> mat2 = new Matrix<int>(2, 4);
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    mat2.Array[i, j] = 6 + 2*i - 2 * j;
                }
            }

            Console.WriteLine(mat);
            Console.WriteLine(mat2);
            Console.WriteLine(mat+mat2);
            
            Matrix<int> mat3 = new Matrix<int>(4, 2);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    mat3.Array[i, j] = 6 + 2*i - 2 * j;
                }
            }
            
            Matrix<int> mat4 = new Matrix<int>(4, 1);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    mat4.Array[i, j] = 6 + 2*i - 2 * j;
                }
            }
            
            Console.WriteLine(mat3);
            Console.WriteLine(mat4);
            Console.WriteLine(mat2 * mat3);
            Console.WriteLine(mat2 * mat4);
            
            
            DiagonalMatrix<int> mat5 = new DiagonalMatrix<int>(4);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    mat5.Array[i, j] = 6 + 2*i - 2 * j;
                }
            }
            
            Console.WriteLine(mat5);
            Console.WriteLine(mat5.IsDiagonal());
            
            DiagonalMatrix<int> mat6 = new DiagonalMatrix<int>(4);
            mat6[0, 0] = 32;
            mat6[1, 1] = 16;
            mat6[2, 2] = 8;
            mat6[3, 3] = 4;
            
            Console.WriteLine(mat6);
            Console.WriteLine(mat6.IsDiagonal());
            
            Console.WriteLine(mat5+mat6);
            Console.WriteLine(mat5*mat6);
            
            
            Matrix<Complex<double>> complexMat1 = new Matrix<Complex<double>>(4, 3);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    complexMat1[i, j] = new Complex<double>(2.4*i, 1.2*j);
                }
            }
            
            Matrix<Complex<double>> complexMat2 = new Matrix<Complex<double>>(3, 2);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    complexMat2[i, j] = new Complex<double>(1.8*i, 0.6*j);
                }
            }
            
            Matrix<Complex<double>> complexMat3 = new Matrix<Complex<double>>(4, 3);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    complexMat3[i, j] = new Complex<double>(1.6*i, j);
                }
            }
            
            Console.WriteLine(complexMat1);
            Console.WriteLine(complexMat2);
            Console.WriteLine(complexMat3);
            Console.WriteLine(complexMat1*complexMat2);
            Console.WriteLine(complexMat1+complexMat3);
            


            DiagonalMatrix<Complex<long>> diagonalComplexMat1 = new DiagonalMatrix<Complex<long>>(3);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    diagonalComplexMat1[i, j] = new Complex<long>(5*i, 3*j);
                }
            }
            
            DiagonalMatrix<Complex<long>> diagonalComplexMat2 = new DiagonalMatrix<Complex<long>>(3);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    diagonalComplexMat2[i, j] = new Complex<long>(4*i, j);
                }
            }
            
            Console.WriteLine(diagonalComplexMat1);
            Console.WriteLine(diagonalComplexMat2);
            Console.WriteLine(diagonalComplexMat1*diagonalComplexMat2);
            Console.WriteLine(diagonalComplexMat1+diagonalComplexMat2);
        }
}