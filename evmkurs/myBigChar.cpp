#include "./includes/libs.h"

int bc_printA(char *str){
        
	printf("\E(0");
	printf("%s\n", str);
	printf("\E(B");
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2){

	cout << "\E[" << y1 <<";" << x1 << "H";
	printf("\E(0l");
	cout << "\E[" << y1 <<";" << x1+1 << "H";
	for(int i = 0; i < x2-1; i++){
		cout << "q";
	}
	
	cout << "\E[" << y1+y2 << ";" << x1 << "H";
	cout << "m";

	cout << "\E[" << y1+y2 << ";" << x1+x2 << "H";
        cout << "j";
        
	cout << "\E[" << y1 << ";" << x1+x2 << "H";
        cout << "k";

	cout << "\E[" << y1+1 << ";" << x1 << "H";
	for(int i = 0; i < y2-1; i++){
		cout << "x";
		cout << "\E[" << y1+2+i << ";" << x1 << "H";
	}

	cout << "\E[" << y1+1 << ";" << x1+x2 << "H";
	for(int i = 0; i < y2-1; i++){
		cout << "x";
		cout << "\E[" << y1+2+i << ";" << x1+x2 << "H";
	}

	cout << "\E[" << y1+y2 <<";" << x1+1 << "H";
	for(int i = 0; i < x2-1; i++){
		cout << "q";
	}	

	cout << "\E(B";
	return 0;
	
}

int bc_printbigchar(long int *a, int x, int y, int simbcolor, int backcolor){

	int f, j = 1, k;
	printf("\E(0");

	cout << "\E[" << y << ";" << x << "H";
	cout << "\E[3" << simbcolor << "m\E[4" << backcolor << "m";
	for(int i = 0, k = 1; i < 32; i++, k++){
		
		f = (a[0] >> (k-1)) & 0x1;
		if(f == 1) printf("a");
		else printf(" ");
		
		if(k%8 == 0){
                        cout << "\E[" << y+j << ";" << x << "H";
                        j++;
                }
	}

	for(int i = 0, k = 1; i < 32; i++, k++){

                f = (a[1] >> (k-1)) & 0x1;
                if(f == 1) printf("a");
                else printf(" ");

		if(k%8 == 0){
                        cout << "\E[" << y+j << ";" << x << "H";
                        j++;
                }

        }

	printf("\E(B");
	return 0;
}


int bc_setbigcharpos(long int *BC, int x, int y, int value){

	if(value < 0) return -1;
	int s, a = 0;
	s = y*8 - 8;
	s+= x;
	if(s > 31){
		s-= 32;
		a = 1;
	}
	if(value == 0){
		BC[a] = BC[a] & (~(1 << (s - 1)));
	}
	else if(value > 0){
		BC[a] = BC[a] | (1 << (s - 1));
	}
	return 0;
}

int bc_getbigcharpos(int ind, int x, int y, long int *value){

	int s, a = 0, place;
	s = y*8 - 8;
	s+= x;
	if(s > 31){
                s-= 32;
                a = 1;
        }
	place = (bigBC[ind][a] >> (s - 1)) & 0x1;
	*value = place;
	return 0;
}

void bc_bigcharwrite(char *file, int *bigChar, int count){
	FILE *bigCharFile = fopen(file,"ab");
	long int temp[2];
		//= nullptr;
	for (int i = 0; i < count; i++){
		temp[0] = bigBC[i][0];
		temp[1] = bigBC[i][1];
		fwrite(&temp[0],sizeof(temp[0]),1,bigCharFile);
		fwrite(&temp[1],sizeof(temp[1]),1,bigCharFile);
	}
	fclose(bigCharFile);
}

void bc_bigcharread(char *file, int *bigChar, int need_count, int *count){
	*count = 0;
	FILE *bigCharFile = fopen(file,"rb");
	long int temp[2];
	for (int i = 0; i < need_count; i++){
		fread(&temp[0], sizeof(int), 1, bigCharFile);
		fread(&temp[1], sizeof(int), 1, bigCharFile);
		bigChar[i] = *temp;
		count++;
	}
	fclose(bigCharFile);
}
