//test.cpp



#include "CryptoKit.h"
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>



using namespace VCF;
using namespace VCF::Crypto;



static void callback(int p, int n, void *arg)
{
	char c='B';
	
	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	//fputc(c,stdout);
	printf( "Generating key, args: p=%d, n=%d...\n",
			p, n );
}

int add_ext(X509 *cert, int nid, char *value)
{
	X509_EXTENSION *ex;
	X509V3_CTX ctx;
	/* This sets the 'context' of the extensions. */
	/* No configuration database */
	X509V3_set_ctx_nodb(&ctx);
	/* Issuer and subject certs: both the target since it is self signed,
	* no request and no CRL
	*/
	X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
	ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (!ex)
		return 0;
	
	X509_add_ext(cert,ex,-1);
	X509_EXTENSION_free(ex);
	return 1;
}

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days)
{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	
	if ((pkeyp == NULL) || (*pkeyp == NULL))
	{
		if ((pk=EVP_PKEY_new()) == NULL)
		{
			abort(); 
			return(0);
		}
	}
	else
		pk= *pkeyp;
	
	if ((x509p == NULL) || (*x509p == NULL))
	{
		if ((x=X509_new()) == NULL)
			goto err;
	}
	else
		x= *x509p;
	
	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
	{
		abort();
		goto err;
	}
	rsa=NULL;
	
	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),0);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);
	
	name=X509_get_subject_name(x);
	
	/* This function creates and adds the entry, working out the
	* correct string type and performing checks on its length.
	* Normally we'd check the return value for errors...
	*/
	X509_NAME_add_entry_by_txt(name,"C",
		MBSTRING_ASC, (const unsigned char*)"UK", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
		MBSTRING_ASC, (const unsigned char*)"The Jimbob-o-rella's", -1, -1, 0);
	
		/* Its self signed so set the issuer name to be the same as the
		* subject.
	*/
	X509_set_issuer_name(x,name);
	
	/* Add various extensions: standard extensions */
	add_ext(x, NID_basic_constraints, "critical,CA:TRUE");
	add_ext(x, NID_key_usage, "critical,keyCertSign,cRLSign");
	
	add_ext(x, NID_subject_key_identifier, "hash");
	
	/* Some Netscape specific extensions */
	add_ext(x, NID_netscape_cert_type, "sslCA");
	
	add_ext(x, NID_netscape_comment, "example comment extension");
	
	
#ifdef CUSTOM_EXT
	/* Maybe even add our own extension based on existing */
	{
		int nid;
		nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
		X509V3_EXT_add_alias(nid, NID_netscape_comment);
		add_ext(x, nid, "example comment alias");
	}
#endif
	
	if (!X509_sign(x,pk,EVP_md5()))
		goto err;
	
	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
	return(0);
}


int my_passwd_cb(char *buf, int size, int rwflag, void *u)
{
	char* passwd = (char*)u;
	
	if ( NULL == passwd ) {
		return 0;
	}

	int passwdLen = strlen(passwd);
	if ( passwdLen <= 0 ) {
		return 0;
	}

	if ( passwdLen > size ) {
		passwdLen = size;
	}
	memcpy( buf, passwd, passwdLen );
	return passwdLen;
}






using namespace VCF;










void testDigests()
{
	MD2 md2;
	MD5 md5;
	VCF::Crypto::SHA1 sha1;
	VCF::Crypto::SHA sha;
	DSS dss;
	DSS1 dss1;
	RipeMD160 rp160;

	char mess1[] = "Test Message";
	char mess2[] = "Hello World\n";

	MessageDigest::DigestResult res = md5.hash( (const unsigned char*)mess1, strlen(mess1) );

	int i = 0;

	printf("md5 Digest is (%d bytes): ", md5.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");


	res = sha1.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("sha1 Digest is (%d bytes): ", sha1.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = sha.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("sha Digest is (%d bytes): ", sha1.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = md2.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("md2 Digest is (%d bytes): ", md2.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = dss.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("dss Digest is (%d bytes): ", dss.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");


	res = dss1.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("dss1 Digest is (%d bytes): ", dss1.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = rp160.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("rp160 Digest is (%d bytes): ", rp160.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");
}

void testRandom()
{
	System::println( Format("Are we seeded OK? %s") % (Random::seeded() ? "yes" : "no") );

	if ( !Random::seeded() ) {
		Random::seed( 209348203 );
		
		System::println( Format("Are we seeded OK? %s") % (Random::seeded() ? "yes" : "no") );
	}

	unsigned int randNum = 0;

	System::println( Format("initial random num: %u") % randNum );

	int ii=0;
	for (ii=0;ii<10;ii++ ) {
		randNum = Random::newInt();
		System::println( Format("random num: %u") % randNum );
	}

	AnsiString s;
	for (ii=0;ii<10;ii++ ) {
		s = Random::newAnsiString();
		System::println( Format( "random num: %.255s") % s.c_str() );
	}
}




void testX509Cert()
{
	X509 *x509=NULL;
	EVP_PKEY *pkey=NULL;
	
	mkcert(&x509,&pkey,512,0,365);
	
	RSA_print_fp(stdout,pkey->pkey.rsa,0);

	printf( "-----------------------------------------------------------------------------\n" );

	X509_print_fp(stdout,x509);
	
	int num = X509_NAME_entry_count( X509_get_issuer_name( x509 ) );
	for ( int j=0;j<num;j++ ) {
		char tmp_buf[256];

		X509_NAME_ENTRY* ne = 
			X509_NAME_get_entry( X509_get_issuer_name( x509 ), j );

		ASN1_OBJECT* obj = X509_NAME_ENTRY_get_object( ne );
		ASN1_STRING* str = X509_NAME_ENTRY_get_data( ne );

		i2t_ASN1_OBJECT(tmp_buf,sizeof(tmp_buf),obj);

		ASN1String s;
		s.assign( str );
		String val = s;
		
	}


	PEM_write_PrivateKey(stdout,pkey,NULL,NULL,0,NULL, NULL);


	PEM_write_PUBKEY(stdout, pkey);


	FILE* cert = fopen( "test509.cer", "wb" );

	PEM_write_X509(stdout,x509);
	PEM_write_X509(cert,x509);
	fclose(cert);

	cert = fopen( "test509-priv.cer", "wb" );
	PEM_write_PrivateKey(cert,pkey,NULL,NULL,0,NULL, NULL);

	fclose(cert);

	
	X509_free(x509);



	X509Certificate c;
	Key k = c.generateRSA(512,0,365,2);
	Key::KeyType t = k.getType();

	FileInputStream fis("test509.cer");
	PEMInputStream pis(&fis);

	X509Certificate* c2 = pis.readCertificate("");

	delete c2;

}

#define PASSWORD	"test"



String gimmeThePassword() 
{
	return String(PASSWORD);
}



void testRSA()
{
	MD5 md5;



	RSAKeyPair kp;
	kp.generate( 512, RSA_F4 );
	String s = kp.toString();




	RSA* rsaKeyPair = RSA_generate_key( 512, RSA_F4, NULL, NULL );

	RSA_print_fp(stdout,rsaKeyPair,0);

	int szOfRSA = RSA_size( rsaKeyPair );

	


	FILE* fp = fopen( "test-pub.pem", "wb" );

	PEM_write_RSAPublicKey(fp,rsaKeyPair);


	fclose(fp);




	fp = fopen( "test-priv.pem", "wb" );
	PEM_write_RSAPrivateKey( fp, rsaKeyPair, EVP_des_ede3_cbc(), NULL, 0, NULL, PASSWORD );
	fclose(fp);


	fp = fopen( "test-priv.pem", "rb" );
	RSA* rsaPriv = NULL;
	if ( !PEM_read_RSAPrivateKey(  fp, &rsaPriv, my_passwd_cb, PASSWORD ) ) {
		unsigned long err = ERR_get_error();
		char tmp[256];
		sprintf( tmp, "Error: %s", ERR_reason_error_string( err ) );
	}
	fclose(fp);

	fp = fopen( "test-pub.pem", "rb" );
	RSA* rsaPub = NULL;
	PEM_read_RSAPublicKey( fp, &rsaPub, NULL, NULL );

	fclose(fp);

	const char* data = "Holy Crap!";




	//sign it
	unsigned char dataDigest[1024];
	size_t dataDigSz = sizeof(dataDigest);
	md5.hash( (const unsigned char*)data, strlen(data), dataDigest, dataDigSz );

	unsigned char signedData[1024];
	size_t signedDataSz = 0;

	int err = RSA_sign( NID_md5, dataDigest, dataDigSz, signedData, &signedDataSz, rsaPriv );



	//verify the message

	md5.hash( (const unsigned char*)data, strlen(data), dataDigest, dataDigSz );

	unsigned char signedData2[1024];
	size_t signedDataSz2 = signedDataSz;

	err = RSA_verify( NID_md5, dataDigest, dataDigSz, signedData, signedDataSz2, rsaPub );



	unsigned char rsaData[1024];
	memset(rsaData, 0, sizeof(rsaData) );


	err = RSA_public_encrypt( strlen(data), (const unsigned char*)data, rsaData, rsaPub, RSA_PKCS1_PADDING );

	printf( "encrypted data (\"%s\", %u bytes) using RSA public key, encrypted data %u bytes.\n",
				data, strlen(data), err );

	//err = RSA_padding_add_PKCS1_type_1( rsaData, sizeof(rsaData), (const unsigned char*)data, strlen(data) );


	unsigned char rsaDecryptedData[1024];
	memset(rsaDecryptedData, 0, sizeof(rsaDecryptedData) );

	err = RSA_private_decrypt( szOfRSA, rsaData, rsaDecryptedData, rsaPriv, RSA_PKCS1_PADDING );

	printf( "decrypted data ( %u bytes) using RSA private key, data ( \"%s\" ) %u bytes.\n",
				err, data, strlen(data) );






	{
		RSAKeyPair kp2;
		kp2.generate( 2048, RSAKeyPair::expRSA_F4 );
		RSAPrivateKey pk = kp2.getPrivateKey();
		RSAPublicKey pubk = kp2.getPublicKey();

		pk.setPassword( PASSWORD );

		DataEncryptionStandard3CBC des3cbc;
		pk.setEncryptionCipher( &des3cbc );


		FileOutputStream fos("test2-priv.pem");
		fos.write( &pk );

		fos.close();

		fos.open( "test2-pub.pem" );
		fos.write( &pubk );
	}

	{
		RSAPrivateKey pk;
		pk.setPassword( PASSWORD );
		FileInputStream fis("test2-priv.pem");
		fis.read( &pk );
	}

	{
		RSAPrivateKey pk;
		pk.PasswordPrompt += gimmeThePassword;
		
		FileInputStream fis("test2-priv.pem");
		fis.read( &pk );

		System::println( "RSAPrivateKey: \n" + pk );
	}

	{
		RSAPublicKey pk;
		
		FileInputStream fis("test2-pub.pem");
		fis.read( &pk );

		System::println( "RSAPublicKey: \n" + pk );
	}
	
}


void testBigNum()
{
	BigInteger bi;
	bi = 1;
	
	BigInteger bi2 = -120;
	int j = bi2;	
	

	bi = 1312;
	bi2 *= bi;

	String bs = bi2.toString();
}


void testBase64()
{
	const char* msg = "Hello world, how are you?";
	char* result = NULL;

	int msgLen = strlen(msg);
	int resultLen = Base64Encoder::safeSizeOf(msgLen);

	result = new char[resultLen+1];
	int ol = 0;
	int tmp = 0;


	Base64Encoder encoder;

	encoder.encode( (const unsigned char*)msg, msgLen, (unsigned char*)result, resultLen+1 );

	encoder.finish( (unsigned char*)result, resultLen+1 );
	
	ol += encoder.size();

	//result[ol-1] = 0;

	System::println( Format("predicted size from %d bytes to b64: %d. Actual: %d") %
		msgLen % Base64Encoder::sizeOf(msgLen) % ol );

	System::println( Format("Base64 encoded \"%s\" into \n\t%s") %
			msg % result );


	Base64Decoder decoder;

	char* decodeResult = new char[resultLen+1];

	memset(decodeResult,0,resultLen+1);

	
	decoder.decode( (const unsigned char*)result, ol, (unsigned char*)decodeResult, resultLen+1	);

	decoder.finish( (unsigned char*)decodeResult, resultLen+1 );

	
	System::println( Format("predicted size from %d bytes to normal : %d. Actual: %d") %
			ol % Base64Decoder::sizeOf(ol) % decoder.size() );

	System::println( Format("Base64 decoded \"%s\" into \n\t\"%s\"") %
			result % decodeResult );

	delete [] result;
	delete [] decodeResult;
}


void testCiphers()
{
	unsigned char key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    unsigned char iv[] = {1,2,3,4,5,6,7,8};

	printf( "Key: " );
	for (int x=0;x<sizeof(key);x++ ) {
		printf( "%X", key[x] );
	}
	printf( "\n" );

	printf( "ivec: " );
	for (int y=0;y<sizeof(iv);y++ ) {
		printf( "%X", iv[y] );
	}
	printf( "\n" );

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit(&ctx, EVP_bf_cbc(), key, iv);

	unsigned char outbuf[1024];
	int outlen = 0;
	int tmplen = 0;
	memset(outbuf,0,sizeof(outbuf) );
	const char* text = "Hello - some text to be encrypted.";

	int err = EVP_EncryptUpdate( &ctx, outbuf, &outlen, (const unsigned char*)text, strlen(text) );
	err = EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen);
	outlen += tmplen;

	printf( "Encrypted \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for (int j=0;j<outlen;j++ ) {
		printf( "%X", outbuf[j] );
	}
	printf( "\n %d bytes\n", outlen );	

	EVP_CIPHER_CTX_cleanup(&ctx);


	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit(&ctx, EVP_bf_cbc(), key, iv);

	unsigned char outbuf2[1024];
	int outlen2 = 0;
	tmplen = 0;
	memset(outbuf2,0,sizeof(outbuf2) );

	err = EVP_DecryptUpdate( &ctx, outbuf2, &outlen2, outbuf, outlen );
	err = EVP_DecryptFinal(&ctx, outbuf2 + outlen2, &tmplen);
	outlen2 += tmplen;


	printf( "Decrypted \n" );
	for (int jj=0;jj<outlen;jj++ ) {
		printf( "%X", outbuf[jj] );
	}

	outbuf2[outlen2] = 0;
	printf( "\n (%d bytes)\n into:\n \"%s\" (%d bytes)\n", outlen, (const char*)outbuf2, outlen2 );



	BlowfishCBC bfCbc;

	memset(outbuf, 0, sizeof(outbuf));
	bfCbc.init( key, sizeof(key), iv, sizeof(iv) );
	bfCbc.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
	bfCbc.finishEncryption( outbuf+bfCbc.getBytesEncrypted(), sizeof(outbuf) );

	printf( "Encrypted \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for (int d=0;d<bfCbc.getBytesEncrypted();d++ ) {
		printf( "%X", outbuf[d] );
	}
	printf( "\n %d bytes\n", bfCbc.getBytesEncrypted() );


	DataEncryptionStandardECB des1;

	memset(outbuf, 0, sizeof(outbuf));
	des1.init( key, sizeof(key), iv, sizeof(iv) );
	des1.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
	des1.finishEncryption( outbuf+des1.getBytesEncrypted(), sizeof(outbuf) );

	printf( "Encrypted \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for ( d=0;d<des1.getBytesEncrypted();d++ ) {
		printf( "%X", outbuf[d] );
	}
	printf( "\n %d bytes\n", des1.getBytesEncrypted() );

	Cast5OFB cast1;

	memset(outbuf, 0, sizeof(outbuf));
	cast1.init( key, sizeof(key), iv, sizeof(iv) );
	cast1.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
	cast1.finishEncryption( outbuf+cast1.getBytesEncrypted(), sizeof(outbuf) );

	printf( "Encrypted using Cast5OFB algo \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for ( d=0;d<cast1.getBytesEncrypted();d++ ) {
		printf( "%X", outbuf[d] );
	}
	printf( "\n %d bytes\n", cast1.getBytesEncrypted() );


	try {
	
		RivestCipher4 rc4;
		//rc4.setKeyLength( sizeof(key) );
		rc4.init( key, sizeof(key), iv, sizeof(iv) );
		
		rc4.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
		rc4.finishEncryption( outbuf+rc4.getBytesEncrypted(), sizeof(outbuf) );
		printf( "Encrypted using RivestCipher4 algo \"%s\" (%d bytes) into:\n", text, strlen(text) );
		for ( d=0;d<rc4.getBytesEncrypted();d++ ) {
			printf( "%X", outbuf[d] );
		}
		printf( "\n %d bytes\n", rc4.getBytesEncrypted() );

		outlen2 = 0;		
		memset(outbuf2,0,sizeof(outbuf2) );

		rc4.decrypt( outbuf, rc4.getBytesEncrypted(), outbuf2, sizeof(outbuf2) );
		rc4.finishDecryption( outbuf2+rc4.getBytesDecrypted(), sizeof(outbuf2) );

		outlen = rc4.getBytesEncrypted();
		printf( "Decrypted \n" );
		for (int jj=0;jj<outlen;jj++ ) {
			printf( "%X", outbuf[jj] );
		}
		
		outbuf2[rc4.getBytesDecrypted()] = 0;
		printf( "\n (%d bytes)\n into:\n \"%s\" (%d bytes)\n", outlen, (const char*)outbuf2, rc4.getBytesDecrypted() );

	}
	catch ( BasicException& e ) {
		System::println( "Error: " + e.getMessage() );
	}

}


void testASN()
{
	 ASN1_INTEGER* i = M_ASN1_INTEGER_new();
	 ASN1_INTEGER_set( i, 100 );

	 long g = ASN1_INTEGER_get( i );

	 

	 TextOutputStream tos;
	 BIOOutputStream bos(&tos);
	 unsigned char tmp2[256];
	 unsigned char* b = tmp2;
	 ASN1_INTEGER_set( i, 50000 );
	 i2d_ASN1_INTEGER( i, &b );

	 memset(tmp2,0,sizeof(tmp2));
	 ASN1_INTEGER_set( i, 5000 );
	 i2d_ASN1_INTEGER( i, &b );

/*
	 BasicInputStream bis(tos.getTextBuffer());

	 ASN1_INTEGER_set( i, 500 );
	 g = ASN1_INTEGER_get( i );


	 BIOInputStream bis2(&bis);
	 char tmp[256];
	 a2i_ASN1_INTEGER( bis2, i, tmp, 256 );
*/
	 g = ASN1_INTEGER_get( i );


	M_ASN1_INTEGER_free( i );

	ASN1_STRING* s ;

	ASN1String ss;
	ss = "Hello there";
	s = ss.detach();

	String s2 = ss;

	ASN1Integer ii;

	tos.seek( 0, stSeekFromStart );

	tos << &ss;

	ss.clear();

	BasicInputStream bis3(tos.getTextBuffer());
	bis3 >> &ss;

	s2 = ss;
}


#pragma comment (lib,"ssleay32d.lib")

void testSSL1()
{
	SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
	SSL * ssl;

	if(! SSL_CTX_load_verify_locations(ctx, NULL, "C:\\cygwin\\usr\\ssl\\certs"))
	{
		/* Handle failed load here */
	}


	BIO* bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio, & ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

	BIO_set_conn_hostname(bio, "sourceforge.net:https" );//sourceforge.net:443");

	if(BIO_do_connect(bio) <= 0)
	{
		ERR_print_errors_fp(stdout);
	}

	int ret = SSL_get_verify_result(ssl); 

	if( ret != X509_V_OK )
	{
		

		int err = SSL_get_error(ssl,ret);

		const char* str = ERR_reason_error_string( err );

		ERR_print_errors_fp(stdout);
	}

	char * request = "GET / HTTP/1.1\x0D\x0AHost: sourceforge.net\x0D\x0A\x43onnection: Close\x0D\x0A\x0D\x0A";
    char r[1024];


	BIO_write(bio, request, strlen(request));


	FILE* out = fopen("out.xml","wb");
	for(;;)
    {
        int p = BIO_read(bio, r, 1023);
        if(p <= 0) break;
        r[p] = 0;
        fprintf( out, "%s", r);
    }
	fclose(out);


	BIO_free_all(bio);
	SSL_CTX_free(ctx);
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	CryptoKit::init( argc, argv );
	

	testSSL1();


/*
	testASN();
	

	testDigests();

	//testRandom();

	testBase64();

	testCiphers();

	testBigNum();
	
	testX509Cert();	

	testRSA();
*/

	CryptoKit::terminate();
	FoundationKit::terminate();
	return 0;
}


