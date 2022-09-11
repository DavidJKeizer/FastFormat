
#include "CppUnitTest.h"
#include "../FastFormat/FastFormat.h"
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FastFormat;

////In order to directly compare our enum class FormatResult, we need to define a wide string conversion so that the unit test frame work can report an appropriate error message.
////It also must be in the correct namespace in order for the compiler to fine it as an overload.
//namespace Microsoft {
//	namespace VisualStudio {
//		namespace CppUnitTestFramework
//		{
//			template<> inline std::wstring ToString<FormatResult>(const FormatResult& t)
//			{
//				return std::to_wstring(static_cast<int32_t>(t));
//			}
//		}
//	}
//}
//       


namespace UnitTests
{
	TEST_CLASS(Parameters)
	{
	public:
		
		TEST_METHOD(Param_nullptr)
		{
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, nullptr);

			Assert::AreEqual(7, result);
			Assert::AreEqual(L"nullptr", buffer);
		}

		TEST_METHOD(Param_wchar_t_ptr)
		{
			wchar_t const* parameter = L"This is a test.";
			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, parameter);

			Assert::AreEqual(15, result);
			Assert::AreEqual(parameter, buffer);
		}

		TEST_METHOD(Param_uint8_t)
		{
			uint8_t number = 255;
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(3, result);
			Assert::AreEqual(L"255", buffer);
		}



		TEST_METHOD(Param_int8_t)
		{
			int8_t number = 127;
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(3, result);
			Assert::AreEqual(L"127", buffer);
		}

		TEST_METHOD(Param_int16_t)
		{
			int16_t number = -32768;
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(6, result);
			Assert::AreEqual(L"-32768", buffer);
		}

		TEST_METHOD(Param_uint16_t)
		{
			uint16_t number = 65535;
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(5, result);
			Assert::AreEqual(L"65535", buffer);
		}

		TEST_METHOD(Param_int32_t)
		{
			int32_t number = -2147483647;
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(11, result);
			Assert::AreEqual(L"-2147483647", buffer);
		}

		TEST_METHOD(Param_uint32_t)
		{
			uint32_t number = 4294967295;

			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(10, result);
			Assert::AreEqual(L"4294967295", buffer);
		}

		TEST_METHOD(Param_int64_t)
		{
			int64_t number = -9223372036854775807;

			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, number);

			Assert::AreEqual(20, result);
			Assert::AreEqual(L"-9223372036854775807", buffer);
		}

		TEST_METHOD(Param_uint64_t)
		{
			uint64_t number = 18446744073709551615;

			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, number);

			Assert::AreEqual(20, result);
			Assert::AreEqual(L"18446744073709551615", buffer);
		}

		TEST_METHOD(Param_char_t_ptr)
		{
			char const* parameter = "This is a test string.";
			wchar_t buffer[32];

			FormatResult result = Format(buffer, 32, parameter);

			Assert::AreEqual(22, result);
			Assert::AreEqual(L"This is a test string.", buffer);
		}

		TEST_METHOD(Param_wstring)
		{
			std::wstring wideString = L"I am a wide string.";
			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, wideString);

			Assert::AreEqual(19, result);
			Assert::AreEqual(wideString.c_str(), buffer);
		}

		TEST_METHOD(Param_string)
		{
			std::string string = "I am a wide string.";
			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, string);

			Assert::AreEqual(19, result);
			Assert::AreEqual(L"I am a wide string.", buffer);
		}

		TEST_METHOD(Param_float32)
		{
			float number = -0.12345678f;
			wchar_t buffer[16];
			FormatResult result = Format(buffer, 16, number);

			Assert::AreEqual(11, result);
			Assert::AreEqual(L"-0.12345678", buffer);
		}

		TEST_METHOD(Param_double64)
		{
			double number = -0.12345678912345;
			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, number);

			Assert::AreEqual(19, result);
			Assert::AreEqual(L"-0.1234567891234500", buffer);
		}
	};
	
	TEST_CLASS(Utilities)
	{
	public:
		TEST_METHOD(CountDigits_0)
		{
			size_t digits = ::CountRequiredCharacters(0);
			Assert::AreEqual(static_cast<size_t>(1), digits);
		}

		TEST_METHOD(CountDigits_Negatives)
		{
			size_t digits = ::CountRequiredCharacters(-123098);
			Assert::AreEqual(static_cast<size_t>(7), digits);
		}

		TEST_METHOD(CountDigits_LargeNumber)
		{
			constexpr size_t maxValue = std::numeric_limits<size_t>::max();

			size_t expectedLength = std::to_string(maxValue).length();
			size_t actualLength = ::CountRequiredCharacters(maxValue);
			Assert::AreEqual(expectedLength, actualLength);
		}

		TEST_METHOD(CountDigits_NetagiveSingleDigit)
		{
			size_t expectedLength = 2;
			size_t actualLength = ::CountRequiredCharacters(-2);
			Assert::AreEqual(expectedLength, actualLength);
		}

		TEST_METHOD(BadBufferPtr)
		{
			FormatResult result = Format(nullptr, 10, "Some parameter.");
			Assert::AreEqual(FormatErrorCode::kInvalidBufferPointer, result);
		}

		TEST_METHOD(BadBufferSize)
		{
			wchar_t buffer[8];
			FormatResult result = Format(buffer, 0, L"Some other parameter.");
			Assert::AreEqual(FormatErrorCode::kInvalidBufferCapacity, result);
		}

		TEST_METHOD(FormatArrayWrapper)
		{
			int32_t numbers[5] = { 1, 2, 3, 4, 5 };
			wchar_t buffer[32];
			FormatResult result = FormatArray(buffer, 32, numbers, 5);

			Assert::AreEqual(15, result);
			Assert::AreEqual(L"[1, 2, 3, 4, 5]", buffer);
		}
	};

	TEST_CLASS(OutOfSpace)
	{
	public:
		TEST_METHOD(Param_nullptr)
		{
			wchar_t buffer[2];
			FormatResult result = Format(buffer, 2, nullptr);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_wchar_t)
		{
			wchar_t buffer[2];
			FormatResult result = Format(buffer, 2, L"I am a big string!");
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_char_t)
		{
			wchar_t buffer[2];
			FormatResult result = Format(buffer, 2, "I am a big string!");
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_uint8_t)
		{
			wchar_t buffer[2];
			uint8_t number = 123;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_int8_t)
		{
			wchar_t buffer[2];
			int8_t number = -123;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_int16_t)
		{
			wchar_t buffer[2];
			int16_t number = -1236;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_uint16_t)
		{
			wchar_t buffer[2];
			uint16_t number = 65236;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_int32_t)
		{
			wchar_t buffer[2];
			int32_t number = -123685;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_uint32_t)
		{
			wchar_t buffer[2];
			uint32_t number = 165236;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}


		TEST_METHOD(Param_int64_t)
		{
			wchar_t buffer[2];
			int64_t number = -124323685;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_uint64_t)
		{
			wchar_t buffer[2];
			uint64_t number = 165414236;
			FormatResult result = Format(buffer, 2, number);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);
		}

		TEST_METHOD(Param_wstring)
		{
			wchar_t buffer[2];
			std::wstring wideString = L"I am a wide string.";
			FormatResult result = Format(buffer, 2, wideString);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);

		}

		TEST_METHOD(Param_string)
		{
			wchar_t buffer[2];
			std::string wideString = "I am a wide string.";
			FormatResult result = Format(buffer, 2, wideString);
			Assert::AreEqual(FormatErrorCode::kNotEnoughSpace, result);

		}
	};

	TEST_CLASS(CombinedFormats)
	{
	public:
		TEST_METHOD(Combined_wide_int32)
		{
			wchar_t const* pWide = L"This number is: ";
			int32_t testInt = -153;
			
			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, pWide, testInt);

			Assert::AreEqual(20, result);
			Assert::AreEqual(L"This number is: -153", buffer);
		}

		TEST_METHOD(Combined_int32_wide)
		{
			wchar_t const* pWide = L" is the number before.";
			int32_t testInt = -123125;

			wchar_t buffer[32];
			FormatResult result = Format(buffer, 32, testInt, pWide);

			Assert::AreEqual(29, result);
			Assert::AreEqual(L"-123125 is the number before.", buffer);
		}

		TEST_METHOD(ManyTypes)
		{
			wchar_t const* pWide = L"I am a wide string.";
			uint8_t int8 = 4;
			int64_t uint8 = -230512443;

			std::string str = "I am a normal string.";

			wchar_t buffer[64];
			FormatResult result = Format(buffer, 64, pWide, int8, uint8, str);

			Assert::AreEqual(51, result);
			Assert::AreEqual(L"I am a wide string.4-230512443I am a normal string.", buffer);

		}
	};

	TEST_CLASS(Benchmarks)
	{
	public:
		TEST_METHOD(SPRINTF_S)
		{
			wchar_t buffer[1024];

			for (int i = 0; i < 100000; i++)
			{
				FormatResult res = swprintf(buffer, 1024,
					L"I am a long string with lots of things. AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" 
					"%s %f %d %u",
					L"I another long string.",
					0.1523135f,
					-13515,
					1234
				);

				Assert::IsTrue(res > 0);
			}


		}

		TEST_METHOD(FASTFORMAT)
		{
			wchar_t buffer[1024];

			for (int i = 0; i < 100000; i++)
			{
				FormatResult res = FastFormat::Format(buffer, 1024,
					L"I am a long string with lots of things. AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					"%s %f %d %u",
					L"I another long string. ",
					0.1523135f,
					L" ",
					-13515,
					L" ",
					1234
				);

				Assert::IsTrue(res > 0);
			}
		}
	};

}
