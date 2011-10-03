#include <fstream>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <io.h>
using namespace std;
// compiled with mingw g++

int gamecode=0;

typedef struct {
	FILE		*fp;
	size_t		size;
	unsigned int	mask;
	unsigned char	v;
} bitop_t;

typedef struct {
	int		width;
	int		height;
	int		bpp;
	unsigned long int	data_size;
	char*	data;
}	image_t;

unsigned char get_byte(FILE *fp)
{
	int c;

	if (fp == NULL) return 0;

	c = fgetc(fp);

	if (c == EOF) return 0;

	return (unsigned char)c;
}

void
bitop_init(bitop_t *b, FILE *fp, size_t size)
{
	if (b == NULL) return;
	if (fp == NULL) return;
	if (size == 0) return;

	b->fp = fp;
	b->size = --size;
	b->mask = 0x100;
	b->v = get_byte(fp);
}

int
bitop_get(bitop_t *b)
{

	if (b == NULL) return 0;

	b->mask >>= 1;
	if (b->mask == 0x00) {
		if (b->size == 0) return 0;
		b->size--;
		b->v = get_byte(b->fp);
		b->mask = 0x80;
	}
	return (b->v & b->mask) ? 1 : 0;
}

unsigned int
bitop_getn(bitop_t *b, int n)
{
	unsigned int v;

	if (b == NULL) return 0;
	if (n < 0 || n > 32) return 0;

	for (v = 0; n > 0; n--) {
		v <<= 1;
		if (bitop_get(b))
			v |= 1;
	}
	return v;
}



union longg{
	unsigned long int i;
	char b[4];
};
union shortt{
	unsigned short int i;
	char b[2];
};
void swapendian(union longg *tmp) {
	union longg temparray;
	temparray.b[0] = tmp->b[3];
	temparray.b[1] = tmp->b[2];
	temparray.b[2] = tmp->b[1];
	temparray.b[3] = tmp->b[0];
	tmp->i = temparray.i;
};

void swapbyte(union shortt *tmp) {
	union shortt temparray;
	temparray.b[0] = tmp->b[1];
	temparray.b[1] = tmp->b[0];
	tmp->i = temparray.i;
}

			#define	BIT_GETN(d,n)							\
				if (remain_bit < n) {						\
					if (src >= data + encode_size) {			\
						break;						\
					}							\
					bits = (bits << 8) | *src++;				\
					remain_bit += 8;					\
				}								\
				remain_bit -= n;						\
				d = (bits >> remain_bit) & ((1 << n) - 1);

			#define	BIT_GET8(d)							\
				if (remain_bit < 8) {						\
					if (src >= data + encode_size) {			\
						break;						\
					}							\
					bits = (bits << 8) | *src++;				\
				}								\
				d = (bits >> remain_bit);

			#define	BIT_SET()							\
				if (dest >= tmp_data + tmp_data_size) {				\
					break;							\
				}								\
				*dest++ = ch;

void deltaextract(unsigned long int offs, ifstream& in, char* fname, union longg *delta, union longg *delta2) {
	ofstream outfile;
	const long int bufsize = 100000;
	int fnamelen;
	char buffer[bufsize+1];
	char extendfname[110], pathname[110];
	char ext[4];
	bool nbzflag = false;
	bool bmpflag = false;
	strcpy(extendfname, "arc\\");
	strcat(extendfname, fname);

	// create the directory, if needed
	for (int i = 0; i<strlen(extendfname); i++) {
		if (extendfname[i] == '\\') {
			strncpy(pathname, extendfname, i);
			pathname[i] = 0;
			mkdir(pathname);
		}
	}
	fnamelen = strlen(extendfname);

	memcpy(ext, &extendfname[fnamelen - 3], 3);
	ext[3] = 0;
	for (int i = 0; i < 3; i++) {
		if ((ext[i] > 64) && (ext[i] < 91)) ext[i]+=32;
	}
	if (strcmp(ext, "nbz") == 0) {
		nbzflag = true;
		offs+=4;
		(delta->i)-=4;
	}
	if (strcmp(ext, "bmp") == 0) {
		bmpflag = true;
	}

// if (bmpflag) { // comment this to parse ALL files, not just BMPs
	outfile.open(extendfname, ios::binary);
	in.seekg(offs, ios::beg);
	while (delta->i > bufsize) {
		in.read((char*) &buffer, bufsize);
		outfile.write((char*) &buffer, bufsize);
		(delta->i)-=bufsize;
		cout << ".";
	}
	in.read((char*) &buffer, delta->i);
	outfile.write((char*) &buffer, delta->i);
	outfile.flush();
	outfile.close();
	cout << "." << endl;
//} // comment this to parse ALL files, not just BMPs

	if (nbzflag) {
		cout << "decompressing nbz to wav..." << endl;
		char nbzname[110];
		char commandln[250];
		strcpy(nbzname, extendfname);
		nbzname[fnamelen - 3] = 'w';
		nbzname[fnamelen - 2] = 'a';
		nbzname[fnamelen - 1] = 'v';
		strcpy(commandln, "bzip2 -d -k -q -c ");
		strcat(commandln, extendfname);
		strcat(commandln, " > ");
		strcat(commandln, nbzname);
		system(commandln);
	}
	if (bmpflag) {
		cout << "determining bmp compression... " << extendfname << endl;
		ifstream bmpin;
		bmpin.open(extendfname, ios::binary);
		bmpin.seekg(0, ios::beg);
		bmpin.seekg(0, ios::end);
		int bmpsize = bmpin.tellg();

		bmpin.seekg(0, ios::beg);
		unsigned char *bmpbuf;
		bmpbuf = new unsigned char[bmpsize+1];
		if (bmpbuf == NULL) {
			cout << "out of memory.\n";
			return;
		}
		bmpin.read((char*) bmpbuf, bmpsize);
		bmpin.close();

		if ((bmpbuf[0] == 'B') && (bmpbuf[1] == 'M')) {
			cout << "uncompressed bmp - leaving alone." << endl;
		} else if ((bmpbuf[4] == 'B') && (bmpbuf[5] == 'Z')) {
			cout << "nbz file (bzip2), decompressing." << endl;

			// UNFINISHED
			// strip first 4 bytes and bzip2 it
			// but err... havent run into bzipped bmps yet....

		} else if (((bmpbuf[0] == 0xA1) && (bmpbuf[1] == 0x53))
		      ||   ((bmpbuf[2] == 0xA1) && (bmpbuf[3] == 0x53)) ){
		    cout << "lzss file, decompressing." << endl;

			#define	RINGBUF_SIZE	256
			#define	LEN		17

			unsigned char ringbuf[RINGBUF_SIZE];
			//	unsigned char *top;
			bitop_t b, *bp;
			int flag;
			int offset, count;
			int bufpos;
			int ch;
			int i, d;

			FILE *fp = fopen(extendfname, "rb");
		    if ((bmpbuf[2] == 0xA1) && (bmpbuf[3] == 0x53)) {
				char cdummy;
				cdummy = fgetc(fp);
				cdummy = fgetc(fp);
			}
			size_t encode_size = bmpsize;
			image_t* img;
			img = new image_t;
			memset (img, 0, sizeof(image_t));
			bitop_init(bp = &b, fp, encode_size);
			img->data_size = delta2->i;
			if (img->data_size < encode_size * 4)
					img->data_size = encode_size * 4;
				char* p = img->data = new char[img->data_size];
				if (p == 0) {
					fclose(fp);
					return;
				}
			memset (ringbuf, 0, RINGBUF_SIZE - LEN);
			bufpos = RINGBUF_SIZE - LEN;



			int fchk = 1;
			while (p < img->data + img->data_size) {
				flag = bitop_get(bp);
				if (flag) {
					ch = bitop_getn(bp, 8);
					ringbuf[bufpos++] = ch;
					if (bufpos >= RINGBUF_SIZE)
						bufpos = 0;
					*p++ = ch;
					if (p >= img->data + img->data_size)
						break;
				} else {
					offset = bitop_getn(bp, 8);
					count = bitop_getn(bp, 4) + 2;

					for (i = 0; i < count; i++) {
						d = offset + i;
						if (d >= RINGBUF_SIZE)
							d -= RINGBUF_SIZE;
						ch = ringbuf[d];

						ringbuf[bufpos++] = ch;
						if (bufpos >= RINGBUF_SIZE)
							bufpos = 0;

						*p++ = ch;
						if (p >= img->data + img->data_size)
							break;
					}
				}
			}

			fclose(fp);

			ofstream bmpout;
			bmpout.open(extendfname, ios::binary);
			bmpout.write((char*) img->data, img->data_size);
			bmpout.close();

			delete[] img->data;
			delete img;

		} else {
			cout << "spb file, decompressing." << endl;

			ofstream bmpout;
			bmpout.open(extendfname, ios::binary);

// SPB DECODE

typedef struct object_tag {
	int type;
	int ref_count;
} object_t;

typedef struct palette_tag {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	v;
} palette_t;

typedef struct image_tag {
	object_t	obj;

	unsigned char	*name;

	int		width;
	int		height;
	int		bpp;
	int		has_mask;
	int		has_clarity;

	int		transmode;
	int		transcolor;

	int		clarity;

	unsigned char	*data;
	off_t		data_offset;
	size_t		data_size;

	unsigned char	*mask;
	off_t		mask_offset;
	size_t		mask_size;
	int		mask_bpp;

	palette_t	*palette;
	int		npalette;
} image_t;

unsigned char *data = bmpbuf;
size_t encode_size = bmpsize;
image_t *img;
img = new image_t;

	unsigned char *src, *dest, *tmp_data;
	unsigned char *p, *q;
	size_t tmp_data_size;
	unsigned int bits;
	int nbit, mask, remain_bit;
	int t;
	unsigned char ch;
	int rgb = 2;
	int i, j;
	int padding = 0;

	img->width = (data[0] * 256) + data[1];
	img->height = (data[2] * 256) + data[3];
	padding = (4 - ((img->width * 3) % 4));
	if (padding == 4) padding = 0;

	img->bpp = 8 * 3;

	img->data_size = img->width * img->height * 3;
	cout << dec;
	cout << img->data_size;

	img->data = (unsigned char *)malloc(img->data_size);
	cout << " bytes allocated" << endl;

	tmp_data_size = img->width * img->height;
	tmp_data = (unsigned char *)malloc(tmp_data_size);

	src = &data[4];
	dest = tmp_data;
	bits = 0;
	remain_bit = 0;
	for (rgb = 2; rgb >= 0; rgb--, dest = tmp_data) {
		BIT_GET8(ch);
		BIT_SET();

		while (dest < tmp_data + tmp_data_size) {
			BIT_GETN(nbit, 3);
			if (nbit == 0) {
				BIT_SET();
				BIT_SET();
				BIT_SET();
				BIT_SET();
				continue;
			}

			if (nbit == 7) {
				BIT_GETN(mask, 1);
				mask++;
			} else {
				mask = nbit + 2;
			}

			for (i = 0; i < 4; i++) {
				if (mask == 8) {
					BIT_GET8(ch);
				} else {
					BIT_GETN(t, mask);
					if (t & 1) {
						ch += (t >> 1) + 1;
					} else {
						ch -= (t >> 1);
					}
				}
				BIT_SET();
			}
		}

		p = tmp_data;
		q = img->data + rgb;
		for (j = 0; j < img->height / 2; j++) {
			for (i = 0; i < img->width; i++) {
				*q = *p++;
				q += 3;
			}
			q += img->width * 3;
			for (i = 0; i < img->width; i++) {
				q -= 3;
				*q = *p++;
			}
			q += img->width * 3;
		}
		if (img->height & 1) {
			for (i = 0; i < img->width; i++) {
				*q = *p++;
				q += 3;
			}
		}
	}

	free(tmp_data);

	unsigned char* flipimg;
	flipimg = new unsigned char[img->data_size];
	unsigned long int offset1, offset2, rowsize;
	rowsize = img->width * 3;
	for (int y = 0; y < (img->height); y++) { // go thru the rows
		for (int x = 0; x < (img->width); x++) { // go thru the pixels
			offset1 = (rowsize * y) + (x * 3);
			offset2 = (rowsize * (img->height - y - 1)) + (x * 3);
			flipimg[offset2 + 0] = img->data[offset1 + 2];
			flipimg[offset2 + 1] = img->data[offset1 + 1];
			flipimg[offset2 + 2] = img->data[offset1 + 0];
		}
	}
			const unsigned long int bmpheadersize = 54;
			char bitmapheader[bmpheadersize];

			memset(bitmapheader, 0, bmpheadersize);

			bitmapheader[0] = 'B'; // BMP header
			bitmapheader[1] = 'M';
			unsigned long longi, bmpfilesize;
			unsigned short shorti;
			bmpfilesize = bmpheadersize + ((img->width * img->height) * 3) + (img->height * padding) + 2;
			memcpy(&bitmapheader[2], &bmpfilesize, 4); // FILESIZE
			longi = bmpheadersize;
			memcpy(&bitmapheader[10], &longi, 4); // OFFSET
			longi = 40;
			memcpy(&bitmapheader[14], &longi, 4); // BLOCKSIZE
			longi = (img->width);
			memcpy(&bitmapheader[18], &longi, 4); // WIDTH
			longi = (img->height);
			memcpy(&bitmapheader[22], &longi, 4); // HEIGHT
			shorti = 1;
			memcpy(&bitmapheader[26], &shorti, 2); // FIELDS = 1
			shorti = 24;
			memcpy(&bitmapheader[28], &shorti, 2); // BPP = 24
			shorti = 0;

			bmpout.write((char*) bitmapheader, bmpheadersize);
			unsigned long int dummyzeros = 0;
			for (int y = 0; y < (img->height); y++) {
			  bmpout.write((char*) &flipimg[(img->width * 3) * y], (img->width * 3));
			  bmpout.write((char*) &dummyzeros, padding);
			}
			// bmpout.write((char*) flipimg, ((img->width * img->height) * 3));
			unsigned char shorts[2];
			shorts[0] = 0;
			shorts[1] = 0;
			bmpout.write((char*) shorts, 2);

free(img->data);
delete[] img;
delete[] flipimg;

			bmpout.close();

		}

		delete[] bmpbuf;
	}


}

int main(){

	ifstream infile;
	char filen[20];
	char outfilen[100];
	unsigned long int currentpos;
	union shortt globalobjs;
	union longg globaloffs, outoffset, outfilesize, expandfilesize;
	char dummy[5];

	cout << "nsaout v1.2 by alamone" << endl;

	infile.open("princess_holiday.exe", ios::binary);
    if (infile.fail()) {
	} else {
		infile.close();
		gamecode = 1;
    };
	infile.clear();

	for (int fhandle = 0; fhandle<100; fhandle++) {

		if (fhandle == 0) {
			strcpy(filen, "arc.nsa");
		} else {
			strcpy(filen, "arc");
			if (fhandle < 10) {
				filen[3] = 48 + fhandle;
				filen[4] = '.';
				filen[5] = 'n';
				filen[6] = 's';
				filen[7] = 'a';
				filen[8] = 0;
			} else {
				int j = 0;
				int k = fhandle;
				while(k > 9){
					j++;
					k-= 10;
				}
				filen[3] = 48 + j;
				filen[4] = 48 + k;
				filen[5] = '.';
				filen[6] = 'n';
				filen[7] = 's';
				filen[8] = 'a';
				filen[9] = 0;
			}
		}

		infile.open(filen, ios::binary);
		if (infile.fail()) {
			break;
		}
		cout << "Processing NSA archive: " << filen;


		if (gamecode == 1) infile.read((char *) &globalobjs, 1); // fix for princess holiday
		infile.read((char *) &globalobjs, 2);
		if (gamecode == 0) {
		  if (globalobjs.i == 0) infile.read((char *) &globalobjs, 2); // fix for hanihani
	    }

		infile.read((char *) &globaloffs, 4);
		swapbyte(&globalobjs);
		swapendian(&globaloffs);

		cout << ", 0x" << hex << globalobjs.i << " objects found." << endl;

		for (int obj = 0; obj < globalobjs.i; obj++) {
			infile.getline(outfilen,100, 0);
			infile.read((char *) &dummy, 1);
			infile.read((char *) &outoffset, 4);
			infile.read((char *) &outfilesize, 4);
			infile.read((char *) &expandfilesize, 4);
			swapendian(&outoffset);
			swapendian(&outfilesize);
			swapendian(&expandfilesize);
			currentpos = infile.tellg();

			//comment 2 below
			cout << "Object #" << hex << obj << ": " << outfilen << ", offset 0x" <<
			hex << outoffset.i + globaloffs.i << ", delta 0x" << hex << outfilesize.i << endl;

			deltaextract(outoffset.i + globaloffs.i, infile, outfilen, &outfilesize, &expandfilesize);
			infile.seekg(currentpos, ios::beg);
		}
		infile.close();

	}
	cout << "Finished extracting.";

};
