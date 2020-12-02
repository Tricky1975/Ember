// Lic:
// Ember
// Turns binary into char*
// 
// 
// 
// (c) Jeroen P. Broks, 2020
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// Please note that some references to data like pictures or audio, do not automatically
// fall under this licenses. Mostly this is noted in the respective files.
// 
// Version: 20.12.02
// EndLic
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

static long int streamsize(FILE *stream){
	long int old = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	long int sz = ftell(stream);
	fseek(stream, old, SEEK_SET);
	return sz;
}


static void Ember(char* filename,char* varname) {
	printf("// Ember from: %s\n",filename);
	FILE * bt = fopen(filename,"rb");
	if (bt==NULL) { printf("// Error opening file\n");  return; }
	int size = streamsize(bt);
	printf("\n\n\nstatic const int %s_SIZE = %10d;\n\n",varname, size);
	printf("static const char %s [%10d] = {\n\t",varname,size);
	for (int i=0;i<size;i++) {
		char c = fgetc(bt);
		if (i) printf(", ");
		if (i%10==0 && i) printf("\n\t");
		if (c>=32 && c<=126 && c!='\\' && c!='\'') 
			printf(" '%c'",c);
		else
			printf("%4d",c);		
	}
	printf("\n};\n\n");
	fclose(bt);
}


int main(int numberofargs,char** args) {
	if (numberofargs<=1) {
		printf("Ember - Coded by Tricky!\n\n");
		printf("Built %s\n\n",__DATE__);
		printf("(c) Jeroen P. Broks, 2020\n\n");
		printf("Usage %s <file> [<idname>]\n\n",args[0]);
		return 0;
	}
	if (numberofargs==2) {
		Ember(args[1],"EMBER");
		return 0;
	}
	Ember(args[1],args[2]);
}
