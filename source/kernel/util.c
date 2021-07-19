void memcpy(char *src, char *dst, int n)
{
	int i;
	for(i = 0; i < n; i++) {
		*(dst + i) = *(src + i);
	}
}
