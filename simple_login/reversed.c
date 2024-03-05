int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4; // [esp+4h] [ebp-3Ch]
  int encoded_input_ptr; // [esp+18h] [ebp-28h] BYREF
  char input[30]; // [esp+1Eh] [ebp-22h] BYREF
  unsigned int length; // [esp+3Ch] [ebp-4h]

  memset(input, 0, sizeof(input));
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stdin, 0, 1, 0);
  printf("Authenticate : ", v4);
  _isoc99_scanf("%30s", input);
  memset(&::input, 0, 0xCu);
  encoded_input_ptr = 0;
  length = Base64Decode((int)input, & );
  if ( length > 0xC )
  {
    puts("Wrong Length");
  }
  else
  {
    memcpy(&::input, encoded_input_ptr, length);
    if ( auth(length) == 1 )
      correct();
  }
  return 0;
}

int __cdecl Base64Decode(int a1, _DWORD *a2)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v7; // [esp+1Ch] [ebp-1Ch]
  int v8; // [esp+20h] [ebp-18h]
  int v9; // [esp+24h] [ebp-14h]
  int v10; // [esp+2Ch] [ebp-Ch]

  v10 = calcDecodeLength(a1);
  *a2 = malloc(v10 + 1);
  v2 = strlen(a1);
  v9 = fmemopen(a1, v2, &unk_80DA64A);
  v3 = BIO_f_base64();
  v8 = BIO_new(v3);
  v4 = BIO_new_fp(v9, 0);
  v7 = BIO_push(v8, v4);
  BIO_set_flags(v7, 256);
  v5 = strlen(a1);
  *(_BYTE *)(*a2 + BIO_read(v7, *a2, v5)) = 0;
  BIO_free_all(v7);
  fclose(v9);
  return v10;
}

_BOOL4 __cdecl auth(int a1)
{
  char v2[8]; // [esp+14h] [ebp-14h] BYREF
  char *s2; // [esp+1Ch] [ebp-Ch]
  int v4; // [esp+20h] [ebp-8h] BYREF

  memcpy(&v4, &input, a1);
  s2 = (char *)calc_md5(v2, 12);
  printf("hash : %s\n", s2);
  return strcmp("f87cd601aa7fedca99018a8be88eda34", s2) == 0;
}

void __noreturn correct()
{
  if ( input == -559038737 )
  {
    puts("Congratulation! you are good!");
    system("/bin/sh");
  }
  exit(0);
}