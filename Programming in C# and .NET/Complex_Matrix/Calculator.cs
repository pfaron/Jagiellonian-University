namespace Complex_Matrix
{
    public interface ICalculator
    {
    }

    public interface ICalculator<T> : ICalculator
    {
        T Add(T a, T b);
        T Multiply(T a, T b);
        T Subtract(T a, T b);
        bool IsZero(T a);
        T ReturnDefaultZero();
    }

    internal static class Calculators
    {
        private static readonly Dictionary<Type, ICalculator> CalcDict = new()
        {
            {typeof(int), new IntCalculator()},
            {typeof(double), new DoubleCalculator()},
            {typeof(decimal), new DecimalCalculator()},
            {typeof(float), new FloatCalculator()},
            {typeof(long), new LongCalculator()},
            {typeof(short), new ShortCalculator()},
            {typeof(uint), new UIntCalculator()},
            {typeof(ulong), new ULongCalculator()},
            {typeof(ushort), new UShortCalculator()},
            {typeof(Complex<int>), new ComplexCalculator<int>()},
            {typeof(Complex<double>), new ComplexCalculator<double>()},
            {typeof(Complex<decimal>), new ComplexCalculator<decimal>()},
            {typeof(Complex<float>), new ComplexCalculator<float>()},
            {typeof(Complex<long>), new ComplexCalculator<long>()},
            {typeof(Complex<short>), new ComplexCalculator<short>()},
            {typeof(Complex<uint>), new ComplexCalculator<uint>()},
            {typeof(Complex<ulong>), new ComplexCalculator<ulong>()},
            {typeof(Complex<ushort>), new ComplexCalculator<ushort>()}
        };

        public static ICalculator<T> GetInstance<T>()
        {
            return (ICalculator<T>) CalcDict[typeof(T)];
        }
    }

    internal class UShortCalculator : ICalculator<ushort>
    {
        public ushort Add(ushort a, ushort b)
        {
            return (ushort) (a + b);
        }

        public ushort Subtract(ushort a, ushort b)
        {
            return (ushort) (a - b);
        }

        public ushort Multiply(ushort a, ushort b)
        {
            return (ushort) (a * b);
        }

        public bool IsZero(ushort a)
        {
            return a == 0;
        }

        public ushort ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class ULongCalculator : ICalculator<ulong>
    {
        public ulong Add(ulong a, ulong b)
        {
            return a + b;
        }

        public ulong Subtract(ulong a, ulong b)
        {
            return a - b;
        }

        public ulong Multiply(ulong a, ulong b)
        {
            return a * b;
        }

        public bool IsZero(ulong a)
        {
            return a == 0;
        }

        public ulong ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class UIntCalculator : ICalculator<uint>
    {
        public uint Add(uint a, uint b)
        {
            return a + b;
        }

        public uint Subtract(uint a, uint b)
        {
            return a - b;
        }

        public uint Multiply(uint a, uint b)
        {
            return a * b;
        }

        public bool IsZero(uint a)
        {
            return a == 0;
        }

        public uint ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class DecimalCalculator : ICalculator<decimal>
    {
        public decimal Add(decimal a, decimal b)
        {
            return a + b;
        }

        public decimal Subtract(decimal a, decimal b)
        {
            return a - b;
        }

        public decimal Multiply(decimal a, decimal b)
        {
            return a * b;
        }

        public bool IsZero(decimal a)
        {
            return a == 0;
        }

        public decimal ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class FloatCalculator : ICalculator<float>
    {
        public float Add(float a, float b)
        {
            return a + b;
        }

        public float Subtract(float a, float b)
        {
            return a - b;
        }

        public float Multiply(float a, float b)
        {
            return a * b;
        }

        public bool IsZero(float a)
        {
            return a == 0;
        }

        public float ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class LongCalculator : ICalculator<long>
    {
        public long Add(long a, long b)
        {
            return a + b;
        }

        public long Subtract(long a, long b)
        {
            return a - b;
        }

        public long Multiply(long a, long b)
        {
            return a * b;
        }

        public bool IsZero(long a)
        {
            return a == 0;
        }

        public long ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class ShortCalculator : ICalculator<short>
    {
        public short Add(short a, short b)
        {
            return (short) (a + b);
        }

        public short Subtract(short a, short b)
        {
            return (short) (a - b);
        }

        public short Multiply(short a, short b)
        {
            return (short) (a * b);
        }

        public bool IsZero(short a)
        {
            return a == 0;
        }

        public short ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class IntCalculator : ICalculator<int>
    {
        public int Add(int a, int b)
        {
            return a + b;
        }

        public int Subtract(int a, int b)
        {
            return a - b;
        }

        public int Multiply(int a, int b)
        {
            return a * b;
        }

        public bool IsZero(int a)
        {
            return a == 0;
        }

        public int ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class DoubleCalculator : ICalculator<double>
    {
        public double Add(double a, double b)
        {
            return a + b;
        }

        public double Subtract(double a, double b)
        {
            return a - b;
        }

        public double Multiply(double a, double b)
        {
            return a * b;
        }

        public bool IsZero(double a)
        {
            return a == 0;
        }

        public double ReturnDefaultZero()
        {
            return 0;
        }
    }

    internal class ComplexCalculator<T> : ICalculator<Complex<T>> where T : IFormattable
    {

        public Complex<T> Add(Complex<T> a, Complex<T> b)
        {
            var calculator = Calculators.GetInstance<T>();
            return new Complex<T>(calculator.Add(a.Real, b.Real), calculator.Add(a.Imaginary, b.Imaginary));
        }

        public Complex<T> Subtract(Complex<T> a, Complex<T> b)
        {
            var calculator = Calculators.GetInstance<T>();
            return new Complex<T>(calculator.Subtract(a.Real, b.Real), calculator.Subtract(a.Imaginary, b.Imaginary));
        }

        public Complex<T> Multiply(Complex<T> a, Complex<T> b)
        {
            var calculator = Calculators.GetInstance<T>();
            return new Complex<T>(
                calculator.Subtract(calculator.Multiply(a.Real, b.Real), calculator.Multiply(a.Imaginary, b.Imaginary)),
                calculator.Add(calculator.Multiply(a.Imaginary, b.Real), calculator.Multiply(a.Real, b.Imaginary)));
        }

        public bool IsZero(Complex<T> a)
        {
            var calculator = Calculators.GetInstance<T>();
            return calculator.IsZero(a.Real) && calculator.IsZero(a.Imaginary);
        }

        public Complex<T> ReturnDefaultZero()
        {
            var calculator = Calculators.GetInstance<T>();
            return new Complex<T>(calculator.ReturnDefaultZero(), calculator.ReturnDefaultZero());
        }
    }
}