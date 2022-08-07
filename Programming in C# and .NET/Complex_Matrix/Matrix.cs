using System.Text;

namespace Complex_Matrix
{
    public class Matrix<T> : IFormattable where T : IFormattable
    {
        protected static readonly ICalculator<T> Calculator = Calculators.GetInstance<T>();
        public int Height { get; }
        public int Width { get; }
        public T[,] Array { get; }

        protected Matrix(int width)
        {
            Height = width;
            Width = width;
            Array = new T[Width, Width];
        }

        public Matrix(int height, int width)
        {
            Height = height;
            Width = width;
            Array = new T[Height, Width];
        }

        public static Matrix<T> operator +(Matrix<T> a, Matrix<T> b)
        {
            if (a.Width != b.Width || a.Height != b.Height)
                throw new ArgumentException("Matrices must have compatible dimensions");

            var result = new Matrix<T>(a.Height, a.Width);

            for (var i = 0; i < a.Height; i++)
            {
                for (var j = 0; j < a.Width; j++)
                {
                    result[i, j] = Calculator.Add(a[i, j], b[i, j]);
                }
            }

            return result;
        }

        public static Matrix<T> operator *(Matrix<T> a, Matrix<T> b)
        {
            if (a.Width != b.Height) throw new ArgumentException("Matrices must have compatible dimensions");

            var result = new Matrix<T>(a.Height, b.Width);

            for (var i = 0; i < a.Height; i++)
            {
                for (var j = 0; j < b.Width; j++)
                {
                    var temp = Calculator.ReturnDefaultZero();
                    for (var k = 0; k < a.Width; k++)
                    {
                        temp = Calculator.Add(temp, Calculator.Multiply(a[i, k], b[k, j]));
                    }

                    result[i, j] = temp;
                }
            }

            return result;
        }

        public virtual T this[int i, int j]
        {
            get => i >= 0 && i < this.Height && j >= 0 && j < this.Width
                ? this.Array[i, j]
                : throw new ArgumentOutOfRangeException();
            set
            {
                if (i < 0 || i >= this.Height || j < 0 || j >= this.Width)
                    throw new ArgumentOutOfRangeException();
                this.Array[i, j] = value;
            }
        }

        public string ToString(string? format, IFormatProvider? formatProvider)
        {
            var sb = new StringBuilder();

            for (var i = 0; i < Height; i++)
            {
                for (var j = 0; j < Width; j++)
                {
                    sb.Append(Array[i, j].ToString(null, null)).Append(' ');
                }

                sb.Append('\n');
            }

            return sb.ToString();
        }
    }

    public class DiagonalMatrix<T> : Matrix<T> where T : IFormattable
    {
        public DiagonalMatrix(int side) : base(side)
        {

        }

        public bool IsDiagonal()
        {
            for (var i = 0; i < Width; i++)
            {
                for (var j = 0; j < i; j++)
                {
                    if (!Calculator.IsZero(Array[i, j])) return false;
                }

                for (var j = i + 1; j < Width; j++)
                {
                    if (!Calculator.IsZero(Array[i, j])) return false;
                }
            }

            return true;
        }
    }
}