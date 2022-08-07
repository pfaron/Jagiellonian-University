namespace Complex_Matrix
{
    public class Complex<T> : IFormattable where T : IFormattable
    {
        public T Real { get; set; }
        public T Imaginary { get; set; }

        public Complex(T real, T imaginary)
        {
            Real = real;
            Imaginary = imaginary;
        }

        public string ToString(string? format, IFormatProvider? formatProvider)
        {
            return "(" + Real + "+" + Imaginary + "i)";
        }

        public bool IsZero()
        {
            var calculator = Calculators.GetInstance<Complex<T>>();
            return calculator.IsZero(this);
        }

        public static Complex<T> operator +(Complex<T> a, Complex<T> b)
        {
            var calculator = Calculators.GetInstance<Complex<T>>();
            return calculator.Add(a, b);
        }

        public static Complex<T> operator *(Complex<T> a, Complex<T> b)
        {
            var calculator = Calculators.GetInstance<Complex<T>>();
            return calculator.Multiply(a, b);
        }
    }
}