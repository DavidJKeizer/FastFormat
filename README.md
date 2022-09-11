FastFormat is template-based string formatter to build high-performance, type safe format methods at compile time.


Usage:

	size_t cont bufferSize = 128;
	wchar_t buffer[bufferSize];

	FastFormat::FormatResult result = Format(buffer, bufferSize, 
		L"I am a wide string, and this is an integer: ", 
		32, " 
		and I am a normal string.");

	The contents of buffer will be:
		L"I am a wide string, and this is an integer: 32 and I am a normal string."

	Always check the return result to see if the format succeeded.
	If the return code is negative, it indicates an error occurred. Otherwise it indicates the number of characters written to the buffer, excluding the null terminating character.

	If an error occurs, the first character of the buffer is set to null.



	If a type is not supported by FastFormat, then a compiler error is provided: "Unsupported format parameter type: " with the function signature.

	To extend fast format, in the FastFormat::Impl namespace add a method with the following type signature:

	inline FastFormat::FormatResult FormatParameter(FastFormat::FormatState state&, CustomType value);


Pros:
	Type-safe.			You cannot attempt to format a value that is not supported.
	Ease of use.		You do not need to recall printf style format strings, or manage pointers between format calls.
	Improved security.	Each string conversion is strictly checked to prevent buffer overflow. 
	High performance.	The recursive unrolling of the parameter pack results in a purely inlined function, meaning that the assembly is the same as doing the c calls yourself. You don't pay for what you don't use!
	Single Header.		Just include this header file in your project, and you are good to go!
	Safely extendable.	Define your own FormatParameter methods to safely extend the supported types.

Cons:
	Increased binary size.			Each unique combination of format parameters requires a unique function overload of FastFormat::Format
	Increased compilation time.		Heavy use of templates, and template meta-programming increases compile times. This may not be acceptable for larger projects.
	Added complexity.				C style format strings are well known. There is an inherent learning curve for using a non-standard formatting method.

Open source under standard MIT license - see License.txt for more information.
