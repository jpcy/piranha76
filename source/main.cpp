#include <stdio.h>
#include <bx/bx.h>
#include "MemoryModule.h"

int main(int /*argc*/, char ** /*argv*/)
{
	const char *filename = "i76.exe";
	FILE *f = fopen(filename, "rb");
	if (!f) {
		fprintf(stderr, "Error opening %s\n", filename);
		return 1;
	}
	fseek(f, 0, SEEK_END);
	auto fileLength = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	auto fileData = new uint8_t[fileLength];
	if (fread(fileData, 1, fileLength, f) != fileLength) {
		delete [] fileData;
		fprintf(stderr, "Error reading %s\n", filename);
		return 1;
	}
	fclose(f);
	HMEMORYMODULE module = MemoryLoadLibrary(fileData, fileLength);
	if (!module) {
		fprintf(stderr, "MemoryLoadLibrary failed\n");
		return 1;
	}
	MemoryCallEntryPoint(module);
	return 0;
}
