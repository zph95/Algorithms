# include<stdio.h>
# include<string.h> 

int group(char ch){
	if(ch == '_')	return 3;
	if(ch - 'i' <= 0)	return 1;
	else if(ch - 'r' <=0)	return 2;
	return 3;
}

void decipher(int g, int k, char* code){
	int array[80],array2[80];
	char backup[81];
	int len = strlen(code);
	int i, j;
	j = 0;
	for(i = 0; i < len; i++)
		if(group(code[i]) == g) array[j++] = i;
	len = j;
	strcpy(backup, code);
	memcpy(array2, array, sizeof(array2));
	for(i = 0;i < len; i++)
	array[i] = array2[(i + k) % len];
	for(i = 0;i < len; i++)
	code[array[i]] = backup[array2[i]];
}

int main(){
	int k1,k2,k3;
	char c[81];
	scanf("%d%d%d", &k1, &k2, &k3);
	while(k1+k2+k3 != 0){
		getchar();
		gets(c);
		decipher(1,k1,c);
		decipher(2, k2, c);
		decipher(3, k3, c);
		printf("%s\n", c);
		scanf("%d%d%d", &k1, &k2, &k3);
	}
	return	0;
}
