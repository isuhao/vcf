
#include <string>
#include <stdio.h>

using namespace std;

int main( int argc, char** argv )
{
	if ( argc < 3 ) {
		printf( "Please pass in a the source dir and file name !\n" );
		return 1;
	}
	string sourcedir = argv[1];

//
	FILE* f = fopen( argv[2], "rb" );
	if ( NULL != f ) {
		fseek( f, 0, SEEK_END );
		int size = ftell( f );
		fseek( f, 0, SEEK_SET );
		
		char* buf = new char[size+1];
		buf[size] = 0;
		fread( buf, 1, size, f );
		
		string s = buf;
		delete [] buf;
		fclose( f );


		int pos = s.find( "<!-- Generated by Doxygen" );
		int endpos = s.find( "<!--Start of custom footer -->", pos + 1 );
		if ( pos != string::npos ) {
			int hrefpos = pos;
			hrefpos = s.find( "<a", hrefpos + 1 );
			pos = s.find_first_of( ">", hrefpos + 1 );
			while ( (pos != string::npos) && (hrefpos != string::npos) && (hrefpos < endpos) && (pos > hrefpos) ) {
				int refpos = s.find( "href", hrefpos + 1 );
				if ( refpos != string::npos ) {
					refpos = s.find( "=\"", refpos+1 );
					if ( refpos != string::npos ) {
						refpos += 2;

						string tmp = s.substr( refpos, pos - (refpos) );

						s.erase( refpos, pos - refpos );
						
						tmp  = "ref.php?src=" + sourcedir + "/" + tmp;
						s.insert( refpos, tmp );

						pos += tmp.size() - (pos - (refpos));

					}
				}
				
				


				hrefpos = s.find( "<a", pos + 1 );
				pos = s.find_first_of( ">", hrefpos + 1 );
			}			
		}

		
		f = fopen( argv[2], "w+" );
		fwrite( s.c_str(), 1, s.size(), f );
		fclose( f );
	}
	else {
		printf( "Couldn't open file: %s\n", argv[1] );
		return 1;
	}
	return 0;
}
