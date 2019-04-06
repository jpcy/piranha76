#include <stdio.h>
#include <bx/bx.h>
#include <parser-library/parse.h>

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	printf("%s\n", argv[1]);
	peparse::parsed_pe *pe = peparse::ParsePEFromFile(argv[1]);
	if (!pe) {
		fprintf(stderr, "%s\n", peparse::GetPEErrString().c_str());
		return 1;
	}
	printf("Base address is 0x%x\n", pe->peHeader.nt.OptionalHeader.ImageBase);
	printf("Machine: %s\n", peparse::GetMachineAsString(pe));
	printf("Subsystem: %s\n", peparse::GetSubsystemAsString(pe));
	printf("Exports:\n");
	for (int i = 0; i < (int)pe->exports.size(); i++) {
		const peparse::exportent &exp = pe->exports[i];
		printf("   %s %s %I64u\n", exp.moduleName.c_str(), exp.symbolName.c_str(), exp.addr);
	}
	printf("Imports:\n");
	for (int i = 0; i < (int)pe->imports.size(); i++) {
		const peparse::importent &import = pe->imports[i];
		printf("   %s %s %I64u\n", import.moduleName.c_str(), import.symbolName.c_str(), import.addr);
	}
	printf("Sections:\n");
	for (int i = 0; i < (int)pe->secs.size(); i++) {
		const peparse::section &section = pe->secs[i];
		printf("   %s: %I64u\n", section.sectionName.c_str(), section.sectionBase);
	}
	printf("Symbols:\n");
	for (int i = 0; i < (int)pe->symbols.size(); i++) {
		const peparse::symbol &symbol = pe->symbols[i];
		printf("   %s: %u\n", symbol.strName.c_str(), symbol.value);
	}
	return 0;
}
