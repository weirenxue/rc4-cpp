#include <iostream>
#include <windows.h>
void swap(BYTE*, BYTE*);

int main()
{
	char msg[] = "encrypt me";
	int msgLenByte = strlen(msg);

	char key[] = "By W.R Xue";
	// 1 <= keyLenByte <= 256. It is usually 5 bytes to 16 bytes.
	UINT32 keyLenByte = strlen(key);

	BYTE S[256];
	// This is key stream
	char *K = (char*)malloc(msgLenByte);
	UINT32 i, j, k, t;

	// KSA (the Key-Scheduling Algorithm)
	// Initialize the S array. After that, the key will no longer be used.
	for (i = 0; i < 256; i++) {
		S[i] = i;
	}
	for (i = 0, j = 0; i < 256; i++) {
		j = (j + S[i] + key[i % keyLenByte]) % 256;
		swap(&S[i], &S[j]);
	}

	// PRGA (the Pseudo-Random Generation Algorithm)
	for (i = 0, j = 0, k = 0; k < msgLenByte; k++) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap(&S[i], &S[j]);
		t = (S[i] + S[j]) % 256;
		// Generate key stream
		K[k] = S[t];
		printf("%02X ", (BYTE)(K[k] ^ msg[k]));
	}
}
void swap(BYTE* x, BYTE* y) {
	char tmp = *x;
	*x = *y;
	*y = tmp;
}