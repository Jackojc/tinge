#include <iostream>
// #define TINGE_PLAIN
#include <tinge.hpp>

int main() {
	tinge::println(
		tinge::fg::dim::black,   "black ",
		tinge::fg::dim::grey,    "grey ",
		tinge::fg::dim::red,     "red ",
		tinge::fg::dim::yellow,  "yellow ",
		tinge::fg::dim::green,   "green ",
		tinge::fg::dim::blue,    "blue ",
		tinge::fg::dim::magenta, "magenta ",
		tinge::fg::dim::cyan,    "cyan "
	);

	tinge::println(
		tinge::fg::black,   "black ",
		tinge::fg::grey,    "grey ",
		tinge::fg::red,     "red ",
		tinge::fg::yellow,  "yellow ",
		tinge::fg::green,   "green ",
		tinge::fg::blue,    "blue ",
		tinge::fg::magenta, "magenta ",
		tinge::fg::cyan,    "cyan "
	);

	tinge::println(
		tinge::fg::bright::black,   "black ",
		tinge::fg::bright::grey,    "grey ",
		tinge::fg::bright::red,     "red ",
		tinge::fg::bright::yellow,  "yellow ",
		tinge::fg::bright::green,   "green ",
		tinge::fg::bright::blue,    "blue ",
		tinge::fg::bright::magenta, "magenta ",
		tinge::fg::bright::cyan,    "cyan "
	);

	tinge::println(
		tinge::bg::black,   "black",   tinge::reset, " ",
		tinge::bg::grey,    "grey",    tinge::reset, " ",
		tinge::bg::red,     "red",     tinge::reset, " ",
		tinge::bg::yellow,  "yellow",  tinge::reset, " ",
		tinge::bg::green,   "green",   tinge::reset, " ",
		tinge::bg::blue,    "blue",    tinge::reset, " ",
		tinge::bg::magenta, "magenta", tinge::reset, " ",
		tinge::bg::cyan,    "cyan",    tinge::reset
	);

	tinge::println(
		tinge::bg::bright::black,   "black",   tinge::reset, " ",
		tinge::bg::bright::grey,    "grey",    tinge::reset, " ",
		tinge::bg::bright::red,     "red",     tinge::reset, " ",
		tinge::bg::bright::yellow,  "yellow",  tinge::reset, " ",
		tinge::bg::bright::green,   "green",   tinge::reset, " ",
		tinge::bg::bright::blue,    "blue",    tinge::reset, " ",
		tinge::bg::bright::magenta, "magenta", tinge::reset, " ",
		tinge::bg::bright::cyan,    "cyan",    tinge::reset
	);


	tinge::println();

	tinge::noticeln("a", "b", "c");
	tinge::warnln("a", "b", "c");
	tinge::errorln("a", "b", "c");
	tinge::successln("a", "b", "c");

	tinge::noticeln(tinge::before{tinge::tab(2)}, "a", "b", "c");
	tinge::warnln(tinge::before{tinge::tab(2)}, "a", "b", "c");
	tinge::errorln(tinge::before{tinge::tab(2)}, "a", "b", "c");
	tinge::successln(tinge::before{tinge::tab(2)}, "a", "b", "c");

	auto b = tinge::before{tinge::tab(2)};
	tinge::noticeln(b, "a", "b", "c");
	tinge::warnln(b, "a", "b", "c");
	tinge::errorln(b, "a", "b", "c");
	tinge::successln(b, "a", "b", "c");


	tinge::println(tinge::fg::make_red("hello"));
	tinge::println(tinge::fg::make_blue("hello"));
	tinge::println(tinge::fg::make_yellow("hello"));

	tinge::println(tinge::bg::make_red("hello"));
	tinge::println(tinge::bg::make_blue("hello"));
	tinge::println(tinge::bg::make_yellow("hello"));

	return 0;
}
