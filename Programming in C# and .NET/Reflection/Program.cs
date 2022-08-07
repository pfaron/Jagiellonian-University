using System.Reflection;

namespace Reflection
{
    internal static class Program
    {
        private static void Main()
        {
            var type = Type.GetType("Reflection.Customer");

            Console.WriteLine("Fields: ");
            
            Console.WriteLine("\n-- Public: \n");
            var publicTypeFields = type.GetFields();
            foreach (var t in publicTypeFields)
            {

                Console.WriteLine($"Attributes: {t.Attributes}");
                Console.WriteLine($"Field name: {t.Name}");
                Console.WriteLine($"Type: {t.FieldType}");
                Console.WriteLine();

            }
            
            Console.WriteLine("\n-- Non Public: \n");
            var nonPublicTypeFields = type.GetFields(BindingFlags.Instance | BindingFlags.NonPublic);
            foreach (var t in nonPublicTypeFields)
            {

                Console.WriteLine($"Attributes: {t.Attributes}");
                Console.WriteLine($"Field name: {t.Name}");
                Console.WriteLine($"Type: {t.FieldType}");
                Console.WriteLine();
                
            }
            
            Console.WriteLine("\nMethods: \n");
            var typeMethods = type.GetMethods(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            foreach (var t in typeMethods)
            {

                Console.WriteLine($"Attributes: {t.Attributes}");
                Console.WriteLine($"Method name: {t.Name}");
                Console.WriteLine($"Return type: {t.ReturnType}");
                Console.WriteLine();

            }
            
            Console.WriteLine("\nNested types: \n");
            var typeNested = type.GetNestedTypes(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            foreach (var t in typeNested)
            {

                Console.WriteLine($"Attributes: {t.Attributes}");
                Console.WriteLine($"Nested type name: {t.Name}");
                Console.WriteLine();

            }
            
            Console.WriteLine("\nProperties: \n");
            var typeProperties = type.GetProperties();
            foreach (var t in typeProperties)
            {
                
                Console.WriteLine($"Property name: {t.Name}");
                Console.WriteLine($"Type: {t.PropertyType}");
                Console.WriteLine($"Has setter: {t.CanWrite}");
                Console.WriteLine($"Has getter: {t.CanRead}");
                Console.WriteLine();

            }

            Console.WriteLine("\nMembers: \n");
            var typeMembers = type.GetMembers();
            foreach (var t in typeMembers)
            {
                Console.WriteLine($"Member name: {t.Name}");
                Console.WriteLine($"Declaring type: {t.DeclaringType}");
                Console.WriteLine($"Module: {t.Module}");
                Console.WriteLine();
            }
            
            
            var customer = Activator.CreateInstance(type, new object[] {"Tadeusz Norek"});
            
            var property = type.GetProperty("Name");
            if (property != null)
            {
                if (property.CanWrite)
                    property.SetValue(customer, "Karol Krawczyk");
                if (property.CanRead)
                    Console.WriteLine(property.GetValue(customer));
            }

            property = type.GetProperty("Address");
            if (property != null)
            {
                if (property.CanWrite)
                    property.SetValue(customer, "Kamienica przy ul. Wolskiej 33");
                if (property.CanRead)
                    Console.WriteLine(property.GetValue(customer));
            }

            property = type.GetProperty("SomeValue");
            if (property != null)
            {
                if (property.CanWrite)
                    property.SetValue(customer, 18);
                if (property.CanRead)
                    Console.WriteLine(property.GetValue(customer));
            }
        }
    }
}