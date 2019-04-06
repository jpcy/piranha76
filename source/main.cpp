#include <stdio.h>
#include <bx/bx.h>
#include <parser-library/parse.h>

static int iterExportsCallback(void *_userData, peparse::VA _addr, std::string &_moduleName, std::string &_symbolName)
{
	printf("   %s %s %I64u\n", _moduleName.c_str(), _symbolName.c_str(), _addr);
	return 0;
}

static int iterImportsCallback(void *_userData, peparse::VA _addr, const std::string &_moduleName, const std::string &_symbolName)
{
	printf("   %s %s %I64u\n", _moduleName.c_str(), _symbolName.c_str(), _addr);
	return 0;
}

static int iterRelocCallback(void *_userData, peparse::VA _addr, peparse::reloc_type _type)
{
	printf("  %I64u %d\n", _addr, _type); 
	return 0;
}

static int iterSymbolCallback(void *_userData, std::string &_name, uint32_t &_value, int16_t &_sectionNumber, uint16_t &_type, uint8_t &_storageClass, uint8_t &_numberOfAuxSymbols)
{
	printf("   %s: %u\n", _name.c_str(), _value);
	return 0;
}

static int iterSectionsCallback(void *_userData, peparse::VA _secBase, std::string &_name, peparse::image_section_header _header, peparse::bounded_buffer *_data)
{
	printf("   %s: %I64u\n", _name.c_str(), _secBase);
	return 0;
}

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
	peparse::IterExpVA(pe, iterExportsCallback, nullptr);
	printf("Imports:\n");
	peparse::IterImpVAString(pe, iterImportsCallback, nullptr);
	/*printf("Relocations:\n");
	peparse::IterRelocs(pe, iterRelocCallback, nullptr);*/
	printf("Sections:\n");
	peparse::IterSec(pe, iterSectionsCallback, nullptr);
	printf("Symbols:\n");
	peparse::IterSymbols(pe, iterSymbolCallback, nullptr);
	return 0;
}
