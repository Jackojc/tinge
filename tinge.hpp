#pragma once


#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>
#include <string>
#include <stdexcept>


// Check current system.
#if defined(__unix__) || defined(__unix) || defined(__linux__) || defined(OS_LINUX)
	#define OS_LINUX
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(OS_WINDOWS)
	#define OS_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__) || defined(OS_MAC)
	#define OS_MAC
#else
	#error Unknown Platform
#endif


// Include platform specific headers.
#if defined(OS_WINDOWS)
	#define WIN32_LEAN_AND_MEAN
	extern "C" {
		#include <windows.h>
	}
#endif


// Exceptions.
#define NEW_EXCEPTION_TYPE(name, default_msg)                                  \
	struct name: public std::runtime_error {                                   \
		template <typename... Ts>                                              \
		name(Ts&&... args): std::runtime_error(((std::string{args}) + ...)) {} \
		name(): std::runtime_error(default_msg) {}                             \
	};                                                                         \

namespace tinge::except {
	NEW_EXCEPTION_TYPE(SetConsoleModeError, "could not set console mode!")
}

#undef NEW_EXCEPTION_TYPE


// Enable ANSI escape sequences on windows.
#if defined(OS_WINDOWS)
namespace tinge::detail {
	struct Init {
		Init() {
			auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (handle != INVALID_HANDLE_VALUE and handle != nullptr) {
				if (DWORD original_mode; GetConsoleMode(handle, &original_mode) == TRUE)
					return SetConsoleMode(handle, original_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
			}

			throw tinge::except::SetConsoleModeError();
		}
	};
}
#endif


// Platform agnostic core implementation.
namespace tinge {

	/*
		todo:
			- disable colours if system does not support ansi escape sequences
			- check if dim bg colours are possible
	*/


	// Colours.
	namespace fg {
		constexpr auto reset   = "\033[39m";
		constexpr auto grey    = "\033[38m";
		constexpr auto gray    = tinge::fg::grey;
		constexpr auto white   = "\033[37m";
		constexpr auto cyan    = "\033[36m";
		constexpr auto magenta = "\033[35m";
		constexpr auto blue    = "\033[34m";
		constexpr auto yellow  = "\033[33m";
		constexpr auto green   = "\033[32m";
		constexpr auto red     = "\033[31m";
		constexpr auto black   = "\033[30m";

		namespace bright {
			constexpr auto reset   = tinge::fg::reset;
			constexpr auto grey    = "\033[98m";
			constexpr auto gray    = tinge::fg::bright::grey;
			constexpr auto white   = "\033[97m";
			constexpr auto cyan    = "\033[96m";
			constexpr auto magenta = "\033[95m";
			constexpr auto blue    = "\033[94m";
			constexpr auto yellow  = "\033[93m";
			constexpr auto green   = "\033[92m";
			constexpr auto red     = "\033[91m";
			constexpr auto black   = "\033[90m";
		}

		namespace dim {
			constexpr auto reset   = tinge::fg::reset;
			constexpr auto grey    = "\033[2;98m";
			constexpr auto gray    = tinge::fg::dim::grey;
			constexpr auto white   = "\033[2;97m";
			constexpr auto cyan    = "\033[2;96m";
			constexpr auto magenta = "\033[2;95m";
			constexpr auto blue    = "\033[2;94m";
			constexpr auto yellow  = "\033[2;93m";
			constexpr auto green   = "\033[2;92m";
			constexpr auto red     = "\033[2;91m";
			constexpr auto black   = "\033[2;90m";
		}
	}


	namespace bg {
		constexpr auto reset   = "\033[49m";
		constexpr auto grey    = "\033[48m";
		constexpr auto gray    = tinge::bg::grey;
		constexpr auto white   = "\033[47m";
		constexpr auto cyan    = "\033[46m";
		constexpr auto magenta = "\033[45m";
		constexpr auto blue    = "\033[44m";
		constexpr auto yellow  = "\033[43m";
		constexpr auto green   = "\033[42m";
		constexpr auto red     = "\033[41m";
		constexpr auto black   = "\033[40m";

		namespace bright {
			constexpr auto reset   = tinge::bg::reset;
			constexpr auto grey    = "\033[108m";
			constexpr auto gray    = tinge::bg::bright::grey;
			constexpr auto white   = "\033[107m";
			constexpr auto cyan    = "\033[106m";
			constexpr auto magenta = "\033[105m";
			constexpr auto blue    = "\033[104m";
			constexpr auto yellow  = "\033[103m";
			constexpr auto green   = "\033[102m";
			constexpr auto red     = "\033[101m";
			constexpr auto black   = "\033[100m";
		}
	}


	// Styles.
	namespace style {
		constexpr auto reset   = "\033[0m";
		constexpr auto bold    = "\033[1m";
		constexpr auto reverse = "\033[7m";
	}


	// Reset colours and style.
	constexpr auto reset         = "\033[0;49;39m";
	constexpr auto reset_colours = "\033[49;39m";
	constexpr auto reset_styles  = "\033[0m";


	// Presets.
	namespace detail {
		// Just used as tags.
		struct Normal  {};
		struct Notice  {};
		struct Warn    {};
		struct Error   {};
		struct Success {};


		std::ostream& operator<<(std::ostream& os, Normal)  { return (os << tinge::reset); };
		std::ostream& operator<<(std::ostream& os, Notice)  { return (os << tinge::style::bold << tinge::fg::white); }
		std::ostream& operator<<(std::ostream& os, Warn)    { return (os << tinge::style::bold << tinge::fg::blue); }
		std::ostream& operator<<(std::ostream& os, Error)   { return (os << tinge::style::bold << tinge::fg::red); }
		std::ostream& operator<<(std::ostream& os, Success) { return (os << tinge::style::bold << tinge::fg::green); }
	}


	namespace style {
		detail::Normal  normal;
		detail::Notice  notice;
		detail::Warn    warn;
		detail::Error   error;
		detail::Success success;
	}
}



// Print functions.
namespace tinge {

	// Print to stdout.
	template <typename... Ts> inline std::ostream& print(Ts&&... args) {
		#ifndef TINGE_PRINT_OFF
			return ((std::cout << tinge::reset) << ... << std::forward<Ts&&>(args)) << tinge::reset;
		#else
			return std::cout;
		#endif
	}


	// Print to whatever clog is.
	template <typename... Ts> inline std::ostream& log(Ts&&... args) {
		#ifndef TINGE_LOG_OFF
			return ((std::clog << tinge::reset) << ... << std::forward<Ts&&>(args)) << tinge::reset;
		#else
			return std::clog;
		#endif
	}


	// Print to stderr.
	template <typename... Ts> inline std::ostream& err(Ts&&... args) {
		#ifndef TINGE_ERR_OFF
			return ((std::cerr << tinge::reset) << ... << std::forward<Ts&&>(args)) << tinge::reset;
		#else
			return std::cerr;
		#endif
	}


	// Symbols for special print functions.
	namespace detail::symbol {
		constexpr auto notice  = "[ ] ";
		constexpr auto warn    = "[*] ";
		constexpr auto error   = "[!] ";
		constexpr auto success = "[^] ";
	}



	// Just output with no fancy formatting.
	#define OUT(name, func) \
		template <typename... Ts> inline std::ostream& name(Ts&&... args) { \
			return tinge::func(tinge::style::name, detail::symbol::name, tinge::reset, std::forward<Ts&&>(args)...); \
		}

	// Same as above but newline appended.
	#define OUTLN(name) \
		template <typename... Ts> inline std::ostream& name##ln(Ts&&... args) { \
			return tinge::name(std::forward<Ts&&>(args)..., '\n'); \
		}

	// Highlight first argument in bold, rest as normal.
	#define OUTEM(name) \
		template <typename T, typename... Ts> inline std::ostream& name##_em(T&& first, Ts&&... args) { \
			return tinge::name(tinge::style::bold, std::forward<T&&>(first), tinge::reset, std::forward<Ts&&>(args)...); \
		}

	// Same as above but newline appended.
	#define OUTEMLN(name) \
		template <typename... Ts> inline std::ostream& name##ln_em(Ts&&... args) { \
			return tinge::name##_em(std::forward<Ts&&>(args)..., '\n'); \
		}

	// Highlight all arguments in bold.
	#define OUTH(name) \
		template <typename... Ts> inline std::ostream& name##_h(Ts&&... args) { \
			return tinge::name(tinge::style::bold, std::forward<Ts&&>(args)...); \
		}

	// Same as above but newline appended.
	#define OUTHLN(name) \
		template <typename... Ts> inline std::ostream& name##ln_h(Ts&&... args) { \
			return tinge::name##_h(std::forward<Ts&&>(args)..., '\n'); \
		}

	// Expand all above macros for particular name.
	#define ALL(name) \
		OUTLN(name) \
		OUTEM(name) \
		OUTEMLN(name) \
		OUTH(name) \
		OUTHLN(name)

	OUT(notice,  log)
	OUT(warn,    log)
	OUT(error,   err)
	OUT(success, print)

	ALL(print)
	ALL(log)
	ALL(err)
	ALL(notice)
	ALL(warn)
	ALL(error)
	ALL(success)
}








