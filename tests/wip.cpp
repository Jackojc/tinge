#include <iostream>

#include <tinge.hpp>



int main() {


	tinge::println("hey", "there");
	tinge::logln("hey", "there");
	tinge::errln("hey", "there");
	tinge::println_em("hey", "there");
	tinge::logln_em("hey", "there");
	tinge::errln_em("hey", "there");
	tinge::println_h("hey", "there");
	tinge::logln_h("hey", "there");
	tinge::errln_h("hey", "there");


	tinge::noticeln("hey", "there");
	tinge::warnln("hey", "there");
	tinge::errorln("hey", "there");
	tinge::successln("hey", "there");
	tinge::noticeln_em("hey", "there");
	tinge::warnln_em("hey", "there");
	tinge::errorln_em("hey", "there");
	tinge::successln_em("hey", "there");
	tinge::noticeln_h("hey", "there");
	tinge::warnln_h("hey", "there");
	tinge::errorln_h("hey", "there");
	tinge::successln_h("hey", "there");

	return 0;
}
