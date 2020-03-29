# Stream IO and File IO

The C language did not build the input/output facilities into the language. In other words, there is no keyword like read or write. Instead, it left the IO to the compiler as external library functions (such as printf and scanf in stdio library). C++ continues formalizes IO in libraries such as iostream and fstream.

So far, we have been using the iostream standard library, which provides cin and cout methods for reading from standard input and writing to standard output respectively.

## Features
* C++ IO is type safe. IO operations are defined for each of the type. If IO operations are not defined for a particular type, compiler will generate an error.
* C++ IO operations are based on streams of bytes and are device independent. The same set of operations can be applied to different types of IO devices (*device independence is the process of making a software application able to function on a wide variety of devices regardless of the local hardware on which the software is used*)

## Stream IO
### Streams

C/C++ IO are based on streams, which are sequence of bytes flowing in and out of the programs (just like water and oil flowing through a pipe). In input operations, data bytes flow from an input source (such as keyboard, file, network or another program) into the program. In output operations, data bytes flow from the program to an output sink (such as console, file, network or another program). Streams acts as an intermediaries between the programs and the actual IO devices, in such the way that frees the programmers from handling the actual devices, so as to archive device independent IO operations.

C++ provides both the formatted and unformatted IO functions. In formatted or high-level IO, bytes are grouped and converted to types such as int, double, string or user-defined types. In unformatted or low-level IO, bytes are treated as raw bytes and unconverted. Formatted IO operations are supported via overloading the stream insertion (<<) and stream extraction (>>) operators, which presents a consistent public IO interface.

**To perform input and output, a C++ program:**

* Construct a stream object.
* Connect (Associate) the stream object to an actual IO device (e.g., keyboard, console, file, network, another program).
* Perform input/output operations on the stream, via the functions defined in the stream's pubic interface in a device independent manner. Some functions convert the data between the external format and internal format (formatted IO); while other does not (unformatted or binary IO).
* Disconnect (Dissociate) the stream to the actual IO device (e.g., close the file).
* Free the stream object.

###  C++ IO Headers, Templates and Classes

* Headers
C++ IO is provided in headers \<iostream\> (which included \<ios\>, \<istream\>, \<ostream\> and \<streambuf\>), \<fstream\> (for file IO), and \<sstream\> (for string IO). Furthermore, the header \<iomanip\> provided manipulators such as setw(), setprecision()setfill() and setbase() for formatting.

* Template Instantiations and typedef

```
typedef basic_ios<char>           ios;
typedef basic_ios<wchar_t>        wios;
typedef basic_istream<char>       istream;
typedef basic_istream<wchar_t>    wistream;
typedef basic_ostream<char>       ostream;
typedef basic_ostream<wchar_t>    wostream;
typedef basic_iostream<char>      iostream;
typedef basic_iostream<wchar_t>   wiostream;
typedef basic_streambuf<char>     streambuf;
typedef basic_streambuf<wchar_t>  wstreambuf;
```

## The <iostream> Header and the Standard Stream Objects: cin, cout, cerr and clog

The \<iostream\> header also included the these headers: \<ios\>, \<istream\>, \<ostream\> and \<streambuf\>. Hence, your program needs to include only the \<iostream\> header for IO operations.

The \<iostream\> header declares these standard stream objects:

* cin (of istream class, basic_istream\<char\> specialization), wcin (of wistream class, basic_istream\<wchar_t\> specialization): corresponding to the standard input stream, defaulted to keyword.
* cout (of ostream class), wcout (of wostream class): corresponding to the standard * output stream, defaulted to the display console.
* cerr (of ostream class), wcerr (of wostream class): corresponding to the standard error stream, defaulted to the display console.
* clog (of ostream class), wclog (of wostream class): corresponding to the standard log stream, defaulted to the display console.

##  The Stream Insertion << and Stream Extraction >> Operators

Formatted output is carried out on streams via the stream insertion << and stream extraction >> operators. For example,
```
cout << value;
cin >> variable;
```

Take note that cin/cout shall be the left operand and the data flow in the direction of the arrows.

**The << and >> operators are overloaded to handle fundamental types (such as int and double), and classes (such as string). You can also overload these operators for your own user-defined types.**

The cin << and cout >> return a reference to cin and cout, and thus, support cascading operations. For example,
```
cout << value1 << value2 << .... ;
cin >> variable1 << variable2 << .... ;
```

## The ostream Class

The ostream class is a typedef to basic_ostream\<char\>. It contains two set of output functions: formatted output and unformatted output.

* The formatted output functions (via overloaded stream insertion operator <<) convert numeric values (such as int, double) from their internal representations (e.g., 16-/32-bit int, 64-bit double) to a stream of characters that representing the numeric values in text form.

* The unformatted output functions (e.g., put(), write()) outputs the bytes as they are, without format conversion.

## Formatting Output via the Overloaded Stream Insertion << Operator

The ostream class overloads the stream insertion << operator for each of the C++ fundamental types (char, unsigned char, signed char, short, unsigned short, int, unsigned int, long, unsigned long, long long (C++11), unsigned long long (C++11), float, double and long double. It converts a numeric value from its internal representation to the text form.

```
ostream & operator<< (type)   // type of int, double etc
```
The << operator returns a reference to the invoking ostream object. Hence, you can concatenate << operations, e.g., cout << 123 << 1.13 << endl;.

The << operator is also overloaded for the following pointer types:

* const char *, const signed char *, const unsigned char *: for outputting C-strings and literals. It uses the terminating null character to decide the end of the char array.
* void *: can be used to print an address.
For example,
```
char str1[] = "apple";
const char * str2 = "orange";

cout << str1 << endl;   // with char *, print C-string
cout << str2 << endl;   // with char *, print C-string
cout << (void *) str1 << endl;  // with void *, print address (regular cast)
cout << static_cast<void *>(str2) << endl;  // with void *, print address
```

#### Flushing the Output Buffer
You can flush the output buffer via:

* flush member function or manipulator:
```
// Member function of ostream class - std::ostream::flush
ostream & flush ();
// Example
cout << "hello";
cout.flush();
 
// Manipulator - std::flush
ostream & flush (ostream & os);
// Example
cout << "hello" << flush;
```

* endl manipulator, which inserts a newline and flush the buffer. Outputting a newline character '\n' may not flush the output buffer; but endl does.
```
// Manipulator - std::endl
ostream & endl (ostream & os)
cin: output buffer is flushed when input is pending, e.g.,
cout << "Enter a number: ";
int number;
cin << number;  // flush output buffer so as to show the prompting message
```

## The istream class

Similar to the ostream class, the istream class is a typedef to basic_istream\<char\>. It also supports formatted input and unformatted input.

* In formatting input, via overloading the >> extraction operator, it converts the text form (a stream of character) into internal representation (such as 16-/32-bit int, 64-byte double).
* In unformatting input, such as get(), getlin(), read(), it reads the characters as they are, without conversion.

### Formatting Input via the Overloaded Stream Extraction >> Operator

The istream class overloads the extraction >> operator for each of the C++ fundamental types (char, unsigned char, signed char, short, unsigned short, int, unsigned int, long, unsigned long, long long (C++11), unsigned long long (C++11), float, double and long double. It performs formatting by converting the input texts into the internal representation of the respective types.

```
istream & operator<< (type &)   // type of int, double etc.
```
The >> operator returns a reference to the invokind istream object. Hence, you can concatenate >> operations, e.g., cin >> number1 << number2 <<....

The >> operator is also overloaded for the following pointer types:

* const char *, const signed char *, const unsigned char *: for inputting C-strings. It uses whitespace as delimiter and adds a terminating null character to the C-string.

*Flushing the Input Buffer - ignore()* : You can use the ignore() to discard characters in the input buffer:

```
istream & ignore (int n = 1, int delim = EOF);
    // Read and discard up to n characters or delim, whichever comes first
 
// Examples
cin.ignore(numeric_limits<streamsize>::max());        // Ignore to the end-of-file
cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore to the end-of-line
```